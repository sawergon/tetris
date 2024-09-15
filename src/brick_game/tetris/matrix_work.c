#include "../../include/tetris.h"

int **createMatrix(int height, int width) {
  if (height <= 0 || width <= 0) {
    return NULL;
  }
  int **matrix = malloc(height * sizeof(int *));
  for (int i = 0; i < height; i++) {
    matrix[i] = malloc(width * sizeof(int));
    for (int j = 0; j < width; j++) {
      matrix[i][j] = 0;
    }
  }
  return matrix;
}

int **copyMatrix(int **matrix, int height, int width) {
  if (matrix == NULL || height <= 0 || width <= 0) {
    return NULL;
  }
  int **new_matrix = createMatrix(height, width);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      new_matrix[i][j] = matrix[i][j];
    }
  }
  return new_matrix;
}

void moveFigureMatrix(Figure_t src, int **dst) {
  if (dst != NULL) {
    for (int i = 0; i < FIGURE_COORD_SIZE; i++) {
      for (int j = 0; j < FIGURE_COORD_SIZE; j++) {
        dst[i][j] = src.data[i][j];
      }
    }
  }
}

void moveMatrix(int **src, int **dst, int height, int width) {
  if (src != NULL && dst != NULL && height > 0 && width > 0) {
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        dst[i][j] = src[i][j];
      }
    }
  }
}

// void printMatrix(int **matrix, int height, int width) {
//  if (height > 0 && width > 0 && matrix != NULL) {
//    for (int i = 0; i < height; i++) {
//      for (int j = 0; j < width; j++) {
//        printf("%d ", matrix[i][j]);
//      }
//      printf("\n");
//    }
//  }
//}

void destroyMatrix(int ***matrix, int height) {
  if (matrix != NULL && height >= 0) {
    for (int i = 0; i < height; i++) {
      free((*matrix)[i]);
    }
    free(*matrix);
    *matrix = NULL;
  }
}
