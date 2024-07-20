.PHONY: all clean test decimal.a check gcov_report
CC=gcc
OS := $(shell uname -s)

ifeq ($(OS), Darwin)
	CC += -D OS_MAC
else
	CC += -D OS_LINUX
endif

default: all
 
all: clean s21_decimal.a test
 
test: s21_decimal.a
ifeq ($(OS), Darwin)
	$(CC) -o test test.c s21_decimal.a -lcheck
	./test
else
	$(CC) -o test test.c s21_decimal.a -lcheck -lm -lsubunit -lrt -lpthread
	./test
endif
 
s21_decimal.a: s21_decimal.o
	ar rcs s21_decimal.a s21_decimal.o
	ranlib $@
	cp $@ lib$@
	
s21_decimal.o: s21_decimal.c
	$(CC) -c -o s21_decimal.o s21_decimal.c

gcov_report: s21_decimal.a
ifeq ($(OS), Darwin)
	$(CC) --coverage -o testresult test.c s21_decimal.a -lcheck
	./testresult
else
	$(CC) --coverage -o testresult test.c s21_decimal.c -lcheck -lm -lsubunit -lrt -lpthread
	./testresult
endif
	lcov -t "testresult" -o testresult.info -c -d .
	genhtml -o report testresult.info

verification:
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extension=c s21_decimal.c s21_decimal.h test.c
	CK_FORK=no leaks -atExit -- ./test

clean:
	rm -rf test *.a *.o *.out *.gc* *.info report testresult CPPLINT.cfg
 
rebuild: clean all