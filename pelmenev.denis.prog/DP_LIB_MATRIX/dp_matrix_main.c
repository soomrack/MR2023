#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "dp_matrix_lib.h"

void main()
{
    struct Matrix A, B;

    A = matrix_allocate(3, 3);
    B = matrix_allocate(3, 3);

    for (int k = 0; k <= A.cols * A.rows - 1; ++k)
        A.data[k] = k+1;
    A.data[3] = 20.0;
    A.data[0] = 0.0;
    print_matrix(A);

    for (int k = 0; k <= B.cols * B.rows - 1; ++k)
        B.data[k] = B.cols * B.rows - k;
    print_matrix(B);

    double a, b;
    a = matrix_det(A);
    b = matrix_det(B);
    printf("det(A) = %4.2f\n", a);
    printf("det(B) = %4.2f\n", b);

    matrix_free(&A);
    matrix_free(&B);
}