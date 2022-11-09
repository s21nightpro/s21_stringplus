#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// A format specifier for print functions follows this prototype:
// %[flags][width][.precision][length]specifier

typedef struct {
    bool minus;    // Left-justify within the given field width
    bool plus;     // Forces to precede the result with a plus or minus sign (+ or -) even for positive numbers
    bool space;    // If no sign is going to be written, a blank space is inserted before the value
    bool hashtag;  // Made some math things with some specifiers
    bool zero;     // Left-pads the number with zeroes (0) instead of spaces
    int width;     // (number) - minimum number of character to be printed   or *
    int precision; // Precision
    char length;   // h, l or L
    int specifier; // just specifier
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

int main () {
    start();
    return 0;
}

void start() {
    char *stroka;
    stroka = (char*)malloc(300*sizeof (char));
    s21_sprintf(stroka, "%s %s %s", "stroka", "hello", "lksjflsj");
    printf("%s\n", stroka);
    free(stroka);
}

int s21_sprintf(char *str, const char *format, ...) {
    flags flag = {0};
    va_list var;
    va_start(var, format);

    while (*format) {
        if (*format == '%') {
            format = parseFormat(format, &flag, var);

        } else {
            int len = strlen(str);
            str[len] = *format;
            str[len + 1] = '\0';
        }
        format++;
    }
    va_end(var);
    return 0;
}

void itoa(int n, char s[]) {
    int i, sign;

    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void reverse(char s[]) {
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

const char *parseFormat(const char *format, flags *f, va_list var) {
    parseFlags(format, f);
    parseWidth(format, f, var);
    parsePrecision(format, f, var);
    parseLength(format, f);
    f->specifier = *format;
    format++;
    return format;
}

const char *parseFlags(const char *format, flags *f) {
    while (*format == '-' || *format == '+' || *format == ' ' ||
           *format == '#' || *format == '0') {
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
            break;
        case 'l':
            f->length = 'l';
            break;
        case 'L':
            f->length = 'L';
            break;
    }
    return format;
}