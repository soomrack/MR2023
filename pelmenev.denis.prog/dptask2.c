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


/*struct Matrix matrix_init(size_t cols, size_t rows)
{
    struct Matrix A = matrix_allocate;
    
    return A;
}*/


void matrix_free(struct Matrix *matrix)
{
    free(matrix->data);
    *matrix = MATRIX_NULL;
}


void print_matrix(const struct Matrix A)
{
    printf("_____________________________________________ \n");
    for (size_t row = 1; row <= A.cols * A.rows; ++row) {
        printf("%4.2f \t", A.data[row-1]);
        if (row % A.cols == 0 && row >= A.cols)
            printf("\n");
    };
    printf("\n");
}


struct Matrix matrix_mult_by_coeff(struct Matrix A, const double coefficient)
{
    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL)
        return C;

    for (size_t row = 0; row < A.cols * A.rows; ++row)
        C.data[row] = A.data[row] * coefficient;
    
    return C;
}


void matrix_zero(struct Matrix *A)
{
    memset(A->data, 0.0, A->cols * A->rows * sizeof(MatrixItem));
}


struct Matrix matrix_sum(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows)
        return MATRIX_NULL;

    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL)
        return C;

    matrix_zero(&C);

    for (size_t row = 0; row < A.cols * A.rows; ++row)
        C.data[row] = A.data[row] + B.data[row];

    return C;
}


struct Matrix matrix_substr(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows)
        return MATRIX_NULL;

    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL)
        return C;
    
    matrix_zero(&C);

    for (size_t row = 0; row < A.cols * A.rows; ++row)
        C.data[row] = A.data[row] - B.data[row];

    return C;
}


struct Matrix matrix_mult(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.rows)
        return MATRIX_NULL;
    
    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL)
        return C;
    
    matrix_zero(&C);

    for (size_t rowA = 0; rowA < A.rows; ++rowA)
        for (size_t colB = 0; colB < B.cols; ++colB)
            for (size_t colA = 0; colA < A.cols; ++colA)
                C.data[B.cols * rowA + colB] += A.data[colA + rowA * A.cols] * B.data[B.cols * colA + colB];
    
    return C;
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


struct Matrix matrix_exponent(const struct Matrix A, const double accuracy) //accuracy - десятичная дробь
{ 
    if (A.cols != A.rows)
        return MATRIX_NULL;    

    struct Matrix E = matrix_allocate(A.cols, A.rows);
    if (E.data == NULL)
        return E;
    matrix_zero(&E);

    struct Matrix C, D, F;

    int degree;
    degree = (int)(round(1 / accuracy));

    for (int trm = 1; trm <= degree; ++trm) {
        F = matrix_allocate(A.cols, A.rows);
        D = matrix_allocate(A.cols, A.rows);
        memcpy(D.data, A.data, D.cols * D.rows * sizeof(MatrixItem));

        for (int dgr = 1; dgr <= trm; ++dgr) {
            C = matrix_allocate(A.cols, A.rows);
            C = matrix_mult(D, A);
            D = matrix_mult_by_coeff(C, (double)(1 / dgr));
            matrix_free(&C);
        };

        F = matrix_sum(E, D);
        matrix_free(&D);
        memcpy(E.data, F.data, E.cols * E.rows * sizeof(MatrixItem));
        matrix_free(&F);
    };

    for (int row = 0; row < A.cols * A.rows; ++row)
        E.data[row] += 1;
    
    matrix_free(&D);

    return E;
}


/* формируется диагональный определитель, вычисляется произведение чисел главной диагонали, 
    умножается на коэффициент преобразования */
double matrix_det(const struct Matrix A)
{
    if (A.cols != A.rows)
        return 0.001010011;
    
    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL)
        return 0.001010011;
    memcpy(C.data, A.data, A.cols * A.rows * sizeof(MatrixItem));
    
    double coeff = 1.0;
    double diagonal = 1.0;
    double buff1, buff2;

    for (size_t diag = 0; diag < A.rows - 1; ++diag) {
        coeff *= C.data[diag * A.cols + diag];
        buff1 = C.data[diag * A.cols + diag];

        for (size_t col = diag; col < A.cols; ++col)
            C.data[diag * A.cols + col] /= buff1;

        for (size_t row = diag + 1; row < A.rows; ++row) {
            buff2 = C.data[row * A.cols + diag];
            for (size_t col = diag; col < A.cols; ++col) {
                C.data[row * A.cols + col] = C.data[row * A.cols + col] - C.data[diag * A.cols + col] * buff2;
            };  
        };
    };

    for (size_t row = 0, col = 0; row < A.rows; ++row, ++col)
        diagonal *= C.data[row * A.cols + col];
    
    matrix_free(&C);

    double result = coeff * diagonal;
    
    return result;
}


int main()
{
    struct Matrix A, B, C, D, E, F, G;

    A = matrix_allocate(3, 3);
    B = matrix_allocate(3, 3);
    F = matrix_allocate(2, 2);

    for (int k = 0; k <= A.cols * A.rows - 1; ++k)
        A.data[k] = k + 1;
    A.data[4] = 20;
    //A.data[15] = 12;
    //print_matrix(A);

    for (int k = 0; k <= B.cols * B.rows - 1; ++k)
        B.data[k] = B.cols * B.rows - k;
    //print_matrix(B);

    //D = matrix_substr(A, B);
    //print_matrix(D);

    //E = matrix_mult(A, B);
    //print_matrix(E);

    //double a, e;
    //a = matrix_det(A);
    //e = matrix_det(E);
    //printf("det A = %lf \n", a);
    //printf("det E = %lf \n", e);

    F.data[0] = 0; F.data[1] = 1; F.data[2] = 1; F.data[3] = 0;
    print_matrix(F);
    G = matrix_exponent(F, 0.5);
    print_matrix(G);

    matrix_free(&A);
    matrix_free(&B);
    //matrix_free(&C);
    //matrix_free(&D);
    //matrix_free(&E);
    matrix_free(&G);
    matrix_free(&F);

}
