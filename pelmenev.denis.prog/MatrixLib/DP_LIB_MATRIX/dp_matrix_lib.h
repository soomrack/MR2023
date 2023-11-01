#ifndef __MATRIX__
#define __MATRIX__

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

struct Matrix matrix_allocate(const size_t cols, const size_t rows);
void matrix_free(struct Matrix *matrix);
void print_matrix(const struct Matrix A);
void matrix_copy(const struct Matrix B, const struct Matrix A);
void matrix_mult_by_coeff(struct Matrix A, const double coefficient);
void matrix_zero(struct Matrix A);
struct Matrix matrix_sum(const struct Matrix A, const struct Matrix B);
void matrix_add(const struct Matrix A, const struct Matrix B);
struct Matrix matrix_substr(const struct Matrix A, const struct Matrix B);
struct Matrix matrix_mult(const struct Matrix A, const struct Matrix B);
void matrix_add_mult(const struct Matrix A, const struct Matrix B);
struct Matrix matrix_transp(const struct Matrix A);
struct Matrix matrix_exponent(const struct Matrix A, const double accuracy);
int matrix_det_if_zero(const struct Matrix A);
void matrix_det_prep(const struct Matrix A, size_t diag, double *coeff);
double matrix_det(const struct Matrix A);

#endif