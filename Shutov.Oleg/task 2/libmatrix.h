#pragma once
typedef double MatrixItem;


struct Matrix {
    size_t rows;
    size_t cols;
    MatrixItem* data;
};


struct Matrix matrix_allocate(const size_t rows, const size_t cols);


void matrix_delete(struct Matrix* A);


void matrix_set_zero(struct Matrix A);


void matrix_set_one(struct Matrix A);


void matrix_print(const struct Matrix A, const char* text);


// A += B
int matrix_add(struct Matrix A, struct Matrix B);


// C = A + B
struct Matrix matrix_sum(struct Matrix A, struct Matrix B);


// A -= B
int matrix_sub(struct Matrix A, struct Matrix B);


// C = A - B
struct Matrix matrix_subtract(struct Matrix A, struct Matrix B);


// MULT = A * B
struct Matrix matrix_multiplication(struct Matrix A, struct Matrix B);


// A *= k
void matrix_multk(struct Matrix A, const MatrixItem k);


// A /= k
void matrix_divk(struct Matrix A, const MatrixItem k);


// C = A^T
struct Matrix matrix_transposition(struct Matrix A);


// det (A)
MatrixItem matrix_determinant(struct Matrix A);


// EXP = e^A
struct Matrix matrix_exp(struct Matrix A);


// filling the matrix with values
void matrix_fill(struct Matrix A, const double* values);
