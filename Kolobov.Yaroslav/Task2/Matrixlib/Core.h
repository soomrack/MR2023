#ifndef CORE_H_INCLUDED
#define CORE_H_INClUDED
#include "Core.c"

typedef MatrixData;

struct Matrix;

enum ErrorType;

void matrix_error(enum ErrorType error);

struct Matrix matrix_allocation(const size_t cols, const size_t rows);

struct Matrix matrix_create(const size_t cols, const size_t rows);

struct Matrix zero_matrix(const size_t cols, const size_t rows);

struct Matrix matrix_fill(const size_t cols, size_t rows, const MatrixData *data);

void matrix_free(struct Matrix *A);

struct Matrix matrix_add(struct Matrix A, struct Matrix B);

struct Matrix matrix_sum(struct Matrix A, struct Matrix B) ;

struct Matrix matrix_substraction(struct Matrix A, struct Matrix B) ;

struct Matrix matrix_difference(struct Matrix A, struct Matrix B) ;

struct Matrix matrix_scalar_multiplication(const struct Matrix A, const double scalar);

struct Matrix matrix_multiplication(const struct Matrix A, const struct Matrix B) ;

double matrix_determinant(const struct Matrix A);

struct Matrix matrix_transposition(const struct Matrix A);

struct Matrix matrix_E(const struct Matrix A);

struct Matrix matrix_exp(const struct Matrix A, const int order);

void matrix_print(const struct Matrix A);

#endif // CORE_H_INCLUDED
