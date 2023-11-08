#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Функция для вывода сообщения об ошибке и выхода из программы
void errorExit(const char *errorMessage) {
    fprintf(stderr, "%s\n", errorMessage);
    exit(1);
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
        errorExit("Ошибка выделения памяти для матрицы.");
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
        errorExit("Невозможно сложить матрицы разных размеров.");
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
        errorExit("Невозможно вычесть матрицы разных размеров.");
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
        errorExit("Невозможно умножить матрицы с данными размерами.");
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
        fprintf(stderr, "Детерминант можно вычислить только для квадратных матриц.\n");
        exit(1);
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

/* Проверка на нулевую матрицу
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
*/

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

// Функция для вычисления экспоненты матрицы методом Паде
Matrix expmPade(Matrix A, int order) {
    if (A.rows != A.cols) {
        errorExit("Матрица должна быть квадратной для вычисления экспоненты.");
    }

    size_t n = A.rows;
    Matrix X = createMatrix(n, n);
    Matrix Y = createMatrix(n, n);
    Matrix D = createMatrix(n, n);
    Matrix N = createMatrix(n, n);
    Matrix temp = createMatrix(n, n);

    int j, k;
    for (j = 1; j <= order; j++) {
        k = 2 * j - 1;
        A = mult(A, A);
        D = mult(A, D);
        N = mult(A, N);
        temp = mult(A, temp);
        D = sum(D, temp);
        temp = mult(A, temp);
        N = sum(N, temp);
    }

    for (j = 1; j <= order; j++) {
        k = 2 * j - 1;
        A = mult(A, A);
        X = sum(X, multScalar(A, 1.0 / (k * k) / D));
        Y = sum(Y, multScalar(A, 1.0 / (k * k) / N));
    }

    Matrix result = sub(X, Y);

    freeMatrix(X);
    freeMatrix(Y);
    freeMatrix(D);
    freeMatrix(N);
    freeMatrix(temp);

    return result;
}

/* Экспоненциальная функция для матрицы
Matrix expm(Matrix A) {
    size_t n = A.rows;
    Matrix result = createMatrix(n, n);

    for (size_t row = 0; row < n; row++) {
        for (size_t col = 0; col < n; col++) {
            result.data[row][col] = (row == col) ? 1.0 : 0.0;
        }
    }

    Matrix term = createMatrix(n, n);
    Matrix tmp = createMatrix(n, n);

    double factorial = 1.0;
    size_t k = 0;

    for (size_t row = 0; row < n; row++) {
        for (size_t col = 0; col < n; col++) {
            term.data[row][col] = A.data[row][col];
        }
    }

    while (1) {
        tmp = createMatrix(n, n);
        for (size_t row = 0; row < n; row++) {
            for (size_t col = 0; col < n; col++) {
                tmp.data[row][col] = 0;
                for (size_t l = 0; l < n; l++) {
                    tmp.data[row][col] += term.data[row][l] * A.data[l][col];
                }
            }
        }

        for (size_t row = 1; row <= k; row++) {
            tmp = mult(tmp, A);
        }

        for (size_t row = 1; row <= k; row++) {
            factorial *= row;
        }

        double termFactor = 1.0 / factorial;
        tmp = multScalar(tmp, termFactor);

        tmp = sum(result, tmp);
        freeMatrix(result);
        result = tmp;

        if (isZeroMatrix(tmp)) {
            break;
        }

        k++;
        factorial = 1.0;
    }

    freeMatrix(term);
    freeMatrix(tmp);

    return result;
}
*/

int main() {
    // Ваш код
    return 0;
}