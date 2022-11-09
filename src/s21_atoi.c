// #include <s21_string.h>

#include <math.h>

#include "s21_sscanf.h"
int s21_atoii(const char *str) {
  int atoint = 0;
  int sign = 1;  //если подают отрицательное число
  if (*str == '-') {
    sign = -1;
    str++;
  }
  if (*str == '+') {
    sign = 1;
    str++;
  }
  while (*str && *str >= '0' && *str <= '9') {
    atoint = atoint * 10 + (*str - '0');
    str++;
  }
  if (sign < 0) atoint *= sign;
  return (atoint);
}

long s21_atol(const char *str) {
  long atol = 0;
  int sign = 1;  //если подают отрицательное число

  if (*str == '-') {
    sign = -1;
    str++;
  }
  if (*str == '+') {
    sign = 1;
    str++;
  }
  while (*str && *str >= '0' && *str <= '9') {
    atol = atol * 10 + (*str - '0');
    str++;
  }
  if (sign < 0) atol *= sign;
  return (atol);
}

long long s21_atoll(const char *str) {
  long long atol = 0;
  int sign = 1;  //если подают отрицательное число
  // int zero = 0;

  //   while (*str != ' ') {
  //   }
  if (*str == '-') {
    sign = -1;
    str++;
  }
  if (*str == '+') {
    sign = 1;
    str++;
  }
  while (*str && *str >= '0' && *str <= '9') {
    atol = atol * 10 + (*str - '0');
    str++;
  }
  if (sign < 0) atol *= sign;
  return (atol);
}

short s21_atos(const char *str) {
  short atos = 0;
  int sign = 1;  //если подают отрицательное число
  if (*str == '-') {
    sign = -1;
    str++;
  }
  if (*str == '+') {
    sign = 1;
    str++;
  }
  while (*str && *str >= '0' && *str <= '9') {
    atos = atos * 10 + (*str - '0');
    str++;
  }
  if (sign < 0) atos *= sign;
  //   if (atoint >)
  return (atos);
}

float s21_atof(const char *str) {
  float atof = 0;
  float fraction = 0;
  int n = 0;  //кол-во знаков после запятой
  int sign = 1;
  if (*str == '-') {
    sign = -1;
    str++;
  }
  if (*str == '+') {
    str++;
  }
  while (*str && ((*str >= '0' && *str <= '9') || *str == '.')) {
    if (*str == '.') {
      str++;
      break;
    }

    atof = atof * 10 + (*str - '0');
    str++;
  }
  //   printf("%f\n", atof);
  while (*str && *str >= '0' && *str <= '9' && n != 5) {
    n++;
    fraction = (*str - '0');
    atof = atof + (fraction / pow(10, n));
    str++;
    printf("%f\n", fraction / pow(10, n));
  }
  //   atof += (fraction / n);
  if (sign < 0) atof *= sign;
  return (atof);
}

double s21_atod(const char *str) {
  double atod = 0;
  double fraction = 0;
  int n = 0;  //кол-во знаков после запятой
  int sign = 1;
  if (*str == '-') {
    sign = -1;
    str++;
  }
  if (*str == '+') {
    str++;
  }
  while (*str && ((*str >= '0' && *str <= '9') || *str == '.')) {
    if (*str == '.') {
      str++;
      break;
    }

    atod = atod * 10 + (*str - '0');
    str++;
  }
  //   printf("%f\n", atod);
  while (*str && *str >= '0' && *str <= '9' && n != 5) {
    n++;
    fraction = (*str - '0');
    atod = atod + (fraction / pow(10, n));
    str++;
    printf("%f\n", fraction / pow(10, n));
  }
  //   atod += (fraction / n);
  if (sign < 0) atod *= sign;
  return (atod);
}

long double s21_atold(const char *str) {
  long double atold = 0;
  long double fraction = 0;
  int n = 0;  //кол-во знаков после запятой
  int sign = 1;
  if (*str == '-') {
    sign = -1;
    str++;
  }
  if (*str == '+') {
    str++;
  }
  while (*str && ((*str >= '0' && *str <= '9') || *str == '.')) {
    if (*str == '.') {
      str++;
      break;
    }
    atold = atold * 10 + (*str - '0');
    str++;
  }
  //   printf("%f\n", atold);
  while (*str && *str >= '0' && *str <= '9' && n != 5) {
    n++;
    fraction = (*str - '0');
    atold = atold + (fraction / pow(10, n));
    str++;
    printf("%Lf\n", fraction / pow(10, n));
  }
  //   atold += (fraction / n);
  if (sign < 0) atold *= sign;
  return (atold);
}