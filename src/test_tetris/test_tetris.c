#include "../include/test_runner.h"
////////////////////////////////////////////////////////////////////////////////
//////////////////////// MATRIX WORK TESTS /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
///////// createMatrix tests ///////////
////////////////////////////////////////
START_TEST(test_createMatrix_valid_size) {
  int height = 3;
  int width = 4;
  int **matrix = createMatrix(height, width);
  ck_assert_ptr_ne(matrix, NULL);
  for (int i = 0; i < height; i++) {
    ck_assert_ptr_ne(matrix[i], NULL);
    for (int j = 0; j < width; j++) {
      ck_assert_int_eq(matrix[i][j], 0);
    }
  }
  // освобождение памяти
  for (int i = 0; i < height; i++) {
    free(matrix[i]);
  }
  free(matrix);
}
END_TEST

START_TEST(test_createMatrix_invalid_size) {
  int height = 0;
  int width = 4;
  int **matrix = createMatrix(height, width);
  ck_assert_ptr_eq(matrix, NULL);
}
END_TEST

START_TEST(test_createMatrix_negative_size) {
  int height = -3;
  int width = 4;
  int **matrix = createMatrix(height, width);
  ck_assert_ptr_eq(matrix, NULL);
}
END_TEST

////////////////////////////////////////
///////// copyMatrix tests /////////////
////////////////////////////////////////

START_TEST(test_copyMatrix_valid_matrix) {
  int height = 3;
  int width = 4;
  int **matrix = createMatrix(height, width);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      matrix[i][j] = i * width + j;
    }
  }
  int **copy = copyMatrix(matrix, height, width);
  ck_assert_ptr_ne(copy, NULL);
  for (int i = 0; i < height; i++) {
    ck_assert_ptr_ne(copy[i], NULL);
    for (int j = 0; j < width; j++) {
      ck_assert_int_eq(copy[i][j], matrix[i][j]);
    }
  }
  // освобождение памяти
  for (int i = 0; i < height; i++) {
    free(matrix[i]);
    free(copy[i]);
  }
  free(matrix);
  free(copy);
}
END_TEST

START_TEST(test_copyMatrix_invalid_matrix) {
  int height = 3;
  int width = 4;
  int **matrix = NULL;
  int **copy = copyMatrix(matrix, height, width);
  ck_assert_ptr_eq(copy, NULL);
}
END_TEST

START_TEST(test_copyMatrix_invalid_size) {
  int height = 3;
  int width = 4;
  int **matrix = createMatrix(height, width);
  int **copy = copyMatrix(matrix, 0, width);
  ck_assert_ptr_eq(copy, NULL);
  // освобождение памяти
  for (int i = 0; i < height; i++) {
    free(matrix[i]);
  }
  free(matrix);
}
END_TEST

START_TEST(test_copyMatrix_negative_size) {
  int height = 3;
  int width = 4;
  int **matrix = createMatrix(height, width);
  int **copy = copyMatrix(matrix, -3, width);
  ck_assert_ptr_eq(copy, NULL);
  // освобождение памяти
  for (int i = 0; i < height; i++) {
    free(matrix[i]);
  }
  free(matrix);
}
END_TEST

////////////////////////////////////////
///////// moveFigureMatrix tests ///////
////////////////////////////////////////

START_TEST(test_moveFigureMatrix_valid_move) {
  Figure_t src;
  for (int i = 0; i < FIGURE_COORD_SIZE; i++) {
    for (int j = 0; j < FIGURE_COORD_SIZE; j++) {
      src.data[i][j] = i + j;
    }
  }

  int **dst = (int **)malloc(FIGURE_COORD_SIZE * sizeof(int *));
  for (int i = 0; i < FIGURE_COORD_SIZE; i++) {
    dst[i] = (int *)malloc(FIGURE_COORD_SIZE * sizeof(int));
    for (int j = 0; j < FIGURE_COORD_SIZE; j++) {
      dst[i][j] = 1;
    }
  }

  moveFigureMatrix(src, dst);

  for (int i = 0; i < FIGURE_COORD_SIZE; i++) {
    for (int j = 0; j < FIGURE_COORD_SIZE; j++) {
      ck_assert_int_eq(dst[i][j], i + j);
    }
  }

  // освобождение памяти
  for (int i = 0; i < FIGURE_COORD_SIZE; i++) {
    free(dst[i]);
  }
  free(dst);
}
END_TEST

START_TEST(test_moveFigureMatrix_null_dst) {
  Figure_t src;
  for (int i = 0; i < FIGURE_COORD_SIZE; i++) {
    for (int j = 0; j < FIGURE_COORD_SIZE; j++) {
      src.data[i][j] = i + j;
    }
  }

  moveFigureMatrix(src, NULL);

  for (int i = 0; i < FIGURE_COORD_SIZE; i++) {
    for (int j = 0; j < FIGURE_COORD_SIZE; j++) {
      ck_assert_int_eq(src.data[i][j], i + j);
    }
  }
}
END_TEST

START_TEST(test_moveFigureMatrix_empty_src) {
  Figure_t src;
  for (int i = 0; i < FIGURE_COORD_SIZE; i++) {
    for (int j = 0; j < FIGURE_COORD_SIZE; j++) {
      src.data[i][j] = 0;
    }
  }

  int **dst = (int **)malloc(FIGURE_COORD_SIZE * sizeof(int *));
  for (int i = 0; i < FIGURE_COORD_SIZE; i++) {
    dst[i] = (int *)malloc(FIGURE_COORD_SIZE * sizeof(int));
    for (int j = 0; j < FIGURE_COORD_SIZE; j++) {
      dst[i][j] = 1;
    }
  }

  moveFigureMatrix(src, dst);

  for (int i = 0; i < FIGURE_COORD_SIZE; i++) {
    for (int j = 0; j < FIGURE_COORD_SIZE; j++) {
      ck_assert_int_eq(dst[i][j], 0);
    }
  }

  // освобождение памяти
  for (int i = 0; i < FIGURE_COORD_SIZE; i++) {
    free(dst[i]);
  }
  free(dst);
}
END_TEST

START_TEST(test_moveFigureMatrix_large_src) {
  Figure_t src;
  for (int i = 0; i < FIGURE_COORD_SIZE; i++) {
    for (int j = 0; j < FIGURE_COORD_SIZE; j++) {
      src.data[i][j] = i * j;
    }
  }

  int **dst = (int **)malloc(FIGURE_COORD_SIZE * sizeof(int *));
  for (int i = 0; i < FIGURE_COORD_SIZE; i++) {
    dst[i] = (int *)malloc(FIGURE_COORD_SIZE * sizeof(int));
    for (int j = 0; j < FIGURE_COORD_SIZE; j++) {
      dst[i][j] = 1;
    }
  }

  moveFigureMatrix(src, dst);

  for (int i = 0; i < FIGURE_COORD_SIZE; i++) {
    for (int j = 0; j < FIGURE_COORD_SIZE; j++) {
      ck_assert_int_eq(dst[i][j], i * j);
    }
  }

  // освобождение памяти
  for (int i = 0; i < FIGURE_COORD_SIZE; i++) {
    free(dst[i]);
  }
  free(dst);
}
END_TEST

START_TEST(test_moveFigureMatrix_negative_src) {
  Figure_t src;
  for (int i = 0; i < FIGURE_COORD_SIZE; i++) {
    for (int j = 0; j < FIGURE_COORD_SIZE; j++) {
      src.data[i][j] = -i - j;
    }
  }

  int **dst = (int **)malloc(FIGURE_COORD_SIZE * sizeof(int *));
  for (int i = 0; i < FIGURE_COORD_SIZE; i++) {
    dst[i] = (int *)malloc(FIGURE_COORD_SIZE * sizeof(int));
    for (int j = 0; j < FIGURE_COORD_SIZE; j++) {
      dst[i][j] = 1;
    }
  }

  moveFigureMatrix(src, dst);

  for (int i = 0; i < FIGURE_COORD_SIZE; i++) {
    for (int j = 0; j < FIGURE_COORD_SIZE; j++) {
      ck_assert_int_eq(dst[i][j], -i - j);
    }
  }

  // освобождение памяти
  for (int i = 0; i < FIGURE_COORD_SIZE; i++) {
    free(dst[i]);
  }
  free(dst);
}
END_TEST

////////////////////////////////////////
///////// moveMatrix tests /////////////
////////////////////////////////////////

START_TEST(test_moveMatrix_validMatrix) {
  int height = 3;
  int width = 3;
  int **src = (int **)malloc(height * sizeof(int *));
  int **dst = (int **)malloc(height * sizeof(int *));
  for (int i = 0; i < height; i++) {
    src[i] = (int *)malloc(width * sizeof(int));
    dst[i] = (int *)malloc(width * sizeof(int));
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      src[i][j] = i * width + j;
    }
  }

  moveMatrix(src, dst, height, width);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      ck_assert_int_eq(dst[i][j], i * width + j);
    }
  }

  for (int i = 0; i < height; i++) {
    free(src[i]);
    free(dst[i]);
  }
  free(src);
  free(dst);
}
END_TEST

START_TEST(test_moveMatrix_nullSrc) {
  int height = 3;
  int width = 3;
  int **src = NULL;
  int **dst = (int **)malloc(height * sizeof(int *));
  for (int i = 0; i < height; i++) {
    dst[i] = (int *)malloc(width * sizeof(int));
  }

  moveMatrix(src, dst, height, width);

  for (int i = 0; i < height; i++) {
    free(dst[i]);
  }
  free(dst);
}
END_TEST

START_TEST(test_moveMatrix_nullDst) {
  int height = 3;
  int width = 3;
  int **src = (int **)malloc(height * sizeof(int *));
  int **dst = NULL;
  for (int i = 0; i < height; i++) {
    src[i] = (int *)malloc(width * sizeof(int));
  }

  moveMatrix(src, dst, height, width);

  for (int i = 0; i < height; i++) {
    free(src[i]);
  }
  free(src);
}
END_TEST

START_TEST(test_moveMatrix_zeroHeight) {
  int height = 0;
  int width = 3;
  int **src = (int **)malloc(height * sizeof(int *));
  int **dst = (int **)malloc(height * sizeof(int *));

  moveMatrix(src, dst, height, width);

  free(src);
  free(dst);
}
END_TEST

START_TEST(test_moveMatrix_zeroWidth) {
  int height = 3;
  int width = 0;
  int **src = (int **)malloc(height * sizeof(int *));
  int **dst = (int **)malloc(height * sizeof(int *));

  moveMatrix(src, dst, height, width);

  free(src);
  free(dst);
}
END_TEST

////////////////////////////////////////
///////// destroyMatrix tests ///////////
////////////////////////////////////////

START_TEST(test_destroyMatrix_validMatrix) {
  int height = 3;
  int width = 3;
  int **matrix = (int **)malloc(height * sizeof(int *));
  for (int i = 0; i < height; i++) {
    matrix[i] = (int *)malloc(width * sizeof(int));
  }

  destroyMatrix(&matrix, height);

  ck_assert_ptr_null(matrix);
}
END_TEST

START_TEST(test_destroyMatrix_nullMatrix) {
  int height = 3;
  int ***matrix = NULL;

  destroyMatrix(matrix, height);

  ck_assert_ptr_null(matrix);
}
END_TEST

START_TEST(test_destroyMatrix_zeroHeight) {
  int height = 0;
  int **matrix = (int **)malloc(height * sizeof(int *));

  destroyMatrix(&matrix, height);

  ck_assert_ptr_null(matrix);
}
END_TEST

START_TEST(test_destroyMatrix_negativeHeight) {
  int height = -1;
  int **matrix = (int **)malloc(3 * sizeof(int *));

  destroyMatrix(&matrix, height);

  ck_assert(matrix != NULL);
  free(matrix);
}
END_TEST

TCase *matrix_suite(void) {
  TCase *tc_core = tcase_create("Matrix");
  ///////////// createMatrix
  tcase_add_test(tc_core, test_createMatrix_valid_size);
  tcase_add_test(tc_core, test_createMatrix_invalid_size);
  tcase_add_test(tc_core, test_createMatrix_negative_size);
  ///////////// copyMatrix
  tcase_add_test(tc_core, test_copyMatrix_valid_matrix);
  tcase_add_test(tc_core, test_copyMatrix_invalid_matrix);
  tcase_add_test(tc_core, test_copyMatrix_invalid_size);
  tcase_add_test(tc_core, test_copyMatrix_negative_size);
  ///////////// moveFigureMatrix
  tcase_add_test(tc_core, test_moveFigureMatrix_valid_move);
  tcase_add_test(tc_core, test_moveFigureMatrix_null_dst);
  tcase_add_test(tc_core, test_moveFigureMatrix_empty_src);
  tcase_add_test(tc_core, test_moveFigureMatrix_large_src);
  tcase_add_test(tc_core, test_moveFigureMatrix_negative_src);
  ///////////// moveMatrix
  tcase_add_test(tc_core, test_moveMatrix_validMatrix);
  tcase_add_test(tc_core, test_moveMatrix_nullSrc);
  tcase_add_test(tc_core, test_moveMatrix_nullDst);
  tcase_add_test(tc_core, test_moveMatrix_zeroHeight);
  tcase_add_test(tc_core, test_moveMatrix_zeroWidth);
  ///////////// destroyMatrix
  tcase_add_test(tc_core, test_destroyMatrix_validMatrix);
  tcase_add_test(tc_core, test_destroyMatrix_nullMatrix);
  tcase_add_test(tc_core, test_destroyMatrix_zeroHeight);
  tcase_add_test(tc_core, test_destroyMatrix_negativeHeight);

  return tc_core;
}

////////////////////////////////////////////////////////////////////////////////
//////////////////////// SCORE WORK TESTS //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
///////// calculateScore tests /////////
////////////////////////////////////////
START_TEST(test_calculateScore_level1_lines1) {
  int lines_dropped = 1;
  int expected_score = 100;
  int actual_score = calculateScore(lines_dropped);
  ck_assert_int_eq(actual_score, expected_score);
}
END_TEST

START_TEST(test_calculateScore_level2_lines2) {
  int lines_dropped = 2;
  int expected_score = 300;
  int actual_score = calculateScore(lines_dropped);
  ck_assert_int_eq(actual_score, expected_score);
}
END_TEST

START_TEST(test_calculateScore_level3_lines3) {
  int lines_dropped = 3;
  int expected_score = 700;
  int actual_score = calculateScore(lines_dropped);
  ck_assert_int_eq(actual_score, expected_score);
}
END_TEST

START_TEST(test_calculateScore_level4_lines4) {
  int lines_dropped = 4;
  int expected_score = 1500;
  int actual_score = calculateScore(lines_dropped);
  ck_assert_int_eq(actual_score, expected_score);
}
END_TEST

START_TEST(test_calculateScore_invalid_lines) {
  int lines_dropped = 5;
  int expected_score = 0;
  int actual_score = calculateScore(lines_dropped);
  ck_assert_int_eq(actual_score, expected_score);
}
END_TEST

////////////////////////////////////////
///////// updateScore tests ////////////
////////////////////////////////////////

START_TEST(test_updateScore_increaseScore) {
  GameInfo_t game;
  game.score = 100;
  game.high_score = 100;
  updateScore(&game, 50);
  ck_assert_int_eq(game.score, 150);
  ck_assert_int_eq(game.high_score, 150);
}
END_TEST

START_TEST(test_updateScore_noIncreaseHighScore) {
  GameInfo_t game;
  game.score = 100;
  game.high_score = 200;
  updateScore(&game, 50);
  ck_assert_int_eq(game.score, 150);
  ck_assert_int_eq(game.high_score, 200);
}
END_TEST

START_TEST(test_updateScore_zeroScore) {
  GameInfo_t game;
  game.score = 0;
  game.high_score = 0;
  updateScore(&game, 100);
  ck_assert_int_eq(game.score, 100);
  ck_assert_int_eq(game.high_score, 100);
}
END_TEST

START_TEST(test_updateScore_negativeScore) {
  GameInfo_t game;
  game.score = 100;
  game.high_score = 100;
  updateScore(&game, -50);
  ck_assert_int_eq(game.score, 50);
  ck_assert_int_eq(game.high_score, 100);
}
END_TEST

////////////////////////////////////////
///////// readHighScore tests //////////
////////////////////////////////////////

START_TEST(test_readHighScore_validFile) {
  GameInfo_t game;
  int expected_code = GAME_TETRIS_SUCCESS;
  int expected_high_score = 1000;

  // Создаем временный файл с высоким счетом
  char filename[] = "tetris_high_score.txt";
  FILE *file = fopen(filename, "w");
  fprintf(file, "%d", expected_high_score);
  fclose(file);

  // Вызываем функцию readHighScore
  int actual_code = readHighScore(&game);

  // Удаляем временный файл
  remove(filename);

  // Проверяем результаты
  ck_assert_int_eq(actual_code, expected_code);
  ck_assert_int_eq(game.high_score, expected_high_score);
}
END_TEST

START_TEST(test_readHighScore_invalidFile) {
  GameInfo_t game;
  int expected_code = GAME_TETRIS_FILE_NOT_FOUND;

  // Удаляем файл, если он существует
  remove(GAME_TETRIS_HIGH_SCORE_FILE);

  // Вызываем функцию readHighScore
  int actual_code = readHighScore(&game);

  // Проверяем результаты
  ck_assert_int_eq(actual_code, expected_code);
}
END_TEST

START_TEST(test_readHighScore_corruptedFile) {
  GameInfo_t game;
  int expected_code = GAME_TETRIS_ERROR_READ;

  // Создаем временный файл с неправильным содержимым
  char filename[] = "tetris_high_score.txt";
  FILE *file = fopen(filename, "w");
  fprintf(file, "abc");
  fclose(file);

  // Вызываем функцию readHighScore
  int actual_code = readHighScore(&game);

  // Удаляем временный файл
  remove(filename);

  // Проверяем результаты
  ck_assert_int_eq(actual_code, expected_code);
  ck_assert_int_eq(game.high_score, 0);
}
END_TEST

START_TEST(test_readHighScore_zeroScore) {
  GameInfo_t game;
  int expected_code = GAME_TETRIS_SUCCESS;

  // Создаем временный файл с нулевым счетом
  char filename[] = "tetris_high_score.txt";
  FILE *file = fopen(filename, "w");
  fprintf(file, "0");
  fclose(file);

  // Вызываем функцию readHighScore
  int actual_code = readHighScore(&game);

  // Удаляем временный файл
  remove(filename);

  // Проверяем результаты
  ck_assert_int_eq(actual_code, expected_code);
  ck_assert_int_eq(game.high_score, 0);
}
END_TEST

START_TEST(test_readHighScore_negativeScore) {
  GameInfo_t game;
  int expected_code = GAME_TETRIS_SUCCESS;

  // Создаем временный файл с отрицательным счетом
  char filename[] = "tetris_high_score.txt";
  FILE *file = fopen(filename, "w");
  fprintf(file, "-100");
  fclose(file);

  // Вызываем функцию readHighScore
  int actual_code = readHighScore(&game);

  // Удаляем временный файл
  remove(filename);

  // Проверяем результаты
  ck_assert_int_eq(actual_code, expected_code);
  ck_assert_int_eq(game.high_score, -100);
}
END_TEST

////////////////////////////////////////
///////// writeHighScore tests /////////
////////////////////////////////////////

START_TEST(test_writeHighScore_newRecord) {
  GameInfo_t game;
  int score = 1000;
  int expected_code = GAME_TETRIS_SUCCESS;

  // Удаляем файл, если он существует
  remove(GAME_TETRIS_HIGH_SCORE_FILE);

  // Вызываем функцию writeHighScore
  int actual_code = writeHighScore(&game, score);

  // Проверяем результаты
  ck_assert_int_eq(actual_code, expected_code);
  ck_assert_int_eq(game.high_score, score);

  // Проверяем содержимое файла
  FILE *file = fopen(GAME_TETRIS_HIGH_SCORE_FILE, "r");
  int actual_score;
  fscanf(file, "%d", &actual_score);
  fclose(file);
  ck_assert_int_eq(actual_score, score);
  remove(GAME_TETRIS_HIGH_SCORE_FILE);
}
END_TEST

START_TEST(test_writeHighScore_noNewRecord) {
  GameInfo_t game;
  int score = 500;
  int expected_code = GAME_TETRIS_SUCCESS;

  // Создаем файл с рекордом 1000
  FILE *file = fopen(GAME_TETRIS_HIGH_SCORE_FILE, "w");
  fprintf(file, "1000");
  fclose(file);

  // Вызываем функцию writeHighScore
  int actual_code = writeHighScore(&game, score);

  // Проверяем результаты
  ck_assert_int_eq(actual_code, expected_code);
  ck_assert_int_eq(game.high_score, 1000);

  // Проверяем содержимое файла
  file = fopen(GAME_TETRIS_HIGH_SCORE_FILE, "r");
  int actual_score;
  fscanf(file, "%d", &actual_score);
  fclose(file);
  ck_assert_int_eq(actual_score, 1000);
  remove(GAME_TETRIS_HIGH_SCORE_FILE);
}
END_TEST

START_TEST(test_writeHighScore_zeroScore) {
  GameInfo_t game;
  int score = 0;
  int expected_code = GAME_TETRIS_SUCCESS;

  // Удаляем файл, если он существует
  remove(GAME_TETRIS_HIGH_SCORE_FILE);

  // Вызываем функцию writeHighScore
  int actual_code = writeHighScore(&game, score);

  // Проверяем результаты
  ck_assert_int_eq(actual_code, expected_code);
  ck_assert_int_eq(game.high_score, 0);

  // Проверяем содержимое файла
  FILE *file = fopen(GAME_TETRIS_HIGH_SCORE_FILE, "r");
  int actual_score;
  fscanf(file, "%d", &actual_score);
  fclose(file);
  ck_assert_int_eq(actual_score, 0);
  remove(GAME_TETRIS_HIGH_SCORE_FILE);
}
END_TEST

START_TEST(test_writeHighScore_negativeScore) {
  GameInfo_t game;
  int score = -100;
  int expected_code = GAME_TETRIS_SUCCESS;

  // Удаляем файл, если он существует
  remove(GAME_TETRIS_HIGH_SCORE_FILE);

  // Вызываем функцию writeHighScore
  int actual_code = writeHighScore(&game, score);

  // Проверяем результаты
  ck_assert_int_eq(actual_code, expected_code);
  ck_assert_int_eq(game.high_score, 0);

  // Проверяем содержимое файла
  FILE *file = fopen(GAME_TETRIS_HIGH_SCORE_FILE, "r");
  int actual_score;
  fscanf(file, "%d", &actual_score);
  fclose(file);
  ck_assert_int_eq(actual_score, 0);
  remove(GAME_TETRIS_HIGH_SCORE_FILE);
}
END_TEST

TCase *score_suite(void) {
  TCase *tc_core = tcase_create("Score");
  ///////////// calculateScore
  tcase_add_test(tc_core, test_calculateScore_level1_lines1);
  tcase_add_test(tc_core, test_calculateScore_level2_lines2);
  tcase_add_test(tc_core, test_calculateScore_level3_lines3);
  tcase_add_test(tc_core, test_calculateScore_level4_lines4);
  tcase_add_test(tc_core, test_calculateScore_invalid_lines);
  ///////////// updateScore
  tcase_add_test(tc_core, test_updateScore_increaseScore);
  tcase_add_test(tc_core, test_updateScore_noIncreaseHighScore);
  tcase_add_test(tc_core, test_updateScore_zeroScore);
  tcase_add_test(tc_core, test_updateScore_negativeScore);
  ///////////// readHighScore
  tcase_add_test(tc_core, test_readHighScore_validFile);
  tcase_add_test(tc_core, test_readHighScore_invalidFile);
  tcase_add_test(tc_core, test_readHighScore_corruptedFile);
  tcase_add_test(tc_core, test_readHighScore_zeroScore);
  tcase_add_test(tc_core, test_readHighScore_negativeScore);
  ///////////// writeHighScore
  tcase_add_test(tc_core, test_writeHighScore_newRecord);
  tcase_add_test(tc_core, test_writeHighScore_zeroScore);
  tcase_add_test(tc_core, test_writeHighScore_negativeScore);
  tcase_add_test(tc_core, test_writeHighScore_noNewRecord);
  return tc_core;
}

////////////////////////////////////////////////////////////////////////////////
//////////////////////// GAME INIT TESTS ///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
///////// createGame tests /////////////
////////////////////////////////////////

START_TEST(test_createGame_mallocSuccess) {
  GameInfo_t *game = createGame();
  ck_assert_ptr_ne(game, NULL);
}
END_TEST

START_TEST(test_createGame_fieldIsNull) {
  GameInfo_t *game = createGame();
  ck_assert_ptr_eq(game->field, NULL);
}
END_TEST

START_TEST(test_createGame_nextIsNull) {
  GameInfo_t *game = createGame();
  ck_assert_ptr_eq(game->next, NULL);
}
END_TEST

START_TEST(test_createGame_scoreIsZero) {
  GameInfo_t *game = createGame();
  ck_assert_int_eq(game->score, 0);
}
END_TEST

START_TEST(test_createGame_allFieldsAreInitialized) {
  GameInfo_t *game = createGame();
  ck_assert_ptr_eq(game->field, NULL);
  ck_assert_ptr_eq(game->next, NULL);
  ck_assert_int_eq(game->score, 0);
  ck_assert_int_eq(game->high_score, 0);
  ck_assert_int_eq(game->level, 0);
  ck_assert_int_eq(game->speed, 0);
  ck_assert_int_eq(game->pause, 0);
}
END_TEST

////////////////////////////////////////
///////// initGame tests ///////////////
////////////////////////////////////////

START_TEST(test_initGame_fieldIsInitialized) {
  GameInfo_t game;
  initGame(&game);
  ck_assert_ptr_ne(game.field, NULL);
  destroyMatrix(&(game.field), GAME_TETRIS_FIELD_HEIGHT);
  remove(GAME_TETRIS_HIGH_SCORE_FILE);
}
END_TEST

START_TEST(test_initGame_nextIsNull) {
  GameInfo_t game;
  initGame(&game);
  ck_assert_ptr_eq(game.next, NULL);
  destroyMatrix(&(game.field), GAME_TETRIS_FIELD_HEIGHT);
}
END_TEST

START_TEST(test_initGame_scoreIsZero) {
  GameInfo_t game;
  initGame(&game);
  ck_assert_int_eq(game.score, 0);
  destroyMatrix(&(game.field), GAME_TETRIS_FIELD_HEIGHT);
}
END_TEST

START_TEST(test_initGame_levelIsOne) {
  GameInfo_t game;
  initGame(&game);
  ck_assert_int_eq(game.level, 1);
  destroyMatrix(&(game.field), GAME_TETRIS_FIELD_HEIGHT);
}
END_TEST

START_TEST(test_initGame_highScoreIsRead) {
  GameInfo_t game;
  FILE *f = fopen(GAME_TETRIS_HIGH_SCORE_FILE, "w");
  fprintf(f, "10000");
  fclose(f);
  initGame(&game);
  ck_assert(game.high_score == 10000);
  remove(GAME_TETRIS_HIGH_SCORE_FILE);
  destroyMatrix(&(game.field), GAME_TETRIS_FIELD_HEIGHT);
}
END_TEST

START_TEST(test_initGame_highScoreRenew) {
  GameInfo_t game;
  game.high_score = 10000;
  initGame(&game);
  ck_assert(game.high_score == 0);
  destroyMatrix(&(game.field), GAME_TETRIS_FIELD_HEIGHT);
}
END_TEST

////////////////////////////////////////
///////// destroyGame tests ////////////
////////////////////////////////////////

START_TEST(test_destroyGame_fieldIsDestroyed) {
  GameInfo_t *game = createGame();
  destroyGame(&game);
  ck_assert_ptr_eq(game->field, NULL);
  remove(GAME_TETRIS_HIGH_SCORE_FILE);
}
END_TEST

START_TEST(test_destroyGame_nextIsDestroyed) {
  GameInfo_t *game = createGame();
  game->next = createMatrix(FIGURE_COORD_SIZE, FIGURE_COORD_SIZE);
  destroyGame(&game);
  ck_assert_ptr_eq(game->field, NULL);
  remove(GAME_TETRIS_HIGH_SCORE_FILE);
}
END_TEST

START_TEST(test_destroyGame_highScoreIsWritten) {
  GameInfo_t *game = createGame();
  game->high_score = 100;
  destroyGame(&game);
  GameInfo_t *new_game = createGame();
  ck_assert(readHighScore(new_game) == GAME_TETRIS_SUCCESS);
  ck_assert(new_game->high_score == 100);
  destroyGame(&new_game);
  remove(GAME_TETRIS_HIGH_SCORE_FILE);
}
END_TEST

START_TEST(test_destroyGame_gameIsNull) {
  GameInfo_t *game = NULL;
  destroyGame(NULL);
  remove(GAME_TETRIS_HIGH_SCORE_FILE);
  destroyGame(&game);
}
END_TEST

TCase *game_init_suite_cases() {
  TCase *tc_core = tcase_create("Game Init");

  /////////// createGame
  tcase_add_test(tc_core, test_createGame_mallocSuccess);
  tcase_add_test(tc_core, test_createGame_fieldIsNull);
  tcase_add_test(tc_core, test_createGame_nextIsNull);
  tcase_add_test(tc_core, test_createGame_scoreIsZero);
  tcase_add_test(tc_core, test_createGame_allFieldsAreInitialized);
  /////////// initGame
  tcase_add_test(tc_core, test_initGame_fieldIsInitialized);
  tcase_add_test(tc_core, test_initGame_nextIsNull);
  tcase_add_test(tc_core, test_initGame_scoreIsZero);
  tcase_add_test(tc_core, test_initGame_levelIsOne);
  tcase_add_test(tc_core, test_initGame_highScoreIsRead);
  tcase_add_test(tc_core, test_initGame_highScoreRenew);
  /////////// destroyGame
  tcase_add_test(tc_core, test_destroyGame_fieldIsDestroyed);
  tcase_add_test(tc_core, test_destroyGame_nextIsDestroyed);
  tcase_add_test(tc_core, test_destroyGame_highScoreIsWritten);
  tcase_add_test(tc_core, test_destroyGame_gameIsNull);
  return tc_core;
}

////////////////////////////////////////////////////////////////////////////////
//////////////////////// FIGURE WORK TESTS /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
///////// getFigureInfo tests //////////
////////////////////////////////////////

START_TEST(test_getFigureInfo_returns_non_null) {
  FigureInfo_t *figure = getFigureInfo();
  ck_assert_ptr_nonnull(figure);
}
END_TEST

START_TEST(test_getFigureInfo_returns_same_pointer) {
  FigureInfo_t *figure1 = getFigureInfo();
  FigureInfo_t *figure2 = getFigureInfo();
  ck_assert_ptr_eq(figure1, figure2);
}
END_TEST

////////////////////////////////////////
/////// getCurrentFigure tests /////////
////////////////////////////////////////

bool isFigureEqual(Figure_t figure1, Figure_t figure2) {
  bool is_equal = true;
  for (int i = 0; i < FIGURE_COORD_SIZE && is_equal; i++) {
    for (int j = 0; j < FIGURE_COORD_SIZE && is_equal; j++) {
      if (figure1.data[i][j] != figure2.data[i][j]) {
        is_equal = false;
      }
    }
  }
  return is_equal;
}

START_TEST(test_getCurrentFigure_returns_valid_figure) {
  FigureInfo_t *figure_info = getFigureInfo();
  fillPosArr(figure_info);
  figure_info->type = 0;
  figure_info->rotate = 0;
  int ExpectedFigure[4][4] = {
      {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  Figure_t figure = getCurrentFigure();
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_int_eq(figure.data[i][j], ExpectedFigure[i][j]);
    }
  }
}
END_TEST

START_TEST(test_getCurrentFigure_different_types) {
  FigureInfo_t *figure_info = getFigureInfo();
  figure_info->type = 0;
  Figure_t figure1 = getCurrentFigure();
  figure_info->type = 1;
  Figure_t figure2 = getCurrentFigure();
  ck_assert_int_eq(isFigureEqual(figure1, figure2), false);
}
END_TEST

START_TEST(test_getCurrentFigure_different_rotations) {
  FigureInfo_t *figure_info = getFigureInfo();
  figure_info->type = L;
  figure_info->rotate = 0;
  Figure_t figure1 = getCurrentFigure();
  figure_info->rotate = 1;
  Figure_t figure2 = getCurrentFigure();

  ck_assert_int_eq(isFigureEqual(figure1, figure2), false);
}
END_TEST

/////////////////////////////////////////
////// getNextFigureRotate tests ////////
/////////////////////////////////////////

START_TEST(test_getNextFigureRotate_returns_valid_figure) {
  FigureInfo_t *figure_info = getFigureInfo();
  fillPosArr(figure_info);
  figure_info->type = 0;
  figure_info->rotate = 0;
  Figure_t cur_figure = getCurrentFigure();
  Figure_t figure = getNextFigureRotate();
  ck_assert_int_eq(isFigureEqual(cur_figure, figure), false);
}
END_TEST

START_TEST(test_getNextFigureRotate_returns_next_rotation) {
  FigureInfo_t *figure_info = getFigureInfo();
  figure_info->rotate = 0;
  Figure_t figure1 = getNextFigureRotate();
  figure_info->rotate = 1;
  Figure_t figure2 = getCurrentFigure();
  ck_assert_int_eq(isFigureEqual(figure1, figure2),
                   true);  // проверяем, что следующая фигура совпадает с
                           // текущей при повороте на 1
}
END_TEST

START_TEST(test_getNextFigureRotate_wraps_around_to_first_rotation) {
  FigureInfo_t *figure_info = getFigureInfo();
  figure_info->rotate = 3;
  Figure_t figure = getNextFigureRotate();
  ck_assert_int_eq(
      isFigureEqual(figure, figure_info->positionArr[figure_info->type][0]),
      true);  // проверяем, что следующая фигура совпадает с первой при повороте
              // на 4
}
END_TEST

TCase *figure_suite() {
  TCase *tc_core = tcase_create("Figure");

  /////////// getFigureInfo
  tcase_add_test(tc_core, test_getFigureInfo_returns_non_null);
  tcase_add_test(tc_core, test_getFigureInfo_returns_same_pointer);
  ////////// getCurrentFigure
  tcase_add_test(tc_core, test_getCurrentFigure_returns_valid_figure);
  tcase_add_test(tc_core, test_getCurrentFigure_different_types);
  tcase_add_test(tc_core, test_getCurrentFigure_different_rotations);
  ////////// getNextFigureRotate
  tcase_add_test(tc_core, test_getNextFigureRotate_returns_valid_figure);
  tcase_add_test(tc_core, test_getNextFigureRotate_returns_next_rotation);
  tcase_add_test(tc_core,
                 test_getNextFigureRotate_wraps_around_to_first_rotation);
  return tc_core;
}

////////////////////////////////////////////////////////////////////////////////
//////////////////////// GAME WORK TESTS ///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////
///////// userInput tests ///////////////
/////////////////////////////////////////

START_TEST(test_terminate) {
  startNewGame();
  userInput(Terminate, false);
  FiniteMachineStatus_t *status = getMachineStatus();
  ck_assert_int_eq(*status, SureEndGame);
}
END_TEST

START_TEST(test_start_new_game) {
  startNewGame();
  userInput(Start, false);
  FiniteMachineStatus_t *status = getMachineStatus();
  ck_assert_int_eq(*status, SpawnFigure);
  cleanParamsInternal();
}
END_TEST

START_TEST(test_start_not_new_game) {
  FiniteMachineStatus_t *status = getMachineStatus();
  *status = SpawnFigure;
  userInput(Start, false);
  ck_assert_int_eq(*status, SpawnFigure);
}
END_TEST

START_TEST(test_pause_not_paused) {
  FiniteMachineStatus_t *status = getMachineStatus();
  *status = SpawnFigure;
  GameInfo_t *game = getGameState();
  game->pause = false;
  userInput(Pause, false);
  ck_assert_int_eq(*status, Paused);
  ck_assert_int_eq(game->pause, true);
  userInput(Pause, false);
  ck_assert_int_eq(*status, Refresh);
  ck_assert_int_eq(game->pause, false);
}
END_TEST

START_TEST(test_left) {
  startNewGame();
  userInput(Start, false);
  FiniteMachineStatus_t *status = getMachineStatus();
  *status = Refresh;
  FigureInfo_t *figure_info = getFigureInfo();
  figure_info->x = 1;
  userInput(Left, false);
  ck_assert_int_eq(*status, Refresh);
  ck_assert_int_eq(figure_info->x, 0);
  cleanParamsInternal();
}
END_TEST

START_TEST(test_right) {
  startNewGame();
  userInput(Start, false);
  FiniteMachineStatus_t *status = getMachineStatus();
  *status = Refresh;
  FigureInfo_t *figure_info = getFigureInfo();
  figure_info->x = 1;
  userInput(Right, false);
  ck_assert_int_eq(*status, Refresh);
  ck_assert_int_gt(figure_info->x, 0);
  cleanParamsInternal();
}
END_TEST

START_TEST(test_down_not_hold) {
  startNewGame();
  userInput(Start, false);
  FiniteMachineStatus_t *status = getMachineStatus();
  *status = Refresh;
  FigureInfo_t *figure_info = getFigureInfo();
  figure_info->y = 0;
  userInput(Down, false);
  ck_assert_int_eq(*status, Refresh);
  ck_assert_int_gt(figure_info->y, 0);
  cleanParamsInternal();
}
END_TEST

START_TEST(test_down_hold) {
  startNewGame();
  userInput(Start, true);
  FiniteMachineStatus_t *status = getMachineStatus();
  *status = Refresh;
  FigureInfo_t *figure_info = getFigureInfo();
  figure_info->y = 0;
  userInput(Down, true);
  ck_assert_int_eq(*status, Refresh);
  ck_assert_int_gt(figure_info->y, 0);
  cleanParamsInternal();
}
END_TEST

START_TEST(test_action) {
  startNewGame();
  userInput(Start, false);
  FiniteMachineStatus_t *status = getMachineStatus();
  *status = SpawnFigure;
  FigureInfo_t *figure_info = getFigureInfo();
  figure_info->rotate = 0;
  figure_info->x = 4;
  figure_info->y = 4;
  userInput(Action, false);
  ck_assert_int_eq(*status, Refresh);
  ck_assert_int_ne(figure_info->rotate, 0);
  cleanParamsInternal();
}
END_TEST

/////////////////////////////////////////
///// updateCurrentState tests //////////
/////////////////////////////////////////

void prepareParamsInternal() {
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

void cleanParamsInternal() {
  GameInfo_t *game_info = getGameState();
  destroyGame(&game_info);
  FigureInfo_t *figure_info = getFigureInfo();
  int **k = figure_info->clean_field;
  destroyMatrix(&k, GAME_TETRIS_FIELD_HEIGHT);
}

START_TEST(test_updateCurrentState) {
  startNewGame();
  userInput(Start, false);

  /////// SpawnFigure

  FiniteMachineStatus_t *status = getMachineStatus();
  FigureInfo_t *figure_info = getFigureInfo();
  GameInfo_t *game_info = getGameState();
  *status = SpawnFigure;
  figure_info->next_type = O;
  FigureType_t pre_type = figure_info->next_type;

  // Call updateCurrentState
  updateCurrentState();

  // Check that figure was spawned correctly
  ck_assert_int_eq(pre_type, figure_info->type);
  ck_assert_int_eq(*status, Refresh);
  figure_info->next_type = O;

  ////// Fall after refresh
  int pre_x = figure_info->x;
  int pre_y = figure_info->y;
  userInput(Up, false);

  updateCurrentState();

  // Check that figure was moved down correctly
  ck_assert_int_eq(pre_x, figure_info->x);
  ck_assert_int_eq(pre_y + 1, figure_info->y);
  ck_assert_int_eq(*status, Refresh);

  //////// CleanLine
  for (int i = 0; i < GAME_TETRIS_FIELD_WIDTH; i++) {
    figure_info->clean_field[GAME_TETRIS_FIELD_HEIGHT - 1][i] = 1;
  }

  updateCurrentState();
  ck_assert_int_eq(game_info->score, 100);

  for (int i = 0; i < GAME_TETRIS_FIELD_WIDTH - 3; i++) {
    figure_info->clean_field[5][i] = 1;
  }

  updateCurrentState();
  ck_assert_int_eq(*status, SpawnFigure);

  for (int i = 0; i < GAME_TETRIS_FIELD_HEIGHT; ++i) {
    for (int j = 0; j < GAME_TETRIS_FIELD_WIDTH; ++j) {
      figure_info->clean_field[i][j] = 0;
    }
  }
  updateCurrentState();
  userInput(Left, false);
  userInput(Left, false);
  userInput(Left, false);
  userInput(Left, false);
  updateCurrentState();
  ////// NOT BREAKE LEFT BORDER
  pre_x = figure_info->x;
  pre_y = figure_info->y;
  userInput(Left, false);
  updateCurrentState();
  ck_assert_int_eq(pre_x, figure_info->x);
  ck_assert_int_eq(pre_y + 1, figure_info->y);

  *status = SpawnFigure;
  figure_info->next_type = O;

  for (int i = 0; i < GAME_TETRIS_FIELD_HEIGHT; ++i) {
    for (int j = 0; j < GAME_TETRIS_FIELD_WIDTH; ++j) {
      figure_info->clean_field[i][j] = 0;
    }
  }
  updateCurrentState();
  userInput(Right, false);
  userInput(Right, false);
  userInput(Right, false);
  userInput(Right, false);
  updateCurrentState();
  ////// NOT BREAKE RIGHT BORDER
  pre_x = figure_info->x;
  pre_y = figure_info->y;
  userInput(Right, false);
  updateCurrentState();
  ck_assert_int_eq(pre_x, figure_info->x);
  ck_assert_int_eq(pre_y + 1, figure_info->y);
  userInput(Left, false);
  /// make left right borders
  for (int i = 0; i < GAME_TETRIS_FIELD_HEIGHT; ++i) {
    figure_info->clean_field[i][0] = 1;
    figure_info->clean_field[i][GAME_TETRIS_FIELD_WIDTH - 1] = 1;
  }
  pre_x = figure_info->x;
  pre_y = figure_info->y;
  userInput(Right, false);
  updateCurrentState();
  ck_assert_int_eq(pre_x, figure_info->x);
  ck_assert_int_eq(pre_y + 1, figure_info->y);

  userInput(Left, false);
  userInput(Left, false);
  userInput(Left, false);
  userInput(Left, false);
  userInput(Left, false);
  userInput(Left, false);
  pre_x = figure_info->x;
  pre_y = figure_info->y;
  updateCurrentState();
  ck_assert_int_eq(pre_x, figure_info->x);
  ck_assert_int_eq(pre_y + 1, figure_info->y);

  /// can't rotate to wall
  figure_info->type = T;
  userInput(Action, false);
  ck_assert_int_eq(figure_info->rotate, 0);

  figure_info->type = O;
  pre_x = figure_info->x;
  userInput(Down, true);
  updateCurrentState();
  ck_assert_int_eq(pre_x, figure_info->x);
  ck_assert_int_eq(GAME_TETRIS_FIELD_HEIGHT - 2, figure_info->y);

  ///// EndGame
  *status = SpawnFigure;
  for (int i = 0; i < GAME_TETRIS_FIELD_HEIGHT; i++) {
    for (int j = 0; j < GAME_TETRIS_FIELD_WIDTH; j++) {
      game_info->field[i][j] = 1;
    }
  }
  updateCurrentState();
  ck_assert_int_eq(*status, EndGame);
}
END_TEST

//////////////////////////////
//////// getHint tests ///////
//////////////////////////////

START_TEST(test_getHint) {
  FigureInfo_t *figure_info = getFigureInfo();
  figure_info->x = 3;
  figure_info->y = 0;
  figure_info->type = T;
  figure_info->rotate = 0;
  figure_info->next_type = T;
  figure_info->clean_field =
      createMatrix(GAME_TETRIS_FIELD_HEIGHT, GAME_TETRIS_FIELD_WIDTH);
  fillPosArr(figure_info);
  Hint_t hint = getHint();
  ck_assert_int_eq(hint.data[0][0], 18);
  ck_assert_int_eq(hint.data[0][1], 5);
  ck_assert_int_eq(hint.data[1][0], 19);
  ck_assert_int_eq(hint.data[1][1], 4);
  ck_assert_int_eq(hint.data[2][0], 19);
  ck_assert_int_eq(hint.data[2][1], 5);
  ck_assert_int_eq(hint.data[3][0], 19);
  ck_assert_int_eq(hint.data[3][1], 6);
  destroyMatrix(&(figure_info->clean_field), GAME_TETRIS_FIELD_HEIGHT);
}
END_TEST

TCase *game_work_suite_cases() {
  TCase *tc_core = tcase_create("Game Work");

  //////////// userInput
  tcase_add_test(tc_core, test_terminate);
  tcase_add_test(tc_core, test_start_new_game);
  tcase_add_test(tc_core, test_start_not_new_game);
  tcase_add_test(tc_core, test_pause_not_paused);
  tcase_add_test(tc_core, test_left);
  tcase_add_test(tc_core, test_right);
  tcase_add_test(tc_core, test_down_not_hold);
  tcase_add_test(tc_core, test_down_hold);
  tcase_add_test(tc_core, test_action);
  //////////// updateCurrentState
  tcase_add_test(tc_core, test_updateCurrentState);
  //////////// getHint
  tcase_add_test(tc_core, test_getHint);
  return tc_core;
}

Suite **s21_tetris_cases(int *amount) {
  *amount = 5;
  Suite **cases = malloc(sizeof(Suite *) * (*amount));

  Suite *matrix_work_suite = suite_create("MATRIX WORK TESTS");
  suite_add_tcase(matrix_work_suite, matrix_suite());

  Suite *score_work_suite = suite_create("SCORE WORK TESTS");
  suite_add_tcase(score_work_suite, score_suite());

  Suite *game_init_suite = suite_create("GAME INIT TESTS");
  suite_add_tcase(game_init_suite, game_init_suite_cases());

  Suite *figure_work_suite = suite_create("FIGURE WORK TESTS");
  suite_add_tcase(figure_work_suite, figure_suite());

  Suite *game_work_suite = suite_create("GAME WORK TESTS");
  suite_add_tcase(game_work_suite, game_work_suite_cases());

  cases[0] = matrix_work_suite;
  cases[1] = score_work_suite;
  cases[2] = game_init_suite;
  cases[3] = figure_work_suite;
  cases[4] = game_work_suite;

  return cases;
}