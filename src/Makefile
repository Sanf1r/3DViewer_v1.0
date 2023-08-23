CFLAGS=-g -c -Wall -Wextra -Werror -std=c11 -pedantic
FLAGS=-Wall -Wextra -Werror -std=c11 -pedantic
FLAGS_CHECK = -lcheck -lgcov
TARGET = s21_helpers.a
SRC = $(wildcard s21_helpers.c)
OBJECTS:=$(SOURCES:.c=.o)
OBJ = $(patsubst s21_helpers.c, s21_helpers.o, $(SRC))
ASAN=#-fsanitize=address -fanalyzer
UNAME = $(shell uname -s)
ifeq ($(UNAME),Darwin)
	CHECK=-lcheck -lm -lpthread -fprofile-arcs -ftest-coverage
endif
ifeq ($(UNAME),Linux)
	CHECK=-lcheck -lm -lpthread -lrt -lsubunit -fprofile-arcs -ftest-coverage
endif

.PHONY: all
all: install

.PHONY: install
install:
	cmake -S . -B ./build && cd ./build && make

.PHONY: uninstall
uninstall:
	rm -rf build

.PHONY: open
open:
	cd build && ./3D_C8

.PHONY: clean
clean:
	rm -rf build
	rm -rf 3D_C8_manual
	rm -rf 3D_C8_v1.0
	rm -f 3D_C8_v1.0.tar.gz
	rm -f *.a *.o
	rm -f *.info *.gcda *.gcno *.gcov *.css *.html
	rm -rf coverage
	rm -rf test

.PHONY: dvi
dvi: 
	makeinfo --html 3D_C8.texi
	open 3D_C8_manual/index.html 

.PHONY: dist
dist:
	mkdir 3D_C8_v1.0
	cp CMakeLists.txt ./3D_C8_v1.0
	cp Makefile ./3D_C8_v1.0
	cp 3D_C8.texi ./3D_C8_v1.0
	cp *.cpp ./3D_C8_v1.0
	cp *.c ./3D_C8_v1.0
	cp *.h ./3D_C8_v1.0
	tar czvf 3D_C8_v1.0.tar.gz ./3D_C8_v1.0
	rm -rf 3D_C8_v1.0

.PHONY: tests
tests: $(OBJ)
	rm -f $(TARGET)
	ar rcs s21_helpers.a $(OBJ)
	ranlib s21_helpers.a
	gcc $(TARGET) $(ASAN) tests/*.c s21_helpers.c $(FLAGS) $(CHECK) $(FLAGS_CHECK) -o test
	./test
	geninfo . -b . -o coverage.info
	genhtml coverage.info -o coverage

.PHONY: gcov_report
gcov_report:
	open coverage/index.html

lint:
	clang-format -n *.c
	clang-format -n *.h
	clang-format -n *.cpp

leaks:
	leaks -atExit -- ./test

