#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i;
  s21_size_t len_str = s21_strlen(src);
  if (n > len_str) {
    for (i = 0; i < len_str; i++) dest[i] = src[i];
  } else {
    for (i = 0; i < n; i++) dest[i] = src[i];
  }
  dest[i] = '\0';
  return dest;
}