#include "libmatrix.h"

int main() {
    struct Matrix A = matrix_create(3, 3, RANDOM);

    A = matrix_multiply(A, 3);
    matrix_print(&A);

    A = matrix_exp(A, 3);
    matrix_print(&A);

    A = matrix_transpose(A);
    matrix_print(&A);

    struct Matrix B = matrix_create(3, 3, IDENTITY);

    B = matrix_multiply(B, 500.);

    A = matrix_subtract(A, B);
    matrix_print(&A);

    double det = matrix_det(A);

    printf("Determinant of the matrix above is %f\n", det);

    struct Matrix C = matrix_create(4, 4, ZEROS);

    matrix_det(C);

    matrix_print(&C);

    matrix_remove(&A);
    matrix_remove(&B);
    matrix_remove(&C);

    return 0;
}