#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "Core.h"

int main()
{
    struct Matrix A, B, C, EXP;

    // printf("\nFirst matrix\n");
    A = matrix_fill(2, 2, (double[]) { 2., 4., 2., 4. });
    // matrix_print(A);

    // printf("Second matrix\n");
    B = matrix_fill(2, 2, (double[]) { 1., 0., 0., 1. });
    // matrix_print(B);

    // printf("Sum1 of matrices\n");
    // matrix_add(A, B);
    // matrix_print(A);

    printf("Sum2 of matrices\n");
    C = matrix_sum(A, B);
    matrix_print(C);

    // printf("Sub1 of matrices\n");
    // matrix_substraction(A, B);
    // matrix_print(A);

    printf("Sub2 of matrices\n");
    C = matrix_difference(A, B);
    matrix_print(C);

    // printf("Multiplying the first matrix by a scalar\n");
    // C = matrix_scalar_multiplication(A, 2);
    // matrix_print(C);

    // printf("Multiplying the first matrix by a second matrix\n");
    // C = matrix_multiplication(A, B);
    // matrix_print(C);

    // printf("Transposed first matrix\n");
    // C = matrix_transposition(A);
    // matrix_print(C);

    // printf("Determinant of the first matrix\n");
    // matrix_determinant(A);
    // printf("%4.2f \n", matrix_determinant(A));
    
    printf("\nExponent of the first matrix\n");
    
    EXP = matrix_exp(A, 20);
    matrix_print(EXP);

    matrix_free(&A);
    matrix_free(&B);
    matrix_free(&C);
    matrix_free(&EXP);

    return 0;
}