#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
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
    if (cols == 0 || rows == 0) {
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
    for (size_t row = 0; row < A.rows; row++) {
        for (size_t col = 0; col < A.cols; col++) {
            A.data[col * A.rows + row] = values[row * A.cols + col];
        }
    }
}


// A = B + C
void matrix_sum(const struct Matrix A, const struct Matrix B, const struct Matrix C)
{
    if (B.cols != C.cols || B.rows != C.rows) {
        matrix_error();
        return;
    }
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
    for (size_t idx = 0; idx < B.cols * B.rows; ++idx) {
        A.data[idx] = B.data[idx] - C.data[idx];
    }
}


// A = B * C
void matrix_mult(const struct Matrix A, const struct Matrix B, const struct Matrix C)
{
    if (B.cols != C.rows || B.rows != C.cols)
    {
        matrix_error();
    }
    MatrixItem data_old;
    for (size_t row = 0; row < B.rows; row++) {
        for (size_t col = 0; col < B.cols; col++) {
            data_old = 0;
            for (size_t idx = 0; idx < C.rows; idx++) {
                data_old +=  B.data[idx * B.rows + col] * C.data[row * C.cols + idx];
            }
            A.data[row * B.cols + col] = data_old;
        }
    }
}


//T = A ^ T
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


struct Matrix Minor(const struct Matrix A, const size_t row, const size_t col)
{
    struct Matrix Minor = matrix_create(A.rows - 1, A.cols - 1);
    size_t idx = 0;
    for (size_t rowA = 0; rowA < A.rows; ++rowA) {
        if (rowA == row) continue;
        for (size_t colA = 0; colA < A.cols; ++colA) {
            if (colA == col) continue;
            Minor.data[idx] = A.data[rowA * A.cols + colA];
            ++idx;
        }
    }
    return Minor;
}


double matrix_determinant(const struct Matrix A) {
    if (A.rows != A.cols) {
        matrix_error();
        return NAN;
    }
    double det = 0;
    int k = 1;
    if (A.rows == 0) return 0;
    if (A.rows == 1) return A.data[0];
    if (A.rows == 2) return (A.data[0] * A.data[3] - A.data[2] * A.data[1]);
    for (unsigned int idx = 0; idx < A.rows; idx++) {
        struct Matrix temp = Minor(A, 0, idx);
        det += k * A.data[idx] * matrix_determinant(temp);
        k = -k;
        matrix_delete(&temp);
    }
    return det;
}


void determinant_print(struct Matrix A, const char* text)
{
    printf("%s\n", text);
    printf("%f\n", matrix_determinant(A));
}


struct Matrix matrix_div(struct Matrix A, unsigned int n) {
    struct Matrix Div = matrix_create(A.cols, A.cols);
    for (size_t rowA = 0; rowA < A.rows; ++rowA) {
        for (size_t colA = 0; colA < A.cols; ++colA) {
            Div.data[rowA * A.rows + colA] = Div.data[rowA * A.rows + colA] / n;
        }
    }
    return Div;
    matrix_delete(&Div);
}


struct Matrix matrix_exponent(struct Matrix A, unsigned int n)
{
    struct Matrix Exp_mult = matrix_create(A.cols, A.cols);
    struct Matrix Exp_old = matrix_create(A.cols, A.cols);
    matrix_set_one(Exp_old);
    struct Matrix Exp_div = matrix_create(A.cols, A.cols);
    matrix_set_one(Exp_div);
    struct Matrix Exp_cpy = matrix_create(A.cols, A.cols);
    struct Matrix Exp = matrix_create(A.cols, A.cols);
    if (n > 0) {
        for (unsigned int i = 1; i < n; ++i) {
            matrix_mult(Exp_mult, A, Exp_div);
            memcpy(Exp_cpy.data, Exp_mult.data, A.rows * A.cols * sizeof(MatrixItem));
            Exp_div = matrix_div(Exp_cpy, i);
            matrix_sum(Exp, Exp_div, Exp_old);
            memcpy(Exp_old.data, Exp.data, A.rows * A.cols * sizeof(MatrixItem));
        }
        return Exp;
    }
    else {
        return Exp_old;
    }
    matrix_delete(&Exp_mult);
    matrix_delete(&Exp_old);
    matrix_delete(&Exp_div);
    matrix_delete(&Exp_cpy);
    matrix_delete(&Exp);
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


int main()
{
    MatrixItem values_A[] =
    { 1., 8., 3.,
      4., 5., 6.,
      7., 8., 9.
    };

    MatrixItem values_B[] =
    { 1., 1., 1.,
      5., 2., 2.,
      3., 3., 3.
    };

    struct Matrix A = matrix_create(3, 3);
    matrix_set_one(A);

    struct Matrix AA = matrix_create(3, 3);
    matrix_set_one(AA);

    struct Matrix B = matrix_create(3, 3);
    matrix_set_one(B);

    struct Matrix E = matrix_create(3, 3);
    matrix_set_one(E);

    struct Matrix C = matrix_create(3, 3);
    struct Matrix D = matrix_create(3, 3);
    struct Matrix P = matrix_create(3, 3);
    struct Matrix T = matrix_create(3, 3);

    matrix_fill(A, values_A);
    matrix_fill(AA, values_A);
    matrix_fill(B, values_B);
    matrix_sum(C, A, B);

    matrix_substraction(D, A, B);

    matrix_mult(P, A, B);

    matrix_trans(A, T);

    matrix_determinant(A);

    struct Matrix Exp = matrix_exponent(A, 0);

    matrix_print(A, "Matrix A");
    matrix_print(B, "Matrix B");
    matrix_print(C, "C = A + B");
    matrix_print(D, "D = A - B");
    matrix_print(P, "P = A * B");
    matrix_print(T, "T = A^T");
    matrix_print(E, "Matrix E");
    determinant_print(A, "detA = ");
    matrix_print(Exp, "Matrix Exp^A=");

    matrix_delete(&A);
    matrix_delete(&B);
    matrix_delete(&C);
    matrix_delete(&D);
    matrix_delete(&P);
    matrix_delete(&T);
    matrix_delete(&E);

    return 0;
}