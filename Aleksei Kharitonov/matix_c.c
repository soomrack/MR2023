#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct Matrix {
    int rows;
    int cols;
    double* data;
};


const struct Matrix NULL_MATRIX = { .rows = 0, .cols = 0, .data = NULL };


struct Matrix matrix_create(const int rows, const int cols)
{
    if (cols == 0 || rows == 0) {
        struct Matrix A = { .cols = cols, .rows = rows, .data = NULL };
        return A;
    };
    if (rows >= SIZE_MAX / sizeof(double) / cols) return NULL_MATRIX;
    struct Matrix A = { .rows = rows, .cols = cols, .data = NULL };
    A.data = malloc(sizeof(double) * A.cols * A.rows);
    if (A.data == NULL)return NULL_MATRIX;
    return A;
}


void matrix_delete(struct Matrix* A) 
{
    A->rows = 0;
    A->cols = 0;
    free(A->data);
    A->data = NULL;
}


void matrix_set_zero(struct Matrix A) 
{
    memset(A.data, 0, sizeof(double) * A.rows * A.cols);
}


void matrix_set_one(struct Matrix A) 
{
    matrix_set_zero(A);
    for (int idx = 0;idx < A.rows * A.cols; idx += A.cols + 1)
        A.data[idx] = 1.;
}


void matrix_print(const struct Matrix A) 
{
    for (int col = 0;col < A.cols;++col) 
    {
        printf("[ ");
        for (int row = 0;row < A.rows;++row)
        {
            printf("%4.2f ", A.data[A.cols * col + row]);
        }
        printf("]\n");
    }
}


// A + B
struct Matrix matrix_add(const struct Matrix A,const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return NULL_MATRIX;
    struct Matrix result = matrix_create(A.cols, A.rows);
    for (int idx = 0; idx < A.cols * A.rows;++idx)
        result.data[idx] = A.data[idx] + B.data[idx];
    return result;
    matrix_delete(&result);
}


// A - B
struct Matrix matrix_minus(struct Matrix A, struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return NULL_MATRIX;
    struct Matrix result = matrix_create(A.cols, A.rows);
    for (int idx = 0; idx < A.cols * A.rows;++idx)
        result.data[idx] = A.data[idx] - B.data[idx];
    return result;
    matrix_delete(&result);
}


// A * B
struct Matrix matrix_mult(struct Matrix A, struct Matrix B)
{
    if (A.cols != B.rows) return NULL_MATRIX;
    struct Matrix result = matrix_create(A.cols, A.rows);
    for (int colB = 0; colB < B.cols; ++colB) 
    {
        for (int rowA = 0; rowA < A.rows; ++rowA) 
        {
            result.data[rowA * result.cols + colB] = 0;
            for (int idx = 0; idx < A.cols; ++idx) 
            {
                result.data[rowA * result.cols + colB] += A.data[rowA * A.cols + idx] * B.data[idx * B.cols + colB];
            }
        }
    };
    return result;
    matrix_delete(&result);
}


//A * number
struct Matrix matrix_mult_on_number(struct Matrix A, int number)
{
    struct Matrix result = matrix_create(A.cols, A.rows);
    for (int idx = 0; idx < A.cols * A.rows;++idx)
        result.data[idx] = A.data[idx] * number;
    return result;
    matrix_delete(&result);
}


// A/number
struct Matrix matrix_div_on_number(struct Matrix A, int number)
{
    struct Matrix result = matrix_create(A.cols, A.rows);
    for (int idx = 0; idx < A.cols * A.rows;++idx)
        result.data[idx] = A.data[idx] / number;
    return result;
    matrix_delete(&result);
}

//A = A^t
struct Matrix matrix_trans(struct Matrix A)
{
    struct Matrix result = matrix_create(A.cols, A.rows);
    int idx = 0;
    for (int col = 0;col < A.cols;++col)
    {
        for (int row = 0;row < A.rows;++row)
        {
            result.data[idx] = A.data[A.cols * row + col];
            idx++;
        }
    }
    return result;
    matrix_delete(&result);
}


//Determinant
float matrix_det(struct Matrix A, int size)
{ 
    if (A.cols != A.rows) return NAN;
    if (size == 1) 
    {
        if (A.rows != 1 || A.cols != 1) return NAN;
        int det = A.data[0];
        return det;
    }
    if (size == 2)
    {
        if (A.rows != 2 || A.cols != 2) return NAN;
        int det = A.data[0] * A.data[3] - A.data[1] * A.data[2];
        return det;
    }
    if (size == 3) 
    {
        if (A.rows != 3 || A.cols != 3) return NAN;
        int tr_1 = A.data[0] * A.data[4] * A.data[8];
        int tr_2 = A.data[1] * A.data[5] * A.data[6];
        int tr_3 = A.data[2] * A.data[3] * A.data[7];
        int tr_4 = A.data[0] * A.data[5] * A.data[7];
        int tr_5 = A.data[1] * A.data[3] * A.data[8];
        int tr_6 = A.data[2] * A.data[4] * A.data[6];
        int det = tr_1 + tr_2 + tr_3 - tr_4 - tr_5 - tr_6;
        return det;
    }
}

// exponent
struct Matrix matrix_exp(struct Matrix A, int N)
{
    struct Matrix exp = matrix_create(A.cols, A.rows);
    struct Matrix temp = matrix_create(A.cols, A.rows);
    struct Matrix stepen = matrix_create(A.cols, A.rows);
    struct Matrix eCopy = matrix_create(A.cols, A.rows);

    matrix_set_one(exp);
    matrix_set_one(stepen);

    for (int i = 1; i <= N; ++i)
    {
        temp = matrix_mult(stepen, stepen);
        matrix_delete(&stepen);

        stepen = matrix_div_on_number(temp, (float) i);
        matrix_delete(&temp);

        eCopy = matrix_add(exp, stepen);
        matrix_delete(&exp);
        exp = eCopy;
    }
    return exp;
}

void matrix_fill(struct Matrix A, const double values[]) 
{
    for (int idx = 0;idx < A.cols * A.rows;++idx)
        A.data[idx] = values[idx];
}


int main() 
{
    struct Matrix A = matrix_create(3, 3);
    struct Matrix B = matrix_create(3, 3);

    struct Matrix result_add = matrix_create(A.cols, A.rows);
    struct Matrix result_minus = matrix_create(A.cols, A.rows);
    struct Matrix result_mult = matrix_create(A.cols, A.rows);
    struct Matrix result_trans = matrix_create(A.cols, A.rows);
    struct Matrix result_exp = matrix_create(A.cols, A.rows);
    struct Matrix result_mult_on_number = matrix_create(A.cols, A.rows);
    struct Matrix result_div_on_number = matrix_create(A.cols, A.rows);
    
   matrix_fill(A, (double[])
    {
        11., 2., 3.,
        4., 5., 6.,
        7., 8., 9.,
    });

     matrix_fill(B, (double[])
    {
        1., 2., 1.,
        2., 1., 1.,
        1., 1., 1.,
    });

    printf("Matrix Add:\n");
    matrix_add(A, B);
    result_add = matrix_add(A, B);
    matrix_print(result_add);
    printf("\n");


    printf("Matrix Minus:\n");
    matrix_minus(A, B);
    result_minus = matrix_minus(A, B);
    matrix_print(result_minus);
    printf("\n");


    printf("Matrix Multiply:\n");
    matrix_mult(A, B);
    result_mult = matrix_mult(A, B);
    matrix_print(result_mult);
    printf("\n");


    printf("Matrix Multiply on number:\n");
    matrix_mult_on_number(A,2);
    result_mult_on_number = matrix_mult_on_number(A, 2);
    matrix_print(result_mult_on_number);
    printf("\n");


    printf("Matrix Div on number:\n");
    matrix_div_on_number(A, 2);
    result_div_on_number = matrix_div_on_number(A, 2);
    matrix_print(result_div_on_number);
    printf("\n");


    printf("Matrix Transpose:\n");
    matrix_trans(A, B);
    result_trans = matrix_trans(A, B);
    matrix_print(result_trans);
    printf("\n");


    printf("Matrix Determinant:");
    printf("%4.2f\n", matrix_det(A, A.rows));
    printf("\n");


    printf("Matrix Exponent:\n");
    matrix_exp(A,15);
    result_exp = matrix_exp(A,15);
    matrix_print(result_exp);
    printf("\n");
    

    matrix_delete(&A);
    matrix_delete(&B);
    matrix_delete(&result_add);
    matrix_delete(&result_minus);
    matrix_delete(&result_trans);
    matrix_delete(&result_mult);
    matrix_delete(&result_mult_on_number);
    matrix_delete(&result_div_on_number);
    matrix_delete(&result_exp);
    return 0;
}
