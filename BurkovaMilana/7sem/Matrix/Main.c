#include <stdio.h>
#include "..\Matrix\Matrix.h";


int main()
{
    double values_A[] =
    { 2., 1., 2.,
      1., 3., 0.,
      3., 0., 3.
    };

    struct Matrix A = matrix_creation(3, 3);
    matrix_set_one(A);
    struct Matrix B = matrix_creation(3, 3);
    matrix_set_one(B);
    struct Matrix C = matrix_creation(3, 3);
    struct Matrix D = matrix_creation(3, 3);

    matrix_fill(A, values_A);
    matrix_fill(B, values_A);

    matrix_sum(A, B, C);

    matrix_sub(A, B, D);

    matrix_mult(A, B);

    matrix_exp(A);

    struct Matrix MULT = matrix_mult(A, B);
    struct Matrix EXP = matrix_trans(matrix_exp(A));
    struct Matrix T = matrix_trans(A);


    matrix_print(A, "Matrix A");
    matrix_print(B, "Matrix B");
    matrix_print(C, "SUM: A + B");
    matrix_print(D, "SUB: A - B");
    matrix_print(MULT, "MULT: A * B");
    matrix_print(T, "TRANS: A^T");
    matrix_print(EXP, "EXP: A ^ e");

    delete_matrix(&A);
    delete_matrix(&B);
    delete_matrix(&C);
    delete_matrix(&D);
    delete_matrix(&MULT);
    delete_matrix(&T);
    delete_matrix(&EXP);

    return(0);
}

