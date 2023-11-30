#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "mat_lib.h"

const struct Matrix NULL_MATRIX = { .rows = 0, .cols = 0, .data = NULL };

struct Matrix matrix_create(const size_t rows, const size_t cols)
{
    if (cols == 0 || rows == 0) {
        struct Matrix A = { .cols = cols, .rows = rows, .data = NULL };
        return A;
    };
    if (rows >= SIZE_MAX / sizeof(double) / cols) return NULL_MATRIX;
    struct Matrix A = { .rows = rows, .cols = cols, .data = NULL };
    A.data = malloc(sizeof(double) * A.cols * A.rows);
    if (A.data == NULL) return NULL_MATRIX;
    return A;
}


void matrix_delete(struct Matrix* A)
{
    A->rows = 0;
    A->cols = 0;
    if (A->data != NULL) free(A->data);
    A->data = NULL;
}


struct Matrix matrix_set_zero(struct Matrix A)
{
    if (A.data == NULL) return NULL_MATRIX;
    memset(A.data, 0, sizeof(double) * A.rows * A.cols);
}


void matrix_set_one(struct Matrix A)
{
    matrix_set_zero(A);
    for (size_t idx = 0;idx < A.rows * A.cols; idx += A.cols + 1)
        A.data[idx] = 1.;
}


void matrix_print(const struct Matrix A)
{
    for (size_t col = 0;col < A.cols;++col)
    {
        printf("[ ");
        for (size_t row = 0;row < A.rows;++row)
        {
            printf("%4.2f ", A.data[A.cols * col + row]);
        }
        printf("]\n");
    }
}


// A + B
struct Matrix matrix_add(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return NULL_MATRIX;
    struct Matrix result = matrix_create(A.cols, A.rows);
    if (result.data == NULL) return NULL_MATRIX;
    for (size_t idx = 0; idx < A.cols * A.rows;++idx)
        result.data[idx] = A.data[idx] + B.data[idx];
    return result;
}


// A - B
struct Matrix matrix_minus(struct Matrix A, struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return NULL_MATRIX;
    struct Matrix result = matrix_create(A.cols, A.rows);
    if (result.data == NULL) return NULL_MATRIX;
    for (size_t idx = 0; idx < A.cols * A.rows;++idx)
        result.data[idx] = A.data[idx] - B.data[idx];
    return result;
}


// A * B
struct Matrix matrix_mult(struct Matrix A, struct Matrix B)
{
    if (A.cols != B.rows) return NULL_MATRIX;
    struct Matrix result = matrix_create(A.cols, A.rows);
    if (result.data == NULL) return NULL_MATRIX;
    for (size_t colB = 0; colB < B.cols; ++colB)
    {
        for (size_t rowA = 0; rowA < A.rows; ++rowA)
        {
            result.data[rowA * result.cols + colB] = 0;
            for (size_t idx = 0; idx < A.cols; ++idx)
            {
                result.data[rowA * result.cols + colB] += A.data[rowA * A.cols + idx] * B.data[idx * B.cols + colB];
            }
        }
    };
    return result;
}


//A * number
struct Matrix matrix_mult_on_number(struct Matrix A, size_t number)
{
    struct Matrix result = matrix_create(A.cols, A.rows);
    if (result.data == NULL) return NULL_MATRIX;
    for (size_t idx = 0; idx < A.cols * A.rows;++idx)
        result.data[idx] = A.data[idx] * number;
    return result;
}


// A/number
struct Matrix matrix_div_on_number(struct Matrix A, size_t number)
{
    struct Matrix result = matrix_create(A.cols, A.rows);
    if (result.data == NULL) return NULL_MATRIX;
    for (size_t idx = 0; idx < A.cols * A.rows;++idx)
        result.data[idx] = A.data[idx] / number;
    return result;
}

//A = A^t
struct Matrix matrix_trans(struct Matrix A)
{
    struct Matrix result = matrix_create(A.cols, A.rows);
    if (result.data == NULL) return NULL_MATRIX;
    size_t idx = 0;
    for (size_t col = 0;col < A.cols;++col)
    {
        for (size_t row = 0;row < A.rows;++row)
        {
            result.data[idx] = A.data[A.cols * row + col];
            idx++;
        }
    }
    return result;
}


//Determinant
double matrix_det(struct Matrix A)
{
    if (A.cols != A.rows) return NAN;
    if (A.cols == 1 && A.rows == 1)
        return A.data[0];
    if (A.cols == 2 && A.rows == 2)
        return A.data[0] * A.data[3] - A.data[1] * A.data[2];
    if (A.cols == 3 && A.rows == 3)
    {
        double tr_1 = A.data[0] * A.data[4] * A.data[8];
        double tr_2 = A.data[1] * A.data[5] * A.data[6];
        double tr_3 = A.data[2] * A.data[3] * A.data[7];
        double tr_4 = A.data[0] * A.data[5] * A.data[7];
        double tr_5 = A.data[1] * A.data[3] * A.data[8];
        double tr_6 = A.data[2] * A.data[4] * A.data[6];
        double det = tr_1 + tr_2 + tr_3 - tr_4 - tr_5 - tr_6;
        return det;
    }
    return NAN;
}

// exponent
struct Matrix matrix_exp(struct Matrix A, size_t N)
{
    struct Matrix exp = matrix_create(A.cols, A.rows);
    if (exp.data == NULL) {
        return NULL_MATRIX;
        matrix_delete(&exp);
    }
    struct Matrix temp = matrix_create(A.cols, A.rows);
    if (temp.data == NULL) {
        return NULL_MATRIX;
        matrix_delete(&exp);
        matrix_delete(&temp);
    }

    struct Matrix stepen = matrix_create(A.cols, A.rows);
    if (stepen.data == NULL) {
        return NULL_MATRIX;
        matrix_delete(&exp);
        matrix_delete(&temp);
        matrix_delete(&stepen);
    }

    struct Matrix eCopy = matrix_create(A.cols, A.rows);
    if (eCopy.data == NULL) {
        return NULL_MATRIX;
        matrix_delete(&exp);
        matrix_delete(&temp);
        matrix_delete(&stepen);
        matrix_delete(&eCopy);
    } 

    matrix_set_one(exp);
    matrix_set_one(stepen);
    
    for (size_t i = 1; i <= N; ++i)
    {

        matrix_delete(&temp);
        temp = matrix_mult(stepen, A);

        matrix_delete(&stepen);
        stepen = matrix_div_on_number(temp, (double)i);
        matrix_delete(&temp);

        matrix_add(exp, stepen);
     if (stepen.data == NULL) {
        return NULL_MATRIX;
        matrix_delete(&exp);
        matrix_delete(&temp);
        matrix_delete(&stepen);
        }
    }
    return exp;
}

void matrix_fill(struct Matrix A, const double values[])
{
    for (size_t idx = 0;idx < A.cols * A.rows;++idx)
        A.data[idx] = values[idx];
}
