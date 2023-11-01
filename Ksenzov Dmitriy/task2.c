#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "libmatrix.h"


int main ()
{
    struct Matrix A, B, C, D, E, F, K;
    MatrixItem G;
 
    A = matrix_create(3, 3, (MatrixItem[]){24., 15., 2.,
                                           40., 5., 7.,
                                           1., 33., 21.});
    B = matrix_create(3, 3, (MatrixItem[]){4., 24., 52.,
                                           10., 15., 0.,
                                           31., 32., 51. });

    matrix_print(A);
    matrix_print(B);

    C = matrix_sum(A, B);
    matrix_print(C);

    D = matrix_subtration(A,B);
    matrix_print(D);

    E = matrix_mult(A,A);
    matrix_print(E);

    F = matrix_transposition(A);
    matrix_print(F);

    G = matrix_determinant(A);
    determinant_print(G);

    K = matrix_exponent(A);
    matrix_print(K);

    matrix_delete(&A);
    matrix_delete(&B);
    matrix_delete(&C);
    matrix_delete(&D);
    matrix_delete(&E);
    matrix_delete(&F);
    matrix_delete(&K);
    return 0;
}