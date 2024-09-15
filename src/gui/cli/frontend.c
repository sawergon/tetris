#include "../../include/tetris_cli.h"

#define KEY_ACTION 32
#define KEY_QUIT 113
#define KEY_START 10

UserAction_t getAction() {
  int ch = getch();
  switch (ch) {
    case KEY_LEFT:
      return Left;
    case KEY_RIGHT:
      return Right;
    case KEY_UP:
      return Up;
    case KEY_DOWN:
      return Down;
    case KEY_ACTION:
      return Action;
    case KEY_QUIT:
      return Terminate;
    case KEY_START:
      return Start;
    case 'p':
      return Pause;
    default:
      return Up;
  }
}

void printRectangle(int top_y, int bottom_y, int left_x, int right_x) {
  mvaddch(top_y, left_x, ACS_ULCORNER);

  int i = left_x + 1;
  for (; i < right_x; i++) {
    mvaddch(top_y, i, ACS_HLINE);
  }
  mvaddch(top_y, i, ACS_URCORNER);

  i = top_y + 1;
  for (; i < bottom_y; i++) {
    mvaddch(i, left_x, ACS_VLINE);
    mvaddch(i, right_x, ACS_VLINE);
  }
  mvaddch(bottom_y, left_x, ACS_LLCORNER);

  i = left_x + 1;
  for (; i < right_x; i++) {
    mvaddch(bottom_y, i, ACS_HLINE);
  }
  mvaddch(bottom_y, i, ACS_LRCORNER);
}

void displayStartMessage() {
  clear();
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  mvprintw(0, 0, "Tetris by kimikodo");
  mvprintw(1, 0, "Have nice game");
  attron(COLOR_PAIR(1));
  mvprintw(3, 0, "Use arrows to move");
  mvprintw(4, 0, "P to pause");
  mvprintw(5, 0, "SPACE  to rotate");
  mvprintw(6, 0, "Q to quite");
  attroff(COLOR_PAIR(1));

  attron(A_BLINK | COLOR_PAIR(2));
  mvprintw(8, 0, "Press ENTER to start");
  attroff(A_BLINK | COLOR_PAIR(2));
  refresh();
}

void displayEndMessage(int score) {
  clear();
  mvprintw(0, 0, "Thank you for playing Tetris");
  mvprintw(1, 0, "PRESS Q TO EXIT");
  mvprintw(2, 0, "PRESS ENTER TO RESTART");
  mvprintw(3, 0, "YOUR SCORE: %d", score);
  refresh();
}

void displayErrorMessage() {
  clear();
  mvprintw(0, 0, "Error");
  refresh();
}

void displayHoldMessage() {
  printRectangle(4, 8, 4, 24);
  attron(A_BLINK);
  mvprintw(5, 5, "Game on hold       ");
  attroff(A_BLINK);
  mvprintw(6, 5, "Press P to continue");
  mvprintw(7, 5, "Press Q to exit    ");
  refresh();
}

void displaySureEndGameMessage() {
  attron(A_BLINK);
  printRectangle(4, 8, 4, 29);
  attroff(A_BLINK);
  mvprintw(5, 5, "Sure want end game?    ");
  mvprintw(6, 5, "Press Q to exit        ");
  mvprintw(7, 5, "Press ENTER to continue");
  refresh();
}

bool getStartCommand() {
  bool run = false;
  bool terminate = false;
  while (!run && !terminate) {
    UserAction_t action = getAction();
    if (action == Start) {
      run = true;
    } else if (action == Terminate) {
      terminate = true;
    }
  }
  return run;
}

void displayGame(GameInfo_t *game) {
  clear();
  printRectangle(0, 21, 0, 11);
  printRectangle(0, 21, 12, 31);
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  init_pair(4, COLOR_YELLOW, COLOR_BLACK);
  init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(6, COLOR_CYAN, COLOR_BLACK);
  init_pair(7, COLOR_WHITE, COLOR_BLACK);
  for (int y = 0; y < GAME_TETRIS_FIELD_HEIGHT; y++) {
    for (int x = 0; x < GAME_TETRIS_FIELD_WIDTH; x++) {
      if (game->field[y][x] == 0) {
        mvaddch(y + 1, x + 1, ' ');
      } else {
        attron(COLOR_PAIR(game->field[y][x]));
        mvaddch(y + 1, x + 1, ACS_CKBOARD);
        attroff(COLOR_PAIR(game->field[y][x]));
      }
    }
  }
  Hint_t hint = getHint();
  if (hint.data[0][0] != 0) {
    for (int i = 0; i < FIGURE_COORD_SIZE; i++) {
      if (game->field[hint.data[i][0]][hint.data[i][1]] == 0) {
        attron(COLOR_PAIR(1));
        mvaddch(hint.data[i][0] + 1, hint.data[i][1] + 1, ACS_BLOCK);
        attroff(COLOR_PAIR(1));
      }
    }
  }
  refresh();
}

void displayHelpInfo(GameInfo_t *game) {
  int delta_y = 1;
  int delta_x = 13;
  mvprintw(delta_y, delta_x, "NEXT FIGURE");
  delta_y += 1;
  printRectangle(delta_y, delta_y + 5, delta_x, delta_x + 5);
  delta_y += 1;
  delta_x += 1;
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  init_pair(4, COLOR_YELLOW, COLOR_BLACK);
  init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(6, COLOR_CYAN, COLOR_BLACK);
  init_pair(7, COLOR_WHITE, COLOR_BLACK);
  for (int i = 0; i < FIGURE_COORD_SIZE; i++) {
    for (int j = 0; j < FIGURE_COORD_SIZE; ++j) {
      if (game->next[i][j] != 0) {
        attron(COLOR_PAIR(game->next[i][j]));
        mvaddch(delta_y + i, delta_x + j, ACS_CKBOARD);
        attroff(COLOR_PAIR(game->next[i][j]));
      }
    }
  }
  delta_y += 5;
  delta_x -= 1;
  mvprintw(delta_y++, delta_x, "SCORE: %d", game->score);
  mvprintw(delta_y++, delta_x, "HIGHSCORE: %d", game->high_score);
  mvprintw(delta_y++, delta_x, "LEVEL: %d", game->level);
  mvprintw(delta_y++, delta_x, "SPEED: %d", game->speed);
}

void gameLoop() {
  bool hold = false;  // зажата ли клавиша
  bool run = false;

  displayStartMessage();

  run = getStartCommand();
  if (run) {
    startNewGame();
    userInput(Start, false);
  }
  while (run) {
    GameInfo_t game = updateCurrentState();
    timeout(game.speed);
    const FiniteMachineStatus_t *status = getMachineStatus();
    if (*status == SureEndGame) {
      displaySureEndGameMessage();
      run = getStartCommand();
      if (run) {
        userInput(Pause, false);
      } else {
        userInput(Terminate, false);
      }
    }
    if (*status == EndGame) {
      displayEndMessage(game.score);
      run = getStartCommand();
      if (run) {
        startNewGame();
        userInput(Start, false);
      }
    } else if (*status == Paused) {
      displayHoldMessage();
    } else if (*status == Refresh) {
      displayGame(&game);
      displayHelpInfo(&game);
    }
    userInput(getAction(), hold);
  }
}