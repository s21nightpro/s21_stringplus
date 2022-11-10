#include <string.h>

#include "s21_string.h"

int main() {
  // char str1[15] = "11191";
  // char str2[30] = "111012";
  // char *str3 = str1 + 2;
  //  char str3[3] = "h2";

  // printf("%s\n", s21_strncat(str, str3, 1));
  // s21_memset(str, '-', 15);
  // memset(str2, '-', 15);
  // char *p = s21_memchr(str, 'l', 5);
  // printf("%s\n", p);
  // char *p2 = memchr(str2, 'l', 5);
  // printf("%s\n", p2);
  // printf("%d\n", memcmp(str, str2, 3));
  // printf("%d\n", s21_memcmp(str, str2, 3));
  // memcpy(str1, str2, 4);
  // s21_memcpy(str1, str2, 4);
  // s21_memmove(str1, str3, 4);
  // printf("%s\n", str1);
  // printf("%s\n", s21_strpbrk(str1, str2));

  // printf("%s\n", strpbrk(str1, str2));
  // printf("%d\n", s21_strcmp(str1, str2));

  // printf("%d\n", strcmp(str1, str2));

  // printf("%d\n", s21_strncmp(str1, str2, 4));

  // printf("%d\n", strncmp(str1, str2, 4));
  char array[100] = "test1/test2/test3/";
  char array2[100] = "test1/test2/test3/";
  char ch[10] = "/";
  char ch2[10] = "/";
  char *istr;
  printf("Исходная строка: %s\n", array);
  printf("Результат разбиения:\n");
  istr = strtok(array, ch);
  while (istr != NULL) {
    // Вывод очередной выделенной части
    printf("%s\n", istr);
    // Выделение очередной части строки
    istr = strtok(NULL, ch);
  }
  istr = s21_strtok(array2, ch2);
  while (istr != NULL) {
    // Вывод очередной выделенной части
    printf("%s\n", istr);
    // Выделение очередной части строки
    istr = s21_strtok(NULL, ch2);
  }
}