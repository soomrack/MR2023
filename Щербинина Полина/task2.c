#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Функция для вывода сообщения об ошибке
void matrix_errormsg(const char *errorMessage) {
    fprintf(stderr, "%s\n", errorMessage);
}

typedef struct {
    int rows;
    int cols;
    double **data;
} Matrix; 

const struct Matrix MATRIX_NULL = {.cols = 0, .rows = 0, .data = NULL};

// Функция для создания матрицы
Matrix matrix_create(int rows, int cols) {
    Matrix A;
    A.rows = rows;
    A.cols = cols;
    
    A.data = (double **)malloc(rows * sizeof(double *) + rows * cols * sizeof(double));
    if (!A.data) {
        matrix_errormsg("Ошибка выделения памяти матрицы.");
        return MATRIX_NULL;
    }
    
    return A;
}

// Функция для освобождения памяти, выделенной под матрицу
void matrix_free(Matrix A)
{

    A.cols = 0;
    A.rows = 0;
    free(A.data);
    A.data = NULL;

}

// Функция для вывода матрицы на экран
void matrix_print(Matrix A) {
    for (int row = 0; row < A.rows; row++) {
        for (int col = 0; col < A.cols; col++) {
            printf("%lf\t", A.data[row][col]);
        }
        printf("\n");
    }
}

// Функция для сложения двух матриц
Matrix matrix_sum(Matrix A, Matrix B) 
{
    if (A.rows != B.rows || A.cols != B.cols) {
        matrix_errormsg("Ошибка: Размеры матриц не совпадают\n");
        return MATRIX_NULL;
    } 
    
    // проверкa создания матриц
    if(A.data == NULL || B.data == NULL){
        matrix_errormsg("MATRIX_NULL");
        return MATRIX_NULL;
    }
 
    Matrix result = matrix_create(A.rows, B.cols);

    if(result.data == NULL){
        matrix_errormsg("MATRIX_NULL");
        return MATRIX_NULL;
    }
    
    for (int row = 0; row < A.rows; row++) {
        for (int col = 0; col < B.cols; col++) {
            result.data[row][col] = A.data[row][col] + B.data[row][col];
        }
    }
    
    return result;
}

// Функция для вычитания двух матриц
Matrix matrix_sub(Matrix A, Matrix B) {
    if (A.rows != B.rows || A.cols != B.cols) {
        matrix_errormsg("Ошибка: Размеры матриц не совпадают\n");
        return MATRIX_NULL;
    }

    if(A.data == NULL || B.data == NULL){
        matrix_errormsg("MATRIX_NULL");
        return MATRIX_NULL;
    }
    
    Matrix result = matrix_create(A.rows, A.cols);
    
    if(result.data == NULL){
        matrix_errormsg("MATRIX_NULL");
        return MATRIX_NULL;
    }
    
    for (int row = 0; row < A.rows; row++) {
        for (int col = 0; col < B.cols; col++) {
            result.data[row][col] = A.data[row][col] - B.data[row][col];
        }
    }
    
    return result;
}

// Функция для умножения двух матриц
Matrix matrix_mult(Matrix A, Matrix B) {
    if (A.cols != B.rows) {
        matrix_errormsg("Ошибка: Размеры матриц не совпадают\n");
        return MATRIX_NULL;
    }

    if(A.data == NULL || B.data == NULL){
        matrix_errormsg("MATRIX_NULL");
        return MATRIX_NULL;
    }
    
    Matrix result = matrix_create(A.rows, B.cols);
    
    if(result.data == NULL){
        matrix_errormsg("MATRIX_NULL");
        return MATRIX_NULL;
    }
    
    for (int row = 0; row < A.rows; row++) {
        for (int col = 0; col < B.cols; col++) {
            result.data[row][col] = 0;
            for (int k = 0; k < A.cols; k++) {
                result.data[row][col] += A.data[row][k] * B.data[k][col];
            }
        }
    }
    
    return result;
}

// Функция для транспонирования матрицы
Matrix matrix_tr(Matrix A) {
    if(A.data == NULL){
        matrix_errormsg("MATRIX_NULL");
        return MATRIX_NULL;
    }
    
    Matrix result = matrix_create(A.cols, A.rows);
    
    if(result.data == NULL){
        matrix_errormsg("MATRIX_NULL");
        return MATRIX_NULL;
    }
    
    for (int row = 0; row < A.rows; row++) {
        for (int col = 0; col < A.cols; col++) {
            result.data[col][row] = A.data[row][col];
        }
    }
    
    return result;
}

// Функция для вычисления детерминанта матрицы (простой метод для квадратных матриц)
double matrix_det(Matrix A) {
    if (A.rows != A.cols) {
        matrix_errormsg("Ошибка: Матрица не является квадратной\n");
        return NAN;
    }
    
    if(A.data == NULL){
        matrix_errormsg("MATRIX_NULL");
        return NAN;
    }
    
    if (A.rows == 1) {
        return A.data[0][0];
    }
    
    if (A.rows == 2) {
        return A.data[0][0] * A.data[1][1] - A.data[0][1] * A.data[1][0];
    }

     if (A.rows == 3) {
        return A.data[0][0] * (A.data[1][1] * A.data[2][2] - A.data[1][2] * A.data[2][1]) -
               A.data[0][1] * (A.data[1][0] * A.data[2][2] - A.data[1][2] * A.data[2][0]) +
               A.data[0][2] * (A.data[1][0] * A.data[2][1] - A.data[1][1] * A.data[2][0]);
    }

    return NAN;
}

Matrix matrix_mult_scalar(Matrix A, double scalar) {
    Matrix result = matrix_create(A.rows, A.cols);
    
    if(result.data == NULL){
        matrix_errormsg("MATRIX_NULL");
        return MATRIX_NULL;
    }
        
    if(A.rows == 0 || A.cols == 0){
        return matrix_errormsg("MATRIX_NULL");
        return MATRIX_NULL;
    }
    
    for (size_t row = 0; row < A.rows; row++) {
        for (size_t col = 0; col < A.cols; col++) {
            result.data[row][col] = A.data[row][col] * scalar;
        }
    }
    return result;
}

void matrix_copy(Matrix destination, const Matrix source) 
{
    for (size_t row = 0; row < source.rows; row++) {
        for (size_t col = 0; col < source.cols; col++) {
            destination.data[row][col] = source.data[row][col];
        }
    }
}

void matrix_add_mult(Matrix A, const Matrix B) 
{
    Matrix result = matrix_create(A.rows, A.cols);
    
    if(result.data == NULL){
        matrix_errormsg("MATRIX_NULL");
        return MATRIX_NULL;
    }
    
    if(A.rows == 0 || A.cols == 0 || B.rows == 0 || B.cols == 0){
        return matrix_errormsg("MATRIX_NULL");
        return MATRIX_NULL;
    }

    for (size_t row = 0; row < A.rows; row++) {
        for (size_t col = 0; col < A.cols; col++) {
            double matrix_sum = 0.0;
            for (size_t k = 0; k < A.cols; k++) {
                matrix_sum += A.data[row][k] * B.data[k][col];
            }
            result.data[row][col] = matrix_sum;
        }
    }

    matrix_copy(A, result);
    matrix_free(result);
}

// Функция для вычисления экспоненты матрицы (простой метод для квадратных матриц)
Matrix matrix_exponent(const Matrix A, const double accuracy) 
{
    if (A.rows != A.cols) {
        matrix_errormsg("Матрица должна быть квадратной для вычисления экспоненты.");
        return MATRIX_NULL;
    }

    size_t n = A.rows;
    Matrix C = matrix_create(n, n);
    Matrix B = matrix_create(n, n);

    if (C.data == NULL || B.data == NULL) {
        matrix_free(C);
        matrix_free(B);
        return MATRIX_NULL;
    }

    matrix_copy(B, A);

    for (size_t trm = 2; trm <= accuracy; ++trm) {
        matrix_sum(B, matrix_mult_scalar(A, 1.0 / trm));
        matrix_sum(C, B);
    }

    matrix_sum(C, A);

    for (size_t diag = 0; diag < C.rows; ++diag) {
        C.data[diag][diag] += 1;
    }

    matrix_free(B);

    return C;
}
