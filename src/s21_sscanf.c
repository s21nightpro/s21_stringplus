#include "s21_sscanf.h"

int s21_sscanf(const char *str, const char *format, ...) {
  va_list va;
  va_start(va, format);
  int *p = va_arg(va, int *);
  *p = 5;
  p = va_arg(va, int *);
  *p = 4;
  p = va_arg(va, int *);
  *p = 3;

  va_end(va);

  return 1;
}

int main() {
  char str[50] = "5 4 3";
  char str2[50], ch;
  int num1, num2, num3;
  s21_sscanf(str, "%d %d %d", &num1, &num2, &num3);
  printf("%d %d %d", num1, num2, num3);
}