#ifndef __MATRIX__
#define __MATRIX__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "dp_matrix_lib.h"


typedef double MatrixItem;


struct Matrix {
    size_t cols;
    size_t rows;
    MatrixItem *data;
};


const struct Matrix MATRIX_NULL = {.cols = 0, .rows = 0, .data = NULL};


struct Matrix matrix_allocate(const size_t cols, const size_t rows)
{
    if (cols == 0 || rows == 0) {
        struct Matrix A = {.cols = cols, .rows = rows, .data = NULL};
        return A;
    };

    if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols) 
        return MATRIX_NULL;
    
    struct Matrix A = {.cols = cols, .rows = rows, .data = NULL};
    A.data = (MatrixItem*)malloc(A.cols * A.rows * sizeof(MatrixItem));
    if (A.data == NULL) {
        return MATRIX_NULL;
    }
    return A;
}


void matrix_free(struct Matrix *matrix)
{
    if (matrix->data == NULL)
        return;
    
    free(matrix->data);
    *matrix = MATRIX_NULL;
    return;
}


void print_matrix(const struct Matrix A)
{
    printf("_____________________________________________ \n");
    for (size_t idx = 1; idx <= A.cols * A.rows; ++idx) {
        printf("%4.2f \t", A.data[idx-1]);
        if (idx % A.cols == 0 && idx >= A.cols)
            printf("\n");
    };
    printf("\n");
    return;
}


// B <- A
void matrix_copy(const struct Matrix B, const struct Matrix A)
{
    if (A.data == NULL) {
        matrix_free(B);
        B = MATRIX_NULL;
        return;
    };
    
    if (!(A.cols == B.cols && A.rows == B.rows)) {
        matrix_free(B);
        B = MATRIX_NULL;
        return;
    };
    
    memcpy(B.data, A.data, A.cols * A.rows * sizeof(MatrixItem));
}


// coeff * A
void matrix_mult_by_coeff(struct Matrix A, const double coefficient)
{
    if (A.data == NULL)
        return;

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        A.data[idx] = A.data[idx] * coefficient;
    
    return;
}


void matrix_zero(struct Matrix A)
{
    memset(A.data, 0, A.cols * A.rows * sizeof(MatrixItem));
    return;
}


// C = A + B
struct Matrix matrix_sum(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows)
        return MATRIX_NULL;

    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL)
        return C;

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        C.data[idx] = A.data[idx] + B.data[idx];

    return C;
}


// A += B
void matrix_add(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows)
        return;

    if (A.data == NULL || B.data == NULL)
        return;

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        A.data[idx] = A.data[idx] + B.data[idx];

    return;
}


// C = A - B
struct Matrix matrix_substr(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows)
        return MATRIX_NULL;

    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL)
        return C;

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        C.data[idx] = A.data[idx] - B.data[idx];

    return C;
}


// C = A * B
struct Matrix matrix_mult(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.rows)
        return MATRIX_NULL;
    
    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL)
        return C;
    
    matrix_zero(C);

    for (size_t rowA = 0; rowA < A.rows; ++rowA)
        for (size_t colB = 0; colB < B.cols; ++colB)
            for (size_t colA = 0; colA < A.cols; ++colA)
                C.data[C.cols * rowA + colB] += A.data[colA + rowA * A.cols] * B.data[B.cols * colA + colB];
    
    return C;
}


// A *= B
void matrix_add_mult(const struct Matrix A, const struct Matrix B)
{
    struct Matrix C;
    C = matrix_mult(A, B);

    if (C.data == NULL)
        return;
    
    matrix_free(&A);
    A = matrix_allocate(C.cols, C.rows);
    A.data = C.data;

    return;
}


struct Matrix matrix_transp(const struct Matrix A)
{
    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL)
        return C;

    for (size_t row = 0; row < A.rows; ++row)
        for (size_t col = 0; col < A.cols; ++col)
            C.data[row * A.cols + col] = A.data[row + col * A.cols];
    
    return C;
}


// C = e ^ (A)
struct Matrix matrix_exponent(const struct Matrix A, const unsigned int degree) //accuracy - десятичная дробь
{ 
    if (A.cols != A.rows)
        return MATRIX_NULL;

    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL)
        return C;
    matrix_zero(C);

    struct Matrix B = matrix_allocate(A.cols, A.rows);
    matrix_copy(B, A);

    for (int trm = 2; trm <= degree; ++trm) {
       matrix_add_mult(B, A);
       matrix_mult_by_coeff(B, 1.0 / trm);
       matrix_add(C, B);
    };

    matrix_add(C, A);

    for (size_t diag = 0; diag < C.rows; ++diag)
        C.data[diag * C.cols + diag] += 1.0;
    
    matrix_free(&B);

    return C;
}


// возвращается 0, если в матрице есть нулевые строки/столбцы
int matrix_det_if_zero(const struct Matrix A)
{
    size_t count;

    for (size_t row = 0; row < A.rows; ++row) { // суммы по строкам
        count = 0;
        for (size_t col = 0; col < A.cols; ++col) {
            count += 1;
            if (A.data[row * A.cols + col] != 0.0)
                break;
        };
        
        if (count == A.cols)
            return 0;
    };
    
    for (size_t col = 0; col < A.cols; ++col) { // суммы по строкам
        count = 0;
        for (size_t row = 0; row < A.rows; ++row) {
            count += 1;
            if (A.data[row * A.cols + col] != 0.0)
                break;
        };
        
        if (count == A.rows)
            return 0;
    };
    
    return 1;
}


// меняет строки местами, если первый символ в диагонали == 0
void matrix_det_prep(const struct Matrix A, size_t diag, double *coeff)
{
    size_t buff_one = diag; // запоминается номер строки

    if (A.data[diag * A.cols + diag] != 0.0) 
        return;
    else {
        for (size_t row = diag; row < A.rows; ++row) {
            buff_one += 1;
            if (A.data[row * A.cols] != 0.0)
                break;
        };

        double buff_two = 0.0; // запоминается значение в ячейке
        
        for (size_t col = diag; col < A.cols; ++col) {
            buff_two = A.data[diag * A.cols + col];
            A.data[diag * A.cols + col] = A.data[buff_one * A.cols + col];
            A.data[buff_one * A.cols + col] = buff_two;
        };

        *coeff *= -1.0;
    };

    return;
}


/* формируется диагональный определитель, вычисляется произведение чисел главной диагонали, 
    умножается на коэффициент преобразования */
double matrix_det(const struct Matrix A)
{
    if (A.cols != A.rows)
        return NAN;
    
    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL)
        return NAN;
    matrix_copy(C, A);

    if (A.cols == 1) {
        matrix_free(&C);
        return A.data[0];
    }; 

    if (matrix_det_if_zero(C) == 0) {
        matrix_free(&C);
        return 0.0;
    };
    
    double coeff = 1.0;
    double diagonal = 1.0;
    double buff_one, buff_two;

    for (size_t diag = 0; diag < A.rows - 1; ++diag) {
        matrix_det_prep(C, diag, &coeff);
        coeff *= C.data[diag * A.cols + diag];
        buff_one = C.data[diag * A.cols + diag];

        for (size_t col = diag; col < A.cols; ++col)
            C.data[diag * A.cols + col] /= buff_one;

        for (size_t row = diag + 1; row < A.rows; ++row) {
            buff_two = C.data[row * A.cols + diag];
            for (size_t col = diag; col < A.cols; ++col) {
                C.data[row * A.cols + col] = C.data[row * A.cols + col] - C.data[diag * A.cols + col] * buff_two;
            };  
        };
    };

    for (size_t diag = 0; diag < A.rows; ++diag)
        diagonal *= C.data[diag * A.cols + diag];
    
    matrix_free(&C);

    double result = coeff * diagonal;
    
    return result;
}

#endif
