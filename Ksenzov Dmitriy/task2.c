#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>


typedef double MatrixItem;

struct Matrix {
    size_t cols;
    size_t rows;
    MatrixItem *data;
};


const struct Matrix MATRIX_NULL = {.rows = 0, .cols = 0, .data = NULL};


void matrix_set_zero(struct Matrix A)
{
    memset(A.data, 0, sizeof(double) * A.rows * A.cols);
}


void matrix_set_one(struct Matrix A)
{
    matrix_set_zero(A);
    for (size_t idx = 0; idx < A.rows * A.cols; idx += A.cols + 1)
    A.data[idx] = 1;
}


struct Matrix matrix_allocate(const size_t rows, const size_t cols)
{
    if (cols == 0 || rows == 0) {
        struct Matrix A = {.cols = cols, .rows = rows, .data = NULL};
        return A;
    };
    if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols) return MATRIX_NULL; // rows * cols < MAX_SIZE / sizeof(double)

    struct Matrix A = {.cols = cols, .rows = rows, .data = NULL};
    A.data = (MatrixItem*)malloc(A.cols * A.rows * sizeof(MatrixItem));
    if (A.data == NULL) {
        return MATRIX_NULL;
    }
    return A;
}


// Function returns MATRIX_NULL if fail
struct Matrix matrix_create(const size_t rows, const size_t cols, const MatrixItem *values)
{
    struct Matrix A = matrix_allocate(rows, cols);
    if (A.data == NULL) return A;
    
    memcpy(A.data, values, rows * cols * sizeof(MatrixItem));
    return A;
}


void matrix_delete(struct Matrix *A)
{
    free(A->data);
    *A = MATRIX_NULL;
}


void matrix_print(const struct Matrix A)
{
    printf("\n");
    for (unsigned int col = 0; col < A.rows; ++col) {
        printf("[ ");
        for (unsigned int row = 0; row < A.cols; ++row) {
            printf(" %4.2f", A.data[row + col * A.cols ]);
        }
        printf("]\n");
    }
}


// A = A + B
// Function return 0 if success
int matrix_add(struct Matrix A, struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return 1;
    
    for (unsigned int idx = 0; idx < A.cols * A.rows; ++idx) A.data[idx] += B.data[idx];
        return 0;
}


// Function returns new matrix C = A + B or MATRIX_NULL if fail
struct Matrix matrix_sum(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return MATRIX_NULL;

    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL) return C;
    
    memcpy(C.data, A.data, C.cols * C.rows * sizeof(MatrixItem));
    matrix_add(C, B);
    return C;
}

// A = A - B
// Function return 0 if success
int matrix_subtract(struct Matrix A, struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return 1;
    
    for (unsigned int idx = 0; idx < A.cols * A.rows; ++idx)
        A.data[idx] -= B.data[idx];
        return 0;
}


// Function returns new matrix C = A - B or MATRIX_NULL if fail
struct Matrix matrix_subtration(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return MATRIX_NULL;

    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL) return C;
    
    memcpy(C.data, A.data, C.cols * C.rows * sizeof(MatrixItem));
    matrix_subtract(C, B);
    return C;
}


// Function returns new matrix C = A * B or MATRIX_NULL if fail
struct Matrix matrix_mult(struct Matrix A, struct Matrix B)
{
    if (A.cols != B.rows) return MATRIX_NULL;
    
    struct Matrix C = matrix_allocate(A.rows, B.cols);
    if (C.data == NULL) return C;

    for (unsigned int C_col = 0; C_col < A.rows; ++C_col) {
        for (unsigned int C_row = 0; C_row < B.cols; ++C_row) {
            for (unsigned int idx = 0; idx < A.cols; ++idx) {
                C.data[C_row + C_col * B.cols] += A.data[idx + (C_col * A.cols)]
                * B.data[idx * B.cols + C_row];
            };
        };
    };
    return C;
}


// Function returns new matrix C = A^T or MATRIX_NULL if fail
struct Matrix matrix_transposition(struct Matrix A)
{
    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL) return C;

    for (unsigned int C_row = 0; C_row < A.cols; ++C_row) {
        for (unsigned int C_col = 0; C_col < A.rows; ++C_col) {
            C.data[C_col + C_row * A.rows] = A.data[C_col * A.cols + C_row];
        };
    };
    return C;
}


// Function returns C = |A| (A[1x1]) or NAN if fail
double matrix_determinant_1x1(struct Matrix A)
{
    double C;

    if (A.cols != 1 && A.rows != 1) return NAN;

    C = A.data[0];
    return C;
}


// Function returns C = |A| (A[2x2]) or NAN if fail
double matrix_determinant_2x2(struct Matrix A)
{
    double C;

    if (A.cols != 2 && A.rows != 2) return NAN;

    C = A.data[0] * A.data[3] - A.data[1] * A.data[2];
    return C;
}


// Function returns C = |A| (A[3x3]) or NAN if fail
double matrix_determinant_3x3(struct Matrix A)
{
    double C;

    if (A.cols != 3 && A.rows != 3) return NAN;

    C =
        + A.data[0] * A.data[4] * A.data[8]
        + A.data[6] * A.data[1] * A.data[5]
        + A.data[3] * A.data[7] * A.data[2]
        - A.data[2] * A.data[4] * A.data[6]
        - A.data[5] * A.data[7] * A.data[0]
        - A.data[3] * A.data[1] * A.data[8];
    return C;
}


void determinant_print(const double A)
{
    printf("\n Matrix determinant = %4.2lf", A);
}


// Function returns new matrix C = e^A or MATRIX_NULL if fail
struct Matrix matrix_exponent(struct Matrix A)
{
    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL) return C;

    struct Matrix D = matrix_allocate(A.cols, A.rows);
    matrix_set_one(D);

    struct Matrix E = matrix_allocate(A.cols, A.rows);

    matrix_set_one(C);

    for (unsigned int k = 1; k <= 100; ++k) {
        
        D = matrix_mult(D, A);

        for (unsigned int idx = 0; idx < E.cols * E.rows; ++idx)
        E.data[idx] = D.data[idx] / k;

        matrix_add(C, E);
    };
    return C;
}


// Function returns new matrix C = |A| or MATRIX_NULL if fail
// struct Matrix matrix_determinant(struct Matrix A)
// {
//     if (A.cols != A.rows) return MATRIX_NULL;

//     struct Matrix C = matrix_allocate(1, 1);
//     if (C.data == NULL) return MATRIX_NULL;

//     struct Matrix D = matrix_allocate(A.rows, A.cols);
//     if (D.data == NULL) return MATRIX_NULL;

//     unsigned int shift_triangle = 0;
//     MatrixItem E = 0;
//     for (unsigned int row = 0; row < A.rows; ++row) {
//          if (A.data[row * A.cols + shift_triangle] = 0) {
//              for (unsigned int change = 1; change <= A.rows - row; ++change) {
//                  if (A.data[row * A.cols + shift_triangle + change * A.cols] != 0) {

//                  }
//              };
//          }
//         else {
//             E = A.data[(row + 1) * A.cols + shift_triangle] / A.data[row * A.cols + shift_triangle];
//             for (unsigned int col = 0; col < A.cols; ++col) {
//             D.data[col] = A.data[A.cols + A.cols * row + col] - E * A.data[A.cols * row + col];
//             };
//         };
//         ++shift_triangle;
//     };

//     unsigned int shift_determinant = 1;
//     for (unsigned int idx = 0; idx < A.cols; idx += A.cols + shift_determinant) {
//             C.data[1] += D.data[idx];
//             ++shift_determinant; 
//     };
//     return C;
// }


int main ()
{
    struct Matrix A, B, C, D, E, F, K;
    double G, H, I;
 
    A = matrix_create(3, 3, (MatrixItem[]){24., 15., 2.,
                                           40., 5., 7.,
                                           1., 33., 21.});
    B = matrix_create(3, 3, (MatrixItem[]){4., 24., 52.,
                                           10., 15., 0.,
                                           31., 32., 51. });

    matrix_print(A);
    matrix_print(B);

    C = matrix_sum(A, B);
    matrix_print(C);

    D = matrix_subtration(A,B);
    matrix_print(D);

    E = matrix_mult(A,B);
    matrix_print(E);

    F = matrix_transposition(A);
    matrix_print(F);

    // G = matrix_determinant(A);
    // matrix_print(G);

    H = matrix_determinant_1x1(B);
    determinant_print(H);

    I = matrix_determinant_2x2(B);
    determinant_print(I);

    G = matrix_determinant_3x3(A);
    determinant_print(G);

    K = matrix_exponent(A);
    matrix_print(K);

    matrix_delete(&A);
    matrix_delete(&B);
    matrix_delete(&C);
    matrix_delete(&D);
    matrix_delete(&E);
    matrix_delete(&F);
    matrix_delete(&K);
    return 0;
}