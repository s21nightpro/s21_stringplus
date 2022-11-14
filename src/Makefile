CC= gcc -std=c11
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

all: test 

test: 
		$(CC) $(TEST_FLAGS) $(CFLAGS)  $(TEST) -o test
debug: 
	$(CC) $(CFLAGS) $(SRC) s21_sprintf.c -o test1 -g
gcov_report: clean
		$(CC) --coverage $(TEST_FLAGS) $(CFLAGS) $(TEST) -o test
		./test
		lcov -t "test" -o test.info -c -d . 
		genhtml -o report test.info
		open report/index.html
clean:
	rm -rf test
	rm -rf *.a *.out *.o report *.gc* libs21_string.a
run:
	./test
s21_string.a: clean
		$(CC) $(CFLAGS) *.c -c 
		ar rc s21_string.a *.o
		ranlib s21_string.a

rebuild:
	make clean
	make all

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem /Users/nightpro/C2_s21_stringplus-0/src

leak:
	CK_FORK=no leaks --atExit -- ./$(NAME)   

linter:
	cp ../materials/linters/.clang-format ..
	clang-format -n *.c *.h tests/*.c
	rm -rf ../.clang-format

