typedef struct {
  int sign_befor_e;
  int sign_after_e;
  int dot;
  int e;
  int digit;
} float_t;
int main() { float_t fl = {0}; }

int isDigit(int a) { return (a >= '0' && a <= '9'); }

int isFloat(int a, float_t *fl) {
  int flag = 1;
  if (isDigit(a)) fl->digit == 1;

  if ((fl->digit == 0 && fl->sign_befor_e == 0 && fl->e == 0 && fl->dot == 0 &&
       (a == '-' || a == '+'))) {
    fl->sign_befor_e++;
  } else if (fl->sign_befor_e == 1 && fl->e == 0 && (a == '-' || a == '+')) {
    flag = 0;
  } else if (fl->sign_after_e == 0 && fl->digit && fl->e == 1 &&
             (a == '-' || a == '+')) {
    fl->sign_after_e++;
  } else if (fl->e == 1 && (a == '-' || a == '+') &&
             (fl->sign_after_e == 1 && !fl->digit)) {
    flag = 0;
  } else if (fl->digit == 1 && fl->e == 0 && (a == 'e' || a == 'E')) {
    fl->e++;
  } else {
    flag = 0;
  }
  return flag;
}
