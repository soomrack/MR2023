#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>

typedef double MatrixItem;

struct Matrix {
    size_t rows;
    size_t cols;
    MatrixItem *data;
};

const struct Matrix MATRIX_NULL = {.rows = 0, .cols = 0, .data = NULL};


struct Matrix matrix_allocate(const size_t rows, const size_t cols)
{
    if(rows == 0 || cols == 0){
        struct Matrix A = {.rows = rows, .cols = cols, .data = NULL};
        return A;
    }

    if(rows >= SIZE_MAX / sizeof(MatrixItem) / cols)
        return MATRIX_NULL;
    
    struct Matrix A = {.rows = rows, .cols = cols, .data = NULL};
    A.data = (MatrixItem*)malloc(A.cols * A.rows * sizeof(MatrixItem));
    
    if (A.data == NULL)
        return MATRIX_NULL;
    
    return A;
}


struct Matrix matrix_create(const size_t rows, const size_t cols, const MatrixItem *values)
{
    struct Matrix A = matrix_allocate(rows, cols);
    if (A.data ==NULL) return A;

    memcpy(A.data, values, rows * cols * sizeof(MatrixItem));
    return A;
}


void matrix_free(struct Matrix *A)
{
    free(A->data);
    *A = MATRIX_NULL;
}


void matrix_print(const struct Matrix A)
{
    for(size_t row = 0; row < A.rows; ++row){
        printf("[");
        for(size_t col = 0; col < A.cols; ++col){
            printf("%.2f ", A.data[A.cols * row + col]);
        }
        printf("]\n");
    }
    printf("\n");
}


// A += B
int matrix_add(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return 1;

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx) {
        A.data[idx] += B.data[idx];
    }
    return 0;
}


// A -= B
int matrix_subtraction(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return 1;

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx) {
        A.data[idx] -= B.data[idx];
    }
    return 0;
}


// A + B = C
struct Matrix matrix_sum(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return MATRIX_NULL;

    struct Matrix C = matrix_allocate(A.rows, A.cols);
    if (C.data == NULL) return C;
    
    memcpy(C.data, A.data, C.cols * C.rows * sizeof(MatrixItem));
    matrix_add(C, B);
    return C;
}


// A - B = C
struct Matrix matrix_difference(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return MATRIX_NULL;

    struct Matrix C = matrix_allocate(A.rows, A.cols);
    if (C.data == NULL) return C;
    
    memcpy(C.data, A.data, C.cols * C.rows * sizeof(MatrixItem));
    matrix_subtraction(C, B);
    return C;
}


// A = x * A
int matrix_scalar(const struct Matrix A, const double x)
{
    for(size_t idx = 0; idx < A.rows * A.cols; idx++){
        A.data[idx] = A.data[idx] * x;
    }
    return 0;
}


// C = A * B
struct Matrix matrix_multiply(const struct Matrix A, const struct Matrix B)
{
    if(A.cols != B.rows) return MATRIX_NULL;

    struct Matrix C = matrix_allocate(A.rows, B.cols);
    if (C.data == NULL) return C;

    for(size_t row = 0; row < A.rows; row++){
        for(size_t col = 0; col < B.cols; col++){
            for(size_t idx = 0; idx < A.cols; idx++){
                C.data[row * B.cols + col] += A.data[row * A.cols + idx] * B.data[col + idx * B.cols];
            }
        }
    }
    return C;
}


struct Matrix matrix_transpose(const struct Matrix A)
{
    struct Matrix T = matrix_allocate(A.cols, A.rows);
    if (T.data == NULL) return T;

    for(size_t row = 0; row < A.cols; row++){
        for(size_t col = 0; col < A.rows; col++){
            T.data[col + A.rows * row] = A.data[col * A.cols + row];
        }
    }
    return T;
}


int main()
{
    struct Matrix A, B, C, T;

    A = matrix_create(3, 2, (double[]){1., 1., 7, 1., 2., 1.});
    B = matrix_create(2, 3, (double[]){1., 5., 6., 1., 1., 1.});

    matrix_print(A);

    //matrix_add(B, A);
    matrix_print(B);

    /*C = matrix_sum(A, B);
    matrix_print(C);

    C = matrix_difference(A, B);
    matrix_print(C);

    matrix_scalar(C, 2.0);
    matrix_print(C);*/

    C = matrix_multiply(A, B);
    matrix_print(C);

    T = matrix_transpose(C);
    matrix_print(T);

    matrix_free(&C);
    matrix_free(&A);
    matrix_free(&B);
    matrix_free(&T);
    return 0;
}
