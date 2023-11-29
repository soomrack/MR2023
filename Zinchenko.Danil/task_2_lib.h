#pragma once
typedef double MatrixItem;
struct Matrix
{
    size_t cols;
    size_t rows;
    MatrixItem* data;
};

struct Matrix matrix_create(const size_t cols, const size_t rows);


void matrix_delete(struct Matrix* A);


void matrix_set_zero(struct Matrix A);


void matrix_error();


void matrix_set_one(struct Matrix A);


void matrix_print(const struct Matrix A, const char* text);


void determinant_print(struct Matrix A, const char* text);


// A += B
int matrix_add(struct Matrix A, struct Matrix B);


// SUM = A + B
void matrix_sum(const struct Matrix A, const struct Matrix B, const struct Matrix C);


// A = B - C
void matrix_substraction(const struct Matrix A, const struct Matrix B, const struct Matrix C)


// MULT = A * B
struct Matrix matrix_mult(const struct Matrix A, const struct Matrix B);


// A *= k
void matrix_mult_k(struct Matrix A, const MatrixItem k);


// A /= k
void matrix_div_k(struct Matrix A, const MatrixItem k);


// TPOSE = A^T
void matrix_trans(struct Matrix A, struct Matrix T);


// det (A)
MatrixItem matrix_determinant(const struct Matrix A);


// EXP = e^A
struct Matrix matrix_exponent(struct Matrix A);


// filling the matrix with values
void matrix_fill(struct Matrix A, const MatrixItem values[]);
