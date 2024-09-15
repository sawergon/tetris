#ifndef C7_BRICKGAME_V1_0_1_SRC_TEST_TETRIS_TEST_RUNNER_H_
#define C7_BRICKGAME_V1_0_1_SRC_TEST_TETRIS_TEST_RUNNER_H_

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "tetris.h"

Suite **s21_tetris_cases(int *amount);

void cleanParamsInternal();

#endif  // C7_BRICKGAME_V1_0_1_SRC_TEST_TETRIS_TEST_RUNNER_H_
