#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
const char *parseLength(const char *format, flags *f);

char *specifier(char *str, flags*, va_list);
void charSpecifier(char *buffer, flags *flag, va_list var);
void widthCharSpecifier(char *buffer, flags *flag, va_list var);

int main() {
  start();
  return 0;
}

void start() {
  char *stroka;
  wchar_t wch = L'w';
  char ch = 'l';
  stroka = (char *)malloc(300 * sizeof(char));
  s21_sprintf(stroka, "%-05cH", wch);
  printf("%s\n", stroka);
  sprintf(stroka, "%-05cH", wch);
  printf("%s\n", stroka);
  free(stroka);
}

int s21_sprintf(char *str, const char *format, ...) {
  flags flag = {0};
  va_list var;
  va_start(var, format);
  char *strStart = str;
  while (*format) {
    if (*format != '%') {
      *str++ = *format++;
    } else {
      format++;  // check symbol after '%'

      // 1) Строка распарсена, флаги расставлены, спецификатор получен
      format = parseFormat(format, &flag, var);
      // 2) В зависимости от спецификатора запускаем определенную функцию,
      // которая считает переменную нужного типа из va_list
      str = specifier(str, &flag, var);
      // 3) Внутри функции выполнить преобразование переменной в char*
      // и сделать нужные действия в зависимости от флагов

      // 4) Вернуть char* и добавить его к str
    }
  }
  va_end(var);
  return str - strStart;
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
  format = parseWidth(format, f, var);
  format = parsePrecision(format, f, var);
  format = parseLength(format, f);
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

char *specifier(char *str, flags* flag, va_list var) {
  // create buffer
  char buffer[512] = "";
  if (flag->specifier == 'd' || flag->specifier == 'i') {

  } else if (flag->specifier == 'f') {

  } else if (flag->specifier == 'd') {

  } else if (flag->specifier == 's') {

  } else if (flag->specifier == 'c') {
    if (flag->length == 'l') {
      widthCharSpecifier(buffer, flag, var);
    } else {
      charSpecifier(buffer, flag, var);
    }
  }

  // add buffer to str
  for (int i = 0; buffer[i]; i++, str++) {
    *str = buffer[i];
  }
  *str = '\0';
  return str;
}

void charSpecifier(char *buffer, flags *flag, va_list var) {
  char ch = va_arg(var, int);
  if (flag->minus && flag->width) {
    buffer[0] = ch;
    for (int i = 1; i < flag->width; i++) {
      buffer[i] = ' ';
    }
  } else if (flag->width) {
    for (int i = 0; i < flag->width; i++) {
      if (i == flag->width - 1) {
        buffer[i] = ch;
      } else {
        buffer[i] = ' ';
      }
    }
  } else {
    buffer[0] = ch;
  }
}

void widthCharSpecifier(char *buffer, flags *flag, va_list var) {
  wchar_t ch = va_arg(var, wchar_t);
  if (flag->minus && flag->width) {
    wcstombs(buffer, &ch, 512);
    for (int i = strlen(buffer); i < flag->width; i++) {
      buffer[i] = ' ';
    }
  } else if (flag->width) {
    char temp[512] = "";
    wcstombs(temp, &ch, 512);
    for (int i = 0; i < flag->width - strlen(temp); i++) {
      buffer[i] = ' ';
    }
    strcat(buffer, temp);
  } else {
    wcstombs(buffer, &ch, 512);
  }
}