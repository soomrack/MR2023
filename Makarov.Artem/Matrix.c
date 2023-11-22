#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include <math.h>


typedef double MatrixItem;


struct Matrix {
    size_t cols;
    size_t rows;
    MatrixItem* data;
};


const struct Matrix MATRIX_NULL = { .cols = 0, .rows = 0,.data = NULL };


struct Matrix matrix_allocate(const size_t rows, const size_t cols)
{
    if (cols == 0 || rows == 0) {
        struct Matrix A = { .cols = cols, .rows = rows, .data = NULL };
        return A;
    }
    if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols) return MATRIX_NULL;

    struct Matrix A = { .cols = cols, .rows = rows, .data = NULL };
    A.data = (MatrixItem*)malloc(A.cols * A.rows * sizeof(MatrixItem));
    if (A.data == NULL) return MATRIX_NULL;
    return A;
}


struct Matrix matrix_create(const size_t rows, const size_t cols, const MatrixItem* data)
{
    struct Matrix A = matrix_allocate(rows, cols);
    if (A.data == NULL) return A;

    memcpy(A.data, data, rows * cols * sizeof(MatrixItem));
    return A;
}


void matrix_free(struct Matrix* A)
{
    if (A->data != NULL) free(A->data);
    *A = MATRIX_NULL;
}


void matrix_print(const struct Matrix A)
{
    for (size_t row = 0; row < A.rows; ++row) {
        printf("[");
        for (size_t col = 0; col < A.cols; ++col) {
            printf(" %4.2f", A.data[A.cols * row + col]);
        }
        printf(" ]\n");
    }
    printf(" \n");
}


int matrix_add(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return 1;

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx) {
        A.data[idx] += B.data[idx];
    }
    return 0;
}


struct Matrix matrix_sum(const struct Matrix A, const struct Matrix B)
{
    if (A.rows != B.rows || A.cols != B.cols) return MATRIX_NULL;

    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL) return MATRIX_NULL;

    memcpy(C.data, A.data, C.cols * C.rows * sizeof(MatrixItem));
    matrix_add(C, B);
    return C;
}


int matrix_subtraction(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return 1;

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx) {
        A.data[idx] -= B.data[idx];
    }
    return 0;
}


struct Matrix matrix_difference(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return MATRIX_NULL;

    struct Matrix C = matrix_allocate(A.rows, A.cols);
    if (C.data == NULL) return MATRIX_NULL;

    memcpy(C.data, A.data, C.cols * C.rows * sizeof(MatrixItem));
    matrix_subtraction(C, B);
    return C;
}


struct Matrix matrix_scalar(const struct Matrix A, const double x)
{
    struct Matrix C = matrix_allocate(A.rows, A.cols);
    if (C.data == NULL) return MATRIX_NULL;

    for (size_t idx = 0; idx < A.cols * A.rows; idx++) {
        C.data[idx] = x * A.data[idx];
    }
    return C;
}


struct Matrix matrix_multiply(const struct Matrix A, const struct Matrix B)
{
    if (A.rows != B.rows) return MATRIX_NULL;

    struct Matrix C = matrix_allocate(A.rows, B.cols);
    if (C.data == NULL) return MATRIX_NULL;

    for (size_t rowA = 0; rowA < A.rows; rowA++)
        for (size_t colB = 0; colB < B.cols; colB++) {
            C.data[rowA * B.cols + colB] = 0;

            for (size_t idx = 0; idx < A.cols; idx++)
                C.data[rowA * B.cols + colB] += A.data[rowA * A.cols + idx] * B.data[idx * B.cols + colB];
        }
    return C;
}


struct Matrix transpose(const struct Matrix A)
{
    struct Matrix T = matrix_allocate(A.cols, A.rows);
    if (T.data == NULL) return MATRIX_NULL;

    for (size_t rows = 0; rows < A.rows; rows++) {
        for (size_t cols = 0; cols < A.cols; cols++) {
            T.data[rows * A.rows + cols] = A.data[cols * A.cols + rows];
        }
    }
    return T;
}


double det(const struct Matrix A)
{
    if (A.rows != A.cols) return NAN;

    if (A.cols == 1) return A.data[0];

    if (A.cols == 2) return (A.data[0] * A.data[3] - A.data[1] * A.data[2]);

    if (A.cols == 3) {
        return (A.data[0] * A.data[4] * A.data[8]) + \
            (A.data[1] * A.data[5] * A.data[6]) + \
            (A.data[2] * A.data[3] * A.data[7]) - \
            (A.data[2] * A.data[4] * A.data[6]) - \
            (A.data[0] * A.data[5] * A.data[7]) - \
            (A.data[1] * A.data[3] * A.data[8]);
    }
    return NAN;
}


int main()
{
    struct Matrix A, B, C, T;


    printf(" First matrix\n");
    A = matrix_create(2, 2, (double[]) { 3., 6., 3., 6. });
    matrix_create(A.cols, A.rows, &A);
    matrix_print(A);


    printf(" Second matrix\n");
    B = matrix_create(2, 2, (double[]) { 2., 3., 4., 5. });
    matrix_create(B.cols, B.rows, &B);
    matrix_print(B);


    printf(" Sum of matrices\n");
    matrix_add(A, B);
    matrix_print(A);


    matrix_subtraction(A, B);


    printf(" Matrix subtraction\n");
    C = matrix_difference(A, B);
    matrix_print(C);


    printf(" Multiplying the matrix by scalar\n");
    C = matrix_scalar(A, 3);
    matrix_print(C);


    printf(" Multiplying the first matrix by a second matrix\n");
    C = matrix_multiply(A, B);
    matrix_print(C);


    printf(" Transposed matrix\n");
    C = transpose(A);
    matrix_print(C);


    printf(" Determinant of the matrix\n");
    det(A);
    printf("%4.2f \n", det(A));


    matrix_free(&A);
    matrix_free(&B);
    matrix_free(&C);


    return 0;
}