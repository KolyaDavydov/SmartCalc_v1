CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage
LIBSOURCES=s21_smartcalc.c
LIBOBJECTS=$(LIBSOURCES:.c=.o)

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

tests: clean test.c s21_smartcalc.a
	$(CC) $(CFLAGS) test.c $(LIBSOURCES) -o run $(CHECKFLAGS) -lgcov --coverage
	./run

# run: clean
# 	$(CC) $(CFLAGS) s21_smartcalc.c s21_smartcalc.h -lm -o  run
# 	./run

gcov_report: tests
	lcov -t "test" -o report.info -c -d .
	genhtml -o report report.info
	open ./report/index.html

# build: clean
# 	mkdir build
# 	cd build;	qmake ../SmartCalcV1.pro
# 	make -C build

install:
	mv Makefile cloneMake
	qmake
	make
	make clean
	rm Makefile
	mv cloneMake Makefile
	mkdir ../app
	mv SmartCalcV1 ../app/
	# make clean

uninstall:
	rm -rf ../app

dist:
	mkdir ../build
	tar -cf ../build/calcV1.tar ../app/SmartCalcV1

leaks: clean
	valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt

clean:
	rm -rf *.o \
					*.a \
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
