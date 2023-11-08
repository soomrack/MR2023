#include "matrix.h"

double matrixSum(Matrix *matrix) {
    double sum = 0;
    __asm__ (
        "xorpd %0, %0;"        
        "begin_loop:"
        "movupd (%1), %%xmm1;"     
        "addpd %%xmm1, %0;"        
        "add $16, %1;"             
        "dec %2;"                  
        "jnz begin_loop;"
        : "+x"(sum)
        : "r"(matrix->data), "r"(matrix->rows * matrix->cols)
    );
    return sum;
}   

Matrix createMatrix(int rows, int cols) {
    Matrix matrix;
    matrix.rows = rows;
    matrix.cols = cols;
    matrix.data = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        matrix.data[i] = (double *)malloc(cols * sizeof(double));
    }
    return matrix;
}

void freeMatrix(Matrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
}

Matrix multiplyMatrix(Matrix *A, Matrix *B) {
    if (A->cols != B->rows) {
        fprintf(stderr, "Несовместимые размеры матриц\n");
        exit(1);
    }

    Matrix result = createMatrix(A->rows, B->cols);

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->cols; j++) {
            result.data[i][j] = 0;
            for (int k = 0; k < A->cols; k++) {
                result.data[i][j] += A->data[i][k] * B->data[k][j];
            }
        }
    }

    return result;
}

void fillMatrixRandom(Matrix *matrix) {
    srand(time(NULL));
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            matrix->data[i][j] = (double)rand() / RAND_MAX; 
        }
    }
}

void fillMatrixValues(Matrix *matrix, double value) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            matrix->data[i][j] = value;
        }
    }
}

void printMatrix(Matrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%f\t", matrix->data[i][j]);
        }
        printf("\n");
    }
}