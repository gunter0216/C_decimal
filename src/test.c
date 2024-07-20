#include <check.h>
#include <stdio.h>
#include "s21_decimal.h"
#include <limits.h>
#include <stdlib.h>

START_TEST(add_test_without_sdvig) {
    printf("---- s21_add_1 test\n");
    s21_decimal number = decimal_init2(0, 0, 0, 0, 0);
    s21_decimal test = decimal_init2(1, 0, 0, 0, 0);
    s21_decimal result = decimal_init2(1, 0, 0, 0, 0);
    number = s21_add(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(1, 0, 0, 0, 0);
    test = decimal_init2(1, 0, 0, 0, 0);
    result = decimal_init2(2, 0, 0, 0, 0);
    number = s21_add(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(UINT_MAX, 0, 0, 0, 0);
    test = decimal_init2(UINT_MAX, 0, 0, 0, 0);
    result = decimal_init2(UINT_MAX - 1, 1, 0, 0, 0);
    number = s21_add(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(0, UINT_MAX, 0, 0, 0);
    test = decimal_init2(0, UINT_MAX, 0, 0, 0);
    result = decimal_init2(0, UINT_MAX - 1, 1, 0, 0);
    number = s21_add(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(UINT_MAX, UINT_MAX, 0, 0, 0);
    test = decimal_init2(UINT_MAX, UINT_MAX, 0, 0, 0);
    result = decimal_init2(UINT_MAX - 1, UINT_MAX, 1, 0, 0);
    number = s21_add(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(UINT_MAX, UINT_MAX, 123, 0, 0);
    test = decimal_init2(UINT_MAX, UINT_MAX, 123, 0, 0);
    result = decimal_init2(UINT_MAX - 1, UINT_MAX, 1 + 123 + 123, 0, 0);
    number = s21_add(number, test);
    ck_assert(0 == s21_is_equal(number, result));
}
END_TEST

START_TEST(add_test_with_sdvig) {
    printf("---- s21_add_2 test\n");
    s21_decimal number = decimal_init2(123, 0, 0, 1, 0);
    s21_decimal test = decimal_init2(123, 0, 0, 1, 0);
    s21_decimal result = decimal_init2(246, 0, 0, 1, 0);
    number = s21_add(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(123, 0, 0, 1, 0);
    test = decimal_init2(123, 0, 0, 2, 0);
    result = decimal_init2(1353, 0, 0, 2, 0);
    number = s21_add(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(UINT_MAX, 0, 0, 0, 0);
    test = decimal_init2(UINT_MAX, 0, 0, 2, 0);
    result = decimal_init2(4294967195, 100, 0, 2, 0);
    number = s21_add(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(UINT_MAX, 0, 0, 28, 0);
    test = decimal_init2(UINT_MAX, 0, 0, 28, 0);
    result = decimal_init2(UINT_MAX - 1, 1, 0, 28, 0);
    number = s21_add(number, test);
    ck_assert(0 == s21_is_equal(number, result));
}
END_TEST

START_TEST(sub_test_without_sdvig) {
    printf("---- s21_sub_1 test\n");
    s21_decimal number = decimal_init2(123, 0, 0, 0, 0);
    s21_decimal test = decimal_init2(123, 0, 0, 0, 0);
    s21_decimal result = decimal_init2(0, 0, 0, 0, 0);
    number = s21_sub(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(UINT_MAX, 1, 0, 0, 0);
    test = decimal_init2(UINT_MAX, 0, 0, 0, 0);
    result = decimal_init2(0, 1, 0, 0, 0);
    number = s21_sub(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(UINT_MAX, 0, 0, 0, 0);
    test = decimal_init2(UINT_MAX, 1, 0, 0, 0);
    result = decimal_init2(0, 1, 0, 0, 1);
    number = s21_sub(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(0, 0, 0, 0, 0);
    test = decimal_init2(UINT_MAX, UINT_MAX, UINT_MAX, 0, 0);
    result = decimal_init2(UINT_MAX, UINT_MAX, UINT_MAX, 0, 1);
    number = s21_sub(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(UINT_MAX, UINT_MAX, UINT_MAX, 0, 0);
    test = decimal_init2(UINT_MAX, UINT_MAX, UINT_MAX, 0, 0);
    result = decimal_init2(0, 0, 0, 0, 0);
    number = s21_sub(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(123, 0, 0, 0, 1);
    test = decimal_init2(123, 0, 0, 0, 0);
    result = decimal_init2(246, 0, 0, 0, 1);
    number = s21_sub(number, test);
    ck_assert(0 == s21_is_equal(number, result));
}
END_TEST

START_TEST(sub_test_with_sdvig) {
    printf("---- s21_sub_2 test\n");
    s21_decimal number = decimal_init2(123, 0, 0, 1, 0);
    s21_decimal test = decimal_init2(123, 0, 0, 2, 0);
    s21_decimal result = decimal_init2(1107, 0, 0, 2, 0);
    number = s21_sub(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(0, 0, 777, 2, 0);
    test = decimal_init2(0, 0, 123, 2, 0);
    result = decimal_init2(0, 0, 654, 2, 0);
    number = s21_sub(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(123456, 0, 0, 2, 0);
    test = decimal_init2(123456, 0, 0, 4, 0);
    result = decimal_init2(12222144, 0, 0, 4, 0);
    number = s21_sub(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(UINT_MAX, 0, 0, 2, 0);
    test = decimal_init2(UINT_MAX, 0, 0, 4, 0);
    result = decimal_init2(4294967197, 98, 0, 4, 0);
    number = s21_sub(number, test);
    ck_assert(0 == s21_is_equal(number, result));
}
END_TEST

START_TEST(mul_test_without_sdvig) {
    printf("---- s21_mul_1 test\n");
    s21_decimal number = decimal_init2(UINT_MAX, 0, 0, 0, 0);
    s21_decimal test = decimal_init2(UINT_MAX, 0, 0, 0, 0);
    s21_decimal result = decimal_init2(1, UINT_MAX - 1, 0, 0, 0);
    number = s21_mul(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(5, 0, 0, 0, 0);
    test = decimal_init2(10, 0, 0, 0, 0);
    result = decimal_init2(50, 0, 0, 0, 0);
    number = s21_mul(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(5, 0, 0, 0, 0);
    test = decimal_init2(10, 0, 0, 0, 1);
    result = decimal_init2(50, 0, 0, 0, 1);
    number = s21_mul(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(5, 0, 0, 0, 1);
    test = decimal_init2(10, 0, 0, 0, 1);
    result = decimal_init2(50, 0, 0, 0, 0);
    number = s21_mul(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(UINT_MAX, UINT_MAX, 0, 0, 0);
    test = decimal_init2(UINT_MAX, 0, 0, 0, 0);
    result = decimal_init2(1, UINT_MAX, UINT_MAX - 1, 0, 0);
    number = s21_mul(number, test);
    ck_assert(0 == s21_is_equal(number, result));
}
END_TEST

START_TEST(mul_test_with_sdvig) {
    printf("---- s21_mul_1 test\n");
    s21_decimal number = decimal_init2(UINT_MAX, 0, 0, 2, 0);
    s21_decimal test = decimal_init2(UINT_MAX, 0, 0, 4, 0);
    s21_decimal result = decimal_init2(1, UINT_MAX - 1, 0, 6, 0);
    number = s21_mul(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(5, 0, 0, 0, 0);
    test = decimal_init2(10, 0, 0, 2, 0);
    result = decimal_init2(50, 0, 0, 2, 0);
    number = s21_mul(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(5, 0, 0, 10, 0);
    test = decimal_init2(10, 0, 0, 10, 1);
    result = decimal_init2(50, 0, 0, 20, 1);
    number = s21_mul(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(5, 0, 0, 9, 1);
    test = decimal_init2(10, 0, 0, 6, 1);
    result = decimal_init2(50, 0, 0, 15, 0);
    number = s21_mul(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(UINT_MAX, UINT_MAX, 0, 13, 0);
    test = decimal_init2(UINT_MAX, 0, 0, 0, 0);
    result = decimal_init2(1, UINT_MAX, UINT_MAX - 1, 13, 0);
    number = s21_mul(number, test);
    ck_assert(0 == s21_is_equal(number, result));
}
END_TEST

START_TEST(div_test_without_sdvig) {
    printf("---- s21_div_1 test\n");
    s21_decimal number = decimal_init2(100, 0, 0, 0, 0);
    s21_decimal test = decimal_init2(10, 0, 0, 0, 0);
    s21_decimal result = decimal_init2(10, 0, 0, 0, 0);
    number = s21_div(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(10, 0, 0, 0, 0);
    test = decimal_init2(10, 0, 0, 0, 0);
    result = decimal_init2(1, 0, 0, 0, 0);
    number = s21_div(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(UINT_MAX, UINT_MAX, UINT_MAX, 0, 0);
    test = decimal_init2(UINT_MAX, UINT_MAX, UINT_MAX, 0, 0);
    result = decimal_init2(1, 0, 0, 0, 0);
    number = s21_div(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(UINT_MAX, UINT_MAX, UINT_MAX, 0, 0);
    test = decimal_init2(UINT_MAX, 0, 0, 0, 0);
    result = decimal_init2(1, 1, 1, 0, 0);
    number = s21_div(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(UINT_MAX, UINT_MAX, UINT_MAX, 0, 0);
    test = decimal_init2(0, UINT_MAX, 0, 0, 0);
    result = decimal_init2(347022085, 347022085, 2328306437, 19, 0);
    number = s21_div(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(9, 0, 0, 0, 0);
    test = decimal_init2(7, 0, 0, 0, 0);
    result = decimal_init2(958698057, 3794769240, 696987110, 28, 0);
    number = s21_div(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(4, 0, 0, 0, 0);
    test = decimal_init2(6, 0, 0, 0, 0);
    result = decimal_init2(178956971, 695075222, 361400724, 28, 0);
    number = s21_div(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(7, 0, 0, 0, 1);
    test = decimal_init2(99, 0, 0, 0, 0);
    result = decimal_init2(2491840243, 3587784250, 38330379, 28, 1);
    number = s21_div(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(7, 0, 0, 0, 0);
    test = decimal_init2(99, 0, 0, 0, 1);
    result = decimal_init2(2491840243, 3587784250, 38330379, 28, 1);
    number = s21_div(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(7, 0, 0, 0, 1);
    test = decimal_init2(99, 0, 0, 0, 1);
    result = decimal_init2(2491840243, 3587784250, 38330379, 28, 0);
    number = s21_div(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(250, 0, 0, 0, 0);
    test = decimal_init2(4, 0, 0, 0, 0);
    result = decimal_init2(625, 0, 0, 1, 0);
    number = s21_div(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(12, 0, 0, 0, 0);
    test = decimal_init2(1, 0, 0, 0, 0);
    result = decimal_init2(12, 0, 0, 0, 0);
    number = s21_div(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(UINT_MAX, 0, 0, 0, 0);
    test = decimal_init2(1, 0, 0, 0, 0);
    result = decimal_init2(UINT_MAX, 0, 0, 0, 0);
    number = s21_div(number, test);
    ck_assert(0 == s21_is_equal(number, result));
}
END_TEST

START_TEST(div_test_with_sdvig) {
    printf("---- s21_div_2 test\n");
    s21_decimal number = decimal_init2(100, 0, 0, 1, 0);
    s21_decimal test = decimal_init2(10, 0, 0, 1, 0);
    s21_decimal result = decimal_init2(10, 0, 0, 0, 0);
    number = s21_div(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(1000, 0, 0, 2, 0);
    test = decimal_init2(10, 0, 0, 0, 0);
    result = decimal_init2(1, 0, 0, 0, 0);
    number = s21_div(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(UINT_MAX, UINT_MAX, UINT_MAX, 28, 0);
    test = decimal_init2(UINT_MAX, UINT_MAX, UINT_MAX, 28, 0);
    result = decimal_init2(1, 0, 0, 0, 0);
    number = s21_div(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(70, 0, 0, 1, 0);
    test = decimal_init2(9900, 0, 0, 2, 0);
    result = decimal_init2(2491840243, 3587784250, 38330379, 28, 0);
    number = s21_div(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(700, 0, 0, 28, 0);
    test = decimal_init2(990, 0, 0, 27, 0);
    result = decimal_init2(2491840243, 3587784250, 38330379, 28, 0);
    number = s21_div(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(4, 0, 0, 0, 0);
    test = decimal_init2(9, 0, 0, 0, 0);
    result = decimal_init2(1550960412, 463383481, 240933816, 28, 0);
    number = s21_div(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(4, 0, 0, 20, 0);
    test = decimal_init2(9, 0, 0, 10, 0);
    result = decimal_init2(293717788, 103480286, 0, 28, 0);
    number = s21_div(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(4, 0, 0, 10, 0);
    test = decimal_init2(9, 0, 0, 20, 0);
    result = decimal_init2(2624702236, 338867517, 2409338161, 19, 0);
    number = s21_div(number, test);
    ck_assert(0 == s21_is_equal(number, result));
}
END_TEST

START_TEST(mod_test_without_sdvig) {
    printf("---- s21_mod_1 test\n");
    s21_decimal number = decimal_init2(123, 0, 0, 0, 0);
    s21_decimal test = decimal_init2(123, 0, 0, 0, 0);
    s21_decimal result = decimal_init2(0, 0, 0, 0, 0);
    number = s21_mod(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(120, 0, 0, 0, 0);
    test = decimal_init2(7, 0, 0, 0, 0);
    result = decimal_init2(1, 0, 0, 0, 0);
    number = s21_mod(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(UINT_MAX, UINT_MAX, 0, 0, 0);
    test = decimal_init2(2, 0, 0, 0, 0);
    result = decimal_init2(1, 0, 0, 0, 0);
    number = s21_mod(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(UINT_MAX, UINT_MAX, 0, 0, 1);
    test = decimal_init2(2, 0, 0, 0, 0);
    result = decimal_init2(1, 0, 0, 0, 0);
    number = s21_mod(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(UINT_MAX, UINT_MAX, 0, 0, 0);
    test = decimal_init2(2, 0, 0, 0, 1);
    result = decimal_init2(1, 0, 0, 0, 0);
    number = s21_mod(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(UINT_MAX, UINT_MAX, 0, 0, 1);
    test = decimal_init2(2, 0, 0, 0, 1);
    result = decimal_init2(1, 0, 0, 0, 0);
    number = s21_mod(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(12, 0, 0, 0, 0);
    test = decimal_init2(1, 0, 0, 0, 0);
    result = decimal_init2(0, 0, 0, 0, 0);
    number = s21_mod(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(UINT_MAX, 0, 0, 0, 0);
    test = decimal_init2(1, 0, 0, 0, 0);
    result = decimal_init2(0, 0, 0, 0, 0);
    number = s21_mod(number, test);
    ck_assert(0 == s21_is_equal(number, result));
}
END_TEST

START_TEST(mod_test_with_sdvig) {
    printf("---- s21_mod_2 test\n");
    s21_decimal number = decimal_init2(123, 0, 0, 1, 0);
    s21_decimal test = decimal_init2(123, 0, 0, 1, 0);
    s21_decimal result = decimal_init2(0, 0, 0, 0, 0);
    number = s21_mod(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(60, 0, 0, 1, 0);
    test = decimal_init2(400, 0, 0, 2, 0);
    result = decimal_init2(2, 0, 0, 0, 0);
    number = s21_mod(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(70000, 0, 0, 4, 0);
    test = decimal_init2(5000000, 0, 0, 6, 0);
    result = decimal_init2(2, 0, 0, 0, 0);
    number = s21_mod(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(123, 0, 0, 1, 0);
    test = decimal_init2(10, 0, 0, 1, 0);
    result = decimal_init2(3, 0, 0, 1, 0);
    number = s21_mod(number, test);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(70, 0, 0, 1, 0);
    test = decimal_init2(4, 0, 0, 0, 0);
    result = decimal_init2(3, 0, 0, 0, 0);
    number = s21_mod(number, test);
    ck_assert(0 == s21_is_equal(number, result));
}
END_TEST

START_TEST(negate_test) {
    printf("---- s21_negate test\n");
    s21_decimal number = decimal_init2(123, 0, 0, 0, 1);
    s21_decimal result = decimal_init2(123, 0, 0, 0, 0);
    number = s21_negate(number);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(123, 0, 0, 0, 0);
    result = decimal_init2(123, 0, 0, 0, 1);
    number = s21_negate(number);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(123, 0, 0, 28, 0);
    result = decimal_init2(123, 0, 0, 28, 1);
    number = s21_negate(number);
    ck_assert(0 == s21_is_equal(number, result));
}
END_TEST

START_TEST(negate_type_test) {
    printf("---- s21_negate_type test\n");
    s21_decimal number = decimal_init();
    s21_decimal result = decimal_init();
    number.value_type = s21_INFINITY;
    result.value_type = s21_NEGATIVE_INFINITY;
    number = s21_negate(number);
    ck_assert(number.value_type == result.value_type);
    //
    number.value_type = s21_NEGATIVE_INFINITY;
    result.value_type = s21_INFINITY;
    number = s21_negate(number);
    ck_assert(number.value_type == result.value_type);
    //
    number.value_type = s21_NAN;
    result.value_type = s21_NAN;
    number = s21_negate(number);
    ck_assert(number.value_type == result.value_type);
}
END_TEST

START_TEST(trancate_test) {
    printf("---- s21_trancate test\n");
    s21_decimal number = decimal_init2(123, 0, 0, 0, 0);
    s21_decimal result = decimal_init2(123, 0, 0, 0, 0);
    number = s21_truncate(number);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(123, 0, 0, 1, 0);
    result = decimal_init2(12, 0, 0, 0, 0);
    number = s21_truncate(number);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(UINT_MAX, UINT_MAX, 0, 10, 0);
    result = decimal_init2(1844674407, 0, 0, 0, 0);
    number = s21_truncate(number);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(0, 0, 0, 10, 0);
    result = decimal_init2(0, 0, 0, 0, 0);
    number = s21_truncate(number);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(UINT_MAX, UINT_MAX, UINT_MAX, 28, 0);
    result = decimal_init2(7, 0, 0, 0, 0);
    number = s21_truncate(number);
    ck_assert(0 == s21_is_equal(number, result));
}
END_TEST

START_TEST(trancate_type_test) {
    printf("---- s21_trancate_type test\n");
    s21_decimal number = decimal_init();
    s21_decimal result = decimal_init();
    number.value_type = s21_INFINITY;
    result.value_type = s21_INFINITY;
    number = s21_truncate(number);
    ck_assert(number.value_type == result.value_type);
    //
    number.value_type = s21_NEGATIVE_INFINITY;
    result.value_type = s21_NEGATIVE_INFINITY;
    number = s21_truncate(number);
    ck_assert(number.value_type == result.value_type);
    //
    number.value_type = s21_NAN;
    result.value_type = s21_NAN;
    number = s21_truncate(number);
    ck_assert(number.value_type == result.value_type);
}
END_TEST

START_TEST(round_test) {
    printf("---- s21_round test\n");
    s21_decimal number = decimal_init2(123, 0, 0, 1, 0);
    s21_decimal result = decimal_init2(12, 0, 0, 0, 0);
    number = s21_round(number);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(125, 0, 0, 1, 0);
    result = decimal_init2(13, 0, 0, 0, 0);
    number = s21_round(number);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(1244445, 0, 0, 5, 0);
    result = decimal_init2(13, 0, 0, 0, 0);
    number = s21_round(number);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(1244444, 0, 0, 5, 0);
    result = decimal_init2(12, 0, 0, 0, 0);
    number = s21_round(number);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(0, 0, 0, 5, 0);
    result = decimal_init2(0, 0, 0, 0, 0);
    number = s21_round(number);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(UINT_MAX, 0, 0, 2, 0);
    result = decimal_init2(4, 1, 0, 2, 0);
    number = s21_round(number);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(UINT_MAX, 0, 0, 2, 1);
    result = decimal_init2(4, 1, 0, 2, 1);
    number = s21_round(number);
    ck_assert(0 == s21_is_equal(number, result));
}
END_TEST

START_TEST(round_type_test) {
    printf("---- s21_round_type test\n");
    s21_decimal number = decimal_init();
    s21_decimal result = decimal_init();
    number.value_type = s21_NAN;
    result.value_type = s21_NAN;
    number = s21_round(number);
    ck_assert(number.value_type == result.value_type);
    //
    number.value_type = s21_INFINITY;
    result.value_type = s21_INFINITY;
    number = s21_round(number);
    ck_assert(number.value_type == result.value_type);
    //
    number.value_type = s21_NEGATIVE_INFINITY;
    result.value_type = s21_NEGATIVE_INFINITY;
    number = s21_round(number);
    ck_assert(number.value_type == result.value_type);
}
END_TEST

START_TEST(floor_test) {
    printf("---- s21_floor test\n");
    s21_decimal number = decimal_init2(123, 0, 0, 1, 0);
    s21_decimal result = decimal_init2(12, 0, 0, 0, 0);
    number = s21_floor(number);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(12967, 0, 0, 3, 0);
    result = decimal_init2(12, 0, 0, 0, 0);
    number = s21_floor(number);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(12967, 0, 0, 3, 1);
    result = decimal_init2(13, 0, 0, 0, 1);
    number = s21_floor(number);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(0, 0, 0, 3, 1);
    result = decimal_init2(0, 0, 0, 0, 1);
    number = s21_floor(number);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(0, 0, 0, 3, 0);
    result = decimal_init2(0, 0, 0, 0, 0);
    number = s21_floor(number);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(355, 0, 0, 3, 0);
    result = decimal_init2(0, 0, 0, 0, 0);
    number = s21_floor(number);
    ck_assert(0 == s21_is_equal(number, result));
    //
    number = decimal_init2(355, 0, 0, 3, 1);
    result = decimal_init2(1, 0, 0, 0, 1);
    number = s21_floor(number);
    ck_assert(0 == s21_is_equal(number, result));
}
END_TEST

START_TEST(floor_type_test) {
    printf("---- s21_floor_type test\n");
    s21_decimal number = decimal_init();
    s21_decimal result = decimal_init();
    number.value_type = s21_INFINITY;
    result.value_type = s21_INFINITY;
    number = s21_floor(number);
    ck_assert(number.value_type == result.value_type);
    //
    number.value_type = s21_NEGATIVE_INFINITY;
    result.value_type = s21_NEGATIVE_INFINITY;
    number = s21_floor(number);
    ck_assert(number.value_type == result.value_type);
    //
    number.value_type = s21_NAN;
    result.value_type = s21_NAN;
    number = s21_floor(number);
    ck_assert(number.value_type == result.value_type);
}
END_TEST

START_TEST(add_type_test) {
    printf("---- s21_add_type test\n");
    s21_decimal number1 = decimal_init();
    s21_decimal number2 = decimal_init();
    s21_decimal result = decimal_init();
    //
    number1.value_type = s21_INFINITY;
    number2.value_type = s21_INFINITY;
    result.value_type = s21_INFINITY;
    number1 = s21_add(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1.value_type = s21_INFINITY;
    number2.value_type = s21_NEGATIVE_INFINITY;
    result.value_type = s21_NORMAL_VALUE;
    number1 = s21_add(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1.value_type = s21_NEGATIVE_INFINITY;
    number2.value_type = s21_INFINITY;
    result.value_type = s21_NORMAL_VALUE;
    number1 = s21_add(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1.value_type = s21_NEGATIVE_INFINITY;
    number2.value_type = s21_NEGATIVE_INFINITY;
    result.value_type = s21_NEGATIVE_INFINITY;
    number1 = s21_add(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1.value_type = s21_NAN;
    number2.value_type = s21_NORMAL_VALUE;
    result.value_type = s21_NAN;
    number1 = s21_add(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1.value_type = s21_NORMAL_VALUE;
    number2.value_type = s21_NAN;
    result.value_type = s21_NAN;
    number1 = s21_add(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1 = decimal_init2(UINT_MAX, UINT_MAX, UINT_MAX, 0, 0);
    number2 = decimal_init2(UINT_MAX, UINT_MAX, UINT_MAX, 0, 0);
    number1.value_type = s21_NORMAL_VALUE;
    number2.value_type = s21_NORMAL_VALUE;
    result.value_type = s21_NAN;
    number1 = s21_add(number1, number2);
    ck_assert(number1.value_type == result.value_type);
}
END_TEST

START_TEST(sub_type_test) {
    printf("---- s21_sub_type test\n");
    s21_decimal number1 = decimal_init();
    s21_decimal number2 = decimal_init();
    s21_decimal result = decimal_init();
    //
    number1.value_type = s21_INFINITY;
    number2.value_type = s21_INFINITY;
    result.value_type = s21_NORMAL_VALUE;
    number1 = s21_sub(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1.value_type = s21_INFINITY;
    number2.value_type = s21_NEGATIVE_INFINITY;
    result.value_type = s21_INFINITY;
    number1 = s21_sub(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1.value_type = s21_NEGATIVE_INFINITY;
    number2.value_type = s21_INFINITY;
    result.value_type = s21_NEGATIVE_INFINITY;
    number1 = s21_sub(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1.value_type = s21_NEGATIVE_INFINITY;
    number2.value_type = s21_NEGATIVE_INFINITY;
    result.value_type = s21_NORMAL_VALUE;
    number1 = s21_sub(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1.value_type = s21_NAN;
    number2.value_type = s21_NORMAL_VALUE;
    result.value_type = s21_NAN;
    number1 = s21_sub(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1.value_type = s21_NORMAL_VALUE;
    number2.value_type = s21_NAN;
    result.value_type = s21_NAN;
    number1 = s21_sub(number1, number2);
    ck_assert(number1.value_type == result.value_type);
}
END_TEST

START_TEST(mul_type_test) {
    printf("---- s21_mul_type test\n");
    s21_decimal number1 = decimal_init();
    s21_decimal number2 = decimal_init();
    s21_decimal result = decimal_init();
    //
    number1.value_type = s21_INFINITY;
    number2.value_type = s21_INFINITY;
    result.value_type = s21_INFINITY;
    number1 = s21_mul(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1.value_type = s21_INFINITY;
    number2.value_type = s21_NEGATIVE_INFINITY;
    result.value_type = s21_NEGATIVE_INFINITY;
    number1 = s21_mul(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1.value_type = s21_NEGATIVE_INFINITY;
    number2.value_type = s21_INFINITY;
    result.value_type = s21_NEGATIVE_INFINITY;
    number1 = s21_mul(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1.value_type = s21_NEGATIVE_INFINITY;
    number2.value_type = s21_NEGATIVE_INFINITY;
    result.value_type = s21_INFINITY;
    number1 = s21_mul(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1.value_type = s21_NAN;
    number2.value_type = s21_NORMAL_VALUE;
    result.value_type = s21_NAN;
    number1 = s21_mul(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1.value_type = s21_NORMAL_VALUE;
    number2.value_type = s21_NAN;
    result.value_type = s21_NAN;
    number1 = s21_mul(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1 = decimal_init2(UINT_MAX, UINT_MAX, UINT_MAX, 0, 0);
    number2 = decimal_init2(UINT_MAX, UINT_MAX, UINT_MAX, 0, 0);
    number1.value_type = s21_NORMAL_VALUE;
    number2.value_type = s21_NORMAL_VALUE;
    result.value_type = s21_NAN;
    number1 = s21_mul(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1 = decimal_init2(UINT_MAX, UINT_MAX, 0, 0, 0);
    number2 = decimal_init2(UINT_MAX, UINT_MAX, 0, 0, 0);
    number1.value_type = s21_NORMAL_VALUE;
    number2.value_type = s21_NORMAL_VALUE;
    result.value_type = s21_NAN;
    number1 = s21_mul(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1 = decimal_init2(UINT_MAX, 0, 0, 15, 0);
    number2 = decimal_init2(UINT_MAX, 0, 0, 15, 0);
    number1.value_type = s21_NORMAL_VALUE;
    number2.value_type = s21_NORMAL_VALUE;
    result.value_type = s21_NAN;
    number1 = s21_mul(number1, number2);
    ck_assert(number1.value_type == result.value_type);
}
END_TEST

START_TEST(div_type_test) {
    printf("---- s21_div_type test\n");
    s21_decimal number1 = decimal_init();
    s21_decimal number2 = decimal_init();
    s21_decimal result = decimal_init();
    s21_decimal result1 = decimal_init2(1, 0, 0, 0, 0);
    s21_decimal result2 = decimal_init2(1, 0, 0, 0, 1);
    //
    number1.value_type = s21_INFINITY;
    number2.value_type = s21_INFINITY;
    number1 = s21_div(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1.value_type = s21_INFINITY;
    number2.value_type = s21_NEGATIVE_INFINITY;
    number1 = s21_div(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1.value_type = s21_NEGATIVE_INFINITY;
    number2.value_type = s21_INFINITY;
    number1 = s21_div(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1.value_type = s21_NEGATIVE_INFINITY;
    number2.value_type = s21_NEGATIVE_INFINITY;
    number1 = s21_div(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1.value_type = s21_NAN;
    number2.value_type = s21_NORMAL_VALUE;
    result.value_type = s21_NAN;
    number1 = s21_div(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1.value_type = s21_NORMAL_VALUE;
    number2.value_type = s21_NAN;
    result.value_type = s21_NAN;
    number1 = s21_div(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1 = decimal_init2(777, 0, 0, 0, 0);
    number2 = decimal_init2(0, 0, 0, 0, 0);
    result.value_type = s21_NAN;
    number1 = s21_div(number1, number2);
    ck_assert(number1.value_type == result.value_type);
}
END_TEST

START_TEST(mod_type_test) {
    printf("---- s21_mod_type test\n");
    s21_decimal number1 = decimal_init();
    s21_decimal number2 = decimal_init();
    s21_decimal result = decimal_init();
    //
    number1.value_type = s21_INFINITY;
    number2.value_type = s21_INFINITY;
    number1 = s21_mod(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1.value_type = s21_INFINITY;
    number2.value_type = s21_NEGATIVE_INFINITY;
    number1 = s21_mod(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1.value_type = s21_NEGATIVE_INFINITY;
    number2.value_type = s21_INFINITY;
    number1 = s21_mod(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1.value_type = s21_NEGATIVE_INFINITY;
    number2.value_type = s21_NEGATIVE_INFINITY;
    number1 = s21_mod(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1.value_type = s21_NAN;
    number2.value_type = s21_NORMAL_VALUE;
    result.value_type = s21_NAN;
    number1 = s21_mod(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1.value_type = s21_NORMAL_VALUE;
    number2.value_type = s21_NAN;
    result.value_type = s21_NAN;
    number1 = s21_mod(number1, number2);
    ck_assert(number1.value_type == result.value_type);
    //
    number1 = decimal_init2(777, 0, 0, 0, 0);
    number2 = decimal_init2(0, 0, 0, 0, 0);
    result.value_type = s21_NAN;
    number1 = s21_mod(number1, number2);
    ck_assert(number1.value_type == result.value_type);
}
END_TEST

START_TEST(is_less_test) {
    printf("---- s21_is_less test\n");
    s21_decimal num1 = decimal_init2(10, 78, 0, 0, 0);
    s21_decimal num2 = decimal_init2(10, 78, 0, 0, 0);
    ck_assert(1 == s21_is_less(num1, num2));
    //
    num1 = decimal_init2(11, 26346, 3, 4, 0);
    num2 = decimal_init2(11, 26346, 3, 3, 0);
    ck_assert(0 == s21_is_less(num1, num2));
    //
    num1 = decimal_init2(12, 235, 2365, 0, 0);
    num2 = decimal_init2(11, 0, 3, 0, 1);
    ck_assert(1 == s21_is_less(num1, num2));
    //
    num1 = decimal_init2(0, 0, 0, 0, 1);
    num2 = decimal_init2(0, 0, 0, 0, 0);
    ck_assert(0 == s21_is_less(num1, num2));
    //
    num1 = decimal_init2(11, 26346, 23525, 6, 0);
    num2 = decimal_init2(11, 26346, 3, 3, 0);
    ck_assert(1 == s21_is_less(num1, num2));
}
END_TEST

START_TEST(is_less_or_equal_test) {
    printf("---- s21_is_less_or_equal test\n");
    s21_decimal num1 = decimal_init2(10, 78, 0, 0, 0);
    s21_decimal num2 = decimal_init2(10, 78, 0, 0, 0);
    ck_assert(0 == s21_is_less_or_equal(num1, num2));
    //
    num1 = decimal_init2(11, 26346, 3, 4, 0);
    num2 = decimal_init2(11, 26346, 3, 3, 0);
    ck_assert(0 == s21_is_less_or_equal(num1, num2));
    //
    num1 = decimal_init2(12, 235, 2365, 0, 0);
    num2 = decimal_init2(11, 0, 3, 0, 1);
    ck_assert(1 == s21_is_less_or_equal(num1, num2));
    //
    num1 = decimal_init2(0, 0, 0, 0, 1);
    num2 = decimal_init2(0, 0, 0, 0, 0);
    ck_assert(0 == s21_is_less_or_equal(num1, num2));
    //
    num1 = decimal_init2(11, 26346, 23525, 6, 0);
    num2 = decimal_init2(11, 26346, 3, 3, 0);
    ck_assert(1 == s21_is_less_or_equal(num1, num2));
}
END_TEST

START_TEST(is_greater_test) {
    printf("---- s21_is_greater test\n");
    s21_decimal num1 = decimal_init2(10, 78, 0, 0, 0);
    s21_decimal num2 = decimal_init2(10, 78, 0, 0, 0);
    ck_assert(1 == s21_is_greater(num1, num2));
    //
    num1 = decimal_init2(11, 26346, 3, 4, 0);
    num2 = decimal_init2(11, 26346, 3, 3, 0);
    ck_assert(1 == s21_is_greater(num1, num2));
    //
    num1 = decimal_init2(12, 235, 2365, 0, 1);
    num2 = decimal_init2(11, 0, 3, 0, 0);
    ck_assert(1 == s21_is_greater(num1, num2));
    //
    num1 = decimal_init2(535, 35, 2, 0, 0);
    num2 = decimal_init2(0, 2135, 0, 0, 1);
    ck_assert(0 == s21_is_greater(num1, num2));
    //
    num1 = decimal_init2(11, 26346, 23525, 6, 0);
    num2 = decimal_init2(11, 26346, 3, 3, 0);
    ck_assert(0 == s21_is_greater(num1, num2));
}
END_TEST

START_TEST(is_greater_or_equal) {
    printf("---- s21_is_greater_or_equal test\n");
    s21_decimal num1 = decimal_init2(10, 78, 0, 6, 1);
    s21_decimal num2 = decimal_init2(10, 78, 0, 6, 1);
    ck_assert(0 == s21_is_greater_or_equal(num1, num2));
    //
    num1 = decimal_init2(11, 26346, 3, 4, 0);
    num2 = decimal_init2(11, 26346, 3, 3, 0);
    ck_assert(1 == s21_is_greater_or_equal(num1, num2));
    //
    num1 = decimal_init2(12, 235, 2365, 0, 1);
    num2 = decimal_init2(11, 0, 3, 0, 0);
    ck_assert(1 == s21_is_greater_or_equal(num1, num2));
    //
    num1 = decimal_init2(535, 35, 2, 0, 0);
    num2 = decimal_init2(0, 2135, 0, 0, 1);
    ck_assert(0 == s21_is_greater_or_equal(num1, num2));
    //
    num1 = decimal_init2(11, 26346, 23525, 6, 0);
    num2 = decimal_init2(11, 26346, 3, 3, 0);
    ck_assert(0 == s21_is_greater_or_equal(num1, num2));
}
END_TEST

START_TEST(is_equal) {
    printf("---- s21_is_equal test\n");
    s21_decimal num1 = decimal_init2(10, 78, 0, 6, 1);
    s21_decimal num2 = decimal_init2(10, 78, 0, 6, 1);
    ck_assert(0 == s21_is_equal(num1, num2));
    //
    num1 = decimal_init2(11, 26346, 3, 4, 0);
    num2 = decimal_init2(11, 26346, 3, 3, 0);
    ck_assert(1 == s21_is_equal(num1, num2));
    //
    num1 = decimal_init2(0, 0, 0, 0, 0);
    num2 = decimal_init2(0, 0, 0, 0, 0);
    ck_assert(0 == s21_is_equal(num1, num2));
    //
    num1 = decimal_init2(259, 259, 259, 23, 0);
    num2 = decimal_init2(259, 259, 259, 23, 0);
    ck_assert(0 == s21_is_equal(num1, num2));
}
END_TEST

START_TEST(is_not_equal) {
    printf("---- s21_is_not_equal test\n");
    s21_decimal num1 = decimal_init2(10, 78, 0, 6, 1);
    s21_decimal num2 = decimal_init2(10, 78, 0, 6, 1);
    ck_assert(1 == s21_is_not_equal(num1, num2));
    //
    num1 = decimal_init2(11, 26346, 3, 4, 0);
    num2 = decimal_init2(11, 26346, 3, 3, 0);
    ck_assert(0 == s21_is_not_equal(num1, num2));
    //
    num1 = decimal_init2(12, 235, 2365, 0, 0);
    num2 = decimal_init2(11, 0, 3, 0, 1);
    ck_assert(0 == s21_is_not_equal(num1, num2));
}
END_TEST

START_TEST(from_int_to_decimal) {
    printf("---- s21_from_int_to_decimal test\n");
    long int temp;
    s21_decimal number = decimal_init2(0, 0, 0, 0, 0);
    s21_decimal result = decimal_init2(INT32_MAX, 0, 0, 0, 0);
    s21_from_int_to_decimal(INT32_MAX, &number);
    ck_assert(0 == s21_is_equal(number, result));
    //
    temp = INT32_MIN;
    temp *= -1;
    result = decimal_init2(temp, 0, 0, 0, 1);
    s21_from_int_to_decimal(INT32_MIN, &number);
    ck_assert(0 == s21_is_equal(number, result));
    //
    result = decimal_init2(0, 0, 0, 0, 0);
    s21_from_int_to_decimal(0, &number);
    ck_assert(0 == s21_is_equal(number, result));
}
END_TEST

START_TEST(from_float_to_decimal) {
    printf("---- s21_from_float_to_decimal test\n");
    s21_decimal number = decimal_init2(0, 0, 0, 0, 0);
    s21_decimal result = decimal_init2(123353, 0, 0, 3, 0);
    s21_from_float_to_decimal(123.353, &number);
    ck_assert(0 == s21_is_equal(number, result));
    //
    result = decimal_init2(123457, 0, 0, 16, 1);
    s21_from_float_to_decimal(-0.0000000000123456789, &number);
    ck_assert(0 == s21_is_equal(number, result));
    //
    result = decimal_init2(123457, 0, 0, 16, 1);
    ck_assert(1 ==  s21_from_float_to_decimal(-9e28, &number));
    //
    result = decimal_init2(0, 0, 0, 0, 0);
    s21_from_float_to_decimal(-0.0000000000000000000000000000000123456789, &number);
    ck_assert(0 == s21_is_equal(number, result));
    //
    result = decimal_init2(2550136832, 1364693707, 4282598581, 0, 0);
    s21_from_float_to_decimal(7.9e28, &number);
    ck_assert(0 == s21_is_equal(number, result));
}
END_TEST

START_TEST(from_decimal_to_int) {
    printf("---- s21_from_decimal_to_int test\n");
    unsigned int temp;
    int a = 0;
    s21_decimal number = decimal_init2(INT_MAX, 0, 0, 0, 0);
    s21_from_decimal_to_int(number, &a);
    ck_assert(a == INT_MAX);
    //
    temp = INT_MAX;
    temp++;
    number = decimal_init2(temp, 0, 0, 0, 1);
    s21_from_decimal_to_int(number, &a);
    ck_assert(a == INT32_MIN);
    //
    number = decimal_init2(25888, 346, 0, 0, 0);
    ck_assert(1 == s21_from_decimal_to_int(number, &a));
    //
    number = decimal_init2(2147483647, 1, 0, 3, 0);
    s21_from_decimal_to_int(number, &a);
    ck_assert(a == 6442450);
}
END_TEST

START_TEST(from_decimal_to_float) {
    printf("---- s21_from_decimal_to_float test\n");
    char str[20] = "";
    float a = 0;
    s21_decimal number = decimal_init2(123353, 0, 0, 3, 0);
    s21_from_decimal_to_float(number, &a);
    snprintf(str, 19 * sizeof(char), "%g", a);
    ck_assert_str_eq("123.353", str);
    //
    number = decimal_init2(123457, 0, 0, 16, 1);
    s21_from_decimal_to_float(number, &a);
    snprintf(str, 19 * sizeof(char), "%g", a);
    ck_assert_str_eq("-1.23457e-11", str);
    //
    number = decimal_init2(2550136832, 1364693707, 4282598581, 0, 0);
    s21_from_decimal_to_float(number, &a);
    snprintf(str, 19 * sizeof(char), "%g", a);
    ck_assert_str_eq("7.9e+28", str);
    //
    number = decimal_init2(123457, 0, 0, 16, 1);
    number.value_type = s21_INFINITY;
    ck_assert(1 == s21_from_decimal_to_float(number, &a));
}
END_TEST

START_TEST(comparison_value_type_test) {
    s21_decimal num1 = decimal_init2(10, 78, 4, 0, 0);
    s21_decimal num2 = decimal_init2(10, 78, 0, 0, 1);
    num1.value_type = s21_NEGATIVE_INFINITY;
    num2.value_type = s21_INFINITY;
    ck_assert(0 == s21_is_less(num1, num2));
    //
    num1 = decimal_init2(10, 73218, 4, 0, 0);
    num2 = decimal_init2(10213, 43, 0, 0, 0);
    num1.value_type = s21_NAN;
    ck_assert(1 == s21_is_equal(num1, num2));
    //
    num1 = decimal_init2(10, 73218, 4, 0, 1);
    num2 = decimal_init2(10213, 43, 0, 0, 0);
    num1.value_type = s21_NORMAL_VALUE;
    num2.value_type = s21_INFINITY;
    ck_assert(0 == s21_is_less(num1, num2));
}
END_TEST

int main(void) {
    Suite *s1 = suite_create("Core");  // Объявляем сьюит
    SRunner *sr = srunner_create(s1);  // Лаунчер сьюита
    int failed_count;  // Статус тестов сьюита
    TCase *Case = tcase_create("Test");  // Новый кейс
    TCase *Comparison = tcase_create("СomparisonTest");
    TCase *Converters = tcase_create("ConvertersTest");
    suite_add_tcase(s1, Case);  // Добавляем кейс
    suite_add_tcase(s1, Comparison);
    suite_add_tcase(s1, Converters);

    tcase_add_test(Case, add_test_without_sdvig);
    tcase_add_test(Case, add_test_with_sdvig);
    tcase_add_test(Case, add_type_test);

    tcase_add_test(Case, sub_test_without_sdvig);
    tcase_add_test(Case, sub_test_with_sdvig);
    tcase_add_test(Case, sub_type_test);

    tcase_add_test(Case, mul_test_without_sdvig);
    tcase_add_test(Case, mul_test_with_sdvig);
    tcase_add_test(Case, mul_type_test);

    tcase_add_test(Case, div_test_without_sdvig);
    tcase_add_test(Case, div_test_with_sdvig);
    tcase_add_test(Case, div_type_test);

    tcase_add_test(Case, mod_test_without_sdvig);
    tcase_add_test(Case, mod_test_with_sdvig);
    tcase_add_test(Case, mod_type_test);

    tcase_add_test(Case, negate_test);
    tcase_add_test(Case, negate_type_test);

    tcase_add_test(Case, trancate_test);
    tcase_add_test(Case, trancate_type_test);

    tcase_add_test(Case, round_test);
    tcase_add_test(Case, round_type_test);

    tcase_add_test(Case, floor_test);
    tcase_add_test(Case, floor_type_test);

    tcase_add_test(Comparison, is_less_test);
    tcase_add_test(Comparison, is_less_or_equal_test);
    tcase_add_test(Comparison, is_greater_test);
    tcase_add_test(Comparison, is_greater_or_equal);
    tcase_add_test(Comparison, is_equal);
    tcase_add_test(Comparison, is_not_equal);
    tcase_add_test(Comparison, comparison_value_type_test);

    tcase_add_test(Converters, from_int_to_decimal);
    tcase_add_test(Converters, from_float_to_decimal);
    tcase_add_test(Converters, from_decimal_to_int);
    tcase_add_test(Converters, from_decimal_to_float);

    srunner_run_all(sr, CK_ENV);
    failed_count = srunner_ntests_failed(sr);
    srunner_free(sr);

    return 0;
}
