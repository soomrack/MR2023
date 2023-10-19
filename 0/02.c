#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>


typedef double MatrixItem;

struct Matrix {
    size_t cols;
    size_t rows;
    MatrixItem *data;
};

const struct Matrix MATRIX_NULL = {.cols = 0, .rows = 0, .data = NULL};


// Function returns MATRIX_NULL if fail
struct Matrix matrix_allocate(const size_t rows, const size_t cols)
{
    if (cols == 0 || rows == 0) {
        struct Matrix A = {.cols = cols, .rows = rows, .data = NULL};
        return A;
    }
    if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols) return MATRIX_NULL;  // rows * cols < MAX_SIZE / sizeof(MatrixItem)
    
    struct Matrix A = {.cols = cols, .rows = rows, .data = NULL};
    A.data = (MatrixItem*)malloc(A.cols * A.rows * sizeof(MatrixItem));
    if (A.data == NULL) {
        return MATRIX_NULL;
    }
    return A;
}


// Function returns MATRIX_NULL if fail
struct Matrix matrix_create(const size_t rows, const size_t cols, const MatrixItem *values)
{
    struct Matrix A = matrix_allocate(rows, cols);
    if (A.data == NULL) return A;
    
    memcpy(A.data, values, rows * cols * sizeof(MatrixItem));
    return A;
}


void matrix_free(struct Matrix *A)
{
    free(A->data);
    *A = MATRIX_NULL;
}


void matrix_print(const struct Matrix A)
{
    for (size_t row = 0; row < A.rows; ++row) {
        printf("[ ");
        for (size_t col = 0; col < A.cols; ++col) {
            printf("%4.2f ", A.data[A.cols * row + col]);
        }
        printf("]\n");
    }
    printf("\n");
}


// A += B
// Function returns 0 if success
int matrix_add(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return 1;

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx) {
        A.data[idx] += B.data[idx];
    }
    return 0;
}


// Function returns MATRIX_NULL if fail
struct Matrix matrix_sum(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return MATRIX_NULL;

    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL) return C;
    
    memcpy(C.data, A.data, C.cols * C.rows * sizeof(MatrixItem));
    matrix_add(C, B);
    return C;
}


int main()
{
    struct Matrix A, B, C;

    A = matrix_create(2, 2, (double[]){1., 1., 1., 1. });
    B = matrix_create(2, 2, (double[]){1., 0., 0., 1. });

    matrix_print(A);

    matrix_add(B, A);
    matrix_print(B);

    C = matrix_sum(A, B);
    matrix_print(C);

    matrix_free(&C);
    matrix_free(&A);
    matrix_free(&B);
    return 0;
}
