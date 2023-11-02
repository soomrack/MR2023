#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "libmatrix.h"


typedef double MatrixItem;


struct Matrix {
    size_t cols;
    size_t rows;
    MatrixItem *data;
};


const struct Matrix MATRIX_NULL = {.rows = 0, .cols = 0, .data = NULL};


// Function returns zero matrix or MATRIX_NULL if fail
void matrix_set_zero(const struct Matrix A)
{
    if (A.cols == 0 || A.rows == 0) return; // MATRIX_NULL
    memset(A.data, 0, sizeof(double) * A.rows * A.cols);
}

// Function returns unit matrix or MATRIX_NULL if fail
void matrix_set_one(const struct Matrix A)
{
    if (A.cols == 0 || A.rows == 0) return; // MATRIX_NULL
    matrix_set_zero(A);
    for (size_t idx = 0; idx < A.rows * A.cols; idx += A.cols + 1)
    A.data[idx] = 1;
}


struct Matrix matrix_allocate(const size_t rows, const size_t cols)
{
    if (cols == 0 || rows == 0) {
        struct Matrix A = {.cols = cols, .rows = rows, .data = NULL};
        return A;
    };
    if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols) return MATRIX_NULL; // rows * cols < MAX_SIZE / sizeof(double)

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


void matrix_delete(const struct Matrix *A)
{
    free(A->data);
    *A = MATRIX_NULL;
}


void matrix_print(const struct Matrix A)
{
    printf("\n");
    for (size_t col = 0; col < A.rows; ++col) {
        printf("[ ");
        for (size_t row = 0; row < A.cols; ++row) {
            printf(" %4.2f", A.data[row + col * A.cols ]);
        }
        printf("]\n");
    }
}


// A = A + B
// Function return 0 if success
int matrix_add(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return 1;
    
    for (size_t idx = 0; idx < A.cols * A.rows; ++idx) A.data[idx] += B.data[idx];
        return 0;
}


// Function returns new matrix C = A + B or MATRIX_NULL if fail
struct Matrix matrix_sum(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return MATRIX_NULL;

    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL) return C;
    
    memcpy(C.data, A.data, C.cols * C.rows * sizeof(MatrixItem));
    matrix_add(C, B);
    return C;
}

// A = A - B
// Function return 0 if success
int matrix_subtract(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return 1;
    
    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        A.data[idx] -= B.data[idx];
        return 0;
}


// Function returns new matrix C = A - B or MATRIX_NULL if fail
struct Matrix matrix_subtration(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return MATRIX_NULL;

    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL) return C;
    
    memcpy(C.data, A.data, C.cols * C.rows * sizeof(MatrixItem));
    matrix_subtract(C, B);
    return C;
}


// Function returns new matrix C = A * B or MATRIX_NULL if fail
struct Matrix matrix_mult(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.rows) return MATRIX_NULL;
    
    struct Matrix C = matrix_allocate(A.rows, B.cols);
    if (C.data == NULL) return C;

    for (size_t C_col = 0; C_col < A.rows; ++C_col) {
        for (size_t C_row = 0; C_row < B.cols; ++C_row) {
            C.data[C_row + C_col * B.cols] = 0;
            for (size_t idx = 0; idx < A.cols; ++idx) {
                C.data[C_row + C_col * B.cols] += A.data[idx + (C_col * A.cols)]
                * B.data[idx * B.cols + C_row];
            };
        };
    };
    return C;
}


// Function returns new matrix C = A^T or MATRIX_NULL if fail
struct Matrix matrix_transposition(const struct Matrix A)
{
    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL) return C;

    for (size_t C_row = 0; C_row < A.cols; ++C_row) {
        for (size_t C_col = 0; C_col < A.rows; ++C_col) {
            C.data[C_col + C_row * A.rows] = A.data[C_col * A.cols + C_row];
        };
    };
    return C;
}


// Function returns C = |A| (A[1x1]) or NAN if fail
MatrixItem matrix_determinant_1x1(const struct Matrix A)
{
    MatrixItem C;

    if (A.cols != 1 && A.rows != 1) return NAN;

    C = A.data[0];
    return C;
}


// Function returns C = |A| (A[2x2]) or NAN if fail
MatrixItem matrix_determinant_2x2(const struct Matrix A)
{
    MatrixItem C;

    if (A.cols != 2 && A.rows != 2) return NAN;

    C = A.data[0] * A.data[3] - A.data[1] * A.data[2];
    return C;
}


// Function returns C = |A| (A[3x3]) or NAN if fail
MatrixItem matrix_determinant_3x3(const struct Matrix A)
{
    MatrixItem C;

    if (A.cols != 3 && A.rows != 3) return NAN;

    C =
        + A.data[0] * A.data[4] * A.data[8]
        + A.data[6] * A.data[1] * A.data[5]
        + A.data[3] * A.data[7] * A.data[2]
        - A.data[2] * A.data[4] * A.data[6]
        - A.data[5] * A.data[7] * A.data[0]
        - A.data[3] * A.data[1] * A.data[8];
    return C;
}


// Function returns C = |A| (A[1x1], A[2x2], A[3x3]) or NAN if fail
MatrixItem matrix_determinant(const struct Matrix A)
{
    if (A.cols != A.rows) return NAN; 

    switch (A.rows)
    {
    case 1:
        return matrix_determinant_1x1(A);
        break;
    case 2:
        return matrix_determinant_2x2(A);
        break;
    case 3:
        return matrix_determinant_3x3(A);
        break;    
    default:
        return NAN;
        break;
    };
    return NAN;
}


void determinant_print(const double A)
{
    printf("\n Matrix determinant = %4.2lf", A);
}


// Function returns new matrix C = e^A or MATRIX_NULL if fail
struct Matrix matrix_exponent(const struct Matrix A)
{
    if (A.cols != A.rows) return MATRIX_NULL;

    if (A.cols == 0) return MATRIX_NULL;
    
    struct Matrix Matrix_result = matrix_allocate(A.cols, A.rows);
    if (Matrix_result.data == NULL) return Matrix_result;

    struct Matrix Matrix_power;

    struct Matrix Matrix_previous_step = matrix_allocate(A.cols, A.rows);
    if (Matrix_previous_step.data == NULL) {
        matrix_delete(&Matrix_result);
        return Matrix_previous_step;
    };

    struct Matrix Matrix_exp = matrix_allocate(A.cols, A.rows);
    if (Matrix_exp.data == NULL) {
        matrix_delete(&Matrix_result);
        matrix_delete(&Matrix_previous_step);
        return Matrix_exp;
    };

    matrix_set_one(Matrix_previous_step);
   
    matrix_add(Matrix_previous_step, A);

    for (unsigned int k = 2; k <= 5; ++k) { 

        Matrix_power = matrix_mult(Matrix_previous_step, A);

        if (Matrix_power.data == NULL) return Matrix_power;
        

        for (unsigned int idx = 0; idx < Matrix_exp.cols * Matrix_exp.rows; ++idx)
            Matrix_exp.data[idx] = Matrix_power.data[idx] / k;

        memcpy(Matrix_previous_step.data, Matrix_exp.data,
               Matrix_exp.rows * Matrix_exp.cols * sizeof(MatrixItem));

        matrix_delete(&Matrix_power);
    };

    memcpy(Matrix_result.data, Matrix_previous_step.data,
           Matrix_previous_step.rows * Matrix_previous_step.cols * sizeof(MatrixItem));
    matrix_delete(&Matrix_previous_step);
    matrix_delete(&Matrix_exp);
    return Matrix_result;
}