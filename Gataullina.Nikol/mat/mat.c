#include "mat_lib.h"


int main()
{
    Matrix A, B;
    A = matrix_create(2, 2, (double[]){1., 1., 1., 1. });
    B = matrix_create(2, 2, (double[]){2., 0., 0., 1. });

    Matrix sum = matrix_addition(&A, &B);
    matrix_print("SUM", sum);
    Matrix mult = matrix_multiplication(&A, &B);
    matrix_print("Mult", mult);
    printf("det %lf", matrix_determinant(&A));
    Matrix revers = matrix_reverse(&A);
    matrix_print("revers", revers);
    Matrix exp = matrix_exponent(&A, 30);
    matrix_print("exponent", exp);
    matrix_free(&A);
    matrix_free(&B);
    matrix_free(&sum);
    matrix_free(&mult);
    matrix_free(&exp);
    return 0;
}