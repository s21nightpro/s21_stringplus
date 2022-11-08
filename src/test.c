#include "s21_sscanf.h"
#include "s21_string.h"
#define buf 100
#include <string.h>
/*int main() {
  char str[buf] = "I 5 bananas";
  char str2[buf], ch;
  int num;
  sscanf(str, "%c %d %s", &ch, &num, str2);
  printf("%c %d %s", ch, num, str2);
}*/

void var(const char *str, char *format, ...) {
  va_list ap;
  va_start(ap, format);
  if (!strcmp(format, "%d")) {
    int x = va_arg(ap, int);
    printf("%s\n", str);
    printf("You passed decimal object with value %d\n", x);
  }

  if (!strcmp(format, "%s")) {
    char *p = va_arg(ap, char *);
    printf("%s\n", str);
    printf("You passed c-string \"%s\"\n", p);
  }
  va_end(ap);
}

int main() {
  char str1[buf] = "abcd";
  var(str1, "%d", 255);
  var(str1, "%s", "test string");
}