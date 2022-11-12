#include "s21_sscanf.h"

// char *pars_format(char *format, flags_t *f) { return format; }
// char *pars_string(char *str, flags_t *f) { return str; }

// int s21_sscanf(const char *str, const char *format, ...) {
//   va_list va;
//   va_start(va, format);
//   flags_t flag_format = {0};
//   while (format) {
//     pars_format(format, &flag_format);

//     format++;
//   }

//   va_end(va);

//   return 1;
// }

int main() {
  // char str[50] = "-12321";
  // char str2[50] = {0};
  char str3[70] = {0};
  // char str2[50], ch;
  // int num1, num2, num3;
  // unsigned int num1 = 0;
  // float num1 = 0;
  // void **num3;
  // void **num2;
  // int x;
  int y = 0;
  int b = 0;
  double a = 13434324234234234234242.2323213;
  y = (int)a;
  for (int i = ; i > 0; i--) {
    str3[b] = digit_to_ascii(y % 10);
    b++;
    y = y / 10;
    printf("char:%c  digit:%d\n", str3[b], b);
  }
  printf("\n");
  printf("double to str:%s\n", str3);
  // int num3 = 0;
  //  char ch;
  //   long num3, num4;
  //   num3 = s21_atol(str);
  //   long long num5, num6;
  //   short num7, num8;
  //   double num9, num10;
  // x = sscanf(str, "%p%s", &num2, str2);
  // printf("%d\n", x);
  // // num3 = s21_usigned_void_atohex(str);
  // printf("str: %s\n", str);
  // // s21_sscanf(str, "%d %d %d", &num1, &num2, &num3);
  // // printf("%d %d %d", num1, num2, num3);
  // printf("num1: \nnum2: %p\nstr: %s\n", num2, str2);
}

/*
перевод аски в целые 4 функции ++
перевод аски в дробные 3 функции ++

перевод 16 ричной в десятичную (большие-маленькие) ++
перевод 8 ричной в десятичную

перевод из научной нотации

IZI ATOI

*/
/*
minus: либо нулевая позиция, либо после е(значит флаг е == 1) флаг может быть
0,1,2,3(3-выход, 2 -используется в е, 1 - нулевая позиция)
plus:  либо нулевая
позиция, либо после е(значит флаг е == 1) флаг может быть 0,1,2,3(3-выход, 2
-используется в е, 1 - нулевая позиция)
dot: любая позиция (до е(флаг е == 0))
флаг может быть 0,1,2
e : любая позиция флаг может быть 0,1,2
функция isDigit
*/

/*
isHex;
знак либо нет либо на нулевой
из макс значения вычесть значения хекса
*/
/*переводить в научную запись, посимвольно вытаскивать из нее
 */
