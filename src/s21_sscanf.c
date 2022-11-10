#include "s21_sscanf.h"

// char *pars_format(char *format, flags_t *f) { return format; }
// char *pars_string(char *str, flags_t *f) { return str; }

// int s21_sscanf(const char *str, const char *format, ...) {
//   va_list va;
//   va_start(va, format);
//   flags_t flag_format = {0};
//   while (format) {
//     pars_format(format, &flag_format);

//     format++;
//   }

//   va_end(va);

//   return 1;
// }

int main() {
  char str[50] = "-777";
  // char str2[50], ch;
  // int num1, num2, num3;
  int num1, num2;
  // long num3, num4;
  // num3 = s21_atol(str);
  // long long num5, num6;
  // short num7, num8;
  // double num9, num10;
  sscanf(str, "%o", &num2);
  num1 = s21_ato8(str);
  // s21_sscanf(str, "%d %d %d", &num1, &num2, &num3);
  // printf("%d %d %d", num1, num2, num3);
  printf("num1: %d\nnum2: %d\n", num1, num2);
}

/*
перевод аски в целые 4 функции
перевод аски в дробные 3 функции

перевод 16 ричной в десятичную (большие-маленькие)
перевод 8 ричной в десятичную

перевод из научной нотации

IZI ATOI

*/