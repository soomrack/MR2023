#pragma once
typedef double MatrixItem;


struct Matrix {
    size_t rows;
    size_t cols;
    MatrixItem* data;
};


struct Matrix matrix_allocation(const size_t rows, const size_t cols);


void matrix_delete(struct Matrix* A);


void matrix_set_zero(struct Matrix A);


void matrix_set_one(struct Matrix A);


void matrix_print(const struct Matrix A, const char* text);


void value_print(MatrixItem A, const char* text);


// A += B
int matrix_add(struct Matrix A, struct Matrix B);


// SUM = A + B
struct Matrix matrix_sum(struct Matrix A, struct Matrix B);


// A -= B
int matrix_sub(struct Matrix A, struct Matrix B);


// DIFF = A - B
struct Matrix matrix_diff(struct Matrix A, struct Matrix B);


// MULT = A * B
struct Matrix matrix_mult(struct Matrix A, struct Matrix B);


// A *= k
void matrix_mult_k(struct Matrix A, const MatrixItem k);


// A /= k
void matrix_div_k(struct Matrix A, const MatrixItem k);


// TPOSE = A^T
struct Matrix matrix_transpose(struct Matrix A);


// A = A^T
void matrix_tpose(struct Matrix A);


// det (A)
MatrixItem matrix_determinant(struct Matrix A);


// EXP = e^A
struct Matrix matrix_exp(struct Matrix A);


// filling the matrix with values
void matrix_fill(struct Matrix A, const double* values); #pragma once
