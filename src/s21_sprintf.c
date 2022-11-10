#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A format specifier for print functions follows this prototype:
// %[flags][width][.precision][length]specifier

typedef struct {
  bool minus;  // Left-justify within the given field width
  bool plus;  // Forces to precede the result with a plus or minus sign (+ or -)
              // even for positive numbers
  bool space;    // If no sign is going to be written, a blank space is inserted
                 // before the value
  bool hashtag;  // Made some math things with some specifiers
  bool zero;     // Left-pads the number with zeroes (0) instead of spaces
  int width;     // (number) - minimum number of character to be printed   or *
  int precision;  // Precision
  char length;    // h, l or L
  int specifier;  // just specifier
} flags;

void start();
int s21_sprintf(char *str, const char *format, ...);
void itoa(int n, char s[]);
void reverse(char s[]);
const char *parseFormat(const char *format, flags *f, va_list var);
const char *parseFlags(const char *format, flags *f);
const char *parseWidth(const char *format, flags *f, va_list var);
const char *parsePrecision(const char *format, flags *f, va_list var);
size_t numsCount(int num);
const char *parseLength(const char *format, flags *f);

void specifier(const char **str, flags *, va_list);

int main() {
  start();
  return 0;
}

void start() {
  char *stroka;
  stroka = (char *)malloc(300 * sizeof(char));
  s21_sprintf(stroka, "%s %s %s", "stroka", "hello", "lksjflsj");
  printf("%s\n", stroka);
  free(stroka);
}

int s21_sprintf(char *str, const char *format, ...) {
  flags flag = NULL;
  va_list var;
  va_start(var, format);

  while (*format) {
    if (*format != '%') {
      *str++ = *format++;
    } else {
      format++;  // check symbol after '%'

      // 1) Строка распарсена, флаги расставлены, спецификатор получен
      format = parseFormat(format, &flag, var);
      // 2) В зависимости от спецификатора запускаем определенную функцию,
      // которая считает переменную нужного типа из va_list
      specifier(&str, &flag, var);
      // 3) Внутри функции выполнить преобразование переменной в char*
      // и сделать нужные действия в зависимости от флагов

      // 4) Вернуть char* и добавить его к str
    }
  }
  va_end(var);
  return 0;
}

void itoa(int n, char s[]) {
  int i, sign;

  if ((sign = n) < 0) n = -n;
  i = 0;
  do {
    s[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);
  if (sign < 0) s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}

void reverse(char s[]) {
  int i, j;
  char c;

  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

const char *parseFormat(const char *format, flags *f, va_list var) {
  format = parseFlags(format, f);
  parseWidth(format, f, var);
  parsePrecision(format, f, var);
  parseLength(format, f);
  f->specifier = *format;
  format++;
  return format;
}

const char *parseFlags(const char *format, flags *f) {
  while (*format == '-' || *format == '+' || *format == ' ' || *format == '#' ||
         *format == '0') {
    switch (*format) {
      case '-':
        f->minus = true;
        break;
      case '+':
        f->plus = true;
        break;
      case ' ':
        f->space = true;
        break;
      case '#':
        f->hashtag = true;
        break;
      case '0':
        f->zero = true;
        break;
    }
    format++;
  }
  return format;
}

const char *parseWidth(const char *format, flags *f, va_list var) {
  if (*format == '*') {
    format++;
    f->width = va_arg(var, int);
  } else if (*format >= 48 && *format <= 57) {
    char tempWidth[512] = "";
    for (int i = 0; *format >= 48 && *format <= 57; i++, format++) {
      tempWidth[i] = *format;
    }
    f->width = atoi(tempWidth);
  }
  return format;
}

const char *parsePrecision(const char *format, flags *f, va_list var) {
  if (*format == '.') {
    format++;
    if (*format == '*') {
      format++;
      f->precision = va_arg(var, int);
    } else if (*format >= 48 && *format <= 57) {
      char tempPrecision[512] = "";
      for (int i = 0; *format >= 48 && *format <= 57; i++, format++) {
        tempPrecision[i] = *format;
      }
      f->precision = atoi(tempPrecision);
    }
  }
  return format;
}

const char *parseLength(const char *format, flags *f) {
  switch (*format) {
    case 'h':
      f->length = 'h';
      break;
    case 'l':
      f->length = 'l';
      break;
    case 'L':
      f->length = 'L';
      break;
  }
  return format;
}

size_t numsCount(int num) {
  size_t count = 1;
  while (n != 0) {
    num /= 10;
    count++;
  }
  return count;
}

void specifier(const char **str, flags *flag, va_list var) {
  if (flag->specifier == 'd' || flag->specifier == 'i') {  // %d  %i
    // your code here

    int64_t num = va_arg(var, int64_t);

    if (flag->width && !(flag->precision)) {    // %3d
      if (flag->minus) {  // %-3d 
        itoa(num, *str);

        for (int i = numsCount(num); i < flags->width; i++) {
          **str++ = ' ';
        }

      } else {  // %3d 
        if (flags->zero) {  // %03d
          for (int i = numsCount(num); i < flags->width; i++) {
            if (flags->plus && (i == (flags->width - 1))) { // WET
              **str++ = num > 0 ? '+' :;
              break;
            }
            **str++ = "0";
          }

          itoa(num, *str);
        } else { // %3d
          for (int i = numsCount(num); i < flags->width; i++) {
            if (flags->plus && (i == (flags->width - 1))) { // WET
              **str++ = num > 0 ? '+': ;
              break;
            }
            **str++ = ' ';
          }
          itoa(num, *str);
        }
      }
    }  else if (flag->precision) {  // %.3d  // must check %3.3 too
    }
  }


}

+ bool minus;  // Left-justify within the given field width
+ bool plus;  // Forces to precede the result with a plus or minus sign (+ or -)
              // even for positive numbers
? bool space;   // If no sign is going to be written, a blank space is inserted
              // before the value
- bool hashtag;   // Made some math things with some specifiers
+ bool zero;    // Left-pads the number with zeroes (0) instead of spaces
+ int width;    // (number) - minimum number of character to be printed   or *
? int precision;  // Precision
char length;    // h, l or L
