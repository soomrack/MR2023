#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<math.h>

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
    if(A->data != NULL) free(A->data);
    *A = MATRIX_NULL;
}


void matrix_print(const struct Matrix A)
{
    for(size_t row = 0; row < A.rows; ++row){
        printf("[");
        for(size_t col = 0; col < A.cols; ++col){
            printf("%.5f ", A.data[A.cols * row + col]);
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
            C.data[row * B.cols + col] = 0;

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


double matrix_determinant_2x2(const struct Matrix A)
{
    if(A.rows != 2 || A.cols != 2){
        printf("неподходящий размер матрицы \n");
        return NAN;
    }

    double detA = A.data[0] * A.data[3] - A.data[1] * A.data[2];
    return detA;
}


double matrix_determinant_3x3(const struct Matrix A)
{
    if(A.rows != 3 || A.cols != 3){
        printf("неподходящий размер матрицы \n");
        return NAN;
    }

    double detA = A.data[0] * A.data[4] * A.data[8] +
                  A.data[1] * A.data[5] * A.data[6] +
                  A.data[2] * A.data[3] * A.data[7] -
                  A.data[2] * A.data[4] * A.data[6] - 
                  A.data[1] * A.data[3] * A.data[8] -
                  A.data[0] * A.data[5] * A.data[7];
    return detA;
}


struct Matrix matrix_degree(const struct Matrix A, const size_t degree)
{
    if (A.cols != A.rows) return MATRIX_NULL;

    struct Matrix C = matrix_allocate(A.rows, A.cols);
    if (C.data == NULL) return C;
    struct Matrix B = matrix_allocate(A.rows, A.cols);
    if (C.data == NULL) return B;

    memcpy(B.data, A.data, C.cols * C.rows * sizeof(MatrixItem));

    for(int i = 1; i < degree; i++){
        C = matrix_multiply(B, A);
        memcpy(B.data, C.data, B.cols * B.rows * sizeof(MatrixItem));
    }

    matrix_free(&C);
    return B;
}


unsigned long int factorial(const size_t x)
{
    unsigned long int f = 1;
    for(int i = 2; i <= x; i++){
        f *= i;
    }
    return f;
}


struct Matrix matrix_exponent(const struct Matrix A)
{
    if(A.rows != A.cols) return MATRIX_NULL;

    struct Matrix E = matrix_allocate(A.rows, A.cols);
    if (E.data == NULL) return E;
    struct Matrix e = matrix_allocate(A.rows, A.cols);
    if (e.data == NULL) return e;

    for (int idx = 0; idx < A.rows * A.cols; idx++){
        E.data[idx] = 0;
    }

    for(int idx = 0; idx < A.rows; idx++){
        E.data[idx + idx * A.cols] = 1.;
    }

    struct Matrix AA = matrix_allocate(A.rows, A.cols);
    if (AA.data == NULL) return AA;
    int f;

    e = matrix_sum(A, E);
    for(int n = 2; n <= 20; n++){
        AA = matrix_degree(A, n);
        f = factorial(n);
        matrix_scalar(AA, (double)1/f);
        matrix_add(e, AA);
    }
    matrix_free(&AA);
    matrix_free(&E);
    return e;
}


int main()
{
    struct Matrix A, B, C;

    //A = matrix_create(3, 3, (double[]){2., -3., -7., 1., 1., 1., 1., 2., 3.});
    B = matrix_create(2, 2, (double[]){1., 5., 6., 1.});
    A = matrix_create(3, 3, (double[]){1., 0., 0., 0., 1., 0., 0., 0., 1.});

    matrix_print(A);
    matrix_print(B);

    /*C = matrix_degree(A, 2);
    matrix_print(C);

    C = matrix_multiply(A, A);
    matrix_print(C);*/

    C = matrix_exponent(A);
    matrix_print(C);



    matrix_free(&C);
    matrix_free(&A);
    matrix_free(&B);
    return 0;
}
