#include "s21_sscanf.h"

char *pars_format(char *format, flags_t *f) { return format; }
char *pars_string(char *str, flags_t *f) { return str; }

int s21_sscanf(const char *str, const char *format, ...) {
  va_list va;
  va_start(va, format);
  flags_t flag_format = {0};
  while (format) {
    pars_format(format, &flag_format);

    format++;
  }

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

/*
перевод аски в целые 4 функции
перевод аски в дробные 3 функции

перевод 16 ричной в десятичную (большие-маленькие)
перевод 8 ричной в десятичную

перевод из научной нотации



*/