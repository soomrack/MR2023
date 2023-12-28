#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    Matrix A = Matrix_create(2, 3);
    Matrix B = Matrix_create(2, 3);

    int dataA[2][3] = { {1, 2, 3}, {4, 5, 6} };
    int dataB[2][3] = { {7, 8, 9}, {10, 11, 12} };

    for (int i = 0; i < A.rows; ++i) {
        for (int j = 0; j < A.cols; ++j) {
            A.data[j + i * A.rows] = dataA[i][j];
        }
    }

    for (int i = 0; i < B.rows; ++i) {
        for (int j = 0; j < B.cols; ++j) {
            B.data[j + i * A.rows] = dataA[i][j];
        }
    }

    printf("Matrix A:\n");
    Matrix_display(&A);

    printf("Matrix B:\n");
    Matrix_display(&B);

    Matrix C = Matrix_add(&A, &B);
    printf("Matrix C = A + B:\n");
    Matrix_display(&C);

    Matrix_free(A);
    Matrix_free(B);
    Matrix_free(C);

    Matrix D = Matrix_create(2, 2);

    double dataD[2][2] = { {1, 2}, {3, 4} };

    for (int i = 0; i < D.rows; ++i) {
        for (int j = 0; j < D.cols; ++j) {
            D.data[j + i * D.rows] = dataD[i][j];
        }
    }

    printf("Matrix D:\n");
    Matrix_display(&D);

    Matrix matExponent = Matrix_exponential(&D);

    printf("\nMatrix E^D\n");
    Matrix_display(&matExponent);

    Matrix E = Matrix_create(3, 3);

    double dataE[3][3] = { {2, 5, 1}, {1, 0, -1}, {3, 0, 2} };

    for (int i = 0; i < E.rows; ++i) {
        for (int j = 0; j < E.cols; ++j) {
            E.data[j + i * E.rows] = dataE[i][j];
        }
    }

    printf("\nMatrix E:\n");
    Matrix_display(&E);

    int determinantB = Matrix_determinant(&E);
    printf("\nDeterminant of Matrix E: %d\n", determinantB);

    Matrix_free(D);
    Matrix_free(matExponent);
    Matrix_free(E);

    return 0;
}
