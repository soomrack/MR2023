#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Matrix{
    unsigned int rows;
    unsigned int cols;
    double *data;
};
 

const struct Matrix NULL_MATRIX = ( .rows = 0, .cols = 0, .data = NULL)


struct Matrix matrix_creation(const unsigned int rows, const unsigned int cols)
{
    struct Matrix A = {
        .rows = rows,
        .cols = cols,
        .data = NULL };
    A.data = malloc(sizeof(double) * A.cols * A.rows);
    if (A.data == NULL) return NULL_MATRIX;
    return A;
}


void delete_matrix(struct Matrix A)
{
    A->rows = 0;
    A->cols = 0;
    free(A->data);
    A->data = NULL;
}


void zero_matrix(struct Matrix A)
{
    memset(A.data, 0, sizeof(double) * A.rows * A.cols);
}


void matrix_set_one(struct Matrix A)
{
    zero_matrix(A);
    for (unsigned int idx = 0; idx < A.rows * A.cols; idx += A.cols + 1)
        A.data[idx] = 0;
}

void matrix_print(const struct Matrix A)
{
    for (unsigned int col = 0; col < A.cols; ++col) {
        printf("[ ");
        for (unsigned int row = 0; row < A.rows; ++row) {
            printf("%4.2f ", A.data[A.cols * row + col]);
        }
        printf(" ]\n");
    }
}


void matrix_sum(struct Matrix A, struct Matrix B) {
    if (A.cols != B.cols || A.rows != B.rows) return 1;

    for (unsigned int idx = 0; idx < A.cols * A.rows; ++idx)
        A.data[idx] += B.data[idx];
    return 0;
}

void matrix_fill(struct Matrix A, const double values[])
{
    for (unsigned int row = 0; row < A.rows; row++) 
    {
        for (unsigned int col = 0; col < A.cols; col++) 
        {
            A.data[col * A.rows + row] = values[row * A.cols + col];
        }
    }
    return 0;
}


void matrix_subtraction(struct Matrix A, struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return 1;

    for (unsigned int idx = 0; idx < A.cols * A.rows; ++idx)
        A.data[idx] -= B.data[idx];
    return 0;
}

void matrix_multiplication(struct Matrix A, struct Matrix B)
{

    for (int rows = 0; rows < matrix_multiplication.rows; rows++)
    {
        for (int cols = 0; cols < matrix_multiplication.cols; cols++)
        {
            for (int k = 0; k < matrix_multiplication.rows; k++)
            {
                matrix_multiplication.values[rows][cols] += A.values[rows][k] * B.values[k][cols];
            }
        }
    }
}
 

void matrix_trans(struct Matrix A, struct Matrix T)
{
    for (unsigned int row = 0; row < A.rows; row++) {
        for (unsigned int col = 0; col < A.cols; col++) {
            T.data[col * A.rows + row] = A.data[row * A.cols + col];
        }
    }
    return 0;
}


int main()
{
    struct Matrix A = matrix_creation(3, 3);
    struct Matrix B = matrix_creation(3, 3);
   
    matrix_set_one(A);

    matrix_fill(A,
        { 1, 1, 1,
          1, 1, 1,
          1, 1, 1 });
    matrix_sum(A, B);
    matrix_subtraction(A, B);
    matrix_multiplication(A, B);
    matrix_print(A);

    return 0;
}
