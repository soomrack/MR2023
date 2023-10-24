#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Matrix.h"

const struct Matrix MATRIX_NULL = { .cols = 0, .rows = 0, .data = NULL };

void error_control(enum Error_type error)
{
    switch (error)
    {
        case memory_alloccation_error:
            printf("no memory was allocated for the array\n");
            break;
        case false_matrix:
            printf("the original matrix is incorrect or difficult to calculate\n");
            break;
        case false_rows_or_cols:
            printf("the number of rows or columns in the matrices is incorrect\n");
            break;
        case empty_matrix:
            printf("Matrix are empty\n");
            break;
        default:
            printf("undeclared error\n");
            break;
    }
}


int matrix_print(struct Matrix *M)
{
    if (M->data == NULL) {
        error_control(empty_matrix);
        return 0;
    }

    printf("\n");
    for (size_t rows = 0; rows < M->rows; rows++) {
        printf("[");
        for (size_t cols = 0; cols < M->cols; cols++) {
            printf("%.1lf", M->data[rows * M->cols + cols]);
            if (cols != M->cols - 1)
                printf("\t");
        }
        printf("]\n");
    }
    printf("\n");
    return 1;
}


struct Matrix memory_allocation(const size_t rows, const size_t cols)
{
    if (cols == 0 || rows == 0) return MATRIX_NULL;

    if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols) {
        error_control(memory_alloccation_error);
        return MATRIX_NULL; 
    }

    struct Matrix M = { .cols = cols, .rows = rows, .data = NULL };
    M.data = (MatrixItem*)malloc(M.cols * M.rows * sizeof(MatrixItem));

    if (M.data == NULL) return MATRIX_NULL;

    return M;
}


void matrix_fill(struct Matrix* M, enum MatrixType mat_type)
{
    switch (mat_type)
    {
    case (zero):
        for (size_t idx = 0; idx < M->cols * M->rows; idx++)
            M->data[idx] = 0.0;
        break;

    case (ones):
        for (size_t idx = 0; idx < M->cols * M->rows; idx++)
            M->data[idx] = 1.0;
        break;

    case (random):
        for (size_t idx = 0; idx < M->cols * M->rows; idx++)
            M->data[idx] = (double)(rand() % 100);
        break;

    case (I):
        if (M->cols == M->rows)
            for (size_t row_M = 0; row_M < M->rows; row_M++)
                for (size_t col_M = 0; col_M < M->cols; col_M++) {

                    if (row_M == col_M)
                        M->data[row_M * M->cols + col_M] = 1.0;
                    else
                        M->data[row_M * M->cols + col_M] = 0.0;
                }
        break;
    }
}


struct Matrix matrix_create(const size_t rows, const size_t cols, enum MatrixType mat_type)
{    
    struct Matrix M = memory_allocation(rows, cols);
    if (M.data == NULL) return M;

    matrix_fill(&M, mat_type);
    return M;
}

void matrix_free(struct Matrix* M)
{
    free(M->data);
    *M = MATRIX_NULL;
}


struct Matrix matrix_subst(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows){
        error_control(false_rows_or_cols);
        return MATRIX_NULL;
    }

    struct Matrix C = memory_allocation(A.rows, A.cols);

    for (size_t idx = 0; idx < A.rows * A.cols; idx++)
        C.data[idx] = B.data[idx] - A.data[idx];
    return C;
}


int matrix_add(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) {
        error_control(false_rows_or_cols);
        return 1;
    }     

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx) {
        A.data[idx] += B.data[idx];
    }
    return 0;
}


struct Matrix matrix_sum(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) {
        error_control(false_rows_or_cols);
        return MATRIX_NULL;
    }

    struct Matrix C = memory_allocation(A.rows, A.cols);
    if (C.data == NULL) return MATRIX_NULL;

    memcpy(C.data, A.data, C.cols * C.rows * sizeof(MatrixItem));
    matrix_add(C, B);
    return C;
}


struct Matrix matrix_mult_on_number(const struct Matrix A, double multiplier)
{
    struct Matrix C = memory_allocation(A.rows, A.cols);

    for (size_t idx = 0; idx < A.rows * A.cols; idx++)
        C.data[idx] = multiplier * A.data[idx];
    return C;
}


struct Matrix matrix_mult(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.rows) {
        error_control(false_rows_or_cols);
        return MATRIX_NULL;
    }
    
    struct Matrix C = memory_allocation(A.rows, B.cols);
    matrix_fill(&C, zero);

    for (size_t row_A = 0; row_A < A.rows; row_A++)
        for (size_t col_B = 0; col_B < B.cols; col_B++)
            for (size_t idx = 0; idx < A.cols; idx++)
                C.data[row_A * A.cols + col_B] += A.data[row_A * A.cols + idx] * B.data[idx * B.cols + col_B];
    return C;
}


struct Matrix transposition(const struct Matrix A)
{
    struct Matrix C = memory_allocation(A.cols, A.rows);
    matrix_fill(&C, zero);

    for (size_t rows = 0; rows < A.rows; rows++)
        for (size_t cols = 0; cols < A.cols; cols++)
            C.data[rows * A.rows + cols] = A.data[cols * A.cols + rows];
    return C;
}


double determinant(struct Matrix A)
{
    if (A.cols != A.rows) {
        error_control(false_rows_or_cols);
        return 404.404;
    }

    if (A.cols == 2)
        return A.data[0] * A.data[3] - A.data[1] * A.data[2];
    else if (A.cols == 3)
        return (A.data[0] * A.data[4] * A.data[8]) + \
                (A.data[1] * A.data[5] * A.data[6]) + \
                (A.data[2] * A.data[3] * A.data[7]) - \
                (A.data[2] * A.data[4] * A.data[6]) - \
                (A.data[0] * A.data[5] * A.data[7]) - \
                (A.data[1] * A.data[3] * A.data[8]);
    else
    {
        error_control(false_matrix);
        return 404.404;
    }
}


double fuctorial(double level)
{
    if (level == 1) return 1;

    return level * fuctorial(level - 1);
}


struct Matrix matrix_stage(struct Matrix M, double level)
{
    if (level == 1) return M;

    return matrix_mult(M, matrix_stage(M, level - 1));
}


struct Matrix matrix_exponential(struct Matrix M, double level)
{
    struct Matrix C;

    if (M.cols != M.rows) {
        error_control(false_rows_or_cols);
        return MATRIX_NULL;
    }

    if (level == 0) {
        C = memory_allocation(M.rows, M.cols);
        matrix_fill(&C, I);
        return C;
    }

    return matrix_sum(matrix_mult_on_number(matrix_stage(M, level), \
        1/fuctorial(level)), matrix_exponential(M, level - 1));
}


void matrix_print_free(struct Matrix *M)
{
    matrix_print(M);
    matrix_free(M);
}