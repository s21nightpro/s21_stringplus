CC= gcc -std=c11 -D_GNU_SOURCE
CFLAGS= -Wall -Wextra -Werror 
TEST= *.c tests/*.c
TEST_FLAGS = -lcheck

OS := $(shell uname -s)

ifeq ($(OS), Darwin)
    TEST_FLAGS = -lcheck
else
	TEST_FLAGS = -lcheck -lpthread -pthread -lrt -lm -lsubunit
endif

all: clean test 

test:
		$(CC) $(TEST_FLAGS) $(CFLAGS)  $(TEST) -o test
gcov_report:
		$(CC) --coverage $(TEST_FLAGS) $(CFLAGS) $(TEST) -o test
		./test
		lcov -t "test" -o test.info -c -d . 
		genhtml -o report test.info
		lynx report/index.html 
clean:
	rm -rf test
	rm -rf *.a *.out *.o report *.gc*
run:
	./test
s21_string.a: clean
		$(CC) $(CFLAGS)  *.c tests/*.c -c 
		ar rc libs21_string.a *.o
		gcc tests/main.c -L. -l s21_string -o rezult

rebuild:
	make clean
	make all
	rm -rf  *.o *.a *test 