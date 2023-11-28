#pragma once


struct Matrix {
    unsigned int rows;
    unsigned int cols;
    double* data;
};


struct Matrix matrix_creation(const unsigned int rows, const unsigned int cols);


void delete_matrix(struct Matrix* A);


void zero_matrix(struct Matrix A);


void matrix_set_one(struct Matrix A);


// A += B
int matrix_add(struct Matrix A, struct Matrix B);


// Ñ = A + B
void matrix_sum(const struct Matrix A, const struct Matrix B, const struct Matrix C);


// C = A - B
void matrix_sub(const struct Matrix A, const struct Matrix B, const struct Matrix C);


// diff = A - B
struct Matrix matrix_diff(struct Matrix A, struct Matrix B);


// mult = A * B
struct Matrix matrix_mult(struct Matrix A, struct Matrix B);


// A /= k
void matrix_div_k(struct Matrix A, const double k);


// trans = A^T
struct Matrix matrix_trans(struct Matrix A);


// exp = e^A
struct Matrix matrix_exp(struct Matrix A);


void matrix_fill(struct Matrix A, const double* values);


void matrix_print(const struct Matrix A, const char* text);
