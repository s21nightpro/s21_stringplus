#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *str = s21_NULL;
  if (src && trim_chars) {
    s21_size_t start = 0, end = 0, size = 0;
    end = s21_strlen(src) - 1;
    for (; src[start] && s21_strchr(trim_chars, src[start]); start++)
      for (; src[end] && end > start && s21_strchr(trim_chars, src[end]); end--)
        size =
            end - start - 3;  // idk why -3 mb arch bug. must be checked on mac
    str = malloc(sizeof(char) * size);  // id rather use static arr in stack
    if (str) {
      s21_strncpy(str, src + start, size);
    }
  }
  return str;
}
