#include <stdio.h>
#include "Matrix.h";

int main()
{
    double a[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    Matrix A = matrix_allocation(3, 3);
    matrix_fill(A, a);
    matrix_print(A, "asdf");
    Matrix res = matrix_allocation(3, 3);
    res = matrix_exp(&res, A);
    matrix_print(res, "asdf");
}