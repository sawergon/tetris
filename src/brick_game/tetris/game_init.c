#include "../../include/tetris.h"

GameInfo_t *createGame() {
  GameInfo_t *game = getGameState();
  game->field = NULL;
  game->next = NULL;
  game->score = 0;
  game->high_score = 0;
  game->level = 0;
  game->speed = 0;
  game->pause = 0;
  return game;
}

void initGame(GameInfo_t *game) {
  game->field = createMatrix(GAME_TETRIS_FIELD_HEIGHT, GAME_TETRIS_FIELD_WIDTH);
  game->next = NULL;
  game->score = 0;
  game->level = 1;
  game->speed = 500;
  game->pause = false;
  if (readHighScore(game) == GAME_TETRIS_FILE_NOT_FOUND) {
    writeHighScore(game, 0);
  }
}

void destroyGame(GameInfo_t **game) {
  if (game != NULL && *game != NULL) {
    if ((*game)->field != NULL) {
      destroyMatrix(&(*game)->field, GAME_TETRIS_FIELD_HEIGHT);
    }
    if ((*game)->next != NULL) {
      destroyMatrix(&(*game)->next, FIGURE_COORD_SIZE);
    }
    writeHighScore(*game, (*game)->high_score);
    //    free(*game);
    //    *game = NULL;
  }
}
