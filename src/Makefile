CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage
LIBSOURCES=s21_smartcalc.c
LIBOBJECTS=$(LIBSOURCES:.c=.o)

TETEX += /usr/bin/texi2dvi

OS = $(shell uname)

ifeq ($(OS), Linux)
	CHECKFLAGS=-lcheck -lm -lpthread -lrt -lsubunit
else
	CHECKFLAGS=-lcheck -lm -lpthread
endif

all: gcov_report

s21_smartcalc.a: $(LIBOBJECTS)
	ar -crs s21_smartcalc.a $(LIBOBJECTS)
	rm -f *.o

test: clean test.c s21_smartcalc.a
	$(CC) $(CFLAGS) test.c $(LIBSOURCES) -o run $(CHECKFLAGS) -lgcov --coverage
	./run

gcov_report: test
	lcov -t "test" -o report.info -c -d .
	genhtml -o report report.info
	open ./report/index.html

install: test clean cppcheak
	mkdir ../build
	cd ../build; qmake ../src/SmartCalcV1.pro
	make -C ../build

uninstall: clean
	rm -rf ../build

cppcheak:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.c *.h *.cpp
	rm .clang-format

dist:
	mkdir ../build
	tar -cf ../build/calcV1.tar ../app/SmartCalcV1

leaks:
	valgrind  --undef-value-errors=yes --leak-check=full --show-leak-kinds=all -s ./../build/SmartCalcV1

clean:
	rm -rf *.o \
					*.a \
					*.txt \
					*.so \
					*.gcno \
					*gcda \
					*.gcov \
					gcov_report.* \
					*.dSYM \
					*.out \
					unit-test \
					vtests_run \
					run \
					SmartCalcV1 \
					.qmake.stash \
					gcov \
					report/ \
					../app/ \
					../build/ \
					report.info
