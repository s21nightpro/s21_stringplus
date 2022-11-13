
#include <stdarg.h>
#include <stdbool.h>

#include "s21_string.h"

typedef struct {
  int width;  // (number) - minimum number of character to be printed
  int asterics;
  char length;     // h, l or L
  char specifier;  // just specifier
  int error;
  int convertions;
} flags_t;

typedef struct {
  int sign_before_e;
  int sign_after_e;
  int dot;
  int e;
  int digit;
} float_flags_t;
