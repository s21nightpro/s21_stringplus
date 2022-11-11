int isPointer(int a, int *first_digit);

int isHex(int a) {
  return (isDigit(a) || (a >= 'a' && a <= 'f') || (a >= 'A' && a <= 'F') ||
          a == 'X' || a == 'x');
}
isPointer(a, &first_digit);

int isPointer(int a, int *first_digit) {
  int flag = 1;
  if (isHex(a)) {
    first_digit = 1;
  } else if (!isHex(a) && first_digit == 0) {
    ;
  } else if (!isHex(a) && first_digit == 1) {
    flag = 0;
  }
  return flag;
}