PACKAGE_NAME = brick_game
VERSION = v1.0
GAME_TETRIS_VERSION = v1.0
GAME_TETRIS_NAME = tetris

CC = gcc
LATEX = pdflatex
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
LDFLAGS = -lncurses
VALGRIND_COMMAND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt

# основные директории
DIR_TESTS = test
DIR_TESTS_TETRIS = $(DIR_TESTS)_$(GAME_TETRIS_NAME)/
DIR_TETRIS_LIB = brick_game/tetris/
DIR_TETRIS_CLI = gui/cli/
DIR_OBJ = obj/
DIR_COV_REPORT = report/
DIR_DOCUMENTATION = doxygen/
DIR_DOC = doc/
DIR_INSTALL = ../$(PACKAGE_NAME)/
DIR_LATEX_OUT = ./$(DIR_DOC)/$(GAME_TETRIS_NAME)_doc

LATEX_FLAGS = -interaction=nonstopmode -synctex=1 -output-format=pdf -output-directory=$(DIR_LATEX_OUT)

LIB_TETRIS_EXEC = s21_tetris.a
LIB_TETRIS_EXEC_TEST = test_$(GAME_TETRIS_NAME)
DOC_EXEC = $(DIR_DOC)*.tex

# собираем все файлы относящиеся к консольному тетрису
SRC_TETRIS_LIB = $(shell find $(DIR_TETRIS_LIB) -name "*.c")
OBJ_TETRIS_LIB = $(patsubst %.c, $(DIR_OBJ)%.o, $(SRC_TETRIS_LIB))
SRC_TEST_TETRIS_LIB = $(shell find $(DIR_TESTS_TETRIS) -name "*.c")
OBJ_TEST_TETRIS_LIB = $(patsubst %.c, $(DIR_OBJ)%.o, $(SRC_TEST_TETRIS_LIB))
SRC_TETRIS_CLI = $(shell find $(DIR_TETRIS_CLI) -name "*.c")
OBJ_TETRIS_CLI = $(patsubst %.c, $(DIR_OBJ)%.o, $(SRC_TETRIS_CLI))

CHECK_INSTALLED = $(find /usr/include /usr/local/include -name check.h)
NCURSES_INSTALLED = $(find /usr/include /usr/local/include -name ncurses.h)

vpath %.c src/gui/cli/%.c

OS = $(shell uname -s)

.PHONY: all clean install uninstall format-check format cppcheck valgrind gcov_report leaks sanitize dvi dist

all: check_libs clean test install

s21_tetris.a: check_libs $(DIR_OBJ) $(OBJ_TETRIS_LIB)
	@echo $(SRC_TETRIS_CLI)
	@echo $(OBJ_TETRIS_CLI)
	@ar rc $@ $(OBJ_TETRIS_LIB)
	@ranlib $@

debug:
	@$(eval CFLAGS += -g)

uninstall: clean

dvi: $(DOC_EXEC) $(DIR_LATEX_OUT)
	@$(LATEX) $(LATEX_FLAGS) $(DOC_EXEC)

dist: clean
	@mkdir -p ../$(PACKAGE_NAME)
	tar -czvf ../$(PACKAGE_NAME)/$(PACKAGE_NAME)_$(VERSION).tar.gz ../src

install: check_libs $(DIR_OBJ) $(OBJ_TETRIS_CLI) $(SRC_TETRIS_CLI) s21_tetris.a
	@$(CC) $(OBJ_TETRIS_CLI) -lncurses -o $(GAME_TETRIS_NAME) -L. $(LIB_TETRIS_EXEC)
	@mkdir -p $(DIR_INSTALL)
	@mv $(GAME_TETRIS_NAME) $(DIR_INSTALL)$(GAME_TETRIS_NAME)

test: check_libs $(LIB_TETRIS_EXEC) $(OBJ_TEST_TETRIS_LIB)
ifeq ($(OS), Darwin)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ_TEST_TETRIS_LIB) $(LIB_TETRIS_EXEC) -o $(DIR_TESTS_TETRIS)$(LIB_TETRIS_EXEC_TEST) -lcheck
else
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ_TEST_TETRIS_LIB) $(LIB_TETRIS_EXEC) -o $(DIR_TESTS_TETRIS)$(LIB_TETRIS_EXEC_TEST) -lcheck -lsubunit -lrt -lpthread -lm
endif
	@$(DIR_TESTS_TETRIS)./$(LIB_TETRIS_EXEC_TEST)

check_libs:
ifeq ($(CHECK_INSTALLED),)
ifeq ($(OS), Darwin)
	@$(brew install check)
else
	@$(sudo apt-get install libcheck-dev)
endif
endif
ifeq ($(NCURSES_INSTALLED),)
ifeq ($(OS), Darwin)
	@$(brew install ncurses)
else
	@$(sudo apt-get install libncurses5-dev libncursesw5-dev)
endif
endif

$(DIR_OBJ)%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)$(DIR_TETRIS_LIB)
	@mkdir -p $(DIR_OBJ)$(DIR_TETRIS_CLI)
	@mkdir -p $(DIR_OBJ)$(DIR_TESTS_TETRIS)

$(DIR_LATEX_OUT):
	@mkdir -p $(DIR_LATEX_OUT)

format-check:
	@cp ../materials/linters/.clang-format ./
	@find . -name '*.c' -o -name '*.h' | xargs clang-format -n
	@rm .clang-format

format:
	@cp ../materials/linters/.clang-format ./
	@find . -name '*.c' -o -name '*.h' | xargs clang-format -i
	@rm .clang-format

cppcheck:
	@find . -name '*.c' -o -name '*.h' | xargs cppcheck --enable=all --suppress=missingIncludeSystem

valgrind: test
	@$(VALGRIND_COMMAND) ./$(DIR_TESTS_TETRIS)/$(LIB_TETRIS_EXEC_TEST)

leaks:
	@$(L_COMMAND) ./$(DIR_TESTS_TETRIS)/$(LIB_TETRIS_EXEC_TEST)

coverage_flag:
	@$(eval CFLAGS += --coverage)

sanitize: sanitize_flag test
	@./$(DIR_TESTS_TETRIS)/$(LIB_TETRIS_EXEC_TEST)

sanitize_flag:
	@$(eval CFLAGS += -fsanitize=address -fsanitize=leak)

gcov_report: coverage_flag test
	@rm -rf $(DIR_OBJ)$(DIR_TESTS_TETRIS)*.gcda $(DIR_OBJ)$(DIR_TESTS_TETRIS)*.gcno
	@rm -rf $(DIR_COV_REPORT)
	@mkdir $(DIR_COV_REPORT)
	@gcovr -o $(DIR_COV_REPORT)gcov_report.html --html --html-details

#doc:
#	@doxygen
#	@firefox $(DOCUMENTATION)html/index.html

clean:
	@find . -name '*.gcno' -delete -o -name '*.gcda' -delete -o -name '*.gcov' -delete -o -name '*.info' -delete
	@rm -rf RESULT_VALGRIND.txt
	@rm -rf $(DIR_COV_REPORT)
	@rm -rf $(DIR_DOCUMENTATION)
	@rm -rf $(DIR_OBJ)
	@rm -rf $(LIB_TETRIS_EXEC)
	@rm -rf $(DIR_TESTS_TETRIS)$(LIB_TETRIS_EXEC_TEST)
	@rm -rf $(DIR_INSTALL)
	@rm -rf $(PACKAGE_NAME)_$(VERSION).tar.gz
