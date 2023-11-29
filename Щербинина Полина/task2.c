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
Matrix create_matrix(int rows, int cols) {
    Matrix A;
    A.rows = rows;
    A.cols = cols;
    
    A.data = (double **)malloc(rows * sizeof(double *) + rows * cols * sizeof(double));
    if (!A.data) {
        return matrix_errormsg("Ошибка выделения памяти матрицы.");
        return MATRIX_NULL;
    }
    
    return A;
}

// Функция для освобождения памяти, выделенной под матрицу
void free_matrix(Matrix A)
{
    if(A.data != NULL || A.cols != 0 || A.rows != 0){

    A.cols = 0;
    A.rows = 0;
    free(A.data);
    A.data = NULL;

    }

}

// Функция для вывода матрицы на экран
void print_matrix(Matrix A) {
    for (int row = 0; row < A.rows; row++) {
        for (int col = 0; col < A.cols; col++) {
            printf("%lf\t", A.data[row][col]);
        }
        printf("\n");
    }
}

// Функция для сложения двух матриц
Matrix sum(Matrix A, Matrix B) 
{
    if (A.rows != B.rows || A.cols != B.cols) {
        return matrix_errormsg("Ошибка: Размеры матриц не совпадают\n");
        return MATRIX_NULL;
    } 
    
    // функция проверки создания матриц
    if(A.rows == 0 || A.cols == 0 || B.rows == 0 || B.cols == 0){
        return matrix_errormsg("MATRIX_NULL");
        return MATRIX_NULL;
    }
 
    Matrix result = create_matrix(A.rows, B.cols);
    for (int row = 0; row < A.rows; row++) {
        for (int col = 0; col < B.cols; col++) {
            result.data[row][col] = A.data[row][col] + B.data[row][col];
        }
    }
    
    return result;
}

// Функция для вычитания двух матриц
Matrix sub(Matrix A, Matrix B) {
    if (A.rows != B.rows || A.cols != B.cols) {
        return matrix_errormsg("Ошибка: Размеры матриц не совпадают\n");
        return MATRIX_NULL;
    }

    if(A.rows == 0 || A.cols == 0 || B.rows == 0 || B.cols == 0){
        return matrix_errormsg("MATRIX_NULL");
        return MATRIX_NULL;
    }
    
    Matrix result = create_matrix(A.rows, A.cols);
    
    for (int row = 0; row < A.rows; row++) {
        for (int col = 0; col < B.cols; col++) {
            result.data[row][col] = A.data[row][col] - B.data[row][col];
        }
    }
    
    return result;
}

// Функция для умножения двух матриц
Matrix mult(Matrix A, Matrix B) {
    if (A.cols != B.rows) {
        return matrix_errormsg("Ошибка: Размеры матриц не совпадают\n");
        return MATRIX_NULL;
    }

    if(A.rows == 0 || A.cols == 0 || B.rows == 0 || B.cols == 0){
        return matrix_errormsg("MATRIX_NULL");
        return MATRIX_NULL;
    }
    
    Matrix result = create_matrix(A.rows, B.cols);
    
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
Matrix tr(Matrix A) {
    if(A.rows == 0 || A.cols == 0){
        return matrix_errormsg("MATRIX_NULL");
        return MATRIX_NULL;
    }
    
    Matrix result = create_matrix(A.cols, A.rows);
    
    for (int row = 0; row < A.rows; row++) {
        for (int col = 0; col < A.cols; col++) {
            result.data[col][row] = A.data[row][col];
        }
    }
    
    return result;
}

// Функция для вычисления детерминанта матрицы (простой метод для квадратных матриц)
double det(Matrix A) {
    if (A.rows != A.cols) {
        return matrix_errormsg("Ошибка: Матрица не является квадратной\n");
        return NAN;
    }
    
    if(A.rows == 0 || A.cols == 0){
        return matrix_errormsg("MATRIX_NULL");
        return MATRIX_NULL;
    }
    
    if (A.rows == 1) {
        return A.data[0][0];
    }
    
    if (A.rows == 2) {
        return A.data[0][0] * A.data[1][1] - A.data[0][1] * A.data[1][0];
    }
    
    return det;
}

// Функция для вычисления экспоненты матрицы (простой метод для квадратных матриц)
Matrix matrix_exponent(const Matrix A, const double accuracy) 
{
    if (A.rows != A.cols) {
        return matrix_errormsg("Матрица должна быть квадратной для вычисления экспоненты.");
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

    int degree = (int)(ceil(1.0 / accuracy));

    for (int trm = 2; trm <= degree; ++trm) {
        add_matrix(B, matrix_mult_scalar(A, 1.0 / trm));
        add_matrix(C, B);
    }

    matrix_sum(C, A);

    for (size_t diag = 0; diag < C.rows; ++diag) {
        C.data[diag][diag] += 1;
    }

    matrix_free(B);

    return C;
}
