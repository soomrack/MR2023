#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


typedef double MatrixData;

struct Matrix{
    unsigned int cols;
    unsigned int rows;
    MatrixData *data;
};

const struct Matrix Matrix_NULL = {.cols = 0, .rows = 0, .data = NULL}; 


struct Matrix matrix_allocation(const unsigned int cols, const unsigned int rows)
{
    if (cols == 0 && rows == 0)
    return Matrix_NULL;

    if (cols == 0 || rows == 0){
    struct Matrix A = {.cols = cols, .rows = rows, .data = NULL};
    return A;
    }

    struct Matrix A = {.cols = cols, .rows = rows, .data = NULL};
    A.data = malloc(A.cols * A.rows * sizeof(MatrixData));
    return A;
}

struct Matrix matrix_fill(const unsigned int cols, unsigned int rows, const MatrixData *data)
{
    struct Matrix A = matrix_allocation(cols, rows);
    
    memcpy(A.data, data, rows * cols * sizeof(MatrixData));
}

void matrix_print(const struct Matrix A)
{
    for (unsigned int row = 0; row < A.rows; ++row){
        printf("[");
        for (unsigned int col = 0; col < A.cols; ++col){
            printf("%f", A.data[A.cols * row + col]);
        }
        printf("]");
    }
}


void matrix_free(struct Matrix *A)
{
    free(A->data);
    *A = Matrix_NULL;
}


int main()
{
    struct Matrix A;

    A = matrix_fill(2, 2, (double[]){1., 2., 3., 4.});

    matrix_print(A);

    matrix_free(&A);

    return 0;
}