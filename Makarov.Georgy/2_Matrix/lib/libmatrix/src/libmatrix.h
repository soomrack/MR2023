#ifndef LIBMATRIX_H
#define LIBMATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

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
    MEMORY_ERROR, BAD_MATRIX_ERROR, COLS_ROWS_ERROR, DET_ERROR, LEVEL_ERROR
};


void matrix_error(enum ErrorType error);

struct Matrix matrix_allocate(const size_t rows, const size_t cols);

void matrix_fill(struct Matrix *M, enum MatrixType matrix_type);

void matrix_print(const struct Matrix *M);

struct Matrix matrix_create(const size_t rows, const size_t cols, enum MatrixType mat_type);

void matrix_free(struct Matrix *M);


struct Matrix matrix_sum(const struct Matrix A, const struct Matrix B);

struct Matrix matrix_subtract(const struct Matrix A, const struct Matrix B);

struct Matrix matrix_multiply(const struct Matrix A, const double scalar);

struct Matrix matrix_product(const struct Matrix A, const struct Matrix B);

struct Matrix matrix_transpose(const struct Matrix A);

double matrix_det(const struct Matrix A);

struct Matrix matrix_pow(const struct Matrix A, const unsigned int n);

unsigned long long matrix_factorial(const unsigned int value);

struct Matrix matrix_exp(const struct Matrix A, const unsigned int n);

#endif //LIBMATRIX_H