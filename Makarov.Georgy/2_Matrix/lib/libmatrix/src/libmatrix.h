#ifndef LIBMATRIX_H
#define LIBMATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef double matrix_item;


struct Matrix {
    size_t rows;
    size_t cols;
    matrix_item *data;
};


enum MatrixType {
    ZEROS, ONES, RANDOM, IDENTITY
};
enum ErrorType {
    MEMORY_ERROR, BAD_MATRIX_ERROR, COLS_ROWS_ERROR, DET_ERROR, EXP_LEVEl_ERROR
};


void error_print(enum ErrorType error);

struct Matrix allocate_memory(const size_t rows, const size_t cols);

void fill_matrix(struct Matrix *M, enum MatrixType matrix_type);

void matrix_print(struct Matrix *M);

struct Matrix matrix_create(size_t rows, size_t cols, enum MatrixType mat_type);

void matrix_remove(struct Matrix *M);


struct Matrix matrix_sum(const struct Matrix A, const struct Matrix B);

struct Matrix matrix_subtract(const struct Matrix A, const struct Matrix B);

struct Matrix matrix_multiply(const struct Matrix A, const double scalar);

struct Matrix matrix_product(const struct Matrix A, const struct Matrix B);

struct Matrix matrix_transpose(const struct Matrix A);

double matrix_det(const struct Matrix A);

struct Matrix matrix_exp(const struct Matrix A, const int n);

#endif //LIBMATRIX_H