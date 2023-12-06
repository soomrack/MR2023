#include <malloc.h>
#include <stdio.h>

#include "matrix.h"

int main(void)
{
    // ? Почему адрес начала массива и адрес начала даты разниться в 32 байта (выравнивание)
    // 

    matrix *a = matrix_new(2, 2);
    matrix_fill(a, INCREASING);
    matrix_print(a);
    printf("\n");

    matrix *b = matrix_new(2, 2);
    matrix_fill(b, INCREASING);
    matrix_print(b);
    printf("\n");

    matrix_increase(a, b);
    matrix_print(a);
    printf("\n");

    matrix_copy(a, b);
    matrix_print(a);
    printf("\n");

    matrix *exp = matrix_new(2, 2);

    exp = matrix_exp(a, 3);
    matrix_print(exp);
    printf("\n");

    exp = matrix_exp(a, 4);
    matrix_print(exp);
    printf("\n");

    exp = matrix_exp(a, 5);
    matrix_print(exp);
    printf("\n");

    return 0;
}