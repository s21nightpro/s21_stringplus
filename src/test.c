#include <stdio.h>
#include <stdlib.h>

void start();

int main() {
  start();
  return 0;
}

// %[flags][width][.precision][length]specifier
void start() {
  char *stroka;
  stroka = (char *)malloc(300 * sizeof(char));
  sprintf(stroka, "% cH", 'h');
  printf("%s\n", stroka);
  free(stroka);
}