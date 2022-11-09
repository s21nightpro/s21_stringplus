#include <check.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>

#include "../s21_string.h"
#include "../s21_strlen.c"

// strspn_1:0: Passed
// strspn_2:0: Assertion 'strspn(str2, "shit
// ") == s21_strspn(str2, "shit ")' failed: strspn(str2, "shit ") == 8,
// s21_strspn(str2, "shit ") == 12
// strspn_3:0: Passed
// strspn_empty:0: Passed
// strspn_gora_:0: Passed
// strspn__gora:0: Passed
// strspn_any_register:0: Assertion
// 's21_strspn(res, src) == strspn(res, src)' failed: s21_strspn(res, src) == 3,
// strspn(res, src) == 1 strspn_num_num:0:
// Passed strspn_long_num_num:0: Passed
// strspn_num_long_num:0: Passed
// strspn_any_num:0: Passed
// strspn_num_with_letter:0: Passed
// strspn_num_with_letter2:0: Assertion
// 's21_strspn(res, src) == strspn(res, src)' failed: s21_strspn(res, src) == 6,
// strspn(res, src) == 3
// :strspn_basic_test:0: Passed
// :strspn_any_sim:0: Assertion
// 's21_strspn(res, src) == strspn(res, src)' failed: s21_strspn(res, src) ==
// 18, strspn(res, src) == 10
// :strspn_upper_letter:0: Assertion
// 's21_strspn(res, src) == strspn(res, src)' failed: s21_strspn(res, src) ==
// 25, strspn(res, src) == 10
// :strspn_lower_letter:0: Assertion
// 's21_strspn(res, src) == strspn(res, src)' failed: s21_strspn(res, src) ==
// 30, strspn(res, src) == 10
// :strspn_not_uniq_sim:0: Assertion
// 's21_strspn(res, src) == strspn(res, src)' failed: s21_strspn(res, src) ==
// 86, strspn(res, src) == 0

START_TEST(strspn_1) {
  char str[] = "12-years";
  ck_assert_int_eq(strspn(str, "1234567890"), s21_strspn(str, "1234567890"));
}
END_TEST

START_TEST(strspn_2) {
  char str2[] = "this is a test";
  ck_assert_int_eq(strspn(str2, "shit "), s21_strspn(str2, "shit "));
}
END_TEST  // FAIL

START_TEST(strspn_3) {
  char str3[] = {'q', 'r', 's', 't', 'w', 's', 'a', 's'};
  ck_assert_int_eq(strspn(str3, "01234"), s21_strspn(str3, "01234"));
}
END_TEST

START_TEST(strspn_empty) {
  char src[] = "";
  char res[] = "";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(strspn_gora_) {
  char src[] = "gora";
  char res[] = "";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(strspn__gora) {
  char src[] = "";
  char res[] = "gora";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(strspn_any_register) {
  char src[] = "gora";
  char res[] = "gOra";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST  // FAIL

START_TEST(strspn_num_num) {
  char src[] = "123";
  char res[] = "123";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(strspn_long_num_num) {
  char src[] = "12345";
  char res[] = "123";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(strspn_num_long_num) {
  char src[] = "123";
  char res[] = "12345";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(strspn_any_num) {
  char src[] = "1234567890";
  char res[] = "0987654321";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(strspn_num_with_letter) {
  char src[] = "1A2A3A4A5A";
  char res[] = "123";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(strspn_num_with_letter2) {
  char src[] = "a1aaa23aaa41235";
  char res[] = "123";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(strspn_basic_test) {
  char src[] = "absD";
  char res[] = "aD";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST  // FAIL

START_TEST(strspn_any_sim) {
  char src[] = "32ASDASDPare[0g9jf m07y271234567890";
  char res[] = "0987654321";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(strspn_upper_letter) {
  char src[] = "32ASDASDPare[0g9jf m07y271234567890";
  char res[] = "1234567890QWERTYUIOPASDFGHJKLZXCVBNM";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST  // FAIL

START_TEST(strspn_lower_letter) {
  char src[] = "32jersASDASDPare[0g9jf m07y271234567890";
  char res[] = "1234567890qwertyuiopasdfghjklczxcvbnm";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST  // FAIL

START_TEST(strspn_not_uniq_sim) {
  char src[] =
      "333333333333333333333333333333333333333333333333333333333333333333333333"
      "33333333333333";
  char res[] =
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "11111111111113";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST  // FAIL

    Suite *
    suite_strspn(void) {
  Suite *s = suite_create("suite_strspn");
  TCase *tc = tcase_create("strspn_tc");
  tcase_add_test(tc, strspn_1);
  tcase_add_test(tc, strspn_2);
  tcase_add_test(tc, strspn_3);
  tcase_add_test(tc, strspn_empty);
  tcase_add_test(tc, strspn_gora_);
  tcase_add_test(tc, strspn__gora);
  tcase_add_test(tc, strspn_any_register);
  tcase_add_test(tc, strspn_num_num);
  tcase_add_test(tc, strspn_long_num_num);
  tcase_add_test(tc, strspn_num_long_num);
  tcase_add_test(tc, strspn_any_num);
  tcase_add_test(tc, strspn_num_with_letter);
  tcase_add_test(tc, strspn_num_with_letter2);
  tcase_add_test(tc, strspn_basic_test);
  tcase_add_test(tc, strspn_any_sim);
  tcase_add_test(tc, strspn_upper_letter);
  tcase_add_test(tc, strspn_lower_letter);
  tcase_add_test(tc, strspn_not_uniq_sim);

  suite_add_tcase(s, tc);
  return s;
}

int main(void) {
  setlocale(LC_ALL, "");
  int nf;
  Suite *s1;
  SRunner *sr;
  s1 = suite_strspn();
  sr = srunner_create(s1);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);

  nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nf == 0 ? 0 : 1;
}
