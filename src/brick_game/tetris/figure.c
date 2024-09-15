#include "../../include/tetris.h"
#include "time.h"

FigureInfo_t *getFigureInfo() {
  static FigureInfo_t figure;
  return &figure;
}

Figure_t getCurrentFigure() {
  FigureInfo_t *figure = getFigureInfo();
  return figure->positionArr[figure->type][figure->rotate];
}

Figure_t getNextFigureRotate() {
  FigureInfo_t *figure = getFigureInfo();
  return figure->positionArr[figure->type][(figure->rotate + 1) & 3];
}

int genRandomNumber() {
  FILE *fp = fopen("/dev/urandom", "rb");
  if (fp == NULL) {
    perror("fopen");
    return 1;
  }

  uint32_t seed;
  size_t bytes_read = fread(&seed, sizeof(seed), 1, fp);
  if (bytes_read != 1) {
    perror("fread");
    fclose(fp);
    return 1;
  }
  fclose(fp);

  srand(seed);
  return rand();
}

FigureType_t getRandomFigureType() { return genRandomNumber() % 7; }

void fillPosArr(FigureInfo_t *figure) {
  int tmp_figures[7][4][4][4] = {
      {{{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
       {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}},
       {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
       {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}}},
      {{{0, 2, 2, 0}, {0, 2, 2, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
       {{0, 2, 2, 0}, {0, 2, 2, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
       {{0, 2, 2, 0}, {0, 2, 2, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
       {{0, 2, 2, 0}, {0, 2, 2, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}},
      {{{0, 0, 3, 0}, {0, 3, 3, 3}, {0, 0, 0, 0}, {0, 0, 0, 0}},
       {{0, 0, 3, 0}, {0, 0, 3, 3}, {0, 0, 3, 0}, {0, 0, 0, 0}},
       {{0, 3, 3, 3}, {0, 0, 3, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
       {{0, 0, 3, 0}, {0, 3, 3, 0}, {0, 0, 3, 0}, {0, 0, 0, 0}}},
      {{{0, 4, 0, 0}, {0, 4, 4, 4}, {0, 0, 0, 0}, {0, 0, 0, 0}},
       {{0, 4, 4, 0}, {0, 4, 0, 0}, {0, 4, 0, 0}, {0, 0, 0, 0}},
       {{0, 4, 4, 4}, {0, 0, 0, 4}, {0, 0, 0, 0}, {0, 0, 0, 0}},
       {{0, 0, 4, 0}, {0, 0, 4, 0}, {0, 4, 4, 0}, {0, 0, 0, 0}}},
      {{{0, 0, 0, 5}, {0, 5, 5, 5}, {0, 0, 0, 0}, {0, 0, 0, 0}},
       {{0, 5, 0, 0}, {0, 5, 0, 0}, {0, 5, 5, 0}, {0, 0, 0, 0}},
       {{0, 5, 5, 5}, {0, 5, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
       {{0, 5, 5, 0}, {0, 0, 5, 0}, {0, 0, 5, 0}, {0, 0, 0, 0}}},
      {{{0, 0, 6, 6}, {0, 6, 6, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
       {{0, 6, 0, 0}, {0, 6, 6, 0}, {0, 0, 6, 0}, {0, 0, 0, 0}},
       {{0, 0, 6, 6}, {0, 6, 6, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
       {{0, 6, 0, 0}, {0, 6, 6, 0}, {0, 0, 6, 0}, {0, 0, 0, 0}}},
      {{{0, 7, 7, 0}, {0, 0, 7, 7}, {0, 0, 0, 0}, {0, 0, 0, 0}},
       {{0, 0, 7, 0}, {0, 7, 7, 0}, {0, 7, 0, 0}, {0, 0, 0, 0}},
       {{0, 7, 7, 0}, {0, 0, 7, 7}, {0, 0, 0, 0}, {0, 0, 0, 0}},
       {{0, 0, 7, 0}, {0, 7, 7, 0}, {0, 7, 0, 0}, {0, 0, 0, 0}}}};
  for (size_t i = 0; i < AMOUNT_OF_FIGURES; i++) {
    for (size_t j = 0; j < ROTATE_DIRECTIONS; j++) {
      Figure_t a;
      for (size_t k = 0; k < FIGURE_COORD_SIZE; k++) {
        for (size_t n = 0; n < FIGURE_COORD_SIZE; n++) {
          a.data[k][n] = tmp_figures[i][j][k][n];
        }
      }
      figure->positionArr[i][j] = a;
    }
  }
}

void placeFigure(FigureInfo_t *figure, GameInfo_t *game) {
  for (int i = 0; i < FIGURE_COORD_SIZE; i++) {
    for (int j = 0; j < FIGURE_COORD_SIZE; j++) {
      int figureData =
          (figure->positionArr[figure->type][figure->rotate]).data[i][j];
      if (figureData != 0) {
        game->field[figure->y + i][figure->x + j] = figureData;
      }
    }
  }
}

/**
 * Возващает координату левой границы фигуры
 * @details
 * поскольку фигуры разные и могут быть по разному повернута, а в массиве фигур
 * хочется хранить все фигуры и все их развороты. То приходиться задействовать
 * поле 4х4 для хранения информации о фигурах. Но возникает ситуация, когда с
 * лева получаются пустые квадраты. В таком случае надо вычислить левую границу
 * фигуры, для определения ее реальной координаты.
 * @param figure фигура
 * @return координата левой границы, в координатах фигуры
 */
int getLeftFigureBorder(Figure_t figure) {
  int left_border = 0;
  bool is_border = false;
  for (int j = 0; j < FIGURE_COORD_SIZE && !is_border; j++) {
    for (int i = 0; i < FIGURE_COORD_SIZE && !is_border; i++) {
      if (figure.data[i][j] != 0) {
        left_border = j;
        is_border = true;
      }
    }
  }
  return left_border;
}

/**
 * Получает координату правой границы фигуры
 * @param figure
 * @return
 */
int getRightFigureBorder(Figure_t figure) {
  int right_border = FIGURE_COORD_SIZE - 1;
  bool is_border = false;
  for (int j = FIGURE_COORD_SIZE - 1; j >= 0 && !is_border; j--) {
    for (int i = FIGURE_COORD_SIZE - 1; i >= 0 && !is_border; i--) {
      if (figure.data[i][j] != 0) {
        right_border = j;
        is_border = true;
      }
    }
  }
  return right_border;
}

/**
 * Получает координату нижней границы фигуры
 * @param figure
 * @return
 */
int getBottomFigureBorder(Figure_t figure) {
  int bottom_border = FIGURE_COORD_SIZE - 1;
  bool is_border = false;
  for (int i = FIGURE_COORD_SIZE - 1; i >= 0 && !is_border; i--) {
    for (int j = 0; j < FIGURE_COORD_SIZE && !is_border; j++) {
      if (figure.data[i][j] != 0) {
        bottom_border = i;
        is_border = true;
      }
    }
  }
  return bottom_border;
}

bool canMovingLeft(FigureInfo_t *figure_info) {
  Figure_t current_figure = getCurrentFigure();
  int **field = figure_info->clean_field;
  bool moving_result = true;
  int x = figure_info->x;
  int y = figure_info->y;
  // если фигура уже на левой границе, то нельзя двигаться влево
  if (x + getLeftFigureBorder(current_figure) < 1) {
    moving_result = false;
  } else {
    for (int i = 0; i < FIGURE_COORD_SIZE && moving_result; i++) {
      for (int j = 0; j < FIGURE_COORD_SIZE && moving_result; j++) {
        if (current_figure.data[i][j] != 0) {
          if (field[y + i][x + j - 1] != 0) {
            moving_result = false;
          }
        }
      }
    }
  }
  return moving_result;
}

bool canMovingRight(FigureInfo_t *figure_info) {
  Figure_t current_figure = getCurrentFigure();
  int **field = figure_info->clean_field;
  bool moving_result = true;
  int x = figure_info->x;
  int y = figure_info->y;
  // если фигура уже на правой границе, то нельзя двигаться вправо
  if (x + getRightFigureBorder(current_figure) >= GAME_TETRIS_FIELD_WIDTH - 1) {
    moving_result = false;
  } else {
    for (int i = 0; i < FIGURE_COORD_SIZE && moving_result; i++) {
      for (int j = 0; j < FIGURE_COORD_SIZE && moving_result; j++) {
        if (current_figure.data[i][j] != 0) {
          if (field[y + i][x + j + 1] != 0) {
            moving_result = false;
          }
        }
      }
    }
  }
  return moving_result;
}

bool canMovingDown(FigureInfo_t *figure_info) {
  Figure_t current_figure = getCurrentFigure();
  int **field = figure_info->clean_field;
  bool moving_result = true;
  int x = figure_info->x;
  int y = figure_info->y;
  // если фигура уже на нижней границе, то нельзя двигаться вниз
  if (y + getBottomFigureBorder(current_figure) >
      GAME_TETRIS_FIELD_HEIGHT - 2) {
    moving_result = false;
  } else {
    for (int i = 0; i < FIGURE_COORD_SIZE && moving_result; i++) {
      for (int j = 0; j < FIGURE_COORD_SIZE && moving_result; j++) {
        if (current_figure.data[i][j] != 0) {
          if (field[y + i + 1][x + j] != 0) {
            moving_result = false;
          }
        }
      }
    }
  }
  return moving_result;
}

bool canRotate(FigureInfo_t *figure_info) {
  Figure_t next_rotate_figure = getNextFigureRotate();
  int **field = figure_info->clean_field;
  bool rotate_result = true;
  int x = figure_info->x;
  int y = figure_info->y;
  for (int i = 0; i < FIGURE_COORD_SIZE && rotate_result; i++) {
    for (int j = 0; j < FIGURE_COORD_SIZE && rotate_result; j++) {
      if (next_rotate_figure.data[i][j] != 0) {
        if (y + i >= GAME_TETRIS_FIELD_HEIGHT ||
            x + j >= GAME_TETRIS_FIELD_WIDTH || field[y + i][x + j] != 0) {
          rotate_result = false;
        }
      }
    }
  }
  return rotate_result;
}

void moveLeft(FigureInfo_t *figure_info) {
  if (canMovingLeft(figure_info)) {
    figure_info->x--;
  }
}

void moveRight(FigureInfo_t *figure_info) {
  if (canMovingRight(figure_info)) {
    figure_info->x++;
  }
}

void moveDown(FigureInfo_t *figure_info) {
  if (canMovingDown(figure_info)) {
    figure_info->y++;
  }
}

void dropDown(FigureInfo_t *figure_info) {
  while (canMovingDown(figure_info)) {
    figure_info->y++;
  }
}

void doRotate(FigureInfo_t *figure_info) {
  if (canRotate(figure_info)) {
    figure_info->rotate = (figure_info->rotate + 1) & 3;
  }
}