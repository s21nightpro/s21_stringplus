#include "s21_sscanf.h"

const char *parseFormat(const char **format, flags_t *f, va_list var);
const char *parseWidth(const char *format, flags_t *f);
const char *parseLength(const char *format, flags_t *f);
const char *parseString(const char *str, flags_t *f);
int parseSpecifier(const char *format, flags_t *f);

int s21_sscanf(const char *str, const char *format, ...) {
  va_list var;
  va_start(var, format);
  int success = 0;
  while (*format != '\0') {
    if (*format == '%') {
      flags_t flag_format = {0};
      format++;
      parseFormat(&format, &flag_format, var);
      parseString(str, &flag_format);
      success++;
    }
    format++;
  }
  va_end(var);

  return success;
}

const char *parseString(const char *str, flags_t *f) {
  /*
  идем по строке в соответствии с флагами
  возвращаем указатель на конец считанной строки
  */
  return str;
}

int main() {
  char str[50] = "5 4 3";
  char str2[50], ch;
  int num1, num2, num3;

  printf("123");
  s21_sscanf(str, "%*4ld%5d%ld", &num1, &num2, &num3);

  // printf("%d %d %d", num1, num2, num3);
}

/*
получаю подстроку
подстрока начинает с % и кончается спецификатором
дальше идёт либо следующий процент или '/0'
структура
ширина:
звездочка: звездочка отменяет ширину
спецификатор:
может быть любое количество чисел и звёздочек
звёздочка отменяет число


*/

const char *parseFormat(const char **format, flags_t *f, va_list var) {
  *format = parseWidth(*format, f);
  *format = parseLength(*format, f);
  parseSpecifier(*format, f);
  *format++;
  return *format;
}

/*
если звёздочка струячим
если цифры и есть звездочка
*/

const char *parseWidth(const char *format, flags_t *f) {
  char tempWidth[512];
  int i = 0;
  while (*format == '*' || (*format >= 48 && *format <= 57)) {
    if (*format == '*') {
      f->asterics = 1;
    } else if (!f->asterics) {
      tempWidth[i] = *format;
      i++;
    }
    format++;
  }
  if (i) f->width = atoi(tempWidth);
  return format;
}

const char *parseLength(const char *format, flags_t *f) {
  switch (*format) {
    case 'h':
      f->length = 'h';
      format++;
      break;
    case 'l':
      f->length = 'l';
      format++;
      break;
    case 'L':
      f->length = 'L';
      format++;
      break;
  }
  return format;
}

int parseSpecifier(const char *format, flags_t *f) {
  char specList[16] = "cdieEfgGosuxXpn";
  int unmatch = 1;
  for (int i = 0; i < 15; i++) {
    if (*format == specList[i]) {
      f->specifier = specList[i];
      unmatch = 0;
      break;
    }
  }
  format++;
  return unmatch;
}