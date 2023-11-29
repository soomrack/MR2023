#ifndef LIBMATRIX_H
#define LIBMATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

struct Matrix {
	size_t rows;
	size_t cols;
	double* data;
};

const struct Matrix NULL_MATRIX = { .rows = 0, .cols = 0, .data = NULL };


struct Matrix matrix_create(const unsigned int rows, const unsigned int cols);

void matrix_delete(struct Matrix* A);
void matrix_set_zero(struct Matrix A);
void matrix_set_onetonum(struct Matrix A);
void matrix_set_numtoone(struct Matrix A)
void matrix_set_one(struct Matrix A);
void matrix_print(const struct Matrix A);
struct Matrix marix_sum(struct Matrix A, struct Matrix B);
struct Matrix matrix_sub(struct Matrix A, struct Matrix B);
int matrix_add(struct Matrix A, struct Matrix B);
struct Matrix matrix_mult(struct Matrix A, struct Matrix B);
struct Matrix matrix_division(struct Matrix A, const double k);
struct Matrix matrix_trans(struct Matrix A);
double matrix_det(struct Matrix A);
struct Matrix matrix_exp(struct Matrix A);

#endif