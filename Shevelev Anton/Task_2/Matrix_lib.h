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

// записываем непосредственно математические операции

int matrix_add(struct Matrix A, struct Matrix B); // A += B



void matrix_sum(const struct Matrix A, const struct Matrix B, const struct Matrix C); // SUM = A + B



void matrix_substraction(const struct Matrix A, const struct Matrix B, const struct Matrix C) // A = B - C



struct Matrix matrix_mult(const struct Matrix A, const struct Matrix B); // MULT = A * B



void matrix_mult_k(struct Matrix A, const MatrixItem k); // A *= k



void matrix_div_k(struct Matrix A, const MatrixItem k); // A /= k



void matrix_trans(struct Matrix A, struct Matrix T); // TPOSE = A^T



MatrixItem matrix_determinant(const struct Matrix A); // det (A)



struct Matrix matrix_exponent(struct Matrix A); // EXP = e^A



void matrix_fill(struct Matrix A, const MatrixItem values[]); // Заполнение матрицы
