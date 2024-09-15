#include "../../include/tetris.h"

void pauseGame(GameInfo_t *game) { game->pause = true; }

void unpauseGame(GameInfo_t *game) { game->pause = false; }

GameInfo_t *getGameState() {
  static GameInfo_t game;
  return &game;
}

Hint_t getHint() {
  Hint_t hint = {0};
  FigureInfo_t *figure_info = getFigureInfo();
  int pre_x = figure_info->x;
  int pre_y = figure_info->y;
  Figure_t current_figure = getCurrentFigure();
  dropDown(figure_info);
  int hint_index = 0;
  for (int i = 0; i < FIGURE_COORD_SIZE; i++) {
    for (int j = 0; j < FIGURE_COORD_SIZE; j++) {
      if (current_figure.data[i][j] != 0) {
        hint.data[hint_index][0] = i + figure_info->y;
        hint.data[hint_index][1] = j + figure_info->x;
        hint_index++;
      }
    }
  }
  figure_info->x = pre_x;
  figure_info->y = pre_y;

  return hint;
}

FiniteMachineStatus_t *getMachineStatus() {
  static FiniteMachineStatus_t status;
  return &status;
}

void prepareParams() {
  FigureInfo_t *figure_info = getFigureInfo();
  fillPosArr(figure_info);
  GameInfo_t *game_info = getGameState();
  initGame(game_info);
  FigureType_t type = getRandomFigureType();
  figure_info->next_type = type;
  figure_info->rotate = 0;
  figure_info->clean_field =
      createMatrix(GAME_TETRIS_FIELD_HEIGHT, GAME_TETRIS_FIELD_WIDTH);
  game_info->next = createMatrix(FIGURE_COORD_SIZE, FIGURE_COORD_SIZE);
  moveFigureMatrix(figure_info->positionArr[type][0], game_info->next);
}

void startNewGame() {
  FiniteMachineStatus_t *status = getMachineStatus();
  *status = NewGame;
}

void userInput(UserAction_t action, __attribute__((unused)) bool hold) {
  FiniteMachineStatus_t *status = getMachineStatus();
  if (action == Terminate) {
    if (*status != Paused) {
      *status = SureEndGame;
      GameInfo_t *game_info = getGameState();
      pauseGame(game_info);
    } else {
      *status = EndGame;
    }
  } else if (action == Start && *status == NewGame) {
    prepareParams();
    *status = SpawnFigure;
  } else if (action == Pause || (*status == SureEndGame)) {
    GameInfo_t *game_info = getGameState();
    if (!game_info->pause) {
      pauseGame(game_info);
      *status = Paused;
    } else {
      unpauseGame(game_info);
      *status = Refresh;
    }
  } else if (*status != Paused) {
    FigureInfo_t *figure_info = getFigureInfo();
    if (action == Left) {
      moveLeft(figure_info);
      *status = Refresh;
    } else if (action == Right) {
      moveRight(figure_info);
      *status = Refresh;
    } else if (action == Down) {
      dropDown(figure_info);
      *status = Refresh;
    } else if (action == Action) {
      doRotate(figure_info);
      *status = Refresh;
    }
  }
}

bool canSpawn(FigureInfo_t *figure_info) {
  Figure_t current_figure = getCurrentFigure();
  int **field = figure_info->clean_field;
  bool spawn_result = true;
  int x = figure_info->x;
  int y = figure_info->y;
  for (int i = 0; i < FIGURE_COORD_SIZE && spawn_result; i++) {
    for (int j = 0; j < FIGURE_COORD_SIZE && spawn_result; j++) {
      if (current_figure.data[i][j] != 0) {
        if (field[y + i][x + j] != 0) {
          spawn_result = false;
        }
      }
    }
  }
  return spawn_result;
}

void dropLine(int **field, int line_number) {
  for (int i = line_number; i > 0; i--) {
    for (int j = 0; j < GAME_TETRIS_FIELD_WIDTH; j++) {
      field[i][j] = field[i - 1][j];
    }
  }
  for (int j = 0; j < GAME_TETRIS_FIELD_WIDTH; j++) {
    field[0][j] = 0;
  }
}

bool isFullLine(int **field, int line_number) {
  bool is_full = true;
  for (int j = 0; j < GAME_TETRIS_FIELD_WIDTH && is_full; j++) {
    if (field[line_number][j] == 0) {
      is_full = false;
    }
  }
  return is_full;
}

void cleanLines(int **field, GameInfo_t *game_info) {
  int amount_of_lines = 0;
  for (int i = 0; i < GAME_TETRIS_FIELD_HEIGHT; i++) {
    if (isFullLine(field, i)) {
      amount_of_lines++;
      dropLine(field, i);
    }
  }
  if (amount_of_lines > 0) {
    int total_score = calculateScore(amount_of_lines);
    updateScore(game_info, total_score);
  }
}

void updateLevel(GameInfo_t *game_info) {
  int new_level = (int)(game_info->score / 600);
  if (game_info->level < 10 && new_level > game_info->level - 1) {
    game_info->level++;
    game_info->speed -= 25;
  }
}

void cleanParams() {
  GameInfo_t *game_info = getGameState();
  FigureInfo_t *figure_info = getFigureInfo();
  destroyMatrix(&(figure_info->clean_field), GAME_TETRIS_FIELD_HEIGHT);
  destroyGame(&game_info);
}

GameInfo_t updateCurrentState() {
  GameInfo_t *game_info = getGameState();
  FiniteMachineStatus_t *status = getMachineStatus();
  FigureInfo_t *figure_info = getFigureInfo();

  if (*status == SpawnFigure) {
    figure_info->x = 3;
    figure_info->y = 0;
    figure_info->rotate = 0;
    moveMatrix(game_info->field, figure_info->clean_field,
               GAME_TETRIS_FIELD_HEIGHT, GAME_TETRIS_FIELD_WIDTH);
    FigureType_t new_type = getRandomFigureType();
    figure_info->type = figure_info->next_type;
    figure_info->next_type = new_type;
    moveFigureMatrix(figure_info->positionArr[new_type][0], game_info->next);
    if (canSpawn(figure_info)) {
      *status = Refresh;
    } else {
      *status = EndGame;
      cleanParams();
    }
  }

  if (*status == Refresh) {
    if (canMovingDown(figure_info)) {
      moveDown(figure_info);
    } else {
      *status = SpawnFigure;
    }
    int scores = game_info->score;
    cleanLines(figure_info->clean_field, game_info);
    if (scores != game_info->score) {
      updateLevel(game_info);
    }
    moveMatrix(figure_info->clean_field, game_info->field,
               GAME_TETRIS_FIELD_HEIGHT, GAME_TETRIS_FIELD_WIDTH);

    placeFigure(figure_info, game_info);
  }

  return *game_info;
}