#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024

// A format specifier for print functions follows this prototype:
// %[flags][width][.precision][length]specifier

typedef struct {
  bool minus;          // Left-justify within the given field width
  bool plus;           // Forces to precede the result with a plus or minus sign (+ or -)
                       // even for positive numbers
  bool space;          // If no sign is going to be written, a blank space is inserted
                       // before the value
  bool hashtag;        // Made some math things with some specifiers
  bool zero;           // Left-pads the number with zeroes (0) instead of spaces
  int width;           // (number) - minimum number of character to be printed   or *
  int precision;       // Precision
  bool isPrecisionSet; // is precision set
  char length;         // h, l or L
  int specifier;       // just specifier
} flags;

void start();
int s21_sprintf(char *str, const char *format, ...);
void itoa(int n, char s[]);
void reverse(char s[]);
int numsCount(int num);

const char *parseFormat(const char *format, flags *f, va_list var);
const char *parseFlags(const char *format, flags *f);
const char *parseWidth(const char *format, flags *f, va_list var);
const char *parsePrecision(const char *format, flags *f, va_list var);
const char *parseLength(const char *format, flags *f);

char *specifier(char *str, flags*, va_list);
void charSpecifier(char *buffer, flags *flag, va_list var);
void widthCharSpecifier(char *buffer, flags *flag, va_list var);
void stringSpecifier(char *buffer, flags *flag, va_list var);
void widthStringSpecifier(char *buffer, flags *flag, va_list var);
void integerSpecifier(char *buffer, flags *flag, va_list var);

int main() {
  start();
  return 0;
}

void start() {
  char *stroka;
  char ch = 'l';
  wchar_t *wch = (wchar_t *)"world";
  stroka = (char *)malloc(300 * sizeof(char));
  s21_sprintf(stroka, "Hello, %20s", "Hello, world");
  printf("%sEND\n", stroka);
  sprintf(stroka, "Hello, %20s", "Hello, world");
  printf("%sEND\n", stroka);
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
    char tempWidth[BUFFER_SIZE] = "";
    for (int i = 0; *format >= 48 && *format <= 57; i++, format++) {
      tempWidth[i] = *format;
    }
    f->width = atoi(tempWidth);
  }
  return format;
}

const char *parsePrecision(const char *format, flags *f, va_list var) {
  if (*format == '.') {
    f->isPrecisionSet = true;
    format++;
    if (*format == '*') {
      format++;
      f->precision = va_arg(var, int);
    } else if (*format >= 48 && *format <= 57) {
      char tempPrecision[BUFFER_SIZE] = "";
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
  char buffer[BUFFER_SIZE] = "";
  if (flag->specifier == 'd' || flag->specifier == 'i') {
    integerSpecifier(buffer, flag, var);
  } else if (flag->specifier == 'f') {

  } else if (flag->specifier == 'd') {

  } else if (flag->specifier == 's') {
    if (flag->length == 'l') {
      widthStringSpecifier(buffer, flag, var);
    } else {
      stringSpecifier(buffer, flag, var);
    }
  } else if (flag->specifier == 'c') {
    if (flag->length == 'l') {
      widthCharSpecifier(buffer, flag, var);
    } else {
      charSpecifier(buffer, flag, var);
    }
  } else {
    buffer[0] = flag->specifier;
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
    wcstombs(buffer, &ch, BUFFER_SIZE);
    for (int i = strlen(buffer); i < flag->width; i++) {
      buffer[i] = ' ';
    }
  } else if (flag->width) {
    char temp[BUFFER_SIZE] = "";
    wcstombs(temp, &ch, BUFFER_SIZE);
    for (int i = 0; i < flag->width - strlen(temp); i++) {
      buffer[i] = ' ';
    }
    strcat(buffer, temp);
  } else {
    wcstombs(buffer, &ch, BUFFER_SIZE);
  }
}

void stringSpecifier(char *buffer, flags *flag, va_list var) {
  char *input = va_arg(var, char *);
  char tempInput[BUFFER_SIZE] = "";
  strcpy(tempInput, input);
  if (flag->isPrecisionSet) {
    tempInput[flag->precision] = '\0';
  }

  int shift = flag->width - strlen(tempInput);
  int lengthInput = strlen(tempInput);

  if (flag->minus && shift > 0) {
    strcpy(buffer, tempInput);
    memset(buffer + lengthInput, ' ', shift);
  } else if (shift > 0) {
    memset(buffer, ' ', shift);
    strcpy(buffer + shift, tempInput);
  } else {
    strcpy(buffer, tempInput);
  }
}

void widthStringSpecifier(char *buffer, flags *flag, va_list var) {
  wchar_t *input = va_arg(var, wchar_t *);
  char tempInput[BUFFER_SIZE] = "";
  char fromWcharToChar[BUFFER_SIZE] = "";
  wcstombs(fromWcharToChar, input, BUFFER_SIZE);
  strcpy(tempInput, fromWcharToChar);
  if (flag->isPrecisionSet) {
    tempInput[flag->precision] = '\0';
  }

  int shift = flag->width - strlen(tempInput);
  int lengthInput = strlen(tempInput);

  if (flag->minus && shift > 0) {
    strcpy(buffer, tempInput);
    memset(buffer + lengthInput, ' ', shift);
  } else if (shift > 0) {
    memset(buffer, ' ', shift);
    strcpy(buffer + shift, tempInput);
  } else {
    strcpy(buffer, tempInput);
  }
}

void integerSpecifier(char *buffer, flags *flag, va_list var) {
    int64_t num = va_arg(var, int64_t);
    char temp[BUFFER_SIZE] = "";
    if (flag->width && !(flag->precision)) {    // %3d
      if (flag->minus) {  // %-3d
        itoa(num, temp);
        strcpy(buffer, temp);
        for (int i = numsCount(num); i < flags->width; i++) {
          buffer[i] = ' ';
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

int numsCount(int num) {
  // count of digits in number
}