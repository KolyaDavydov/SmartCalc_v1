CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra
OS = $(shell uname)

ifeq ($(OS), Linux)
	CHECKFLAGS=-lcheck -lm -lpthread -lrt
else
	CHECKFLAGS=-lcheck -lm -lpthread
endif

run: clean
	$(CC) $(CFLAGS) s21_smartcalc.c s21_smartcalc.h -lm -o  run
	./run

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
		gcov \
		report/ \
		report.info
