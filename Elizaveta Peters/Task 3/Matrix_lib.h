#pragma once


struct Matrix matrix_allocation(const unsigned int rows, const unsigned int cols);


void matrix_delete(struct Matrix* A);


void matrix_set_zero(struct Matrix A);


void matrix_set_one(struct Matrix A);


void matrix_print(const struct Matrix A, const char* text);


// A += B
int matrix_add(struct Matrix A, struct Matrix B);


// SUM = A + B
struct Matrix matrix_sum(struct Matrix A, struct Matrix B);


// SUB = A - B
struct Matrix matrix_sub(struct Matrix A, struct Matrix B);


// MULT = A * B
struct Matrix matrix_multip(struct Matrix A, struct Matrix B);


// A /= k
void matrix_div_k(struct Matrix A, const double k);


// TRANS = A^T
struct Matrix matrix_trans(struct Matrix A);


// EXP = e^A
struct Matrix matrix_exp(struct Matrix A);


// filling the matrix with values
void matrix_fill(struct Matrix A, const double* values);