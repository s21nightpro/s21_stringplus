#include "s21_sprintf.h"

// A format specifier for print functions follows this prototype:
// %[flags][width][.precision][length]specifier

int main() {
  start();
  return 0;
}

void start() {
  char *stroka;
  char *stroka2;
  stroka = (char *)malloc(300 * sizeof(char));
  stroka2 = (char *)malloc(300 * sizeof(char));
  unsigned int num = 0x0001;
  s21_sprintf(stroka, "Hello, % p", &num);
  printf("%sEND\n", stroka);
  sprintf(stroka2, "Hello, % p", &num);
  printf("%sEND\n", stroka2);
  free(stroka);
  free(stroka2);
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
      format++;
      format = parseFormat(format, &flag, var);
      str = specifier(str, &flag, var);
      if (flag.specifier == 'n') {
        int *pointer = va_arg(var, int *);
        *pointer = str - strStart;
      }
    }
  }
  va_end(var);
  return str - strStart;
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

char *specifier(char *str, flags *flag, va_list var) {
  char buffer[BUFFER_SIZE] = "";
  if (flag->specifier == 'd' || flag->specifier == 'i') {
    integerSpecifier(buffer, flag, var);
  } else if (flag->specifier == 'u') {
    unsignedSpecifier(buffer, flag, var);
  } else if (flag->specifier == 'o') {
    octalSpecifier(buffer, flag, var);
  } else if (flag->specifier == 'f') {
    floatSpecifier(buffer, flag, var);
  } else if (flag->specifier == 'p') {
    pointerSpecifier(buffer, flag, var);
  } else if (flag->specifier == 'e' || flag->specifier == 'E') {
    exponentSpecifier(buffer, flag, var);
  } else if (flag->specifier == 'g' || flag->specifier == 'G') {
  } else if (flag->specifier == 'x' || flag->specifier == 'X') {
    hexSpecifier(buffer, flag, var);
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
  if (flag->specifier == 'G' || flag->specifier == 'X' ||
      flag->specifier == 'E') {
    toUpper(buffer);
  }

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
    for (int i = s21_strlen(buffer); i < flag->width; i++) {
      buffer[i] = ' ';
    }
  } else if (flag->width) {
    char temp[BUFFER_SIZE] = "";
    wcstombs(temp, &ch, BUFFER_SIZE);  // ? нельзя
    for (int i = 0; i < flag->width - s21_strlen(temp); i++) {
      buffer[i] = ' ';
    }
    s21_strcat(buffer, temp);
  } else {
    wcstombs(buffer, &ch, BUFFER_SIZE);
  }
}

void stringSpecifier(char *buffer, flags *flag, va_list var) {
  char *input = va_arg(var, char *);
  char tempInput[BUFFER_SIZE] = "";
  s21_strcpy(tempInput, input);
  if (flag->isPrecisionSet) {
    tempInput[flag->precision] = '\0';
  }

  int shift = flag->width - s21_strlen(tempInput);
  int lengthInput = s21_strlen(tempInput);

  if (flag->minus && shift > 0) {
    s21_strcpy(buffer, tempInput);
    s21_memset(buffer + lengthInput, ' ', shift);
  } else if (shift > 0) {
    s21_memset(buffer, ' ', shift);
    s21_strcpy(buffer + shift, tempInput);
  } else {
    s21_strcpy(buffer, tempInput);
  }
}

void widthStringSpecifier(char *buffer, flags *flag, va_list var) {
  wchar_t *input = va_arg(var, wchar_t *);
  char tempInput[BUFFER_SIZE] = "";
  char fromWcharToChar[BUFFER_SIZE] = "";
  wcstombs(fromWcharToChar, input, BUFFER_SIZE);
  s21_strcpy(tempInput, fromWcharToChar);
  if (flag->isPrecisionSet) {
    tempInput[flag->precision] = '\0';
  }

  int shift = flag->width - s21_strlen(tempInput);
  int lengthInput = s21_strlen(tempInput);

  if (flag->minus && shift > 0) {
    s21_strcpy(buffer, tempInput);
    s21_memset(buffer + lengthInput, ' ', shift);
  } else if (shift > 0) {
    s21_memset(buffer, ' ', shift);
    s21_strcpy(buffer + shift, tempInput);
  } else {
    s21_strcpy(buffer, tempInput);
  }
}

void integerSpecifier(char *buffer, flags *flag, va_list var) {
  int64_t num = va_arg(var, int64_t);

  if (flag->length == 0) {
    num = (int32_t)num;
  } else if (flag->length == 'h') {
    num = (int16_t)num;
  }

  integerToString(buffer, num, 10);
  formatPrecision(buffer, flag);
  formatFlags(buffer, flag);
}

/// ?DELETE?
int numsCount(int64_t num) {
  // count of digits in number
  int result = 0;
  if (!num) {
    result = 1;
  } else {
    while (num) {
      num /= 10;
      result++;
    }
  }
  return result;
}
/// ?DELETE?

void integerToString(char *buffer, int64_t num, int notation) {
  char temp[BUFFER_SIZE] = "";
  int sign = 0;
  bool negative = num < 0 ? true : false;
  num = negative ? -num : num;
  if (!num) {
    buffer[0] = '0';
  }
  while (num) {
    temp[sign] = "0123456789abcdef"[num % notation];
    num /= notation;
    sign++;
  }
  if (negative) {
    temp[sign] = '-';
  }
  int len = s21_strlen(temp);
  for (int i = 0, j = len - 1; i < len; i++, j--) {
    buffer[i] = temp[j];
  }
}

void unsignedToString(char *buffer, uint64_t num, int notation) {
  char temp[BUFFER_SIZE] = "";
  int sign = 0;
  if (!num) {
    buffer[0] = '0';
  }
  while (num) {
    temp[sign] = "0123456789abcdef"[num % notation];
    num /= notation;
    sign++;
  }
  int len = s21_strlen(temp);
  for (int i = 0, j = len - 1; i < len; i++, j--) {
    buffer[i] = temp[j];
  }
}

void formatPrecision(char *buffer, flags *flag) {
  char temp[BUFFER_SIZE] = "";
  int len = s21_strlen(buffer);
  int sign = 0;
  if (buffer[0] == '-') {
    temp[0] = '-';
    sign = 1;
    len--;
  }

  if (flag->precision > len) {
    int i;
    for (i = sign; i < flag->precision - len + sign; i++) {
      temp[i] = '0';
    }
    for (int j = sign; buffer[j]; j++, i++) {
      temp[i] = buffer[j];
    }
    s21_strcpy(buffer, temp);
  }

  bool isInteger = flag->specifier == 'd' || flag->specifier == 'i' ||
                   flag->specifier == 'o' || flag->specifier == 'u' ||
                   flag->specifier == 'x' || flag->specifier == 'X';

  if (flag->isPrecisionSet && flag->precision == 0 && isInteger &&
      buffer[0] == '0') {
    buffer[0] = '\0';
  }
}

void formatFlags(char *buffer, flags *flag) {
  char temp[BUFFER_SIZE] = "";
  if (flag->plus && flag->specifier != 'u' && flag->specifier != 'p') {
    temp[0] = buffer[0] == '-' ? '-' : '+';
    s21_strcpy(temp + 1, buffer[0] == '-' ? buffer + 1 : buffer);
    s21_strcpy(buffer, temp);
  } else if (flag->space && buffer[0] != '-' && flag->specifier != 'u' &&
             flag->specifier != 'p') {
    temp[0] = ' ';
    s21_strcpy(temp + 1, buffer);
    s21_strcpy(buffer, temp);
  }
  if (flag->width > (int)s21_strlen(buffer)) {
    int diff = flag->width - s21_strlen(buffer);
    if (flag->minus) {
      s21_strcpy(temp, buffer);
      s21_memset(temp + s21_strlen(buffer), ' ', diff);
    } else {
      s21_memset(temp, flag->zero ? '0' : ' ', diff);
      s21_strcpy(temp + diff, buffer);
    }
    s21_strcpy(buffer, temp);
  }
}

void unsignedSpecifier(char *buffer, flags *flag, va_list var) {
  uint64_t num = va_arg(var, uint64_t);

  if (flag->length == 0) {
    num = (uint32_t)num;
  } else if (flag->length == 'h') {
    num = (uint16_t)num;
  }

  unsignedToString(buffer, num, 10);
  formatPrecision(buffer, flag);
  formatFlags(buffer, flag);
}

void floatSpecifier(char *buffer, flags *flag, va_list var) {
  long double num;
  if (flag->length == 'L') {
    num = va_arg(var, long double);
  } else {
    num = va_arg(var, double);
  }

  if (!flag->isPrecisionSet) {
    flag->precision = 6;
  }

  doubleToString(num, buffer, flag);
  formatFlags(buffer, flag);
}

void doubleToString(long double num, char *buffer, flags *flag) {
  char temp[BUFFER_SIZE] = "";
  int sign = 0;
  int notation = 10;
  bool negative = num < 0 ? true : false;
  num = negative ? -num : num;
  long double tempNum = num;
  while (tempNum) {
    if (tempNum < 1) {
      break;
    }
    temp[sign] = digitToAscii((int)fmod(tempNum, notation));
    tempNum /= notation;
    sign++;
  }
  if (negative) {
    temp[sign] = '-';
  }
  int len = s21_strlen(temp);
  int index = 0;
  for (int j = len - 1; index < len; index++, j--) {
    buffer[index] = temp[j];
  }
  if (index == 0 || negative && index == 1) {
    buffer[index++] = '0';
  }
  int tempIndex = index;
  buffer[index++] = '.';
  char tempRightPart[BUFFER_SIZE] = "";
  long double l = 0, r = modfl(num, &l);
  for (int p = 0; p < flag->precision; p++) {
    r = r * 10;
    tempRightPart[p] = digitToAscii((int)r);
  }
  long long rightPart = roundl(r);
  if (!rightPart) {
    for (int i = 0; i < flag->precision; i++) {
      buffer[index++] = '0';
    }
  } else {
    int len = s21_strlen(tempRightPart);
    for (int i = len, j = 0; rightPart || i > 0; rightPart /= 10, i--, j++) {
      tempRightPart[j] = digitToAscii((int)(rightPart % 10 + 0.5));
    }
    for (int i = len; i > 0; i--) {
      buffer[index++] = tempRightPart[i - 1];
    }
  }
  if (tempIndex == index - 1 && !flag->hashtag) {
    buffer[tempIndex] = '\0';
  }
}

char digitToAscii(int a) { return 48 + a; }

int asciiToDigit(char a) { return a - 48; }

void exponentSpecifier(char *buffer, flags *flag, va_list var) {
  long double num;
  if (flag->length == 'L') {
    num = va_arg(var, long double);
  } else {
    num = va_arg(var, double);
  }

  int pow = 0;
  char sign = (int)num == 0 ? '-' : '+';

  if ((int)num - num) {
    while ((int)num == 0) {
      pow++;
      num *= 10;
    }
  } else {
    sign = '+';
  }
  while ((int)num / 10 != 0) {
    pow++;
    num /= 10;
  }

  if (!flag->isPrecisionSet) {
    flag->precision = 6;
  }

  doubleToString(num, buffer, flag);
  putExponentToString(buffer, pow, sign);
  formatFlags(buffer, flag);
}

void putExponentToString(char *buffer, int pow, char sign) {
  int len = s21_strlen(buffer);
  buffer[len] = 'e';
  buffer[len + 1] = sign;
  buffer[len + 3] = digitToAscii(pow % 10);
  pow /= 10;
  buffer[len + 2] = digitToAscii(pow % 10);
  buffer[len + 4] = '\0';
}

void toUpper(char *buffer) {
  for (int i = 0; i < s21_strlen(buffer); i++) {
    if (buffer[i] >= 97 && buffer[i] <= 122) {
      buffer[i] -= 32;
    }
  }
}

void octalSpecifier(char *buffer, flags *flag, va_list var) {
  buffer[0] = '0';
  int64_t num = va_arg(var, int64_t);
  integerToString(buffer + flag->hashtag, num, 8);
  formatPrecision(buffer, flag);
  formatFlags(buffer, flag);
}

void hexSpecifier(char *buffer, flags *flag, va_list var) {
  uint64_t num = va_arg(var, uint64_t);

  if (flag->length == 0) {
    num = (uint32_t)num;
  } else if (flag->length == 'h') {
    num = (uint16_t)num;
  }

  unsignedToString(buffer, num, 16);
  formatPrecision(buffer, flag);
  if (flag->hashtag) {
    insertDecimalOx(buffer, flag);
  }
  formatFlags(buffer, flag);
}

void insertDecimalOx(char *buffer, flags *flag) {
  bool isAllDigitsIsZeroes = false;
  for (int i = 0; buffer[i]; i++) {
    if (buffer[i] == '0') {
      isAllDigitsIsZeroes = true;
      break;
    }
  }
  if (!isAllDigitsIsZeroes || flag->specifier == 'p') {
    s21_memmove(buffer + 2, buffer, s21_strlen(buffer));
    buffer[0] = '0';
    buffer[1] = 'x';
  }
}

void pointerSpecifier(char *buffer, flags *flag, va_list var) {
  unsignedToString(buffer, va_arg(var, uint64_t), 16);
  formatPrecision(buffer, flag);
  insertDecimalOx(buffer, flag);
  formatFlags(buffer, flag);
}