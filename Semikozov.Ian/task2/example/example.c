#include "matrix.h"

int main() {
    Matrix A = createMatrix(2, 3);
    Matrix B = createMatrix(3, 2);

    // fillMatrixRandom(A);
    fillMatrixValues(&A, 2.0);
    fillMatrixValues(&B, 2.0);

    double sum = matrixSum(&A);
    printf("Сумма элементов матрицы A %f\n", sum);
    Matrix C = multiplyMatrix(&A, &B);

    printf("Матрица A:\n");
    printMatrix(&A);

    printf("Матрица B:\n");
    printMatrix(&B);

    printf("Результат умножения A и B:\n");
    printMatrix(&C);

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);

    return 0;
}