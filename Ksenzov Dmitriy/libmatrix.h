#ifndef __LIBMATRIX__
#define __LIBMATRIX__


typedef double MatrixItem;


struct Matrix;


void matrix_set_zero(struct Matrix A);
void matrix_set_one(struct Matrix A);
struct Matrix matrix_create(const size_t rows, const size_t cols, const MatrixItem *values);
void matrix_delete(struct Matrix *A);
void matrix_print(const struct Matrix A);
int matrix_add(struct Matrix A, struct Matrix B);
struct Matrix matrix_sum(const struct Matrix A, const struct Matrix B);
int matrix_subtract(struct Matrix A, struct Matrix B);
struct Matrix matrix_subtration(const struct Matrix A, const struct Matrix B);
struct Matrix matrix_mult(struct Matrix A, struct Matrix B);
struct Matrix matrix_transposition(struct Matrix A);
MatrixItem matrix_determinant(struct Matrix A);
void determinant_print(const double A);
struct Matrix matrix_exponent(struct Matrix A);


#endif