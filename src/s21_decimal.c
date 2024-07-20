#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "s21_decimal.h"
#include <limits.h>
#include <string.h>

int comparison(s21_decimal num1, s21_decimal num2, int stepen);  // 1 - меньше, 2 - больше, 3 - равны
void writeUnit(s21_decimal *num1, int num2);     // записывает единицу в бит num2 считая слево
s21_decimal delete_zero(s21_decimal num);
s21_decimal getOstatok(s21_decimal num);
int shift(s21_decimal *num1, int num2);          //  сдвигает двоичное представление на 1 вправо
void unShift(s21_decimal *num1, int num2);       //  сдвигает двоичное представление на 1 влево
unsigned long int* readMantis(s21_decimal num);  //  1010 -> unsigned long int[3]
void writeMantis(s21_decimal *num1, unsigned long int *num2);  //  записывает в манту из массива целых чисел
int shift10(s21_decimal *num, int count);        //  умножает число на 10
void freeMantis(s21_decimal *num);               //  зануляет мантису
int getSymbol(s21_decimal num1);                 //  возвращает знак +-
void setSymbol(s21_decimal *num1, int num2);     //  устанавливает знак +-
unsigned long int* createArr3(
    unsigned long int n1, unsigned long int n2, unsigned long int n3);  // create long int[3]
int getStepen(s21_decimal num1);                //  берёт степень смещения
void setStepen(s21_decimal *num1, int num2);    //  устанавливает степень смещения
void add2(s21_decimal *number, s21_decimal *num1, s21_decimal *num2);
int mul2(unsigned long int *n1, unsigned long int *n2, unsigned long int *n3, int iter);
s21_decimal mul3(s21_decimal num1, s21_decimal num2);
s21_decimal div_after_point(
    s21_decimal num, s21_decimal num1, s21_decimal num2, int umnogilNa10, int *numStepen);
s21_decimal div2(s21_decimal num1, s21_decimal num2);
s21_decimal div_before_point(
        s21_decimal *num, s21_decimal num1, s21_decimal *num2);
s21_decimal mod2(s21_decimal num1, s21_decimal num2);

s21_decimal decimal_init() {
    s21_decimal num = { { 0, 0, 0, 0 }, 0 };
    return num;
}

s21_decimal decimal_init2(
        unsigned int n1, unsigned int n2, unsigned int n3, unsigned int n4, unsigned int n5) {
    s21_decimal num = { { n1, n2, n3, 0 }, 0 };
    setStepen(&num, n4);
    setSymbol(&num, n5);
    return num;
}

int getStepen(s21_decimal num1) {
    int num = 0;
    for (int i = 16; i <= 23; i++) {
        num += (_Bool)((1 << i) & num1.bits[3]) * pow(2, i - 16);
    }
    return num;
}

void setStepen(s21_decimal *num1, int num2) {
    for (int i = 16; i <= 23; i++) {
        num1 -> bits[3] &= ~(1 << i);
    }
    for (int i = 16; i <= 23; i++) {
        num1 -> bits[3] |= (num2 % 2) << i;
        num2 /= 2;
    }
}

int getSymbol(s21_decimal num1) {
    return (_Bool)((1 << 31) & num1.bits[3]);
}

void setSymbol(s21_decimal *num1, int num2) {   //  1 : '-'; 0 : '+';
    int symbol = getSymbol(*num1);
    if (num2 == 1 && symbol != 1)
        num1 -> bits[3] |= 1 << 31;
    else if (num2 == 0 && symbol != 0)
        num1 -> bits[3] &= ~(1 << 31);
}

s21_decimal s21_negate(s21_decimal num) {
    if (num.value_type == s21_NORMAL_VALUE) {
        num.bits[3] ^= (1 << 31);
    } else if (num.value_type == s21_INFINITY) {
        num.value_type = s21_NEGATIVE_INFINITY;
    } else if (num.value_type == s21_NEGATIVE_INFINITY) {
        num.value_type = s21_INFINITY;
    } else {
        num.value_type = s21_NAN;
    }
    return num;
}

int getLastBool(s21_decimal num) {
    return (_Bool)((1 << 31) & num.bits[2]);
}

int shift(s21_decimal *num1, int num2) {
    int error = 0;
    for (int i = 0; i < num2; i++) {
        int x = num1 -> bits[2] & (1 << 31);
        if (x != 0)
            error = 1;
        num1 -> bits[2] = num1 -> bits[2] << 1;
        num1 -> bits[2] &= ~(1 << 0);
        x = num1 -> bits[1] & (1 << 31);
        if (x != 0)
            num1 -> bits[2] |= (1 << 0);
        num1 -> bits[1] = num1 -> bits[1] << 1;
        num1 -> bits[1] &= ~(1 << 0);
        x = num1 -> bits[0] & (1 << 31);
        if (x != 0)
            num1 -> bits[1] |= (1 << 0);
        num1 -> bits[0] = num1 -> bits[0] << 1;
        num1 -> bits[0] &= ~(1 << 0);
    }
    return error;
}

void unShift(s21_decimal *num1, int num2) {
    for (int i = 0; i < num2; i++) {
        int x;
        num1 -> bits[0] = num1 -> bits[0] >> 1;
        num1 -> bits[0] &= ~(1 << 31);
        x = num1 -> bits[1] & (1 << 0);
        if (x != 0)
            num1 -> bits[0] |= (1 << 31);
        num1 -> bits[1] = num1 -> bits[1] >> 1;
        num1 -> bits[1] &= ~(1 << 31);
        x = num1 -> bits[2] & (1 << 0);
        if (x != 0)
            num1 -> bits[1] |= (1 << 31);
        num1 -> bits[2] = num1 -> bits[2] >> 1;
        num1 -> bits[2] &= ~(1 << 31);
    }
}

void writeUnit(s21_decimal *num1, int num2) {
    num1 -> bits[num2 / 32] |= (1 << (num2 % 32));
}

void writeMantis(s21_decimal *num1, unsigned long int *num2) {
    freeMantis(num1);
    for (int i = 0; i < 3; i++) {
        num1 -> bits[i] = num2[i];
    }
}

void freeMantis(s21_decimal *num) {
    for (int i = 0; i < 3; i++) {
        num -> bits[i] = 0;
    }
}

unsigned long int* createArr3(unsigned long int n1, unsigned long int n2, unsigned long int n3) {
    unsigned long int *n = (unsigned long int*)malloc(3 * sizeof(unsigned long int));
    n[0] = n1;
    n[1] = n2;
    n[2] = n3;
    return n;
}

int shift10(s21_decimal *num, int count) {
    int error = 0;
    for (int i = 0; i < count; i++) {
        unsigned long int *n = readMantis(*num);
        n[0] *= 10;
        n[1] *= 10;
        n[2] *= 10;
        while (n[0] > UINT_MAX) {
            n[1] = n[1] + 1;
            n[0] = n[0] - UINT_MAX - 1;
        }
        while (n[1] > UINT_MAX) {
            n[2] = n[2] + 1;
            n[1] = n[1] - UINT_MAX - 1;
        }
        if (n[2] >= UINT_MAX)
            error = 1;
        if (error == 0)
            writeMantis(num, n);
        free(n);
    }
    return error;
}

int isZero(s21_decimal num) {
    int temp = 0;
    unsigned long int *arr = readMantis(num);
    if (arr[0] == 0 && arr[1] == 0 && arr[2] == 0)
        temp = 1;
    free(arr);
    return temp;
}

unsigned long int* readMantis(s21_decimal num) {
    unsigned long int *arr = (unsigned long int*)malloc(3 * sizeof(unsigned long int));
    for (int i = 0; i < 3; i++)
        arr[i] = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 32; j++) {
            arr[i] += (_Bool)((1 << j) & num.bits[i]) * pow(2, j);
        }
    }
    return arr;
}

void add2(s21_decimal *number, s21_decimal *num1, s21_decimal *num2) {
    int s1 = getStepen(*num1);
    int s2 = getStepen(*num2);
    if (s1 < s2) {
        setStepen(number, s2);
        shift10(num1, s2 - s1);
    } else {
        setStepen(number, s1);
        shift10(num2, s1 - s2);
    }
    long int *n1 = readMantis(*num1);
    long int *n2 = readMantis(*num2);
    long int *n3 = createArr3(0, 0, 0);
    if (getSymbol(*num1) == getSymbol(*num2)) {
        setSymbol(number, getSymbol(*num1));
        for (int i = 0; i < 3; i++)
            n3[i] = n2[i] + n1[i];
        for (int i = 0; i < 2; i++) {
            if (n3[i] > UINT_MAX) {
                n3[i + 1]++;
                n3[i] -= UINT_MAX + 1;
            }
        }
        if (n3[2] > UINT_MAX) {
            number -> value_type = s21_NAN;
        }
    } else {
        int sym1 = getSymbol(*num1);
        int sym2 = getSymbol(*num2);
        setSymbol(num1, 0);
        setSymbol(num2, 0);
        int whoIsMore = s21_is_less(*num1, *num2);
        for (int i = 0; i < 3; i++) {
            if (whoIsMore == 0)
                n3[i] = n2[i] - n1[i];
            else
                n3[i] = n1[i] - n2[i];
        }
        for (int i = 0; i < 2; i++) {
            if (n3[i] < 0) {
                n3[i + 1]--;
                n3[i] = n3[i] + UINT_MAX + 1;
            }
        }
        if (whoIsMore == 0)
            setSymbol(number, sym2);
        else
            setSymbol(number, sym1);
    }
    writeMantis(number, n3);
    free(n1);
    free(n2);
    free(n3);
}

s21_decimal s21_add(s21_decimal num1, s21_decimal num2) {
    s21_decimal number = decimal_init();
    if (num1.value_type == s21_NORMAL_VALUE && num2.value_type == s21_NORMAL_VALUE) {
        add2(&number, &num1, &num2);
    } else {
        if (num1.value_type != s21_NAN && num2.value_type != s21_NAN) {
            if (num1.value_type == num2.value_type)
                number.value_type = num1.value_type;
            else
                number.value_type = s21_NORMAL_VALUE;
        } else {
            number.value_type = s21_NAN;
        }
    }
    if (number.value_type == s21_NAN) {
        number = decimal_init2(0, 0, 0, 0, 0);
        number.value_type = s21_NAN;
    }
    return number;
}

s21_decimal s21_sub(s21_decimal num1, s21_decimal num2) {
    s21_decimal number = decimal_init();
    if (num1.value_type == s21_NORMAL_VALUE && num2.value_type == s21_NORMAL_VALUE) {
        num2 = s21_negate(num2);
        number = s21_add(num1, num2);
    } else {
        if (num1.value_type != s21_NAN && num2.value_type != s21_NAN) {
            if (num1.value_type == num2.value_type)
                number.value_type = s21_NORMAL_VALUE;
            else
                number.value_type = num1.value_type;
        } else {
            number.value_type = s21_NAN;
        }
    }
    return number;
}

int mul2(unsigned long int *n1, unsigned long int *n2, unsigned long int *n3, int iter) {
    int error = 0;
    unsigned long temp = UINT_MAX;
    temp++;
    n3[0] = 0;
    n3[1] = 0;
    n3[2] = 0;
    for (int i = iter; i < 3; i++)
        n3[i] = n2[iter] * n1[i - iter];
    if (n3[2] <= UINT_MAX) {
        n3[2] += (n3[1] / temp);
        n3[1] = n3[1] % temp;
        if (n3[2] <= UINT_MAX) {
            n3[1] += (n3[0] / temp);
            n3[0] = n3[0] % temp;
            n3[2] += (n3[1] / temp);
            n3[1] = n3[1] % temp;
            if (n3[2] > UINT_MAX) {
                error = 1;
            }
        } else {
            error = 1;
        }
    } else {
        error = 1;
    }
    return error;
}

s21_decimal mul3(s21_decimal num1, s21_decimal num2) {
    s21_decimal number = decimal_init();
    s21_decimal addNumber = decimal_init();
    if (getSymbol(num1) != getSymbol(num2)) {
        setSymbol(&number, 1);
        setSymbol(&addNumber, 1);
    }
    unsigned long int *n1 = readMantis(num1);
    unsigned long int *n2 = readMantis(num2);
    unsigned long int *n3 = createArr3(0, 0, 0);
    if ((n1[2] != 0 && (n2[2] != 0 || n2[1] != 0)) ||
        (n2[2] != 0 && (n1[2] != 0 || n1[1] != 0))) {
        number.value_type = s21_NAN;
    } else {
        for (int i = 0; i < 3; i++) {
            if (n2[i] != 0) {
                if (mul2(n1, n2, n3, i)) {
                    number.value_type = s21_NAN;
                } else {
                    writeMantis(&addNumber, n3);
                    number = s21_add(number, addNumber);
                    freeMantis(&addNumber);
                }
            }
        }
    }
    if (getStepen(num1) + getStepen(num2) > 28) {
        number.value_type = s21_NAN;
    } else {
        setStepen(&number, getStepen(num1) + getStepen(num2));
    }
    free(n1);
    free(n2);
    free(n3);
    return number;
}

s21_decimal s21_mul(s21_decimal num1, s21_decimal num2) {
    s21_decimal number = decimal_init();
    if (num1.value_type == s21_NORMAL_VALUE && num2.value_type == s21_NORMAL_VALUE) {
        number = mul3(num1, num2);
    } else {
        if (num1.value_type != s21_NAN && num2.value_type != s21_NAN) {
            if (num1.value_type == num2.value_type)
                number.value_type = s21_INFINITY;
            else
                number.value_type = s21_NEGATIVE_INFINITY;
        } else {
            number.value_type = s21_NAN;
        }
    }
    return number;
}

s21_decimal div_before_point(
        s21_decimal *num, s21_decimal num1, s21_decimal *num2) {
    int sdvig = 1;
    while (!s21_is_less(*num2, num1) && !getLastBool(*num2)) {
        shift(num2, 1);
        sdvig++;
    }
    if (sdvig != 1 && getLastBool(*num2) == 0) {
        unShift(num2, 1);
        sdvig--;
    }
    while (sdvig > 0) {
        if (0 == s21_is_greater_or_equal(num1, *num2)) {
            num1 = s21_sub(num1, *num2);
            writeUnit(num, sdvig - 1);
        }
        if (sdvig != 1)
            unShift(num2, 1);
        sdvig--;
    }
    return num1;
}

s21_decimal div_after_point(
        s21_decimal num, s21_decimal num1, s21_decimal num2, int umnogilNa10, int *numStepen) {
    s21_decimal one = decimal_init2(1, 0, 0, 0, 0);
    int stop = 1;
    while (!isZero(num1) && stop != 0) {
        if (*numStepen + umnogilNa10 < 28 && !shift10(&num, 1)) {
            shift10(&num1, 1);
            *numStepen = *numStepen + 1;
            while (s21_is_less(num1, num2)) {
                num1 = s21_sub(num1, num2);
                num = s21_add(num, one);
            }
        } else if (stop != 0) {
            int temp = 0;
            shift10(&num1, 1);
            while (s21_is_less(num1, num2)) {
                num1 = s21_sub(num1, num2);
                temp++;
            }
            if (temp >= 5) {
                stop = 0;
                num = s21_add(num, one);
            } else if (temp == 4) {
                stop++;
            } else {
                stop = 0;
            }
            if (stop > 10)
                stop = 0;
        } else {
            stop = 0;
        }
    }
    return num;
}

s21_decimal div2(s21_decimal num1, s21_decimal num2) {
    s21_decimal num = decimal_init();
    s21_decimal dec10 = decimal_init2(10, 0, 0, 0, 0);
    unsigned long int *arrNum2 = readMantis(num2);
    int umnogilNa10 = 0;
    int numSymbol = 0;
    if (getSymbol(num1) != getSymbol(num2))
        numSymbol = 1;
    setSymbol(&num1, 0);
    setSymbol(&num2, 0);
    int s1 = getStepen(num1);
    int s2 = getStepen(num2);
    if (s1 < s2)
        shift10(&num1, s2 - s1);
    else if (s1 > s2)
        shift10(&num2, s1 - s2);
    setStepen(&num1, 0);
    setStepen(&num2, 0);
    while (0 == s21_is_less(num1, num2)) {
        num1 = s21_mul(num1, dec10);
        setStepen(&dec10, getStepen(num1));
        umnogilNa10++;
    }
    if (!(arrNum2[0] == 0 && arrNum2[1] == 0 && arrNum2[2] == 0)) {
        num1 = div_before_point(&num, num1, &num2);
        int numStepen = 0;
        num = div_after_point(num, num1, num2, umnogilNa10, &numStepen);
        setSymbol(&num, numSymbol);
        setStepen(&num, numStepen);
    } else {
        num.value_type = s21_NAN;
    }
    if (umnogilNa10 != 0) {
        umnogilNa10 += getStepen(num);
        if (umnogilNa10 > 28)
            umnogilNa10 = 28;
        setStepen(&num, umnogilNa10);
    }
    free(arrNum2);
    return num;
}

s21_decimal s21_div(s21_decimal num1, s21_decimal num2) {
    s21_decimal num = decimal_init();
    if (num1.value_type == s21_NORMAL_VALUE && num2.value_type == s21_NORMAL_VALUE) {
        num = div2(num1, num2);
    } else {
        if (num1.value_type != s21_NAN && num2.value_type != s21_NAN) {
            if (num1.value_type == num2.value_type)
                num = decimal_init2(1, 0, 0, 0, 0);
            else
                num = decimal_init2(1, 0, 0, 0, 1);
        } else {
            num.value_type = s21_NAN;
        }
    }
    return num;
}

s21_decimal mod2(s21_decimal num1, s21_decimal num2) {
    unsigned long int *arrNum2 = readMantis(num2);
    int numSymbol = 0;
    setSymbol(&num1, 0);
    setSymbol(&num2, 0);
    int s1 = getStepen(num1);
    int s2 = getStepen(num2);
    int s3;
    if (s1 < s2) {
        s3 = s2;
        shift10(&num1, s2 - s1);
    } else if (s1 > s2) {
        s3 = s1;
        shift10(&num2, s1 - s2);
    } else {
        s3 = s1;
    }
    setStepen(&num1, 0);
    setStepen(&num2, 0);
    if (!(arrNum2[0] == 0 && arrNum2[1] == 0 && arrNum2[2] == 0)) {
        int sdvig = 1;
        while (0 == s21_is_less(num2, num1) && !getLastBool(num2)) {
            shift(&num2, 1);
            sdvig++;
        }
        if (sdvig != 1 && getLastBool(num2) == 0) {
            unShift(&num2, 1);
            sdvig--;
        }
        while (sdvig > 0) {
            if (0 == s21_is_greater_or_equal(num1, num2)) {
                num1 = s21_sub(num1, num2);
            }
            if (sdvig != 1)
                unShift(&num2, 1);
            sdvig--;
        }
        while (s21_is_less(num1, num2)) {
            num1 = s21_sub(num1, num2);
        }
    } else {
        num1 = decimal_init();
        num1.value_type = s21_NAN;
    }
    setStepen(&num1, s3);
    free(arrNum2);
    return num1;
}

s21_decimal s21_mod(s21_decimal num1, s21_decimal num2) {
    if (num1.value_type == s21_NORMAL_VALUE && num2.value_type == s21_NORMAL_VALUE) {
        num1 = mod2(num1, num2);
    } else {
        if (num1.value_type != s21_NAN && num2.value_type != s21_NAN) {
            num1 = decimal_init();
        } else {
            num1 = decimal_init();
            num1.value_type = s21_NAN;
        }
    }
    return num1;
}

int s21_is_less(s21_decimal num1, s21_decimal num2) {
    int result = 2;
    int temp = 0;
    int st1 = getStepen(num1);
    int st2 = getStepen(num2);
    int symb1 = getSymbol(num1);
    int symb2 = getSymbol(num2);
    if (st1 > st2) {
        temp = comparison(num2, num1, st1 - st2);
        if (temp == 1)
            temp = 2;
        else if (temp == 2)
            temp = 1;
    } else {
        temp = comparison(num1, num2, st2 - st1);
    }
    if (num1.value_type == s21_NORMAL_VALUE && num2.value_type == s21_NORMAL_VALUE) {
        if (temp == 2 && symb1 == 1 && symb2 == 1 ||
            temp == 1 && symb1 == 0 && symb2 == 0 || temp == 1 && symb1 != symb2)
            result = 0;
        else
            result = 1;
    } else {
        if (temp == 1)
            result = 0;
        else
            result = 1;
    }
    return result;
}

int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2) {
    int result = 2;
    int temp = 0;
    int st1 = getStepen(num1);
    int st2 = getStepen(num2);
    int symb1 = getSymbol(num1);
    int symb2 = getSymbol(num2);
    if (st1 > st2) {
        temp = comparison(num2, num1, st1 - st2);
        if (temp == 1)
            temp = 2;
        else if (temp == 2)
            temp = 1;
    } else {
        temp = comparison(num1, num2, st2 - st1);
    }
    if (num1.value_type == s21_NORMAL_VALUE && num2.value_type == s21_NORMAL_VALUE) {
        if (temp == 2 && symb1 == 1 && symb2 == 1 ||
            temp == 1 && symb1 == 0 && symb2 == 0 || temp == 3 || temp == 1 && symb1 != symb2)
            result = 0;
        else
            result = 1;
    } else {
        if (temp == 1 || temp == 3)
            result = 0;
        else
            result = 1;
    }
    return result;
}

int s21_is_greater(s21_decimal num1, s21_decimal num2) {
    int result = 2;
    int temp = 0;
    int st1 = getStepen(num1);
    int st2 = getStepen(num2);
    int symb1 = getSymbol(num1);
    int symb2 = getSymbol(num2);
    if (st1 > st2) {
        temp = comparison(num2, num1, st1 - st2);
        if (temp == 1)
            temp = 2;
        else if (temp == 2)
            temp = 1;
    } else {
        temp = comparison(num1, num2, st2 - st1);
    }
    if (num1.value_type == s21_NORMAL_VALUE && num2.value_type == s21_NORMAL_VALUE) {
        if (temp == 1 && symb1 == 1 && symb2 == 1 ||
            temp == 2 && symb1 == 0 && symb2 == 0 || temp == 2 && symb1 != symb2)
            result = 0;
        else
            result = 1;
    } else {
        if (temp == 2)
            result = 0;
        else
            result = 1;
    }
    return result;
}

int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2) {
    int result = 2;
    int temp = 0;
    int st1 = getStepen(num1);
    int st2 = getStepen(num2);
    int symb1 = getSymbol(num1);
    int symb2 = getSymbol(num2);
    if (st1 > st2) {
        temp = comparison(num2, num1, st1 - st2);
        if (temp == 1)
            temp = 2;
        else if (temp == 2)
            temp = 1;
    } else {
        temp = comparison(num1, num2, st2 - st1);
    }
    if (num1.value_type == s21_NORMAL_VALUE && num2.value_type == s21_NORMAL_VALUE) {
        if (temp == 1 && symb1 == 1 && symb2 == 1 ||
            temp == 2 && symb1 == 0 && symb2 == 0 || temp == 3 || temp == 2 && symb1 != symb2)
            result = 0;
        else
            result = 1;
    } else {
        if (temp == 2 || temp == 3)
            result = 0;
        else
            result = 1;
    }
    return result;
}

int s21_is_equal(s21_decimal num1, s21_decimal num2) {
    int result = 2;
    int temp = 0;
    int st1 = getStepen(num1);
    int st2 = getStepen(num2);
    int symb1 = getSymbol(num1);
    int symb2 = getSymbol(num2);
    if (symb1 == 0 && symb2 == 1 || symb1 == 1 && symb2 == 0) {
        result = 1;
    } else {
        if (st1 > st2)
            temp = comparison(num2, num1, st1 - st2);
        else
            temp = comparison(num1, num2, st2 - st1);
    }
    if (num1.value_type == s21_NORMAL_VALUE && num2.value_type == s21_NORMAL_VALUE) {
        if (symb1 == symb2 && temp == 3)
            result = 0;
        else
            result = 1;
    } else {
        result = 1;
    }
    return result;
}

int s21_is_not_equal(s21_decimal num1, s21_decimal num2) {
    int result = 2;
    int temp = 0;
    int st1 = getStepen(num1);
    int st2 = getStepen(num2);
    int symb1 = getSymbol(num1);
    int symb2 = getSymbol(num2);
    if (st1 > st2)
        temp = comparison(num2, num1, st1 - st2);
    else
        temp = comparison(num1, num2, st2 - st1);
    if (num1.value_type == s21_NORMAL_VALUE && num2.value_type == s21_NORMAL_VALUE) {
        if (temp == 1 || temp == 2 || temp == 3 && symb1 != symb2)
            result = 0;
        else
            result = 1;
    } else {
        result = 0;
    }
    return result;
}

int comparison(s21_decimal num1, s21_decimal num2, int stepen) {
    int result = 0;
    unsigned long int *n1 = readMantis(num1);
    unsigned long int *n2 = readMantis(num2);
    int symb1 = getSymbol(num1);
    int symb2 = getSymbol(num2);
    if ((num1.value_type == s21_NEGATIVE_INFINITY ||
         num1.value_type == s21_NORMAL_VALUE) &&  num2.value_type == s21_INFINITY) {
        result = 1;
    } else if ((num1.value_type == s21_INFINITY ||
                num1.value_type == s21_NORMAL_VALUE) &&  num2.value_type == s21_NEGATIVE_INFINITY) {
        result = 2;
    } else if (num1.value_type == s21_NORMAL_VALUE && num2.value_type == s21_NORMAL_VALUE) {
        if (symb1 == 0 && symb2 == 1) {
            result = 2;
        } else if (symb1 == 1 && symb2 == 0) {
            result = 1;
        } else {
            for (int i = 0; i <= stepen; i++) {
                free(n1);
                n1 = readMantis(num1);
                if (n1[2] > n2[2] && i <= stepen && result == 0) {
                    result = 2;
                } else if (n1[2] < n2[2] && i == stepen && result == 0) {
                    result = 1;
                } else if (n2[2] == n1[2] && i == stepen && result == 0) {
                    if (n1[1] > n2[1]) {
                        result = 2;
                    } else if (n1[1] < n2[1]) {
                        result = 1;
                    } else {
                        if (n1[0] > n2[0])
                            result = 2;
                        else if (n1[0] < n2[0])
                            result = 1;
                        else
                            result = 3;
                    }
                }
                shift10(&num1, 1);
            }
        }
    } else {
        result = 4;
    }
    free(n1);
    free(n2);
    return result;
}

s21_decimal s21_truncate(s21_decimal num) {
    if (num.value_type == 0) {
        num = s21_sub(num, getOstatok(num));
    }
    return num;
}

s21_decimal getOstatok(s21_decimal num) {
    s21_decimal decTemp = decimal_init2(1, 0, 0, 0, 0);
    int s = getStepen(num);
    shift10(&decTemp, s);
    setStepen(&decTemp, getStepen(num));
    s21_decimal decOstatok = decimal_init();
    decOstatok = s21_mod(num, decTemp);
    return decOstatok;
}

s21_decimal delete_zero(s21_decimal num) {
    if (getStepen(num) != 0) {
        s21_decimal deka = decimal_init2(1, 0, 0, 0, 0);
        shift10(&deka, getStepen(num));
        setStepen(&num, 0);
        num = s21_div(num, deka);
    }
    return num;
}

s21_decimal s21_floor(s21_decimal num) {
    if (num.value_type == 0) {
        int symbol = getSymbol(num);
        setSymbol(&num, 0);
        s21_decimal ostatok = getOstatok(num);
        unsigned long int *arr = readMantis(ostatok);
        if (arr[0] != 0 || arr[1] != 0 || arr[2] != 0) {
            num = s21_sub(num, ostatok);
            if (symbol == 1) {
                s21_decimal unit = decimal_init2(1, 0, 0, 0, 0);
                num = s21_add(num, unit);
            }
        }
        setSymbol(&num, symbol);
        free(arr);
    }
    return num;
}

s21_decimal s21_round(s21_decimal num) {
    if (num.value_type == 0) {
        int symbol = getSymbol(num);
        setSymbol(&num, 0);
        s21_decimal ostatok = getOstatok(num);
        num = s21_sub(num, ostatok);
        s21_decimal dec5 = decimal_init2(4, 0, 0, 1, 0);
        s21_decimal dec4 = decimal_init2(4, 0, 0, 1, 0);
        s21_decimal addDec5 = decimal_init2(5, 0, 0, 1, 0);
        s21_decimal addDec4 = decimal_init2(4, 0, 0, 1, 0);
        int add = 0;
        int stepen4 = 1;
        int stepen5 = 1;
        for (int i = 0; i < getStepen(ostatok); i++) {
            setStepen(&addDec5, ++stepen5);
            setStepen(&addDec4, ++stepen4);
            unsigned long int *arr = readMantis(dec4);
            writeMantis(&dec5, arr);
            free(arr);
            dec4 = s21_add(dec4, addDec4);
            dec5 = s21_add(dec5, addDec5);
            if (!s21_is_less(dec5, ostatok)) {
                add = 1;
            } else if (s21_is_less_or_equal(dec4, ostatok)) {
                break;
            }
        }
        if (add == 1) {
            s21_decimal unit = decimal_init2(1, 0, 0, 0, 0);
            num = s21_add(num, unit);
        }
        setSymbol(&num, symbol);
    }
    return num;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    if (src < 0) {
        setSymbol(dst, 1);
        src = -src;
    } else {
        setSymbol(dst, 0);
    }
    unsigned long int *arr = createArr3(src, 0, 0);
    setStepen(dst, 0);
    writeMantis(dst, arr);
    free(arr);
    return 0;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    int error = 0;
    int stepen = 0;
    int E = 0;
    char stepen1[3] = "";
    char stepen2[3] = "";
    char s[15] = "";
    char number[7] = "";
    unsigned int temp1 = 0;
    char max1[15] = "";
    char max2[8] = "7.92281";
    int sign = 0;
    int k = 0;
    *dst = decimal_init2(0, 0, 0, 0, 0);
    dst -> value_type = s21_NORMAL_VALUE;
    snprintf(s, 15 * sizeof(char), "%g", src);
    for (int i = 0; s[i] != '\0'; i++) {
        if ((s[i] <= '9' && s[i] >= '0') && E == 0 && k <= 5) {
            number[k] = s[i];
            k++;
        }
        if (E == 1) {
            stepen1[0] = s[i + 1];
            stepen1[1] = s[i + 2];
            E = 2;
        }
        if (E == 3) {
            stepen2[0] = s[i + 1];
            stepen2[1] = s[i + 2];
            E = 4;
        }
        if (s[i] == 'e' && s[i + 1] == '-')
            E = 1;
        if (s[i] == 'e' && s[i + 1] == '+')
            E = 3;
        if (sign == 1 && E == 0)
            stepen++;
        if (s[i] == '.')
            sign = 1;
    }
    snprintf(max1, 15 * sizeof(char), "%g", atoi(number) / pow(10, strlen(number) - 1));
    for (int i = 0; i < 8; i++) {
        if (max1[i] > max2[i]) {
            error = 1;
        }
    }
    if (E == 2 && atoi(stepen1) > 28) {
        error == 0;
    } else if (E == 4 && (atoi(stepen2) > 28 || (atoi(stepen2) == 28 && error == 1))) {
        if (s[0] == '-')
            dst -> value_type = s21_NEGATIVE_INFINITY;
        else
            dst -> value_type = s21_INFINITY;
    } else {
        error == 0;
        if (s[0] == '-')
            setSymbol(dst, 1);
        else
            setSymbol(dst, 0);
        if (E == 2)
            stepen += atoi(stepen1);
        else if (E == 4)
            stepen = 0;
        setStepen(dst, stepen);
        temp1 = atoi(number);
        unsigned long int *n = createArr3(temp1, 0, 0);
        writeMantis(dst, n);
        if (E == 4)
            shift10(dst, atoi(stepen2) + 1 - strlen(number));
        free(n);
    }
    return error;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    int error = 0;
    src = s21_truncate(src);
    src = delete_zero(src);
    unsigned long int *n = readMantis(src);
    long int temp = n[0];
    if (getSymbol(src) == 1)
        temp *= -1;
    if (temp > INT_MAX || temp < INT_MIN || n[1] != 0 || n[2] != 0 || src.value_type != s21_NORMAL_VALUE) {
        error = 1;
    } else {
        *dst = temp;
    }
    free(n);
    return error;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int error = 0;
    unsigned long int *n = readMantis(src);
    float result = 0;
    *dst = 0;
    if (src.value_type != 0) {
        error = 1;
    } else {
        float temp1 = n[0];
        float temp2 = n[1] * pow(2, 32);
        float temp3 = n[2] * pow(2, 64);
        result = (temp1 + temp2 + temp3) / pow(10, getStepen(src));
        *dst = result;
        if (getSymbol(src) == 1)
            *dst *= -1;
    }
    free(n);
    return error;
}
