#include <iostream>
#include <cmath>
#include <vector>

struct Matrix {
    int rows;
    int cols;
    std::vector<std::vector<double>> data;
};

Matrix create_matrix(int rows, int cols) {
    Matrix A;
    A.rows = rows;
    A.cols = cols;
    A.data.resize(rows, std::vector<double>(cols));
    return A;
}

void free_matrix(Matrix& A) {
    A.data.clear();
}

void print_matrix(const Matrix& A) {
    for (int row = 0; row < A.rows; row++) {
        for (int col = 0; col < A.cols; col++) {
            std::cout << A.data[row][col] << "\t";
        }
        std::cout << std::endl;
    }
}

Matrix sum(const Matrix& A, const Matrix& B) {
    if (A.rows != B.rows || A.cols != B.cols) {
        std::cout << "Ошибка: Размеры матриц не совпадают" << std::endl;
        return create_matrix(0, 0);
    }
    Matrix result = create_matrix(A.rows, A.cols);
    for (int row = 0; row < A.rows; row++) {
        for (int col = 0; col < A.cols; col++) {
            result.data[row][col] = A.data[row][col] + B.data[row][col];
        }
    }
    return result;
}

Matrix sub(const Matrix& A, const Matrix& B) {
    if (A.rows != B.rows || A.cols != B.cols) {
        std::cout << "Ошибка: Размеры матриц не совпадают" << std::endl;
        return create_matrix(0, 0);
    }
    Matrix result = create_matrix(A.rows, A.cols);
    for (int row = 0; row < A.rows; row++) {
        for (int col = 0; col < A.cols; col++) {
            result.data[row][col] = A.data[row][col] - B.data[row][col];
        }
    }
    return result;
}

Matrix mult(const Matrix& A, const Matrix& B) {
    if (A.cols != B.rows) {
        std::cout << "Ошибка: Невозможно умножить матрицы" << std::endl;
        return create_matrix(0, 0);
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

Matrix tr(const Matrix& A) {
    Matrix result = create_matrix(A.cols, A.rows);
    for (int row = 0; row < A.rows; row++) {
        for (int col = 0; col < A.cols; col++) {
            result.data[col][row] = A.data[row][col];
        }
    }
    return result;
}

double det(const Matrix& A) {
    if (A.rows != A.cols) {
        std::cout << "Ошибка: Матрица не является квадратной" << std::endl;
        return NAN;
    }
    if (A.rows == 1) {
        return A.data[0][0];
    }
    if (A.rows == 2) {
        return A.data[0][0] * A.data[1][1] - A.data[0][1] * A.data[1][0];
    }
    double determinant = 0;
    for (int col = 0; col < A.cols; col++) {
        Matrix submat = create_matrix(A.rows - 1, A.cols - 1);
        for (int row = 1; row < A.rows; row++) {
            for (int k = 0; k < A.cols; k++) {
                if (k < col) {
                    submat.data[row - 1][k] = A.data[row][k];
                } else if (k > col) {
                    submat.data[row - 1][k - 1] = A.data[row][k];
                }
            }
        }
        determinant += A.data[0][col] * det(submat) * (col % 2 == 0 ? 1 : -1);
        free_matrix(submat);
    }
    return determinant;
}

Matrix A_exp(const Matrix& A, int n) {
    if (A.rows != A.cols) {
        std::cout << "Ошибка: Матрица не является квадратной" << std::endl;
        return create_matrix(0, 0);
    }
    Matrix result = create_matrix(A.rows, A.cols);
    Matrix temp = create_matrix(A.rows, A.cols);
    for (int row = 0; row < A.rows; row++) {
        for (int col = 0; col < A.cols; col++) {             
            if (row == col) {
                result.data[row][col] = 1;
                temp.data[row][col] = A.data[row][col];
            } else {
                result.data[row][col] = 0;
                temp.data[row][col] = 0;
            }
        }
    }
    for (int k = 1; k <= n; k++) {
        for (int row = 0; row < A.rows; row++) {
            for (int col = 0; col < A.cols; col++) {
                for (int p = 0; p < A.cols; p++) {
                    temp.data[row][col] += (A.data[row][p] * result.data[p][col]);
                }
            }
        }
        Matrix temp2 = result;
        result = temp;
        temp = temp2;
    }
    free_matrix(temp);
    return result;
}


