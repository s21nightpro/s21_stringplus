CC= gcc -std=c11 -D_GNU_SOURCE
CFLAGS= -Wall -Wextra -Werror 
TEST= *.c tests/*.c
TEST_FLAGS = -lcheck
SRC = s21_strlen.c s21_strcat.c s21_strncat.c s21_memset.c \
s21_memchr.c s21_memcmp.c s21_memcpy.c s21_memmove.c \
s21_strpbrk.c s21_strcmp.c s21_strncmp.c s21_strcspn.c \
s21_strstr.c s21_strchr.c  s21_strrchr.c s21_strncpy.c \
s21_strcpy.c s21_strerror.c s21_strtok.c s21_insert.c \
s21_trim.c s21_to_lower.c s21_to_upper.c s21_strspn.c \



OS := $(shell uname -s)

ifeq ($(OS), Darwin)
    TEST_FLAGS = -lcheck
else
	TEST_FLAGS = -lcheck -lpthread -pthread -lrt -lm -lsubunit
endif
# all: build7 run
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

build7:
	$(CC)  s21_sprintf.c  $(SRC) -o test -g


rebuild:
	make clean
	make all
	rm -rf  *.o *.a *test 