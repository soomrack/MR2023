#include <stdio.h>
#include "..\MatrixLib\MatrixLib.h";

int main()
{
    struct Matrix A = matrix_create(3, 3);
    matrix_set_zero(A);

    MatrixItem values_A[] =
    { 1., 8., 3.,
      8., 5., 8.,
      7., 8., 9.
    };

    matrix_fill(A, values_A);

    struct Matrix B = matrix_create(3, 3);
    matrix_set_zero(B);

    MatrixItem values_B[] =
    { 9., 8., 7.,
      6., 5., 4.,
      3., 2., 1.
    };

    matrix_fill(B, values_B);

    struct Matrix C = matrix_create(3, 3);
    matrix_set_zero(C);
    C = matrix_sum(A, B);

    matrix_print(A, "Matrix a");
    matrix_print(B, "Matrix b");
    matrix_print(C, "Matrix c");

    matrix_delete(&A);
    matrix_delete(&B);
    matrix_delete(&C);
}
