#include <stdarg.h>
#include <stdbool.h>

#include "s21_string.h"

typedef struct {
  int width;  // (number) - minimum number of character to be printed
  int asterics;
  char length;     // h, l or L
  char specifier;  // just specifier
} flags_t;

int s21_sscanf(const char *str, const char *format, ...);
