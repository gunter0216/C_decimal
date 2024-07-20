#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

typedef enum {
    s21_NORMAL_VALUE = 0,
    s21_INFINITY = 1,
    s21_NEGATIVE_INFINITY = 2,
    s21_NAN = 3
} value_type_t;

typedef struct {
    int bits[4];
    value_type_t value_type;
} s21_decimal;

s21_decimal decimal_init();
s21_decimal decimal_init2(
    unsigned int n1, unsigned int n2, unsigned int n3, unsigned int n4, unsigned int n5);

s21_decimal s21_add(s21_decimal num1, s21_decimal num2);  // +
s21_decimal s21_sub(s21_decimal num1, s21_decimal num2);  // -
s21_decimal s21_mul(s21_decimal num1, s21_decimal num2);  // *
s21_decimal s21_div(s21_decimal num1, s21_decimal num2);  // /
s21_decimal s21_mod(s21_decimal num1, s21_decimal num2);  // %

int s21_is_less(s21_decimal num1, s21_decimal num2);            // <
int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2);   // <=
int s21_is_greater(s21_decimal num1, s21_decimal num2);         // >
int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2);  // >=
int s21_is_equal(s21_decimal num1, s21_decimal num2);           // ==
int s21_is_not_equal(s21_decimal num1, s21_decimal num2);       // !=

s21_decimal s21_floor(s21_decimal);  // Округляет в сторону отрицательной бесконечности
s21_decimal s21_round(s21_decimal);  // Округляет Decimal до ближайшего целого числа
s21_decimal s21_truncate(s21_decimal num1);  // Возвращает только целые цифры, дробные отбрасываются
s21_decimal s21_negate(s21_decimal num);    // инвертирует знак '+' -> '-'; '-' -> '+'

int s21_from_int_to_decimal(int src, s21_decimal *dst);      // из int
int s21_from_float_to_decimal(float src, s21_decimal *dst);  // из float
int s21_from_decimal_to_int(s21_decimal src, int *dst);      // в int
int s21_from_decimal_to_float(s21_decimal src, float *dst);  // в float

#endif  // SRC_S21_DECIMAL_H_
