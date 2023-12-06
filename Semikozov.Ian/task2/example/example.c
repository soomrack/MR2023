#include "matrix.h"


int main() {
    Matrix_Instance matrix1 = create_matrix(4, 4);
    Matrix_Instance matrix2 = create_matrix(2, 2);

    fill_matrix_random(matrix1);
    print_matrix(matrix1);
    printf("\n\n");

    matrix1.pData[0][0] = 1.0;
    matrix1.pData[0][1] = 2.0;
    matrix1.pData[0][2] = 3.0;
    matrix1.pData[0][3] = 4.0;
    matrix1.pData[1][0] = 5.0;
    matrix1.pData[1][1] = 6.0;
    matrix1.pData[1][2] = 7.0;
    matrix1.pData[1][3] = 8.0;
    matrix1.pData[2][0] = 9.0;
    matrix1.pData[2][1] = 10.0;
    matrix1.pData[2][2] = 11.0;
    matrix1.pData[2][3] = 12.0;
    matrix1.pData[3][0] = 13.0;
    matrix1.pData[3][1] = 14.0;
    matrix1.pData[3][2] = 15.0;
    matrix1.pData[3][3] = 16.0;

    print_matrix(matrix1);
    printf("\n\n");

    matrix2.pData[0][0] = 0;
    matrix2.pData[0][1] = 1.0;
    matrix2.pData[1][0] = 2.0;
    matrix2.pData[1][1] = 3.0;

    Matrix_Instance expo = exponent_matrix(matrix2, 3);
    print_matrix(expo);
    printf("\n\n");
    free_matrix(expo);

    Matrix_Instance t_matrix = transpose_matrix(matrix1);
    printf("\n\n");
    print_matrix(t_matrix);
    free_matrix(t_matrix);

    Matrix_Instance det_matrix = create_matrix(4, 4, Random_Matrix);
    double determinant = determinant_matrix(det_matrix);
    printf("Determinant is %f", determinant);
    printf("\n\n");

    Matrix_Instance mul_matrix = multiply_matrix(matrix1, 12);
    print_matrix(mul_matrix);
    printf("\n\n");
    free_matrix(mul_matrix);

    Matrix_Instance mul_matrices = multiply_matrix(matrix1, matrix2);
    print_matrix(mul_matrices);
    printf("\n\n");
    free_matrix(mul_matrices);

    Matrix_Instance sum_matrix = sum_matrices(matrix1, matrix2);
    print_matrix(sum_matrix);
    printf("\n\n");
    free_matrix(sum_matrix);

    free_matrix(matrix1);
    free_matrix(matrix2);
    return 0;
}