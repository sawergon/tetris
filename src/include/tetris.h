#ifndef C7_BRICKGAME_V1_0_1_SRC_BRICK_GAME_TETRIS_TETRIS_H_
#define C7_BRICKGAME_V1_0_1_SRC_BRICK_GAME_TETRIS_TETRIS_H_

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

#define GAME_TETRIS_NAME "s21_tetris"
#define GAME_TETRIS_FIELD_WIDTH 10
#define GAME_TETRIS_FIELD_HEIGHT 20

#define GAME_TETRIS_HIGH_SCORE_FILE "tetris_high_score.txt"
#define GAME_TETRIS_SUCCESS 0
#define GAME_TETRIS_FILE_NOT_FOUND (-1)
#define GAME_TETRIS_ERROR_READ (-2)

#define AMOUNT_OF_FIGURES 7
#define ROTATE_DIRECTIONS 4
#define FIGURE_COORD_SIZE 4

#define GAME_NEXT_LEVEL_SCORE_JUMP_COEFFICIENT 10000
#define GAME_NEXT_LEVEL_SPEED_JUMP_COEFFICIENT 1.5

// глобальные координаты
#define FIGURE_START_POSITION_X 3
#define FIGURE_START_POSITION_Y 0
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int **field;     // игровое поле
  int **next;      // следующая фигура
  int score;       // текущий счет
  int high_score;  // максимальный счет
  int level;       // текущий уровень
  int speed;       // текущая скорость
  int pause;       // Остановлена ли игра
} GameInfo_t;

typedef enum {
  I,  // прямая линия
  O,  // квадрат
  T,  // т образная
  J,  // Г
  L,  // обратная Г
  S,  // зигзаг
  Z   // обратный зигзаг
} FigureType_t;

typedef enum {
  Refresh,  // обновление игрового поля
  EndGame,  // конец игры
  Paused,   // пауза
  NewGame,  // новая игра(первое состояние автомата)
  SpawnFigure,  // появление новой фигуры
  SureEndGame   // подтверждение конца игры
} FiniteMachineStatus_t;

typedef enum { ToUp, ToDown, ToLeft, ToRight } RotateDirection_t;

typedef struct {
  int data[FIGURE_COORD_SIZE][FIGURE_COORD_SIZE];
} Figure_t;
// по типу фигуры и направлению поворота можно получить текущую фигуру из
// массива фигур
typedef struct {
  int x;  // самый левый пиксель поля фигуры в координатах игрового поля
  int y;  // самый верхний пиксель поля фигуры в координатах игрового поля
  FigureType_t type;       // тип фигуры
  FigureType_t next_type;  // следующий тип фигуры
  int **clean_field;  // игровое поле без этой самой фигуры
  RotateDirection_t rotate;  // направление поворота
  Figure_t positionArr[AMOUNT_OF_FIGURES][ROTATE_DIRECTIONS];
} FigureInfo_t;

typedef struct {
  int data[4][2];
} Hint_t;
/**
 * @addtogroup GameInit Инициализация игры
 * @{
 */
/**
 * Функция создания игры.
 * Происходит инициализация объекта нулевыми значениями, поэтому после следует
 * вызвать функцию `initGame`
 * @return созданная игра
 * @warning требуется вызов функции `initGame` для инициализации игры
 */
GameInfo_t *createGame();

/**
 * Функция инициализации игры.
 * @param game игра
 * @warning требуется вызов функции `createGame` перед вызовом функции
 */
void initGame(GameInfo_t *game);

/**
 * Функция уничтожения игры.
 * @param game игра
 * @warning требуется вызов функции `destroyGame`
 */
void destroyGame(GameInfo_t **game);
/// @}

/**
 * @addtogroup MatrixWork Работа с матрицами поля
 * @{
 */
/**
 * Функция для создания матрицы
 * @param height высота матрицы
 * @param width ширина матрицы
 * @return созданная матрица
 */
int **createMatrix(int height, int width);

/**
 * Функция для вывода матрицы на экран
 * @param game игра
 */
void printMatrix(int **matrix, int height, int width);

/**
 * Функция для освобождения матрицы
 * @param matrix матрица
 * @param height высота матрицы
 * @param width ширина матрицы
 */
void destroyMatrix(int ***matrix, int height);

/**
 * Функция для копирования матрицы
 * @param matrix матрица для копирования
 * @param height высота
 * @param width ширина
 * @return скопированная матрица
 */
int **copyMatrix(int **matrix, int height, int width);

/**
 * Функция для перемещения матриц
 * @param src Матрица для перемещения
 * @param dst Матрица куда
 * @param height
 * @param width
 */
void moveMatrix(int **src, int **dst, int height, int width);

/**
 * Функция для перемещения матрицы фигуры
 * @param src Матрица для перемещения
 * @param dst Матрица куда
 */
void moveFigureMatrix(Figure_t src, int **dst);
/// @}

/**
 * @addtogroup ScoreWork Работа с счетом
 * @{
 */

/**
 * Функция для вычисления счета
 * @param level Текущий уровень
 * @param lines_dropped Количество собранных линий
 * @return Общий счет
 */
int calculateScore(int lines_dropped);

/**
 * Функция для обновления счета
 * @param game игра
 * @param score на сколько нужно увеличить счет
 */
void updateScore(GameInfo_t *game, int score);

/**
 * Функция считывания максимального счета из файла
 * @param game игра
 * @return максимальный счет
 */
int readHighScore(GameInfo_t *game);

/**
 * Функция записи максимального счета в файл
 * @param game игра
 * @param score максимальный счет
 */
int writeHighScore(GameInfo_t *game, int score);
/// @}

/**
 * @addtogroup GameWork Работа игры
 * @{
 */

/**
 * Функция для обработки пользовательского ввода
 * @param action действие пользователя
 * @param hold зажатие клавиши
 */
void userInput(UserAction_t action, __attribute__((unused)) bool hold);

/**
 * Функция для обновления текущей игровой информации
 * @return текущая игровая информация
 */
GameInfo_t updateCurrentState();

/**
 * Получение текущей игровой информации
 * @return игровая информация
 */
GameInfo_t *getGameState();

/**
 * Функция для получения состояния автомата
 * @return состояние автомата
 */
FiniteMachineStatus_t *getMachineStatus();

/**
 * Функция для начала новой игры
 */
void startNewGame();

/**
 * Функция для получения подсказки
 * @return подсказка
 */
Hint_t getHint();
/// @}

/**
 * @addtogroup FigureWork Работа с фигурами
 * @{
 */

/**
 * Функция для получения информации о фигуре
 * @return информация о фигуре
 */
FigureInfo_t *getFigureInfo();

/**
 * Функция для заполнения информации о всех фигурах (нужно для инициализации)
 * @param figure информация о фигуре
 */
void fillPosArr(FigureInfo_t *figure);

/**
 * Функция для размещения фигуры на поле
 * @param figure информация о фигуре
 * @param game игра
 */
void placeFigure(FigureInfo_t *figure, GameInfo_t *game);

/**
 * Функция для получения текущей фигуры
 * @return матрица 4х4 текущей фигуры
 */
Figure_t getCurrentFigure();

/**
 * Функция для получения фигуры после вращения
 * @return матрица 4х4 следующей фигуры
 */
Figure_t getNextFigureRotate();

/**
 * Функция для осуществления вращения фигуры
 * @param figure_info информация о фигуре
 */
void doRotate(FigureInfo_t *figure_info);

/**
 * Функция для перемещения фигуры влево
 * @param figure_info информация о фигуре
 */
void moveLeft(FigureInfo_t *figure_info);

/**
 * Функция для перемещения фигуры вправо
 * @param figure_info информация о фигуре
 */
void moveRight(FigureInfo_t *figure_info);

/**
 * Функция для перемещения фигуры вниз на один шаг
 * @param figure_info информация о фигуре
 */
void moveDown(FigureInfo_t *figure_info);

/**
 * Функция для перемещения фигуры в самый низ
 * @param figure_info
 */
void dropDown(FigureInfo_t *figure_info);

/**
 * Получение случайного типа фигуры
 * @return
 */
FigureType_t getRandomFigureType();

/**
 * Функция для проверки возможности перемещения фигуры вниз
 * @param figure_info информация о фигуре
 * @return возможно ли смещение
 */
bool canMovingDown(FigureInfo_t *figure_info);
/// @}
#endif  // C7_BRICKGAME_V1_0_1_SRC_BRICK_GAME_TETRIS_TETRIS_H_
