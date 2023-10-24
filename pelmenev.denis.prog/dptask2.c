#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>


typedef double MatrixItem;


enum MatrixTypes { zero, one, random };
//enum MatrixForms { equal, mult, square };
//enum MATRIX_ERROR {};


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
    printf("Matrix = \n");
    for (size_t row = 0; row < A.cols * A.rows; ++row) {
        printf("%2f \t", A.data[row]);
        if (row % A.cols == 0 && row >= A.cols)
            printf("\n");
    };
}


void matrix_mult_by_coeff(struct Matrix *A, const double coefficient)
{
    for (size_t row = 0; row < A->cols * matrix->rows; ++row)
        A->data[row] = A->data[row] * coefficient;
}


struct Matrix matrix_sum(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows)
        return MATRIX_NULL;

    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL)
        return C;

    for (size_t row = 0; size_t <= A.cols * A.rows - 1; row++)
        C.data[row] = A.data[row] + B.data[row];

    return C;
}


void matrix_substr(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows)
        return MATRIX_NULL;

    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL)
        return C;

    for (size_t row = 0; size_t <= A.cols * A.rows - 1; row++)
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
            matrix2->data[row * A.cols + col] = matrix1.data[row + col * A.cols];
    
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
        return;
    
    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL)
        return;
    C = A;
    
    double coeff = 1.0;
    double dmult = 1.0;

    for (size_t row1 = 0, col1 = 0; row1 < A.rows - 1; ++row1, ++col1) {
        coeff *= A.data[row1 * A.cols + col1];
        for (size_t col2 = col1; col2 < A.cols; ++col2) {
            C.data[row1 * col2 + col2] = C.data[row1 * col2 + col2] / A.data[row1 * A.cols + col1];
            C.data[(row1 + 1) * col2 + col2] -= C.data[row1 * col2 + col2] * C.data[(row1 + 1) * col2];
        };
    };

    for (size_t row = 0, col = 0; row < A.rows; ++row, ++col)
        dmult *= C.data[row * col + col];
    
    matrix_free(&C);
    
    return coeff * dmult;
}


int main()
{
    struct Matrix A, B, C, D;

    //matrix_init(3, 3, &A, one);
    matrix_init(2, 2, &B, random);
    matrix_init(2, 2, &C, random);

    for (int k = 0; k <= C.cols * C.rows - 1; ++k)
        C.data[k] = k + 1;
    print_matrix(C);

    for (int k = 0; k <= B.cols * B.rows - 1; ++k)
        B.data[k] = B.cols * B.rows - k;
    print_matrix(B);

    //matrix_transp(C, &D);

    //matrix_mult(C, B, &D);

    matrix_exponent(C, &D, 0.1);

    print_matrix(D);

    //matrix_free(&A);
    matrix_free(&B);
    matrix_free(&C);
    matrix_free(&D);

}
