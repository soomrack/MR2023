#include <iostream>
#include <cmath>
#include <vector>

class Matrix {
public:
    // Конструктор по умолчанию
    Matrix() : rows(0), cols(0) {}

    // Конструктор с параметрами
    Matrix(size_t rows, size_t cols) : rows(rows), cols(cols), data(rows, std::vector<double>(cols, 0.0)) {}

    // Конструктор копирования
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols), data(other.data) {}

    // Деструктор
    ~Matrix() {}

    // Перегруженный оператор присваивания
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            rows = other.rows;
            cols = other.cols;
            data = other.data;
        }
        return *this;
    }

    // Сложение матриц
    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            errorMsg("Невозможно сложить матрицы разных размеров.");
            return Matrix();
        }
        Matrix result(rows, cols);
        for (size_t row = 0; row < rows; ++row) {
            for (size_t col = 0; col < cols; ++col) {
                result.data[row][col] = data[row][col] + other.data[row][col];
            }
        }
        return result;
    }

    // Вычитание матриц
    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            errorMsg("Невозможно вычесть матрицы разных размеров.");
            return Matrix();
        }
        Matrix result(rows, cols);
        for (size_t row = 0; row < rows; ++row) {
            for (size_t col = 0; col < cols; ++col) {
                result.data[row][col] = data[row][col] - other.data[row][col];
            }
        }
        return result;
    }

    // Умножение матриц
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            errorMsg("Невозможно умножить матрицы с данными размерами.");
            return Matrix();
        }
        Matrix result(rows, other.cols);
        for (size_t row = 0; row < rows; ++row) {
            for (size_t col = 0; col < other.cols; ++col) {
                result.data[row][col] = 0;
                for (size_t k = 0; k < cols; ++k) {
                    result.data[row][col] += data[row][k] * other.data[k][col];
                }
            }
        }
        return result;
    }

    // Транспонирование матрицы
    Matrix transpose() const {
        Matrix result(cols, rows);
        for (size_t row = 0; row < rows; ++row) {
            for (size_t col = 0; col < cols; ++col) {
                result.data[col][row] = data[row][col];
            }
        }
        return result;
    }

    // Вычисление детерминанта
    double determinantLU() const {
        if (rows != cols) {
            errorMsg("Детерминант можно вычислить только для квадратных матриц.");
            return NAN;
        }
        size_t n = rows;
        double det = 1.0;
        Matrix copy(*this);
        for (size_t k = 0; k < n - 1; ++k) {
            if (copy.data[k][k] == 0.0) {
                errorMsg("Найдено деление на ноль при вычислении детерминанта.");
                return NAN;
            }
            for (size_t i = k + 1; i < n; ++i) {
                double factor = copy.data[i][k] / copy.data[k][k];
                for (size_t j = k; j < n; ++j) {
                    copy.data[i][j] -= factor * copy.data[k][j];
                }
            }
        }
        for (size_t i = 0; i < n; ++i) {
            det *= copy.data[i][i];
        }
        return det;
    }

    // Проверка на нулевую матрицу
    bool isZeroMatrix() const {
        for (size_t row = 0; row < rows; ++row) {
            for (size_t col = 0; col < cols; ++col) {
                if (data[row][col] != 0.0) {
                    return false; // Не нулевая матрица
                }
            }
        }
        return true; // Нулевая матрица
    }

    // Умножение матрицы на скаляр
    Matrix operator*(double scalar) const {
        Matrix result(rows, cols);
        for (size_t row = 0; row < rows; ++row) {
            for (size_t col = 0; col < cols; ++col) {
                result.data[row][col] = data[row][col] * scalar;
            }
        }
        return result;
    }

private:
    size_t rows;
    size_t cols;
    std::vector<std::vector<double>> data;

    // Функция для вывода сообщения об ошибке и возврата NaN
    void errorMsg(const char* errorMessage) const {
        std::cerr << errorMessage << std::endl;
    }
};

// Функция для вычисления экспоненты матрицы методом Тейлора
Matrix matrix_exponent(const Matrix& A, const double accuracy) {
    if (A.rows != A.cols) {
        errorExit("Матрица должна быть квадратной для вычисления экспоненты.");
    }
    size_t n = A.rows;
    Matrix C(n, n);
    Matrix B(A);
    int degree = static_cast<int>(ceil(1.0 / accuracy));
    for (int trm = 2; trm <= degree; ++trm) {
        B = B * A;
        B = B * (1.0 / trm);
        C = C + B;
    }
    C = C + A;
    for (size_t diag = 0; diag < C.rows; ++diag) {
        C.data[diag][diag] += 1;
    }
    return C;
}
