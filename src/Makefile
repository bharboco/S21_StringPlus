CC = gcc
CFLAGS = -c -Wall -Werror -Wextra -std=c11
LDFLAGS = -O2 -Wall -Werror -Wextra -std=c11
SOURCE = s21_*.c
OBJECTS = $(patsubst %.c,%.o, ${SOURCE})

all: s21_string.a

s21_string.a: $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE)
	ar rc s21_string.a $(OBJECTS)
	ranlib s21_string.a

test: test.c s21_string.a
	$(CC) $(LDFLAGS) -o test test.c s21_string.a -lcheck
	./test

gcov_report: clean $(SOURCE)
	gcc --coverage $(SOURCE) test.c -o s21_test -lcheck
	./s21_test
	lcov -t "s21_test" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	open ./report/index.html

rebuild: clean all 

clang:
	clang-format -i *.c *.h

clean:
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./test && rm -rf ./gcov_report
	-rm -rf ./report/
	-rm -rf s21_test