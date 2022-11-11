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
int numsCount(int64_t num);

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

void integerToString(char *buffer, int64_t num);
void formatPrecision(char *buffer, flags *flag);
void formatFlags(char *buffer, flags *flag);
