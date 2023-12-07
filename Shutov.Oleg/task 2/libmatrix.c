#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

typedef double MatrixItem;

struct Matrix {
    size_t rows;
    size_t cols;
    MatrixItem* data;
};

const struct Matrix MATRIX_NULL = { .rows = 0, .cols = 0, .data = NULL };


// Function returns MATRIX_NULL if fail
struct Matrix matrix_allocate(const size_t rows, const size_t cols)
{
    if (cols == 0 || rows == 0) {
        struct Matrix A = { .rows = rows, .cols = cols, .data = NULL};
        return A;
    }
    if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols) return MATRIX_NULL;  // rows * cols < MAX_SIZE / sizeof(double)
    
    struct Matrix A = { .rows = rows, .cols = cols, .data = NULL};
    A.data = (MatrixItem*)malloc(A.rows * A.cols * sizeof(MatrixItem));
    if (A.data == NULL) return MATRIX_NULL;
    return A;
}


void matrix_fill(struct Matrix A, const double* values)
{
    memcpy(A.data, values, sizeof(MatrixItem) * A.rows * A.cols);
    return;
}


void matrix_delete(struct Matrix* A)
{
    A->rows = 0;
    A->cols = 0;
    if (A->data != NULL) free(A->data); 
    A->data = NULL ;
}


void matrix_set_zero(struct Matrix A)
{
    if (A.data == NULL) return;
    memset(A.data, 0, sizeof(MatrixItem) * A.cols * A.rows);
}


void matrix_set_one(struct Matrix A)
{
    matrix_set_zero(A);
    for (size_t idx = 0; idx < A.rows * A.cols; idx += A.cols + 1)
        A.data[idx] = 1.;
}


// B += A
// Function returns 0 if success
int matrix_add(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return 1;

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx) {
        A.data[idx] += B.data[idx];
    }
    return 0;
}


// C = A + B
struct Matrix matrix_sum(struct Matrix A, struct Matrix B) 
{
    if (A.cols != B.cols || A.rows != B.rows) return MATRIX_NULL;

    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL) return MATRIX_NULL;

    memcpy(C.data, A.data, C.cols * C.rows * sizeof(MatrixItem));
    matrix_add(C, B);
    return C;
}

    
// B -= A
// Function returns 0 if success
int matrix_sub(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return 1;

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx) {
        A.data[idx] -= B.data[idx];
    }
    return 0;
}


// C = A - B
struct Matrix matrix_subtract(struct Matrix A, struct Matrix B) 
{
    if (A.cols != B.cols || A.rows != B.rows) return MATRIX_NULL;

    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL) return MATRIX_NULL;

    memcpy(C.data, A.data, C.cols * C.rows * sizeof(MatrixItem));
    matrix_sub(C, B);
    return C;
}


// C = A * B
struct Matrix matrix_multiplication(struct Matrix A, struct Matrix B) 
{
    if (A.rows != B.cols) return MATRIX_NULL;

    struct Matrix C = matrix_allocate(A.rows, B.cols);
    if (C.data == NULL) return MATRIX_NULL;

    for (size_t colC = 0; colC < A.rows; ++colC) {
        for (size_t rowC = 0; rowC < B.cols; ++rowC) {
            C.data[rowC + colC * B.cols] = 0;
            for (size_t idx = 0; idx < B.cols; ++idx) {
                C.data[rowC + colC * A.rows] += A.data[idx + colC * A.rows]
                    * B.data[idx * B.cols + rowC];
            };
        };
    };
    return C;
}


// A /= k
void matrix_divk(struct Matrix A, MatrixItem k)
{
    for (size_t idx = 0; idx < A.cols * A.rows; ++idx) {
        A.data[idx] /= k;
    }
    return;
}


// A *= k
void matrix_multk(struct Matrix A, const MatrixItem k)
{
    for (size_t idx = 0; idx < A.cols * A.rows; ++idx) {
        A.data[idx] *= k;
    }
    return;
}


// EXP = e^A
struct Matrix matrix_exp(const struct Matrix A)
{
    if (A.cols != A.rows) return MATRIX_NULL;
    if (A.cols == 0) return MATRIX_NULL;

    struct Matrix exp = matrix_allocate(A.rows, A.cols);
    if (exp.data == NULL) return exp;
    matrix_set_one(exp);

    struct Matrix step_one = matrix_allocate(A.rows, A.cols);
    if (step_one.data == 0) {
        matrix_delete(&exp);
        return step_one;
    };
    matrix_set_one(step_one);

    struct Matrix step_two;

    for (int idx = 1; idx < 100; ++idx) {

        step_two = matrix_multiplication(step_one, A);
        if (step_two.data == NULL) {
            matrix_delete(&step_one);
            matrix_delete(&exp);
            return step_two;
        }
        matrix_divk(step_two, idx);
        memcpy(step_one.data, step_two.data, sizeof(MatrixItem) * step_one.cols * step_one.rows);
        matrix_add(exp, step_one);

    }
    matrix_delete(&step_one);
    matrix_delete(&step_two);
    return exp;
}


// C = A^T 
struct Matrix matrix_transposition(struct Matrix A)
{
    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL) return C;

    for (size_t rowC = 0; rowC < A.cols; ++rowC) {
        for (size_t colC = 0; colC < A.rows; ++colC) {
            C.data[colC * A.cols + rowC] = A.data[rowC * A.cols + colC];
        };
    };
    return C;
}


// det (A)
MatrixItem matrix_determinant(struct Matrix A)
{
    MatrixItem det;

    if (A.cols == 1 && A.rows == 1) {
        det = A.data[0];
        return det;
    }

    if (A.cols == 2 && A.rows == 2) {
        det = A.data[0] * A.data[3] - A.data[1] * A.data[2];
        return det;
    }

    if (A.cols == 3 && A.rows == 3) {
        det =
            A.data[0] * A.data[4] * A.data[8]
            + A.data[1] * A.data[5] * A.data[6]
            + A.data[2] * A.data[7] * A.data[3]
            - A.data[2] * A.data[4] * A.data[6]
            - A.data[0] * A.data[5] * A.data[7]
            - A.data[1] * A.data[8] * A.data[3];
        return det;
    }

    return NAN;
}


void matrix_print(const struct Matrix A, const char *text)
{
    printf("%s\n", text);
    for (size_t col = 0; col < A.cols; ++col) {
        printf("[ ");
        for (size_t row = 0; row < A.rows; ++row) {
            printf("%4.2f ", A.data[A.cols * row + col]);
        }
        printf(" ]\n");
    }
    printf("\n");
}
