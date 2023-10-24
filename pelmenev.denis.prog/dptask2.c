#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


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


void matrix_mult_by_coeff(struct Matrix *A, const double coefficient)
{
    for (size_t row = 0; row < A->cols * A->rows; ++row)
        A->data[row] = A->data[row] * coefficient;
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


/*void matrix_exponent(const struct Matrix matrix1, struct Matrix *matrix2, const double accuracy) //accuracy - десятичная дробь
{ 
    if (matrix_check_size(matrix1, matrix1, square) != 1) {
        printf("Invalid matrix size \n");
        return;
    };

    struct Matrix buffer1, buffer2, buffer3;
    matrix_init(matrix1.cols, matrix1.rows, &buffer1, random);
    matrix_init(matrix1.cols, matrix1.rows, &buffer2, random);
    matrix_init(matrix1.cols, matrix1.rows, &buffer3, random);

    matrix_free(matrix2);

    matrix_init(matrix1.cols, matrix1.rows, matrix2, zero);

    int degree;
    degree = (int)(round(1 / accuracy));

    for (int k = 1; degree; ++k) {
        buffer1 = matrix1;
        for (int m = 1; m <= k; ++m) {
            matrix_mult(buffer1, matrix1, &buffer2);
            matrix_mult_by_coeff(&buffer2, 1 / m);
            buffer1 = buffer2;
        };
        matrix_sum(*matrix2, buffer1, &buffer3);
        *matrix2 = buffer3;
    };
    
    matrix_free(&buffer1);
    matrix_free(&buffer2);

    for (int p = 0; p <= matrix1.cols * matrix1.rows - 1; ++p)
        matrix2->data[p] += 1;
}*/


/* формируется диагональный определитель, вычисляется произведение чисел главной диагонали, 
    умножается на коэффициент преобразования */
double matrix_det(const struct Matrix A)
{
    if (A.cols != A.rows)
        return 0.001010011;
    
    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL)
        return 0.001010011;
    for (size_t row = 0; row < A.cols * A.rows; ++row)
        C.data[row] = A.data[row];
    
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
    struct Matrix A, B, C, D, E;

    A = matrix_allocate(3, 3);
    B = matrix_allocate(3, 3);

    for (int k = 0; k <= A.cols * A.rows - 1; ++k)
        A.data[k] = k + 1;
    A.data[4] = -1;
    //print_matrix(A);

    for (int k = 0; k <= B.cols * B.rows - 1; ++k)
        B.data[k] = B.cols * B.rows - k;
    //print_matrix(B);

    D = matrix_substr(A, B);
    //print_matrix(D);

    E = matrix_mult(A, B);
    //print_matrix(E);

    double a, e;
    a = matrix_det(A);
    e = matrix_det(E);
    printf("det A = %lf \n", a);
    printf("det E = %lf \n", e);

    matrix_free(&A);
    matrix_free(&B);
    matrix_free(&C);
    matrix_free(&D);
    matrix_free(&E);

}
