#include "s21_sscanf.h"

void parseFormat(const char **format, flags_t *f);
const char *parseWidth(const char *format, flags_t *f);
const char *parseLength(const char *format, flags_t *f);
const char *parseSpecifier(const char *format, flags_t *f);

void parseString(const char **str, flags_t *f, va_list var);

int isDigit(char a);
void assignInt(char *str, va_list var);

int s21_sscanf(const char *str, const char *format, ...) {
  va_list var;
  va_start(var, format);
  int success = 0;
  while (*format != '\0') {
    if (*format == '%') {
      flags_t flag_format = {0};
      format++;
      parseFormat(&format, &flag_format);
      parseString(&str, &flag_format, var);
      if (flag_format.error) break;
      success++;
    }
  }
  va_end(var);

  return success;
}

void parseString(const char **str, flags_t *f, va_list var) {
  char str_temp[1024] = {0};
  int i = 0;
  switch (f->specifier) {
    case 'd':
      while (isDigit(**str)) {
        str_temp[i] = **str;
        (*str)++;
        i++;
      }
      assignInt(str_temp, var);
      break;
  }
}

int isDigit(char a) { return (a >= '0' && a <= '9'); }

void assignInt(char *str, va_list var) {
  int x = 1123;  // s21_atoii(str);
  int *y = va_arg(var, int *);
  *y = x;
}

/*
идем по строке в соответствии с флагами
меняем указатель на конец считанной строки
*/

/*
если нет флагов считываем первое число/строку до разделителя
если есть звёздочка перемещаем указатель но не пишем переменную
если есть

*/

/*
что может считывать наша функция?
целые числа
дробные числа
отрицательные
символы строки

c - считывает 1 символ
s - считывает строку
d - считывает 10тичное число
i - знаковое 10тичное, 8ричное, 16ричное
default:



eEfgG - десятичное с плаваюшей или научная нотация
o - беззнак 8ричное
u - беззнак десятичное целое
xX - беззнак 16ричное целое
p - адрес указателя
n - количество считанных символов

*/

// eturn str;

int main() {
  char str[50] = "1123";
  char str2[50], ch;
  int num1, num2, num3;

  // printf("123");
  s21_sscanf(str, "%d", &num1);
  printf("%d", num1);

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

void parseFormat(const char **format, flags_t *f) {
  *format = parseWidth(*format, f);
  *format = parseLength(*format, f);
  *format = parseSpecifier(*format, f);

  // return *format;
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

const char *parseSpecifier(const char *format, flags_t *f) {
  char specList[16] = "cdieEfgGosuxXpn";
  int unmatch = 1;
  for (int i = 0; i < 15; i++) {
    if (*format == specList[i]) {
      f->specifier = specList[i];
      unmatch = 0;
      break;
    }
  }
  f->error = unmatch;

  return ++format;
}