CC = gcc -Wextra -Werror -Wall -std=c11



SRC = s21_strlen.c s21_strcat.c s21_strncat.c s21_memset.c \
s21_memchr.c s21_memcmp.c s21_memcpy.c s21_memmove.c \
s21_strpbrk.c s21_strcmp.c s21_strncmp.c s21_strcspn.c \
s21_strstr.c s21_strchr.c  s21_strrchr.c s21_strncpy.c \
s21_strcpy.c s21_strerror.c s21_strtok.c s21_insert.c \
s21_trim.c s21_to_lower.c s21_to_upper.c s21_strspn.c \
s21_sscanf.c test.c

all: build3 run  

build3: 
		gcc s21_sscanf.c -o test

build: 
		$(CC) $(SRC) -o test -g

build2: 
		gcc $(SRC) -o test -g

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem  /Users/suzibill/projects/C2_s21_stringplus-0/src/

leak:
	CK_FORK=no leaks --atExit -- ./$(NAME)   

linter:
	cp ../materials/linters/.clang-format ..
	clang-format -n *.c *.h
	rm -rf ../.clang-format

run: 
		./test
