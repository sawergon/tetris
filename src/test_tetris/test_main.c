#include "../include/test_runner.h"

int main(void) {
  SRunner *sr;

  sr = srunner_create(NULL);
  int tetris_test_amount = 0;
  Suite **tetris_cases = s21_tetris_cases(&tetris_test_amount);
  for (int i = 0; i < tetris_test_amount; i++) {
    srunner_add_suite(sr, tetris_cases[i]);
  }

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  //  ck_report(sr);
  srunner_free(sr);
  free(tetris_cases);
  remove("tetris_high_score.txt");
  remove("../tetris_high_score.txt");
  return 0;
}