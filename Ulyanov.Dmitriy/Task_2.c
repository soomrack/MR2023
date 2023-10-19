#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef double MatrixItem;

struct Matrix {
    size_t cols;
    size_t rows;
    MatrixItem *data;
};

const struct Matrix NULL_MATRIX = { .cols = 0, .rows = 0, .data = NULL };


// Function returns Null_Matrix if fail
struct Matrix matrix_allocate(const size_t rows, const size_t cols)
{
    if (cols == 0 || rows == 0) {
        struct Matrix A = { .cols = cols, .rows = rows, .data = NULL };
        return A;
    };
    if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols) return NULL_MATRIX;

    struct Matrix A = { .cols = cols, .rows = rows, .data = NULL };
    A.data = (MatrixItem *)malloc(A.cols * A.rows * sizeof(MatrixItem));
    if (A.data == NULL) return NULL_MATRIX;
    return A;
}


// Function return NULL_MATRIX if fail
struct Matrix matrix_create(const size_t rows, const size_t cols, const MatrixItem *values)
{
    struct Matrix A = matrix_allocate(rows, cols);
    if (A.data == NULL) {
        return NULL_MATRIX;
    };

    memcpy(A.data, values, A.cols * A.rows * sizeof(MatrixItem));
    return A;
}


void matrix_set_zero(struct Matrix A)
{
    memset(A.data, 0, sizeof(double) * A.rows * A.cols);
}


void matrix_set_one(struct Matrix A)
{
    matrix_set_zero(A);
    for (size_t idx = 0; idx < A.rows * A.cols; idx += A.cols + 1)
        A.data[idx] = 1.;
}


void matrix_print(const struct Matrix A)
{

    for (size_t row = 0; row < A.rows; ++row) {
        printf("[ ");
        for (size_t col = 0; col < A.cols; ++col) {
            printf(" %4.2f ", A.data[A.cols * row + col]);
        }
        printf(" ]\n");
    }
    printf("\n");
}


// A += B
// Function returns 0 if success
int matrix_add(const struct Matrix A, const struct Matrix B) {
    if (A.cols != B.cols || A.rows != B.rows) return 1;

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        A.data[idx] += B.data[idx];
    return 0;
}


// Function returns new matrix C = A + B or NULL_MATRIX if fail
struct Matrix matrix_sum(const struct Matrix A, const struct Matrix B) 
{
    if (A.cols != B.cols || A.rows != B.rows) {
        return NULL_MATRIX;
    }
    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == 0) return NULL_MATRIX;

    memcpy(C.data, A.data, C.cols * C.rows * sizeof(MatrixItem));
    matrix_add(C, B);
    return C;
}

// A -= B
// Function return 0 if success
int matrix_subs(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return 1;

    for (unsigned int idx = 0; idx < A.cols * A.rows; ++idx)
        A.data[idx] = A.data[idx] - B.data[idx];
    return 0;
}


// C = A - B
// Function return C = A - B or NULL_MATRIX if fail 
struct Matrix matrix_minus(struct Matrix A, struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return NULL_MATRIX;

    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL) return NULL_MATRIX;

    memcpy(C.data, A.data, C.cols * C.rows * sizeof(MatrixItem));
    matrix_subs(C, B);
    return C;
}

//C = A * B
// Function return C = A * B or NULL_MATRIX if fail
struct Matrix matrix_mult(struct Matrix A, struct Matrix B)
{
    if (A.rows != B.cols) return NULL_MATRIX;

    struct Matrix C = matrix_allocate(B.cols, A.rows);
    if (C.data == NULL) return NULL_MATRIX;

    for (size_t col = 0; col < B.cols; ++col) {
        for (size_t row = 0; row < A.rows; ++row) {
            C.data[row * C.cols + col] = 0;
            for (size_t idx = 0; idx < A.cols; ++idx) {
                C.data[row * C.cols + col] += A.data[row * A.cols + idx] * B.data[idx * B.cols + col];
            }
        }
    };
    return C;
}


struct Matrix matrix_trans(struct Matrix A)
{
    struct Matrix B = matrix_allocate(A.cols, A.rows);
    if (B.data == 0) return NULL_MATRIX;

    for (size_t row = 0; row < A.rows; ++row) {
        for (size_t col = 0; col < A.cols; ++col) {
            B.data[col * A.cols + row] = A.data[row * A.cols +col];
        }
    }
    return B;
}

// det(A), A[2][2]
// Function return det(A) or 0 if fail
int matrix_det2x2(struct Matrix A)
{
    if (A.rows != 2 || A.cols != 2) return 440;
    
    int det = A.data[0] * A.data[3] - A.data[1] * A.data[2];
    return det;
}

// det(A), A[3][3]
// Function return det(A) or 0 if fail
int matrix_det3x3(struct Matrix A)
{
    if (A.rows != 3 || A.cols != 3) return 440;

    int det = (A.data[0] * A.data[4] * A.data[8] + A.data[1] * A.data[5] * A.data[6] + A.data[3] * A.data[7] * A.data[2]) - (A.data[2] * A.data[4] * A.data[6] + A.data[1] * A.data[3] * A.data[8] + A.data[5] * A.data[7] * A.data[0]);
    return det;
}



void matrix_delete(struct Matrix *A)
{
    free(A->data);
    A->data = NULL;
}


int main()
{
    struct Matrix  A, B, C, D;
    double values[] = { 3., 1., 8., 1. };
    double values2[] = { 12., 2., 3., 6. };
    double values3[] = { 1., 2., 3., 4., 1., 1., 1., 1., 1.};
    A = matrix_create(2, 2, values);
    B = matrix_create(2, 2, values2);
    D = matrix_create(3, 3, values3);

    matrix_print(A);

  /*  matrix_add(B, A);
    matrix_print(B);

    C = matrix_sum(A, B);
    matrix_print(C);

    matrix_subs(B, A);
    matrix_print(B);

    C = matrix_minus(A, B);
    matrix_print(C);*/

    /*C = matrix_mult(A, B);
    matrix_print(C);*/

    A = matrix_trans(A);
    matrix_print(A);

    int det = matrix_det2x2(A);
    printf("\n%d\n", det);

    int det3 = matrix_det3x3(D);
    printf("\n%d\n", det3);

    //matrix_set_one(A);


    matrix_delete(&A);
    matrix_delete(&B);
    matrix_delete(&C);

    return 0;
}
