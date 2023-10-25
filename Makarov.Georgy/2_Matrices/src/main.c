#include "matrices.h"


int main() {
    struct Matrix A = create_matrix(3, 3, IDENTITY);
    struct Matrix B = create_matrix(3, 3, RANDOM);

    B = matrix_scalar_multiplication(&B, 3);

    struct Matrix C = matrices_subtraction(&A, &B);

    print_matrix(&C);

    C = matrix_transposition(&C);

    print_matrix(&C);

    delete_matrix(&A);
    delete_matrix(&B);
    delete_matrix(&C);

    return 0;
}
