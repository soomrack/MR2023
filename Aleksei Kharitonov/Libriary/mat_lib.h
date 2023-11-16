#ifndef LIBMATRIX_H
#define LIBMATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct Matrix {
    int rows;
    int cols;
    double* data;
};


struct Matrix matrix_create(const int rows, const int cols);


void matrix_delete(struct Matrix* A);


void matrix_set_zero(struct Matrix A);


void matrix_set_one(struct Matrix A);


void matrix_print(const struct Matrix A);


// A + B
struct Matrix matrix_add(const struct Matrix A, const struct Matrix B);


// A - B
struct Matrix matrix_minus(struct Matrix A, struct Matrix B);


// A * B
struct Matrix matrix_mult(struct Matrix A, struct Matrix B);


//A * number
struct Matrix matrix_mult_on_number(struct Matrix A, int number);


// A/number
struct Matrix matrix_div_on_number(struct Matrix A, int number);


//A = A^t
struct Matrix matrix_trans(struct Matrix A);


//Determinant
double matrix_det(struct Matrix A);


// exponent
struct Matrix matrix_exp(struct Matrix A, int N);


void matrix_fill(struct Matrix A, const double values[]);

#endif
