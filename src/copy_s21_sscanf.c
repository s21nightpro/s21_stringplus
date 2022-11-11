#include "s21_sscanf.h"

void parseFormat(const char **format, flags_t *f);
const char *parseWidth(const char *format, flags_t *f);
const char *parseLength(const char *format, flags_t *f);
const char *parseSpecifier(const char *format, flags_t *f);

void parseString(const char **str, flags_t *f, va_list var);

int isDigit(int a);
int isAscii(int a);
int isSeporator(int a);
int isHex(int a);
int isOct(int a);
int isPointer(int a, int *first_digit);

void assignInt(char *str, va_list var, flags_t *f, int base);
void assignChar(char ch, va_list var, flags_t *f);
void assignString(char *str, va_list var, flags_t *f);

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
  char ch = 0;
  int i = 0;
  while (isSeporator(**str)) {
    (*str)++;
  }

  switch (f->specifier) {
    case 'd':
      while (isDigit(**str) && (f->width != 0)) {
        str_temp[i] = **str;
        (*str)++;
        i++;
        f->width--;
      }
      if (!f->asterics) assignInt(str_temp, var, f, 10);
      break;
    case 'c':
      if (isAscii(**str)) {
        ch = **str;
        if (!f->asterics) assignChar(ch, var, f);
        (*str)++;
        break;
      }
    case 's':  // если нам важна длина, нам не важны пробелы
      if (f->width != -1) {
        while ((f->width != 0) && (**str)) {
          str_temp[i] = **str;
          (*str)++;
          i++;
          f->width--;
        }
      } else {
        while (!isSeporator(**str) && (**str)) {
          str_temp[i] = **str;
          (*str)++;
          i++;
          f->width--;
        }
      }
      if (!f->asterics) assignString(str_temp, var, f);
      break;
    case 'e':
      if (**str == '0') {
        (*str)++;
        if ((**str) == 'x' || (**str) == 'X') {
          (*str)++;
          while (isHex(**str) && (f->width != 0)) {
            ;
          }
        } else {
          while (isOct(**str) && (f->width != 0)) {
            ;
          }
        }
      } else {
        while (isDigit(**str) && (f->width != 0)) {
          str_temp[i] = **str;
          (*str)++;
          i++;
          f->width--;
        }
        if (!f->asterics) assignInt(str_temp, var, f, 10);
      }
  }
}

int isDigit(int a) { return (a >= '0' && a <= '9'); }

int isAscii(int a) { return (a >= 0 && a <= 127); }

int isSeporator(int a) { return ((a == '\n') || (a == 32) || (a == '\0')); }

int isHex(int a) {
  return (isDigit(a) || (a >= 'a' && a <= 'f') || (a >= 'A' && a <= 'F') ||
          a == 'X' || a == 'x');
}

int isPointer(int a, int *first_digit) {
  int flag = 1;
  if (isHex(a)) {
    first_digit = 1;
  } else if (!isHex(a) && first_digit == 0) {
    ;
  } else if (!isHex(a) && first_digit == 1) {
    flag = 0;
  }
  return flag;
}

int isOct(int a) { return (isDigit(a) && a < '8'); }

void assignInt(char *str, va_list var, flags_t *f, int base) {
  if (f->length == 'h') {
    short num_short = s21_atos(str);
    short *p_short = va_arg(var, short *);
    *p_short = num_short;
  } else if (f->length == 'l') {
    long num_long = s21_atol(str);
    long *p_long = va_arg(var, long *);
    *p_long = num_long;
  } else {
    int num_int = s21_atoii(str);
    int *p_int = va_arg(var, int *);
    *p_int = num_int;
  }
}

void assignChar(char ch, va_list var, flags_t *f) {
  char *p_char = va_arg(var, char *);
  *p_char = ch;
}

void assignString(char *str, va_list var, flags_t *f) {
  char *p_char = va_arg(var, char *);
  s21_strcpy(p_char, str);
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
  char str[50] = "23334 234 abcdef";
  char str2[50], ch;
  int num1, num2, num3;

  // printf("123");
  s21_sscanf(str, "%4d%d%*d%s", &num1, &ch, str2);
  // sscanf(str, "%0d", &num2);
  printf("%d %d %s", num1, ch, str2);

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
  if (i) f->width = s21_atoii(tempWidth);
  if (f->width == 0) f->width = -1;
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
