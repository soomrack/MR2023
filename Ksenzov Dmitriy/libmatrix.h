#ifndef LIBMATRIX_H
#define LIBMATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

typedef double MatrixItem;


struct Matrix {
    size_t cols;
    size_t rows;
    MatrixItem *data;
};


const struct Matrix MATRIX_NULL = {.rows = 0, .cols = 0, .data = NULL};


void matrix_set_zero(const struct Matrix A);
void matrix_set_one(const struct Matrix A);
struct Matrix matrix_create(const const size_t rows, const size_t cols, const MatrixItem *values);
void matrix_delete(const struct Matrix *A);
void matrix_print(const struct Matrix A);
int matrix_add(const struct Matrix A, struct Matrix B);
struct Matrix matrix_sum(const struct Matrix A, const struct Matrix B);
int matrix_subtract(const struct Matrix A, struct Matrix B);
struct Matrix matrix_subtration(const struct Matrix A, const struct Matrix B);
struct Matrix matrix_mult(const struct Matrix A, struct Matrix B);
struct Matrix matrix_transposition(const struct Matrix A);
MatrixItem matrix_determinant(const struct Matrix A);
void determinant_print(const MatrixItem A);
struct Matrix matrix_exponent(const struct Matrix A);


#endif