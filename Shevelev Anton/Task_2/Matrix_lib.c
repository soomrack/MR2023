#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>


typedef double MatrixItem;
struct Matrix
{
    size_t cols;
    size_t rows;
    MatrixItem* data;
};


const struct Matrix MATRIX_NULL = { .cols = 0,  .rows = 0, .data = NULL };


struct Matrix matrix_create(const size_t cols, const size_t rows)
{
    if (cols == 0 || rows == 0) 
    {
        struct Matrix A = { .cols = cols, .rows = rows, .data = NULL };
        return A;
    }
    if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols) return MATRIX_NULL;
    struct Matrix A = { .cols = cols, .rows = rows, .data = NULL };
    A.data = malloc(sizeof(MatrixItem) * A.cols * A.rows);
    if (A.data == NULL) return MATRIX_NULL;
    return A;
}


void matrix_set_zero(struct Matrix A)
{
    if (A.data == NULL) return;
    memset(A.data, 0, sizeof(MatrixItem) * A.cols * A.rows);
}


void matrix_set_one(struct Matrix A)
{
    matrix_set_zero(A);
    for (size_t idx = 0; idx < A.cols * A.rows; idx += A.cols + 1)
        A.data[idx] = 1;
}


void matrix_error()
{
    printf("Error: different number of columns or rows\n");
}


void matrix_fill(struct Matrix A, const MatrixItem values[])
{
    if (A.data == NULL) {
        matrix_error();
        return;
    }
    memcpy(A.data, values, A.rows * A.cols * sizeof(MatrixItem));
}


void matrix_sum(const struct Matrix A, const struct Matrix B, const struct Matrix C) // A = B + C
{
    if (B.cols != C.cols || B.rows != C.rows) {
        matrix_error();
        return;
    }
    if (A.data == NULL) return MATRIX_NULL;
    for (size_t idx = 0; idx < B.cols * B.rows; ++idx) {
        A.data[idx] = B.data[idx] + C.data[idx];
    }
}

// A = B - C
void matrix_substraction(const struct Matrix A, const struct Matrix B, const struct Matrix C)
{
    if (B.cols != C.cols || B.rows != C.rows) {
        matrix_error();
        return;
    }
    if (A.data == NULL) return MATRIX_NULL;
    for (size_t idx = 0; idx < B.cols * B.rows; ++idx) {
        A.data[idx] = B.data[idx] - C.data[idx];
    }
}


struct Matrix matrix_mult(const struct Matrix A, const struct Matrix B) // MULT = A * B
{  
    if (A.cols != B.rows) {
        matrix_error();
        return;
    }

    struct Matrix mult = matrix_create(A.rows, B.cols);
    if (mult.data == NULL) return MATRIX_NULL;

    for (size_t row = 0; row < A.rows; row++) {
        for (size_t col = 0; col < B.cols; col++) {
            for (size_t idx = 0; idx < A.cols; idx++) {
                mult.data[row * mult.cols + col] += A.data[row * A.cols + idx] * B.data[col + idx * B.cols];
            }
        }
    }
    return mult;
}


void matrix_trans(struct Matrix A, struct Matrix T)
{
    for (size_t row = 0; row < A.rows; row++) {
        for (size_t col = 0; col < A.cols; col++) {
            T.data[col * A.rows + row] = A.data[row * A.cols + col];
        }
    }
}


void matrix_delete(struct Matrix* A)
{
    A->rows = 0;
    A->cols = 0;
    free(A->data);
    A->data = NULL;
}


MatrixItem matrix_determinant(const struct Matrix A) //детерминант
{
    MatrixItem det;

    if (A.cols == 1 && A.rows == 1) 
    {
        det = A.data[0];
        return det;
    }

    if (A.cols == 2 && A.rows == 2) {
        det = A.data[0] * A.data[3] - A.data[1] * A.data[2];
        return det;
    }

    if (A.cols == 3 && A.rows == 3) {
        det =
            A.data[0] * A.data[4] * A.data[8] + A.data[1] * A.data[5] * A.data[6] + A.data[2] * A.data[7] * A.data[3]
            - A.data[2] * A.data[4] * A.data[6] - A.data[0] * A.data[5] * A.data[7]- A.data[1] * A.data[8] * A.data[3];
        return det;
    }

    return NAN;
}


void determinant_print(struct Matrix A, const char* text)
{
    printf("%s\n", text);
    printf("%f\n", matrix_determinant(A));
}


int matrix_add(struct Matrix A, struct Matrix B)  //A += B
{
    if (A.cols != B.cols || A.rows != B.rows) return 1;

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        A.data[idx] += B.data[idx];
    return 0;
}


void matrix_mult_k(struct Matrix A, const MatrixItem k) // A *= k
{
    for (size_t idx = 0; idx < A.cols * A.rows; ++idx) {
        A.data[idx] *= k;
    }
    return;
}


void matrix_div_k(struct Matrix A, const MatrixItem k)  // A /= k
{
    for (size_t idx = 0; idx < A.cols * A.rows; ++idx) {
        A.data[idx] /= k;
    }
    return;
}


struct Matrix matrix_exponent(struct Matrix A)  // Exp = e^A
{
    if (A.cols != A.rows) return MATRIX_NULL;
    if (A.cols == 0) return MATRIX_NULL;

    struct Matrix exp = matrix_create(A.rows, A.cols);
    if (exp.data == NULL) return MATRIX_NULL;
    matrix_set_one(exp);

    struct Matrix term_prev = matrix_create(A.rows, A.cols);
    if (term_prev.data == 0) {
        matrix_delete(&exp);
        return MATRIX_NULL;
    };
    matrix_set_one(term_prev);

    struct Matrix term_next;

    for (int idx = 1; idx < 100; ++idx) {

        term_next = matrix_mult(term_prev, A);
        if (term_next.data == NULL) {
            matrix_delete(&term_prev);
            matrix_delete(&exp);
            return MATRIX_NULL;
        }
        matrix_div_k(term_next, idx);
        memcpy(term_prev.data, term_next.data, sizeof(MatrixItem) * term_prev.cols * term_prev.rows);
        matrix_delete(&term_next);
        matrix_add(exp, term_prev);

    }
    matrix_delete(&term_prev);
    return exp;
}


void matrix_print(const struct Matrix A, const char* text)
{
    printf("%s\n", text);
    for (size_t col = 0; col < A.cols; ++col) {
        printf("[");
        for (size_t row = 0; row < A.rows; ++row) {
            printf("%4.2f ", A.data[A.cols * row + col]);
        }
        printf("]\n");
    }
    printf("\n");
}
