#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Matrix.h"

const struct Matrix MATRIX_NULL = { .cols = 0, .rows = 0, .data = NULL };
enum ErrorType { MEM_ALLOC_ERROR, FALSE_MATRIX, FALSE_ROWS_COLS, EMPTY_MATRIX };

void matrix_exaption(enum Error_type error)
{
    switch (error)
    {
        case MEM_ALLOC_ERROR:
            printf("no memory was allocated for the array\n");
            break;
        case FALSE_MATRIX:
            printf("the original matrix is incorrect or difficult to calculate\n");
            break;
        case FALSE_ROWS_COLS:
            printf("the number of rows or columns in the matrices is incorrect\n");
            break;
        case EMPTY_MATRIX:
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
        matrix_exaption(EMPTY_MATRIX);
        return 0;
    }

    printf("\n");
    for (size_t rows = 0; rows < M->rows; rows++) {
        printf("[");
        for (size_t cols = 0; cols < M->cols; cols++) {
            printf("%.10lf", M->data[rows * M->cols + cols]);
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
    if (cols == 0 || rows == 0) {
        struct Matrix M = { .cols = cols, .rows = rows, .data = NULL };
        return M;
    }

    if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols) {
        matrix_exaption(MEM_ALLOC_ERROR);
        return MATRIX_NULL; 
    }

    struct Matrix M = { .cols = cols, .rows = rows, .data = NULL };
    M.data = (MatrixItem*)malloc(M.cols * M.rows * sizeof(MatrixItem));

    if (M.data == NULL) {
        matrix_exaption(MEM_ALLOC_ERROR);
        return MATRIX_NULL;
    }

    if (M.data == NULL) return MATRIX_NULL;

    return M;
}


void matrix_fill(struct Matrix* M, enum MatrixType mat_type)
{
    switch (mat_type)
    {
    case (ZERO):
        for (size_t idx = 0; idx < M->cols * M->rows; idx++)
            M->data[idx] = 0.0;
        break;

    case (ONES):
        for (size_t idx = 0; idx < M->cols * M->rows; idx++)
            M->data[idx] = 1.0;
        break;

    case (RANDOM):
        for (size_t idx = 0; idx < M->cols * M->rows; idx++)
            M->data[idx] = (double)(rand() % 100);
        break;

    case (I):
        if (M->cols == M->rows) {
            matrix_fill(M, ZERO);
            for (size_t row_col_M = 0; row_col_M < M->rows; row_col_M++)
                M->data[row_col_M * M->cols + row_col_M] = 1.0;
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
        matrix_exaption(FALSE_ROWS_COLS);
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
        matrix_exaption(FALSE_ROWS_COLS);
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
        matrix_exaption(FALSE_ROWS_COLS);
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
        matrix_exaption(FALSE_ROWS_COLS);
        return MATRIX_NULL;
    }
    
    struct Matrix C = memory_allocation(A.rows, B.cols);
    matrix_fill(&C, ZERO);

    for (size_t row_A = 0; row_A < A.rows; row_A++)
        for (size_t col_B = 0; col_B < B.cols; col_B++)
            for (size_t idx = 0; idx < A.cols; idx++)
                C.data[row_A * A.cols + col_B] += A.data[row_A * A.cols + idx] * B.data[idx * B.cols + col_B];
    return C;
}


struct Matrix transposition(const struct Matrix A)
{
    struct Matrix C = memory_allocation(A.cols, A.rows);
    matrix_fill(&C, ZERO);

    for (size_t rows = 0; rows < A.rows; rows++)
        for (size_t cols = 0; cols < A.cols; cols++)
            C.data[rows * A.rows + cols] = A.data[cols * A.cols + rows];
    return C;
}


double determinant(struct Matrix A)
{
    if (A.cols != A.rows) {
        matrix_exaption(FALSE_ROWS_COLS);
        return NAN;
    }

    if (A.cols == 2) {
        return A.data[0] * A.data[3] - A.data[1] * A.data[2];
    }

    if (A.cols == 3) {
        return (A.data[0] * A.data[4] * A.data[8]) + \
            (A.data[1] * A.data[5] * A.data[6]) + \
            (A.data[2] * A.data[3] * A.data[7]) - \
            (A.data[2] * A.data[4] * A.data[6]) - \
            (A.data[0] * A.data[5] * A.data[7]) - \
            (A.data[1] * A.data[3] * A.data[8]);
    }
    
    matrix_exaption(FALSE_MATRIX);
    return NAN;
}


struct Matrix matrix_exponential_summand(struct Matrix M, unsigned int level)
{
    struct Matrix C;
    unsigned int n = 1;

    for (unsigned int counter = 1; counter <= level; counter++) n *= counter;

    for (unsigned int counter = 1; counter <= level; counter++) {
        if (counter == 1) C = matrix_mult(M, M);
        else C = matrix_mult(C, M);
    }

    return matrix_mult_on_number(C, 1/(double)n);
}


struct Matrix matrix_exponential(struct Matrix M, unsigned long int level)
{
    struct Matrix C, S;

    if (M.cols != M.rows) {
        matrix_exaption(FALSE_ROWS_COLS);
        return MATRIX_NULL;
    }    

    for (unsigned int count = 0; count <= level; count++) {
        if (count == 0) {
            S = memory_allocation(M.rows, M.cols);
            matrix_fill(&S, I);
            continue;
        }

        C = matrix_exponential_summand(M, count);
        matrix_add(S, C);
        matrix_free(&C);
    }
    return S;
}


void matrix_print_free(struct Matrix *M)
{
    matrix_print(M);
    matrix_free(M);
}