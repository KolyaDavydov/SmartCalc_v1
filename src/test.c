#include <check.h>
#include <math.h>
#include <string.h>

#include "s21_smartcalc.h"

START_TEST(test_smart_calc_1) {
  char input[255] = "3+4*2/(1-5)^2";
  double result = 0;
  int error = calc(input, &result, 0);
  ck_assert_int_eq(OK, error);
  ck_assert_double_eq(result, 3.5);
}
END_TEST

START_TEST(test_smart_calc_2) {
  char input[255] = "1+2+3+4*5*6^7";
  double result;
  int error = calc(input, &result, 0);
  ck_assert_int_eq(OK, error);
  ck_assert_double_eq((int)result, 5598726);
}
END_TEST

START_TEST(test_smart_calc_3) {
  char input[255] = "123.456+2*3^4";
  double result;
  int error = calc(input, &result, 0);
  ck_assert_int_eq(OK, error);
  ck_assert_double_eq(result, 285.456);
}
END_TEST

START_TEST(test_smart_calc_4) {
  char input[255] = "(8+2*5)/(1+3*2-4)";

  double result;
  int error = calc(input, &result, 0);
  ck_assert_int_eq(OK, error);
  ck_assert_double_eq(result, 6);
}
END_TEST

START_TEST(test_smart_calc_5) {
  char input[255] =
      "(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/2)))";

  double result;
  int error = calc(input, &result, 0);
  ck_assert_int_eq(OK, error);
  ck_assert_double_eq(result, 10);
}
END_TEST

START_TEST(test_smart_calc_6) {
  char input[255] = "cos(1*2)-1";
  double result;
  int error = calc(input, &result, 0);
  ck_assert_int_eq(OK, error);
  ck_assert_double_eq_tol(result, -1.41614683655, 1e-06);
}
END_TEST

START_TEST(test_smart_calc_7) {
  char input[255] =
      "cos(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/"
      "2)))-1";
  double result;
  int error = calc(input, &result, 0);
  ck_assert_int_eq(OK, error);
  ck_assert_double_eq_tol(result, -1.83907152908, 1e-06);
}
END_TEST

START_TEST(test_smart_calc_8) {
  char input[255] = "sin(+2)";
  double result;
  int error = calc(input, &result, 0);
  ck_assert_int_eq(OK, error);
  ck_assert_double_eq_tol(result, 0.909297, 1e-06);
}
END_TEST

START_TEST(test_smart_calc_9) {
  char input[255] = "-2%(-2)";
  double result;
  int error = calc(input, &result, 0);
  ck_assert_int_eq(OK, error);
  ck_assert_double_eq(result, 0);
}
END_TEST

START_TEST(test_smart_calc_10) {
  char input[255] = "+3+4*2/1-5+2^2";
  double result;
  int error = calc(input, &result, 0);
  ck_assert_int_eq(OK, error);
  ck_assert_double_eq_tol(result, 10, 1e-06);
}
END_TEST

START_TEST(test_smart_calc_11) {
  double x = 10;
  char input[255] = "3+4*2/1-5+2^2";
  double result;
  int error = calc(input, &result, x);
  ck_assert_int_eq(OK, error);
  ck_assert_double_eq_tol(result, 10, 1e-06);
}
END_TEST

START_TEST(test_smart_calc_12) {
  double x = 0.0003;
  char input[255] = "asin(2*X)";
  double result;
  int error = calc(input, &result, x);
  ck_assert_int_eq(OK, error);
  ck_assert_double_eq_tol(result, 0.0006, 1e-06);
}
END_TEST

START_TEST(test_smart_calc_13) {
  double x = 0.0019;
  char input[255] = "acos(2*X)";
  double result;
  int error = calc(input, &result, x);
  ck_assert_int_eq(OK, error);
  ck_assert_double_eq_tol(result, 1.567, 1e-03);
}
END_TEST

START_TEST(test_smart_calc_14) {
  double x = 0.0019;
  char input[255] = "atan(2*X)";
  double result;
  int error = calc(input, &result, x);
  ck_assert_int_eq(OK, error);
  ck_assert_double_eq_tol(result, 0.00379998, 1e-06);
}
END_TEST

START_TEST(test_smart_calc_15) {
  double x = 0.004;
  char input[255] = "tan(2*X)";
  double result;
  int error = calc(input, &result, x);
  ck_assert_int_eq(OK, error);
  ck_assert_double_eq_tol(result, 0.00800017, 1e-06);
}
END_TEST

START_TEST(test_smart_calc_16) {
  double x = 25;
  char input[255] = "sqrt(2*X)";
  double result;
  int error = calc(input, &result, x);
  ck_assert_int_eq(OK, error);
  ck_assert_double_eq_tol(result, 7.07107, 1e-05);
}
END_TEST

START_TEST(test_smart_calc_17) {
  double x = 0.0019;
  char input[255] = "2.3+5.5";
  double result;
  int error = calc(input, &result, x);
  ck_assert_int_eq(OK, error);
  ck_assert_double_eq(result, 7.8);
}
END_TEST

START_TEST(test_smart_calc_18) {
  char input[255] = "-(-3+2)";
  double result;
  int error = calc(input, &result, 0);
  ck_assert_int_eq(OK, error);
  ck_assert_int_eq((int)result, 1);
}
END_TEST

START_TEST(test_smart_calc_19) {
  char input[255] = "(-2-3+1)";
  double result;
  int error = calc(input, &result, 0);
  ck_assert_int_eq(OK, error);
  ck_assert_int_eq((int)result, -4);
}
END_TEST

START_TEST(test_smart_calc_20) {
  char input[255] = "(+2-6)+(-4-10)";
  double result;
  int error = calc(input, &result, 0);
  ck_assert_int_eq(OK, error);
  ck_assert_int_eq((int)result, -18);
}

START_TEST(test_smart_calc_21) {
  char input[255] = "-2-3+1";
  double result;
  int error = calc(input, &result, 0);
  ck_assert_int_eq(OK, error);
  ck_assert_int_eq((int)result, -4);
}
END_TEST

START_TEST(test_smart_calc_22) {
  char input[255] = "5%3";
  double result;
  int error = calc(input, &result, 0);
  ck_assert_int_eq(OK, error);
  ck_assert_int_eq(result, 2);
}
END_TEST

START_TEST(test_smart_calc_23) {
  char input[255] = "(132+sin(asin(sqrt(ln(log(228.11)))))-4*5^6*(123))";
  double result;
  int error = calc(input, &result, 0);
  ck_assert_int_eq(OK, error);
  ck_assert_int_eq(result, -7687367.073);
}
END_TEST

START_TEST(test_smart_calc_24) {
  char input[255] =
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  double result;
  int error = calc(input, &result, 0);
  ck_assert_int_eq(OK, error);
  ck_assert_int_eq(result, -30.07);
}
END_TEST

START_TEST(test_smart_calc_25) {
  char input[255] = "sin(-1)";
  double result;
  int error = calc(input, &result, 0);
  ck_assert_int_eq(OK, error);
  ck_assert_int_eq(result, 0.84);
}
END_TEST

START_TEST(test_smart_calc_26) {
  char input[255] = "(/)3";
  double result;
  int error = calc(input, &result, 0);
  ck_assert_int_eq(ERR, error);
}
END_TEST

START_TEST(test_smart_calc_27) {
  char input[255] = "3%/";
  double result;
  int error = calc(input, &result, 0);
  ck_assert_int_eq(ERR, error);
}
END_TEST

START_TEST(test_smart_calc_28) {
  char input[255] = "(/3)";
  double result;
  int error = calc(input, &result, 0);
  ck_assert_int_eq(ERR, error);
}
END_TEST

START_TEST(test_smart_calc_29) {
  double x = 2;
  char input[255] = "(-2-3+X)";
  double result;
  int error = calc(input, &result, x);
  ck_assert_int_eq(OK, error);
  ck_assert_int_eq((int)result, -3);
}
END_TEST

START_TEST(test_smart_calc_30) {
  char input[255] = "4/0";
  double result;
  int error = calc(input, &result, 0);
  ck_assert_int_eq(ERR_DIV_ZERO, error);
}
END_TEST

START_TEST(test_smart_calc_31) {
  char input[255] = "1.1+2.3";
  double result;
  int error = calc(input, &result, 0);
  ck_assert_int_eq(OK, error);
  ck_assert_double_eq(result, 3.4);
}
END_TEST

START_TEST(test_smart_calc_32) {
  double **res = annuity_credit_calc(100000, 2, 7.1);
  ck_assert_int_eq(res[0][0], 1);
  ck_assert_double_eq(res[0][1], 50444.19);
  ck_assert_double_eq(res[0][2], 49852.52);
  ck_assert_double_eq(res[0][3], 591.67);
  ck_assert_double_eq(res[0][4], 50147.48);

  ck_assert_int_eq(res[1][0], 2);
  ck_assert_double_eq(res[1][1], 50444.19);
  ck_assert_double_eq(res[1][2], 50147.48);
  ck_assert_double_eq(res[1][3], 296.71);
  ck_assert_double_eq(res[1][4], 0);
}
END_TEST

START_TEST(test_smart_calc_33) {
  double **res = dif_credit_calc(100000, 2, 7.1);
  ck_assert_int_eq(res[0][0], 1);
  ck_assert_double_eq(res[0][1], 50591.67);
  ck_assert_double_eq(res[0][2], 50000);
  ck_assert_double_eq(res[0][3], 591.67);
  ck_assert_double_eq(res[0][4], 50000);

  ck_assert_int_eq(res[1][0], 2);
  ck_assert_double_eq(res[1][1], 50295.83);
  ck_assert_double_eq(res[1][2], 50000);
  ck_assert_double_eq(res[1][3], 295.83);
  ck_assert_double_eq(res[1][4], 0);
}
END_TEST

int main() {
  Suite *s1 = suite_create("s21_smart_calc: ");
  TCase *tc1_1 = tcase_create("s21_smart_calc: ");
  SRunner *sr = srunner_create(s1);
  int result;
  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_1, test_smart_calc_1);
  tcase_add_test(tc1_1, test_smart_calc_2);
  tcase_add_test(tc1_1, test_smart_calc_3);
  tcase_add_test(tc1_1, test_smart_calc_4);
  tcase_add_test(tc1_1, test_smart_calc_5);
  tcase_add_test(tc1_1, test_smart_calc_6);
  tcase_add_test(tc1_1, test_smart_calc_7);
  tcase_add_test(tc1_1, test_smart_calc_8);
  tcase_add_test(tc1_1, test_smart_calc_9);
  tcase_add_test(tc1_1, test_smart_calc_10);
  tcase_add_test(tc1_1, test_smart_calc_11);
  tcase_add_test(tc1_1, test_smart_calc_12);
  tcase_add_test(tc1_1, test_smart_calc_13);
  tcase_add_test(tc1_1, test_smart_calc_14);
  tcase_add_test(tc1_1, test_smart_calc_15);
  tcase_add_test(tc1_1, test_smart_calc_16);
  tcase_add_test(tc1_1, test_smart_calc_17);
  tcase_add_test(tc1_1, test_smart_calc_18);
  tcase_add_test(tc1_1, test_smart_calc_19);
  tcase_add_test(tc1_1, test_smart_calc_20);
  tcase_add_test(tc1_1, test_smart_calc_21);
  tcase_add_test(tc1_1, test_smart_calc_22);
  tcase_add_test(tc1_1, test_smart_calc_23);
  tcase_add_test(tc1_1, test_smart_calc_24);
  tcase_add_test(tc1_1, test_smart_calc_25);
  tcase_add_test(tc1_1, test_smart_calc_26);
  tcase_add_test(tc1_1, test_smart_calc_27);
  tcase_add_test(tc1_1, test_smart_calc_28);
  tcase_add_test(tc1_1, test_smart_calc_29);
  tcase_add_test(tc1_1, test_smart_calc_30);
  tcase_add_test(tc1_1, test_smart_calc_31);
  tcase_add_test(tc1_1, test_smart_calc_32);
  tcase_add_test(tc1_1, test_smart_calc_33);

  srunner_run_all(sr, CK_NORMAL);
  result = srunner_ntests_failed(sr);
  srunner_free(sr);
  return result == 0 ? 0 : 1;
}