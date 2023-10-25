#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct Matrix {
    size_t cols;
    size_t rows;
    double* data;
};

const struct Matrix MATRIX_NULL = { .cols = 0, .rows = 0, .data = NULL };


struct Matrix matrix_init(const size_t rows, const size_t cols)
{
    /*if ((rows * cols) < (max size_t / sizeof(double))) {
        return MATRIX_NULL;
    }*/

    struct Matrix A = { .cols = cols, .rows = rows, .data = NULL };
    A.data = (double*)malloc(A.cols * A.rows * sizeof(double));
    if (A.data == NULL) {
        return MATRIX_NULL;
    }
    return A;
}


struct Matrix matrix_create(const size_t rows, const size_t cols, const double* values)
{
    struct Matrix A = matrix_init(rows, cols);
    if (A.data == NULL) return A;

    memcpy(A.data, values, rows * cols * sizeof(double));
    return A;
}


void matrix_free(struct Matrix* A)
{
    A->cols = 0;
    A->rows = 0;
    free(A->data);
    A->data = NULL;
}


void matrix_print(const struct Matrix A)
{
    for (size_t row = 0; row < A.rows; ++row) {
        printf("[ ");
        for (size_t col = 0; col < A.cols; ++col) {
            printf("%4.2f ", A.data[A.cols * row + col]);
        }
        printf("]\n");
    }
    printf("\n");
}


/*
// A += B
int matrix_add(struct Matrix* A, struct Matrix* B)
{
    if (A->cols != B->cols || A->rows != B->rows) return 1;

    for (size_t idx = 0; idx < A->cols * A->rows; ++idx) {
        A->data[idx] += B->data[idx];
    }
    return 0;
}*/


struct Matrix matrix_sum(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return MATRIX_NULL;

    struct Matrix C = matrix_init(A.cols, A.rows);
    for (size_t idx = 0; idx < C.cols * C.rows; ++idx) {
        C.data[idx] = A.data[idx] + B.data[idx];
    }
    return C;
}


struct Matrix matrix_scalar_mult(const struct Matrix A)
{
    double scalar = 5.;
    struct Matrix S = matrix_init(A.cols, A.rows);
    for (size_t idx = 0; idx < S.cols * S.rows; ++idx) {
        S.data[idx] = scalar * A.data[idx];
    }
    return S;
}


 struct Matrix matrix_mult(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.rows) {
        return MATRIX_NULL;
    }

    struct Matrix M = matrix_init(A.rows, B.cols);
    if (M.data == NULL)
        

    /*struct Matrix BT = matrix_init(A.rows, B.cols);

    for (size_t row = 0; row < A.rows; ++row)
        for (size_t col = 0; col < A.cols; ++col)
            BT.data[row * A.cols + col] = A.data[row + col * A.cols];*/

        for (size_t rowA = 0; rowA < A.rows; ++rowA)
            for (size_t colB = 0; colB < B.cols; ++colB)
                for (size_t colA = 0; colA < A.cols; ++colA)
                    M.data[B.cols * rowA + colB] +=
                    A.data[colA + rowA * A.cols] * B.data[B.cols * colA + colB];
    
    return M;
}


 struct Matrix matrix_tr(const struct Matrix A, const struct Matrix B)
 {
     struct Matrix T = matrix_init(A.rows, B.cols);

     for (size_t row = 0; row < A.rows; ++row)
         for (size_t col = 0; col < A.cols; ++col)
             T.data[row * A.cols + col] = A.data[row + col * A.cols];

     return T;
 }


 /*struct Matrix matrix_exp(const struct Matrix A, const struct Matrix B)
 {
     struct Matrix E = matrix_init(A.rows, B.cols);

     ...

     return E;
 }*/


int main()
{
    struct Matrix A, B, C, S, M, T; // +E (exp matrix) and +DET (not matrix)

    A = matrix_create(2, 2, (double[]) { 1., 2., 3., 4. });
    B = matrix_create(2, 2, (double[]) { 1., 0., 0., 1. });

    matrix_print(A);

   // matrix_add(&B, &A);
    matrix_print(B);

    C = matrix_sum(A, B);
    matrix_print(C);

    S = matrix_scalar_mult(A);
    matrix_print(S);

    M = matrix_mult(A, B);
    matrix_print(M);

    T = matrix_tr(A, B);
    matrix_print(T);

    matrix_free(&T);
    matrix_free(&M);
    matrix_free(&S);
    matrix_free(&C);
    matrix_free(&A);
    matrix_free(&B);
    return 0;
}


















/*ptr = malloc(30 * size of(double))
for () {
	*ptr = malloc(50 * size of(double));
}
(50 * 30)* size of(double) + 30 * size of(double*);


enum  // ???
memset(RES->data, 0.0, );  // как заполнить матрицу нулями

Посмотри, как можно указатели обозначать:*/


/*struct Error {
	int level;
	int char msg[100];
};
}
struct Error malloc_error = { critical," " };

Error_msg(malloc_error);*/



