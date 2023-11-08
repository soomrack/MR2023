#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int rows;
    int cols;
    double **data;
} Matrix;

double matrixSum(Matrix *matrix);
Matrix createMatrix(int rows, int cols);
void freeMatrix(Matrix *matrix);
Matrix multiplyMatrix(Matrix *A, Matrix *B);
void fillMatrixRandom(Matrix *matrix);
void fillMatrixValues(Matrix *matrix, double value);
void printMatrix(Matrix *matrix);

#endif // MATRIX_H