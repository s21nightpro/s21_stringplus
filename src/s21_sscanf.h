#include <stdarg.h>
#include <stdbool.h>

#include "s21_string.h"

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
} flags_t;

int s21_sscanf(const char *str, const char *format, ...);
