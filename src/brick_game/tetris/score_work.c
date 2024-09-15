#include "../../include/tetris.h"

int calculateScore(int lines_dropped) {
  int score = 0;
  switch (lines_dropped) {
    case 1:
      score = 100;
      break;
    case 2:
      score = 300;
      break;
    case 3:
      score = 700;
      break;
    case 4:
      score = 1500;
      break;
    default:
      break;
  }
  return score;
}

void updateScore(GameInfo_t *game, int score) {
  game->score += score;
  if (game->score > game->high_score) {
    game->high_score = game->score;
  }
}

int readHighScore(GameInfo_t *game) {
  int code = GAME_TETRIS_SUCCESS;
  FILE *file = fopen(GAME_TETRIS_HIGH_SCORE_FILE, "r");
  if (file == NULL) {
    code = GAME_TETRIS_FILE_NOT_FOUND;
  } else {
    if (fscanf(file, "%d", &game->high_score) != 1) {
      code = GAME_TETRIS_ERROR_READ;
      game->high_score = 0;
    }
    fclose(file);
  }
  return code;
}

int writeHighScore(GameInfo_t *game, int score) {
  /// открываем файл и считываем предыдущее значение
  int code = readHighScore(game);
  if (code == GAME_TETRIS_FILE_NOT_FOUND) {
    /// если нет файла, то создаем его с рекордом 0
    game->high_score = 0;
  }
  FILE *file = fopen(GAME_TETRIS_HIGH_SCORE_FILE, "w");
  code = GAME_TETRIS_SUCCESS;
  if (game->high_score < score) {
    fprintf(file, "%d", score);
    game->high_score = score;
  } else {
    fprintf(file, "%d", game->high_score);
  }
  fclose(file);
  return code;
}