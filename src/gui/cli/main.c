#include "../../include/tetris_cli.h"

#define WIN_WIDTH 80
#define WIN_HEIGHT 25

int main() {
  initscr();
  noecho();
  cbreak();
  curs_set(0);
  //    wresize(stdscr, WIN_HEIGHT, WIN_WIDTH);
  keypad(stdscr, TRUE);

  gameLoop();

  endwin();

  //  printf("Hello");
  //  gameLoop();
  return 0;
}
