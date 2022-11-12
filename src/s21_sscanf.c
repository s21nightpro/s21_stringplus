#include "s21_sscanf.h"

void parseFormat(const char **format, flags_t *f);
const char *parseWidth(const char *format, flags_t *f);
const char *parseLength(const char *format, flags_t *f);
const char *parseSpecifier(const char *format, flags_t *f);

void parseString(const char **str, const s21_size_t str_len, flags_t *f,
                 va_list var, char skip);

int isSign(int a);
int isDigit(int a);
int isAscii(int a);
int isSeporator(int a);
int isHex(int a);
int isOct(int a);
int isFloat(int a, float_flags_t *fl);

void assignChar(char ch, va_list var, flags_t *f);
void assignString(char *str, va_list var, flags_t *f);
void assignFloat(char *str, va_list var, flags_t *f);
void assignN(int n, va_list var, flags_t *f);
void assignInt(char *str, va_list var, flags_t *f);
void assignHex(char *str, va_list var, flags_t *f);
void assignOct(char *str, va_list var, flags_t *f);
void assignIntUnsigned(char *str, va_list var, flags_t *f);
void assignOctUnsigned(char *str, va_list var, flags_t *f);
void assignHexUnsigned(char *str, va_list var, flags_t *f);
void assignVoid(char *str, va_list var, flags_t *f);

int main() {
  int num1, num2;

  // char a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5;

  // num1 = s21_sscanf("ABCD", "%c%*c%c%c", &a1, &b1, &c1);
  // num2 = sscanf("ABCD", "%c%*c%c%c", &a2, &b2, &c2);
  // printf("%d\n%d", num1, num2);

  long double a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0, d1 = 1, d2 = 0;

  const char str[] = "53.1 -4.1135 41.3333 +2.0001";
  const char fstr[] = "%Lf %Lf %Lf %Lf";

  num1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  num2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  printf("%d %d", num1, num2);
  //  printf("%d %d %d", num1, num2, num3);
}

int s21_sscanf(const char *str, const char *format, ...) {
  int success = 0;
  int convertions = 0;
  va_list var;
  va_start(var, format);
  const s21_size_t str_len = s21_strlen(str);
  char skip = '\0';
  while (*format != '\0') {
    if (*format == '%') {
      flags_t flag_format = {0};
      format++;
      parseFormat(&format, &flag_format);
      parseString(&str, str_len, &flag_format, var, skip);
      if (flag_format.convertions || flag_format.asterics) convertions++;
      if (flag_format.error) break;
      if (!flag_format.asterics) success++;
      skip = '\0';
    } else if (skip == '\0' || skip == *format) {
      skip = *format;
      format++;
    } else {
      break;
    }
  }
  va_end(var);

  return convertions ? success : -1;
}

void parseString(const char **str, const s21_size_t str_len, flags_t *f,
                 va_list var, char skip) {
  char str_temp[1024] = {'\0'};
  char ch = 0;
  int i = 0;
  int n = 0;
  int sign = 0;
  float_flags_t float_struct = {0};

  while ((isSeporator(**str) && f->specifier != 'c' && **str != '\0') ||
         (**str == skip && **str != '\0')) {
    (*str)++;
  }
  if (**str != '\0') {
    switch (f->specifier) {
      case 'd':
        while (
            (isDigit(**str) || (isSign(**str) && !sign &&
                                (isDigit(*((*str) + 1))) && f->width != 1)) &&
            (f->width != 0)) {
          str_temp[i] = **str;
          (*str)++;
          i++;
          sign++;
          f->width--;
        }
        if (!i) f->error = 1;
        if (!f->asterics && i) assignInt(str_temp, var, f);
        break;
      case 'u':
        while (isDigit(**str) && (f->width != 0)) {
          str_temp[i] = **str;
          (*str)++;
          i++;
          sign++;
          f->width--;
        }
        if (!i)
          f->error = 1;
        else if (!f->asterics)
          assignIntUnsigned(str_temp, var, f);
        break;
      case 'c':
        if (isAscii(**str)) {
          ch = **str;
          if (!f->asterics) assignChar(ch, var, f);
          (*str)++;
          break;
        } else {
          f->error = 1;
        }
      case 's':
        while ((f->width != 0 && !isSeporator(**str))) {
          str_temp[i] = **str;
          (*str)++;
          i++;
          f->width--;
        }
        if (!i)
          f->error = 1;
        else if (!f->asterics)
          assignString(str_temp, var, f);
        break;
      case 'i':
        if (**str == '0') {
          (*str)++;
          if ((**str) == 'x' || (**str) == 'X') {
            (*str)++;
            while ((isHex(**str) || (isSign(**str) && isHex(*((*str) + 1)) &&
                                     !sign && f->width != 1)) &&
                   (f->width != 0)) {
              str_temp[i] = **str;
              (*str)++;
              i++;
              f->width--;
              sign++;
            }
            if (!i)
              f->error = 1;
            else if (!f->asterics)
              assignHex(str_temp, var, f);
          } else {
            while ((isOct(**str) || (isSign(**str) && isOct(*((*str) + 1)) &&
                                     !sign && f->width != 1)) &&
                   (f->width != 0)) {
              str_temp[i] = **str;
              (*str)++;
              i++;
              f->width--;
              sign++;
            }
            if (!i)
              f->error = 1;
            else if (!f->asterics)
              assignOct(str_temp, var, f);
          }
        } else {
          while ((isDigit(**str) || (isSign(**str) && isDigit(*((*str) + 1)) &&
                                     !sign && f->width != 1)) &&
                 (f->width != 0)) {
            str_temp[i] = **str;
            (*str)++;
            i++;
            f->width--;
            sign++;
          }
          if (!i)
            f->error = 1;
          else if (!f->asterics)
            assignInt(str_temp, var, f);
        }
        break;

      case 'o':
        while (isOct(**str) && (f->width != 0)) {
          str_temp[i] = **str;
          (*str)++;
          i++;
          f->width--;
        }
        if (!i)
          f->error = 1;
        else if (!f->asterics)
          assignOctUnsigned(str_temp, var, f);
        break;

      case 'x':
      case 'X':
        while ((isHex(**str)) && (f->width != 0)) {
          str_temp[i] = **str;
          (*str)++;
          i++;
          f->width--;
        }
        if (!i)
          f->error = 1;
        else if (!f->asterics)
          assignHexUnsigned(str_temp, var, f);
        break;

      case 'e':
      case 'E':
      case 'f':
      case 'g':
      case 'G':
        while (isFloat(**str, &float_struct) && (f->width != 0)) {
          str_temp[i] = **str;
          (*str)++;
          i++;
          f->width--;
        }
        if (!i)
          f->error = 1;
        else if (!f->asterics)
          assignFloat(str_temp, var, f);
        break;

      case 'n':
        n = str_len - s21_strlen(*str);
        if (!f->asterics) assignN(n, var, f);
        break;

      case 'p':
        while ((isHex(**str)) && (f->width != 0)) {
          str_temp[i] = **str;
          (*str)++;
          i++;
          f->width--;
        }
        if (!i)
          f->error = 1;
        else if (!f->asterics)
          assignVoid(str_temp, var, f);
        break;
    }
  } else {
    f->error++;
  }
}

int isFloat(int a, float_flags_t *fl) {
  int flag = 1;
  if (isDigit(a)) {
    fl->digit = 1;
  } else if ((fl->digit == 0 && fl->sign_before_e == 0 && fl->e == 0 &&
              fl->dot == 0 && (a == '-' || a == '+'))) {
    fl->sign_before_e++;
  } else if (fl->sign_before_e == 1 && fl->e == 0 && (a == '-' || a == '+')) {
    flag = 0;
  } else if (fl->sign_after_e == 0 && fl->digit && fl->e == 1 &&
             (a == '-' || a == '+')) {
    fl->sign_after_e++;
  } else if (fl->e == 1 && (a == '-' || a == '+') &&
             (fl->sign_after_e == 1 && !fl->digit)) {
    flag = 0;
  } else if (fl->digit == 1 && fl->e == 0 && (a == 'e' || a == 'E')) {
    fl->e++;
  } else if (fl->e == 0 && fl->dot == 0 && (a == '.')) {
    fl->dot++;
  } else {
    flag = 0;
  }
  return flag;
}

/*
c - считывает 1 символ
s - считывает строку
d - считывает 10тичное число
i - знаковое 10тичное, 8ричное, 16ричное

eEfgG - десятичное с плаваюшей или научная нотация
o - беззнак 8ричное
u - беззнак десятичное целое
xX - беззнак 16ричное целое
p - адрес указателя
n - количество считанных символов
*/

int isDigit(int a) { return (a >= '0' && a <= '9'); }

int isAscii(int a) { return (a >= 0 && a <= 127); }

int isSeporator(int a) {
  return ((a == '\n') || (a == 32) || (a == '\0' || (a == '\t')));
}

int isHex(int a) {
  return (isDigit(a) || (a >= 'a' && a <= 'f') || (a >= 'A' && a <= 'F'));
}

int isOct(int a) { return (isDigit(a) && a < '8'); }

int isSign(int a) { return (a == '+' || a == '-'); }

void assignHex(char *str, va_list var, flags_t *f) {
  f->convertions++;
  if (f->length == 'h') {
    *va_arg(var, short *) = (short)s21_atohex(str);
  } else if (f->length == 'l') {
    *va_arg(var, long *) = s21_atohex(str);
  } else {
    *va_arg(var, int *) = (int)s21_atohex(str);
  }
}

void assignHexUnsigned(char *str, va_list var, flags_t *f) {
  f->convertions++;
  if (f->length == 'h') {
    *va_arg(var, unsigned short *) = (unsigned short)s21_usigned_atohex(str);
  } else if (f->length == 'l') {
    *va_arg(var, unsigned long *) = s21_usigned_atohex(str);
  } else {
    *va_arg(var, unsigned int *) = (unsigned int)s21_usigned_atohex(str);
  }
}

void assignOct(char *str, va_list var, flags_t *f) {
  f->convertions++;
  if (f->length == 'h') {
    *va_arg(var, short *) = (short)s21_ato8(str);
  } else if (f->length == 'l') {
    *va_arg(var, long *) = s21_ato8(str);
  } else {
    *va_arg(var, int *) = (int)s21_ato8(str);
  }
}

void assignOctUnsigned(char *str, va_list var, flags_t *f) {
  f->convertions++;
  if (f->length == 'h') {
    *va_arg(var, unsigned short *) = (unsigned short)s21_unsigned_ato8(str);
  } else if (f->length == 'l') {
    *va_arg(var, unsigned long *) = s21_unsigned_ato8(str);
  } else {
    *va_arg(var, unsigned int *) = (unsigned int)s21_unsigned_ato8(str);
  }
}

void assignIntUnsigned(char *str, va_list var, flags_t *f) {
  f->convertions++;
  if (f->length == 'h') {
    *va_arg(var, short *) = (unsigned short)s21_atos(str);
  } else if (f->length == 'l') {
    *va_arg(var, long *) = s21_atol(str);
  } else {
    *va_arg(var, int *) = (unsigned int)s21_atoii(str);
  }
}

void assignInt(char *str, va_list var, flags_t *f) {
  f->convertions++;
  if (f->length == 'h') {
    *va_arg(var, short *) = (short)s21_atos(str);
  } else if (f->length == 'l') {
    *va_arg(var, long *) = s21_atol(str);
  } else {
    *va_arg(var, int *) = (int)s21_atoii(str);
  }
}

void assignVoid(char *str, va_list var, flags_t *f) {
  f->convertions++;
  void **dest = va_arg(var, void **);

  *dest = (void *)(0x0 + s21_usigned_atohex(str));
}

void assignN(int n, va_list var, flags_t *f) {
  f->convertions++;
  if (f->length == 'h') {
    *va_arg(var, short *) = n;
  } else if (f->length == 'l') {
    *va_arg(var, long *) = n;
  } else {
    *va_arg(var, int *) = n;
  }
}

void assignFloat(char *str, va_list var, flags_t *f) {
  f->convertions++;
  if (f->length == 'l') {
    *va_arg(var, double *) = (double)s21_atoE(str);
    ;
  } else if (f->length == 'L') {
    *va_arg(var, long double *) = s21_atoE(str);
  } else {
    *va_arg(var, float *) = (float)s21_atoE(str);
  }
}

void assignChar(char ch, va_list var, flags_t *f) {
  f->convertions++;
  *va_arg(var, char *) = ch;
}

void assignString(char *str, va_list var, flags_t *f) {
  f->convertions++;
  s21_strcpy(va_arg(var, char *), str);
}

void parseFormat(const char **format, flags_t *f) {
  *format = parseWidth(*format, f);
  *format = parseLength(*format, f);
  *format = parseSpecifier(*format, f);
}

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
      if ((*format) == 'l') format++;
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
