#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Функция для вывода сообщения об ошибке и возврата NaN
double errorMsg(const char *errorMessage) {
    fprintf(stderr, "%s\n", errorMessage);
    return NAN;
}

// Структура для представления матрицы
typedef struct {
    size_t rows;
    size_t cols;
    double **data;
} Matrix;

// Создать матрицу
Matrix createMatrix(size_t rows, size_t cols) {
    Matrix A;
    A.rows = rows;
    A.cols = cols;

    // Выделяем память для указателей на строки и данных матрицы одним блоком
    A.data = (double **)malloc(rows * sizeof(double *) + rows * cols * sizeof(double));
    if (!A.data) {
        return errorMsg("Ошибка выделения памяти для матрицы.");
    }

    // Устанавливаем указатели на строки
    A.data[0] = (double *)(A.data + rows);
    for (size_t row = 1; row < rows; row++) {
        A.data[row] = A.data[row - 1] + cols;
    }

    return A;
}

// Освободить память, выделенную для матрицы
void freeMatrix(Matrix A) {
    free(A.data);
}

// Сложение матриц
Matrix sum(Matrix A, Matrix B) {
    if (A.rows != B.rows || A.cols != B.cols) {
        return errorMsg("Невозможно сложить матрицы разных размеров.");
    }

    Matrix result = createMatrix(A.rows, A.cols);

    for (size_t row = 0; row < A.rows; row++) {
        for (size_t col = 0; col < A.cols; col++) {
            result.data[row][col] = A.data[row][col] + B.data[row][col];
        }
    }

    return result;
}

// Вычитание матриц
Matrix sub(Matrix A, Matrix B) {
    if (A.rows != B.rows || A.cols != B.cols) {
        return errorMsg("Невозможно вычесть матрицы разных размеров.");
    }

    Matrix result = createMatrix(A.rows, A.cols);

    for (size_t row = 0; row < A.rows; row++) {
        for (size_t col = 0; col < A.cols; col++) {
            result.data[row][col] = A.data[row][col] - B.data[row][col];
        }
    }

    return result;
}

// Умножение матриц
Matrix mult(Matrix A, Matrix B) {
    if (A.cols != B.rows) {
        return errorMsg("Невозможно умножить матрицы с данными размерами.");
    }

    Matrix result = createMatrix(A.rows, B.cols);

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
Matrix tr(Matrix A) {
    Matrix result = createMatrix(A.cols, A.rows);

    for (size_t row = 0; row < A.rows; row++) {
        for (size_t col = 0; col < A.cols; col++) {
            result.data[col][row] = A.data[row][col];
        }
    }

    return result;
}

// Вычисление детерминанта
double detLU(Matrix A) {
    if (A.rows != A.cols) {
        return errorMsg("Детерминант можно вычислить только для квадратных матриц.");
    }

    size_t n = A.rows;
    double det = 1.0;

    // Создаем копию матрицы, чтобы не изменять исходную
    Matrix copy = createMatrix(n, n);
    for (size_t row = 0; row < n; row++) {
        for (size_t col = 0; col < n; col++) {
            copy.data[row][col] = A.data[row][col];
        }
    }

    for (size_t k = 0; k < n - 1; k++) {
        if (copy.data[k][k] == 0.0) {
            return errorMsg("Найдено деление на ноль при вычислении детерминанта.");
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
    freeMatrix(copy);

    return det;
}

// Проверка на нулевую матрицу
int isZeroMatrix(Matrix A) {
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
Matrix multScalar(Matrix A, double scalar) {
    Matrix result = createMatrix(A.rows, A.cols);
    for (size_t row = 0; row < A.rows; row++) {
        for (size_t col = 0; col < A.cols; col++) {
            result.data[row][col] = A.data[row][col] * scalar;
        }
    }
    return result;
}

// Функция для вычисления экспоненты матрицы методом Тейлора
Matrix matrix_exponent(const Matrix A, const double accuracy) {
    if (A.rows != A.cols) {
        errorExit("Матрица должна быть квадратной для вычисления экспоненты.");
    }

    size_t n = A.rows;
    Matrix C = createMatrix(n, n);
    Matrix B = createMatrix(n, n);
    copyMatrix(B, A);

    int degree = (int)(ceil(1.0 / accuracy));

    for (int trm = 2; trm <= degree; ++trm) {
        addMultMatrix(B, A);
        multMatrixByScalar(B, 1.0 / trm);
        addMatrix(C, B);
    }

    addMatrix(C, A);

    for (size_t diag = 0; diag < C.rows; ++diag) {
        C.data[diag][diag] += 1;
    }

    freeMatrix(B);

    return C;
}
