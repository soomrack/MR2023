#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>


const double EPS = 1e-7;

typedef struct Matrix
{
    size_t rows;
    size_t cols;
    double *data;
} Matrix;


const Matrix MATRIX_NULL = {.cols = 0, .rows = 0, .data = NULL};


void matrix_error_message()
{
    printf("Error! Check your actions!\n");
}


Matrix matrix_allocation(const size_t rows, const size_t cols)
{
    if (rows >= SIZE_MAX / sizeof(double) / cols) { // rows * cols < MAX_SIZE / sizeof(double)
        return MATRIX_NULL; 
    }
    Matrix matrix = {rows, cols, NULL};
    matrix.data = (double *)malloc(rows * cols * sizeof(double));
    if (matrix.data == NULL){
        matrix.rows = 0;
        matrix.cols = 0;
        matrix_error_message();
    }
    return matrix;
}


// Function returns MATRIX_NULL if fail
Matrix matrix_create(const size_t rows, const size_t cols, const double *data)
{
    Matrix A = matrix_allocation (rows, cols);
    if (A.data == NULL) return A;
    
    memcpy(A.data, data, rows * cols * sizeof(double));
    return A;
}


void matrix_free( Matrix *A)
{
    if(A->data != NULL || A->cols != 0 || A->rows != 0){
    A->cols = 0;
    A->rows = 0;
    free(A->data);
    A->data = NULL;
    }
}


// Создание матрицы заполненной нулями
void matrix_zero(const Matrix matrix)
{
    memset (matrix->data, 0, matrix->rows * matrix->cols * sizeof(double));
}


// Создание единичной матрицы
void matrix_identity(const Matrix matrix)
{
    if (matrix->rows != matrix->cols){
        matrix_error_message();
        return;
    }
    matrix_zero(matrix);
    for (unsigned int idx = 0; idx < matrix->rows * matrix->cols; idx += matrix->rows + 1)
        matrix->data[idx] = 1.0;
}


void matrix_print(const char *function_name, const Matrix A)
{ // Блок вывода
    printf("\n%s\n", function_name);
    for (unsigned int row = 0; row < A.rows; row++){
        for (unsigned int col = 0; col < A.cols; col++){
            printf("%lf ", A.data[row * A.cols + col]);
        }
        printf("\n"); 
    }
}


Matrix matrix_addition(const Matrix *A, const Matrix *B)
{
    if (A->rows != B->rows || A->cols != B->cols){
        matrix_error_message();
        return MATRIX_NULL;
    }
    Matrix sum = matrix_allocation(A->rows, A->cols);
    for (unsigned int index = 0; index < A->rows * A->cols; index++){
        sum.data[index] = A->data[index] + B->data[index];
    }
    return sum;
}


Matrix matrix_substract(Matrix *A, Matrix *B)
{
    if (A->rows != B->rows || A->cols != B->cols){
        matrix_error_message();
        return MATRIX_NULL;
    }
    Matrix sub = matrix_allocation(A->rows, A->cols);
    for (unsigned int index = 0; index < A->rows * A->cols; index++){
        sub.data[index] = A->data[index] - B->data[index];
    }
    return sub;
}

Matrix matrix_multiplication(const Matrix *A, const Matrix *B)
{
    if (A->cols != B->rows){
        matrix_error_message();
        return MATRIX_NULL;
    }
    Matrix multy = matrix_allocation(A->rows, B->cols);
    for (size_t row = 0; row < multy.rows; row++){
        for (size_t col = 0; col < multy.cols; col++){
            double sum = 0;
            for (unsigned int k = 0; k < A->cols; k++){
                sum += A->data[row * A->cols + k] * B->data[k * B->cols + col];
            }
            multy.data[row * multy.cols + col] = sum;
        }
    }
    return multy;
}


Matrix matrix_minor(const Matrix *matrix, const unsigned int minor_row, const unsigned int minor_col)
{
    if (matrix->rows == 0 || matrix->cols == 0 || matrix->data == NULL){
        return MATRIX_NULL;
    }
    Matrix minor = matrix_allocation(matrix->rows - 1, matrix->cols - 1);
    unsigned int minor_index = 0;
    for (unsigned int row = 0; row < matrix->rows; row++){
        for (unsigned int col = 0; col < matrix->cols; col++){
            if (row == minor_row || col == minor_col)
                continue;
            minor.data[minor_index++] = matrix->data[row * matrix->cols + col];
        }
    }
    return minor;
}


// Определитель с рекурсивным вызовом
double matrix_determinant(const Matrix *matrix) 
{ 
    if (matrix->rows != matrix->cols){
        matrix_error_message();
        return NAN;
    }
    double det = 0;
    int k = 1;
    if (matrix->rows == 0)
        return NAN;
    if (matrix->rows == 1)
        return matrix->data[0];
    if (matrix->rows == 2)
        return (matrix->data[0] * matrix->data[3] - matrix->data[2] * matrix->data[1]);
    for (unsigned int idx = 0; idx < matrix->rows; idx++){
        Matrix temp = matrix_minor(matrix, 0, idx);
        if (temp.data == NULL) {
            return NAN;
        }
        det += k * matrix->data[idx] * matrix_determinant(&temp);
        k = -k;
        matrix_free(&temp);
    }
    return det;
}

// Транспонирование матрицы
Matrix matrix_transposition(const Matrix *A)
{
    Matrix trans = matrix_allocation(A->cols, A->rows);
    for (unsigned int row = 0; row < trans.rows; row++){
        for (unsigned int col = 0; col < trans.cols; col++){
            trans.data[row * trans.cols + col] = A->data[col * trans.rows + row];
        }
    }
    return trans;
}


// Функция нахождения обратной матрицы
Matrix matrix_reverse(const Matrix *A)
{
    double det = matrix_determinant(A);
    if (A->rows != A->cols){
        matrix_error_message();
        return MATRIX_NULL;
    }
    if (fabs(det) < EPS){
        matrix_error_message();
        return MATRIX_NULL;
    }
    Matrix reverse = matrix_allocation(A->rows, A->cols);
        if (reverse.data == NULL) {
            return NAN;
        }
    Matrix temp;
    int k = 1;
    for (unsigned int row = 0; row < reverse.rows; row++){
        for (unsigned int col = 0; col < reverse.cols; col++)
        {
            temp = matrix_minor(A, row, col);
            reverse.data[row * A->cols + col] = k * matrix_determinant(&temp);
            k = -k;
        }
        matrix_free(&temp);
    }
    Matrix temp_transpose = matrix_transposition(&reverse);
    matrix_free(&reverse);
    return reverse;
}

Matrix matrix_exponent(const Matrix *matrix, const unsigned int n)
{
    if (matrix->rows != matrix->cols){
        matrix_error_message();
        return MATRIX_NULL; // Если матрица не квадратная, возвращаем пустую матрицу
    }
    Matrix ex = matrix_allocation(matrix->rows, matrix->cols);
        if (ex.data == NULL) {
            return NAN;
        }
    matrix_identity(&ex);
    Matrix temp = matrix_allocation(matrix->rows, matrix->cols);
        if (temp.data == NULL) {
            return NAN;
        }
    matrix_identity(&temp);
    double fact = 1.0;
    for (unsigned int i = 1; i < n; i++){
        fact *= i;
        temp = matrix_multiplication(&temp, matrix);
    }
    matrix_free(&temp);
    return ex;
}