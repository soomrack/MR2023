#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


enum MatrixTypes { zero, one, random };
enum MatrixForms { equal, mult, square };


struct Matrix {
    unsigned int cols;
    unsigned int rows;
    double *data;
};


int matrix_check_size(struct Matrix matrix1, struct Matrix matrix2, enum MatrixForms mform)
{
    if (mform == equal) {
        if (matrix1.cols == matrix2.cols && matrix1.rows == matrix2.rows)
            return 1;
    };

    if (mform == square) {
        if (matrix1.cols == matrix1.rows)
            return 1;
    };

    if (mform == mult) {
        if (matrix1.cols == matrix2.rows)
            return 1;
    };
}


void matrix_init(const unsigned int cols, const unsigned int rows, struct Matrix *matrix, enum MatrixTypes matrix_types)
{
    matrix->cols = cols;
    matrix->rows = rows;
    matrix->data = (double*)malloc(cols * rows * sizeof(double));

    if (matrix_types == zero)
        memset(matrix->data, 0.0, cols * rows * sizeof(double));

    if (matrix_types == one) {
        if (matrix_check_size(*matrix, *matrix, square) != 1) {
            printf("Invalid matrix size \n");
            return;
        };

        memset(matrix->data, 0.0, cols * rows * sizeof(double));

        for (int k = 0; k <= cols * rows - 1; k += (cols + 1))
            matrix->data[k] = 1;
    };
}


void matrix_free(struct Matrix *matrix)
{
    matrix->cols = 0;
    matrix->rows = 0;
    free(matrix->data);
    matrix->data = NULL;
}


void print_matrix(const struct Matrix matrix)
{
    printf("Matrix = \n");
    for (int k = 1; k <= matrix.cols * matrix.rows; ++k) {
        printf("%2f \t", matrix.data[k-1]);
        if (k % matrix.cols == 0 && k >= matrix.cols)
            printf("\n");
    };
}


void matrix_add_coefficient(struct Matrix *matrix, int coefficient)
{
    for (int k = 0; k <= (*matrix).cols * (*matrix).rows - 1; ++k)
        matrix->data[k] = (*matrix).data[k] * coefficient;
}


void matrix_sum(const struct Matrix matrix1, const struct Matrix matrix2, struct Matrix *matrix3)
{
    if (matrix_check_size(matrix1, matrix2, equal) != 1) {
        printf("Invalid matrix sizes \n");
        return;
    };

    matrix_free(matrix3);  

    matrix_init(matrix1.cols, matrix1.rows, matrix3, random);

    for (int k = 0; k <= matrix1.cols * matrix1.rows - 1; k++)
        matrix3->data[k] = matrix1.data[k] + matrix2.data[k];
}


void matrix_minus(const struct Matrix matrix1, const struct Matrix matrix2, struct Matrix *matrix3)
{
    if (matrix_check_size(matrix1, matrix2, equal) != 1) {
        printf("Invalid matrix sizes \n");
        return;
    };

    matrix_free(matrix3);

    matrix_init(matrix1.cols, matrix1.rows, matrix3, random);

    for (int k = 0; k <= matrix1.cols * matrix1.rows - 1; k++)
        matrix3->data[k] = matrix1.data[k] - matrix2.data[k];
}


void matrix_mult(const struct Matrix matrix1, const struct Matrix matrix2, struct Matrix *matrix3)
{
    if (matrix_check_size(matrix1, matrix2, mult) != 1) {
        printf("Invalid matrix sizes \n");
        return;
    };

    matrix_free(matrix3);

    matrix_init(matrix2.cols, matrix1.rows, matrix3, random);

    for (int k = 1; k <= matrix1.rows; ++k)
        for (int m = 0; m <= matrix2.cols - 1; ++m)
            for (int p = 1; p <= matrix1.cols; ++p)
                matrix3->data[matrix2.cols * (k - 1) + m] += matrix1.data[p - 1 + (k - 1) * matrix1.cols] 
                * matrix2.data[matrix2.cols * (p - 1) + m];
}


void matrix_transp(const struct Matrix matrix1, struct Matrix *matrix2)
{
    matrix_free(matrix2);

    matrix_init(matrix1.rows, matrix1.cols, matrix2, random);

    for (int k = 1; k <= matrix1.rows; ++k)
        for (int m = 1; m <= matrix1.cols; ++m)
            matrix2->data[(k - 1) * matrix1.cols + m - 1] = matrix1.data[k - 1 + (m - 1) * matrix1.cols];
}


void matrix_exponent(const struct Matrix matrix1, struct Matrix *matrix2, const double accuracy) //accuracy - десятичная дробь
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
            matrix_add_coefficient(&buffer2, 1 / m);
            buffer1 = buffer2;
        };
        matrix_sum(*matrix2, buffer1, &buffer3);
        *matrix2 = buffer3;
    };
    
    matrix_free(&buffer1);
    matrix_free(&buffer2);

    for (int p = 0; p <= matrix1.cols * matrix1.rows - 1; ++p)
        matrix2->data[p] += 1;
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

    matrix_exponent(C, &D, 1.0);

    print_matrix(D);

    //matrix_free(&A);
    matrix_free(&B);
    matrix_free(&C);
    matrix_free(&D);

}
