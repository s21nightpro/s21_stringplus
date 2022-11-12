#include "s21_sprintf.h"

#include "s21_sscanf.h"
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
  double num = -.047999982222;
  s21_sprintf(stroka, "Hello, %e", num);
  printf("%sEND\n", stroka);
  sprintf(stroka2, "Hello, %e", num);
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
  // create buffer
  char buffer[BUFFER_SIZE] = "";
  if (flag->specifier == 'd' || flag->specifier == 'i') {
    integerSpecifier(buffer, flag, var);
  } else if (flag->specifier == 'u') {
    unsignedSpecifier(buffer, flag, var);
  } else if (flag->specifier == 'f') {
    floatSpecifier(buffer, flag, var);
  } else if (flag->specifier == 'e' || flag->specifier == 'E') {
    eSpecifier(buffer, flag, var);
  } else if (flag->specifier == 'g' || flag->specifier == 'G') {
  } else if (flag->specifier == 'x' || flag->specifier == 'X') {
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
  int len = strlen(temp);
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
  int len = strlen(temp);
  for (int i = 0, j = len - 1; i < len; i++, j--) {
    buffer[i] = temp[j];
  }
}

void formatPrecision(char *buffer, flags *flag) {
  char temp[BUFFER_SIZE] = "";
  int len = strlen(buffer);
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
    strcpy(buffer, temp);
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
  if (flag->plus && flag->specifier != 'u') {
    temp[0] = buffer[0] == '-' ? '-' : '+';
    strcpy(temp + 1, buffer[0] == '-' ? buffer + 1 : buffer);
    strcpy(buffer, temp);
  } else if (flag->space && buffer[0] != '-' && flag->specifier != 'u') {
    temp[0] = ' ';
    strcpy(temp + 1, buffer);
    strcpy(buffer, temp);
  }
  if (flag->width > (int)strlen(buffer)) {
    int diff = flag->width - strlen(buffer);
    if (flag->minus) {
      strcpy(temp, buffer);
      memset(temp + strlen(buffer), ' ', diff);
    } else {
      memset(temp, flag->zero ? '0' : ' ', diff);
      strcpy(temp + diff, buffer);
    }
    strcpy(buffer, temp);
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

void eSpecifier(char *buffer, flags *flag, va_list var) {
  long double num;
  if (flag->length == 'L') {
    num = va_arg(var, long double);
  } else {
    num = va_arg(var, double);
  }

  if (!flag->isPrecisionSet) {
    flag->precision = 6;
  }

  eToString(num, buffer, flag);

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
  int len = strlen(temp);
  int index = 0;
  for (int j = len - 1; index < len; index++, j--) {
    buffer[index] = temp[j];
  }
  if (index == 0 || negative && index == 1) {
    buffer[index++] = '0';
  }
  int tempIndex = index;
  buffer[index++] = '.';

  for (int p = 0; p < flag->precision; index++, p++) {
    num *= 10;
    long double ten = 10;
    double res = fmod(num, ten);
    buffer[index] = digitToAscii((int)res);
  }
  if (tempIndex == index - 1 && !flag->hashtag) {
    buffer[tempIndex] = '\0';
  }
}

char digitToAscii(int a) { return 48 + a; }

void eToString(double num, char *buffer, flags *flag) {
  char temp[BUFFER_SIZE] = "";
  int sign = 0;
  int degree_mimus = 0;
  int sign_mimus = 0;
  int index = 0;
  int sign_degree = 1;
  int degree = 0;
  int dot = 0;
  int len = 0;
  int notation = 10;
  bool negative = num < 0 ? true : false;
  num = negative ? -num : num;
  double tempNum = num;
  while (tempNum) {
    if (tempNum < 1 && degree == 0) {
      sign_degree = -1;
      degree_mimus++;
      tempNum *= 10;
      // degree = 1;
    } else if (tempNum < 1) {
      break;
    } else {
      temp[sign] = digitToAscii((int)fmod(tempNum, notation));
      degree++;
      tempNum /= notation;
      sign++;
    }
  }
  if (degree_mimus) degree += degree_mimus;
  if (negative) {
    buffer[index] = '-';
    // flag->precision++;
    index++;
    sign_mimus = 1;
  }
  len += strlen(temp);
  buffer[index] = temp[len - 1];
  index++;
  buffer[index] = '.';
  index++;

  for (int j = len - 2; index < len + 1 + sign_mimus; index++, j--) {
    buffer[index] = temp[j];
  }
  int tempIndex = index;
  tempNum = num - (int)num;
  tempNum = tempNum * pow(10, flag->precision);
  tempNum = round(tempNum);
  tempNum = tempNum / pow(10, flag->precision);
  // buffer[index++] = '.';
  for (int p = 0; p < (flag->precision - degree + 1); index++, p++) {
    tempNum *= 10;
    long double ten = 10;
    double res = fmod(tempNum, ten);
    buffer[index] = digitToAscii((int)res);
  }
  buffer[index] = 'e';
  index++;
  // temp[sign] = {0};
  if (sign_degree == 1) {
    buffer[index] = '+';
  } else {
    buffer[index] = '-';
  }
  index++;
  degree--;
  if (degree > 10) {
    sign = 0;
    while (degree > 0) {
      temp[sign] = digitToAscii((int)fmod(degree, notation));
      degree /= notation;
      sign++;
    }
    for (s21_size_t j = sign - 1; j > 0; j--) {
      buffer[index] = temp[j];
      index++;
    }
  } else {
    buffer[index] = '0';
    index++;
    buffer[index] = digitToAscii((int)fmod(degree, notation));
  }
  if (index == index - 1 && !flag->hashtag) {
    buffer[index] = '\0';
  }
}

//надо проверять на значения чтобы всегда было больше 1? если нет вызывать
//другую функцию