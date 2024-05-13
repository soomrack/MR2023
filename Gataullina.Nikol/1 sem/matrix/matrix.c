#include "matrix_lib.h"

int main()
{
    Matrix A, B;
    A = matrix_create(3, 3, (double[]){3., 6., 7., 5., 3., 3., 5., 6., 2.0, 9.0});
    B = matrix_create(3, 3, (double[]){3., 7., 4., 3., 5., 2., 8., 9., 1.0, 9.0});

    Matrix sum = matrix_addition(&A, &B);
    matrix_print("SUM", sum);
    Matrix mult = matrix_multiplication(&A, &B);
    matrix_print("Mult", mult);
    printf("det %lf", matrix_determinant(&A));
    Matrix revers = matrix_reverse(&A);
    matrix_print("revers", revers);
    Matrix exp = matrix_exponent(&A, 50);
    matrix_print("exponent", exp);
    matrix_free(&A);
    matrix_free(&B);
    matrix_free(&sum);
    matrix_free(&mult);
    matrix_free(&exp);
    return 0;
}