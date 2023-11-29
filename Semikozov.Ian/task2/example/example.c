#include "matrix.h"

int main() {
    Matrix_Instance matrix1 = create_matrix(2, 2, Zero_Matrix);
    Matrix_Instance matrix2 = create_matrix(2, 2, Identity_Matrix);

    matrix1.pData[0][0] = 1.0;
    matrix1.pData[0][1] = 2.0;
    matrix1.pData[1][0] = 3.0;
    matrix1.pData[1][1] = 4.0;

    matrix2.pData[0][0] = 5.0;
    matrix2.pData[0][1] = 6.0;
    matrix2.pData[1][0] = 7.0;
    matrix2.pData[1][1] = 8.0;

    Matrix_Instance result = sum_matrix(matrix1, matrix2);

    for (size_t i = 0; i < result.numRows; ++i) {
        for (size_t j = 0; j < result.numCols; ++j) {
            printf("%.2f ", result.pData[i][j]);
        }
        printf("\n");
    }

    free_matrix(matrix1);
    free_matrix(matrix2);
    free_matrix(result);

    return 0;
}