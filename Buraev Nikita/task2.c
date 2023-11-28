#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Функция для вывода сообщения об ошибке
void matrix_errormsg(const char *errorMessage) {
    fprintf(stderr, "%s\n", errorMessage);
}

// Структура для представления матрицы
typedef struct {
    size_t rows;
    size_t cols;
    double **data;
} Matrix;

const struct Matrix MATRIX_NULL = {.cols = 0, .rows = 0, .data = NULL};

// Создать матрицу
Matrix matrix_create(size_t rows, size_t cols) {
    Matrix A;
    A.rows = rows;
    A.cols = cols;

    // Выделяем память для указателей на строки и данных матрицы одним блоком
    A.data = (double **)malloc(rows * sizeof(double *) + rows * cols * sizeof(double));
    if (!A.data) {
        return MATRIX_NULL;
        return matrix_errormsg("Ошибка выделения памяти для матрицы.");
    }

    // Устанавливаем указатели на строки
    A.data[0] = (double *)(A.data + rows);
    for (size_t row = 1; row < rows; row++) {
        A.data[row] = A.data[row - 1] + cols;
    }

    return A;
}

// Освободить память, выделенную для матрицы
void matrix_free(Matrix A)
{
    if(A.data != NULL || A.cols != 0 || A.rows != 0){

    A.cols = 0;
    A.rows = 0;
    free(A.data);
    A.data = NULL;

    }

}


// Сложение матриц
Matrix matrix_sum(Matrix A, Matrix B) {
    if (A.rows != B.rows || A.cols != B.cols) {
        return matrix_errormsg("Невозможно сложить матрицы разных размеров.");
    }

    Matrix result = matrix_create(A.rows, A.cols);
    
    if(A.rows == 0 || A.cols == 0 || B.rows == 0 || B.cols == 0){
        return matrix_errormsg("MATRIX_NULL");
        return MATRIX_NULL;
    }
    
    for (size_t row = 0; row < A.rows; row++) {
        for (size_t col = 0; col < A.cols; col++) {
            result.data[row][col] = A.data[row][col] + B.data[row][col];
        }
    }

    return result;
}

// Вычитание матриц
Matrix matrix_sub(Matrix A, Matrix B) {
    if (A.rows != B.rows || A.cols != B.cols) {
        return matrix_errormsg("Невозможно вычесть матрицы разных размеров.");
    }

    Matrix result = matrix_create(A.rows, A.cols);
    
    if(A.rows == 0 || A.cols == 0 || B.rows == 0 || B.cols == 0){
        return matrix_errormsg("MATRIX_NULL");
        return MATRIX_NULL;
    }
    
    for (size_t row = 0; row < A.rows; row++) {
        for (size_t col = 0; col < A.cols; col++) {
            result.data[row][col] = A.data[row][col] - B.data[row][col];
        }
    }

    return result;
}

// Умножение матриц
Matrix matrix_mult(Matrix A, Matrix B) {
    if (A.cols != B.rows) {
        return matrix_errormsg("Невозможно умножить матрицы с данными размерами.");
    }

    Matrix result = matrix_create(A.rows, B.cols);
    
    if(A.rows == 0 || A.cols == 0 || B.rows == 0 || B.cols == 0){
        return matrix_errormsg("MATRIX_NULL");
        return MATRIX_NULL;
    }
    
    for (size_t row = 0; row < A.rows; row++) {
        for (size_t col = 0; col < B.cols; col++) {
            result.data[row][col] = 0;
            for (size_t k = 0; k < A.cols; k++) {
                result.data[row][col] += A.data[row][k] * B.data[k][col];
            }
        }
    }

    return result;
}

// Транспонирование матрицы
Matrix matrix_tr(Matrix A) {
    Matrix result = matrix_create(A.cols, A.rows);
    
    if(A.rows == 0 || A.cols == 0){
        return matrix_errormsg("MATRIX_NULL");
        return MATRIX_NULL;
    }
    
    for (size_t row = 0; row < A.rows; row++) {
        for (size_t col = 0; col < A.cols; col++) {
            result.data[col][row] = A.data[row][col];
        }
    }

    return result;
}

// Вычисление детерминанта
double matrix_det_lu(Matrix A) {
    if (A.rows != A.cols) {
        return NAN;
        return matrix_errormsg("Детерминант можно вычислить только для квадратных матриц.");
    }
    
    if(A.rows == 0 || A.cols == 0){
        return matrix_errormsg("MATRIX_NULL");
        return MATRIX_NULL;
    }

    size_t n = A.rows;
    double det = 1.0;

    // Создаем копию матрицы, чтобы не изменять исходную
    Matrix copy = matrix_create(n, n);
    for (size_t row = 0; row < n; row++) {
        for (size_t col = 0; col < n; col++) {
            copy.data[row][col] = A.data[row][col];
        }
    }

    for (size_t k = 0; k < n - 1; k++) {
        if (copy.data[k][k] == 0.0) {
            return NAN;
            return matrix_errormsg("Найдено деление на ноль при вычислении детерминанта.");
        }
        for (size_t i = k + 1; i < n; i++) {
            double factor = copy.data[i][k] / copy.data[k][k];
            for (size_t j = k; j < n; j++) {
                copy.data[i][j] -= factor * copy.data[k][j];
            }
        }
    }

    for (size_t i = 0; i < n; i++) {
        det *= copy.data[i][i];
    }

    // Освобождаем память для копии матрицы
    matrix_free(copy);

    return det;
}

// Проверка на нулевую матрицу
int matrix_is_zero(Matrix A) {
    for (size_t row = 0; row < A.rows; row++) {
        for (size_t col = 0; col < A.cols; col++) {
            if (A.data[row][col] != 0.0) {
                return 0; // Не нулевая матрица
            }
        }
    }
    return 1; // Нулевая матрица
}

// Умножение матрицы на скаляр
Matrix matrix_mult_scalar(Matrix A, double scalar) {
    Matrix result = matrix_create(A.rows, A.cols);
        
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

// Функция для копирования матрицы
void matrix_copy(Matrix destination, const Matrix source) {
    for (size_t row = 0; row < source.rows; row++) {
        for (size_t col = 0; col < source.cols; col++) {
            destination.data[row][col] = source.data[row][col];
        }
    }
}

// Функция для прибавления к матрице произведения двух матриц
void matrix_add_mult(Matrix A, const Matrix B) {
    Matrix result = matrix_create(A.rows, A.cols);
    
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

// Функция для вычисления экспоненты матрицы методом Тейлора
Matrix matrix_exponent(const Matrix A, const double accuracy) {
    if (A.rows != A.cols) {
        matrix_errormsg("Матрица должна быть квадратной для вычисления экспоненты.");
        return matrix_create(0, 0); // Возвращаем нулевую матрицу
    }

    size_t n = A.rows;
    Matrix C = matrix_create(n, n);
    Matrix B = matrix_create(n, n);

    if (C.data == NULL || B.data == NULL) {
        matrix_free(C);
        matrix_free(B);
        return matrix_create(0, 0); // Возвращаем нулевую матрицу
    }

    matrix_copy(B, A);

    int degree = (int)(ceil(1.0 / accuracy));

    for (int trm = 2; trm <= degree; ++trm) {
        addMatrix(B, matrix_mult_scalar(A, 1.0 / trm));
        addMatrix(C, B);
    }

    matrix_sum(C, A);

    for (size_t diag = 0; diag < C.rows; ++diag) {
        C.data[diag][diag] += 1;
    }

    matrix_free(B);

    return C;
}
