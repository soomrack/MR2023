#include "matrix.h"


int main() {
    Matrix_Instance matrix1 = create_matrix(2, 2);
    Matrix_Instance matrix2 = create_matrix(2, 2);
    
    matrix1.pData[0][0] = 1.0;
    matrix1.pData[0][1] = 2.0;
    matrix1.pData[1][0] = 3.0;
    matrix1.pData[1][1] = 4.0;

    matrix2.pData[0][0] = 5.0;
    matrix2.pData[0][1] = 6.0;
    matrix2.pData[1][0] = 7.0;
    matrix2.pData[1][1] = 8.0;

    Matrix_Instance matrixDet = create_matrix(4, 4, Random_Matrix);
    print_matrix(matrixDet);
    double determinant = determinant_matrix(matrixDet);
    printf("Determinant is %f", determinant);
    Matrix_Instance matrr1 = create_matrix(5, 5);
    Matrix_Instance matrr = create_matrix(5, 5, Identity_Matrix);
    // print_matrix(matrr);
    Matrix_Instance matrixMul = multiply_matrix(matrr, 12);

    // print_matrix(matrixMul);
    // free_matrix(matrixMul);

    // matrix_copy(matrr, matrr1);
    Matrix_Instance result = sum_matrix(matrix1, matrix2);

    // print_matrix(matrr1);

    free_matrix(matrix1);
    free_matrix(matrix2);
    free_matrix(result);

    return 0;
}