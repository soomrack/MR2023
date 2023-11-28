#include "matrixlib.h"

int main() {
    struct Matrix A = matrix_create(3, 3, RANDOM);
    struct Matrix B = matrix_create(3, 3, IDEN);
    struct Matrix C = matrix_create(3, 3, IDEN);
    struct Matrix D = matrix_create(3, 3, IDEN);

    matrix_print(A);

    D = matrix_multiply(D, 0.1);
    C = matrix_multiply(C, 0.1);


   


    B = matrix_sum(B, A);
    B = matrix_sum(B, C);
    B = matrix_sum(B, D);


    A = matrix_exp(A, 3);
    matrix_print(A);

    matrix_print(B);

    matrix_free(&A);
    matrix_free(&B);
    matrix_free(&C);
    matrix_free(&D);

    return 0;
}