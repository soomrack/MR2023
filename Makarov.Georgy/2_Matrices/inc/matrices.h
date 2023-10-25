#ifndef MATRICES_H
#define MATRICES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>


struct Matrix {
    size_t rows;
    size_t cols;
    double *data;
};


enum MatrixType {
    ZEROS, ONES, RANDOM, IDENTITY
};
enum ErrorType {
    MEMORY_ERROR, BAD_MATRIX_ERROR, COLS_ROWS_ERROR
};


void print_matrix(struct Matrix *M);

void print_error(enum ErrorType error);

struct Matrix allocate_memory(size_t rows, size_t cols);

struct Matrix create_matrix(size_t rows, size_t cols, enum MatrixType mat_type);

void delete_matrix(struct Matrix *matrix);

struct Matrix matrices_sum(const struct Matrix *A, const struct Matrix *B);

struct Matrix matrices_subtraction(const struct Matrix *A, const struct Matrix *B);

struct Matrix matrix_scalar_multiplication(const struct Matrix *A, double scalar);

struct Matrix matrices_multiplication(const struct Matrix *A, const struct Matrix *B);

struct Matrix matrix_transposition(const struct Matrix *A);

#endif //MATRICES_H