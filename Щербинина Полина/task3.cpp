#include <iostream>
#include <cmath>
#include <vector>

class Matrix {
public:
    int rows;
    int cols;
    std::vector<std::vector<double>> data;

    Matrix() : rows(0), cols(0) {}

    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        data.resize(rows, std::vector<double>(cols));
    }

    void resize(int new_rows, int new_cols) {
        rows = new_rows;
        cols = new_cols;
        data.resize(new_rows, std::vector<double>(new_cols));
    }

    void print() const {
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                std::cout << data[row][col] << "\t";
            }
            std::cout << std::endl;
        }
    }

    static Matrix create(int rows, int cols) {
        Matrix A(rows, cols);
        return A;
    }

    static void free(Matrix& A) {
        A.data.clear();
    }

    static Matrix sum(const Matrix& A, const Matrix& B) {
        if (A.rows != B.rows || A.cols != B.cols) {
            std::cout << "Ошибка: Размеры матриц не совпадают" << std::endl;
            return create(0, 0);
        }
        Matrix result(A.rows, A.cols);
        for (int row = 0; row < A.rows; row++) {
            for (int col = 0; col < A.cols; col++) {
                result.data[row][col] = A.data[row][col] + B.data[row][col];
            }
        }
        return result;
    }

    static Matrix sub(const Matrix& A, const Matrix& B) {
        if (A.rows != B.rows || A.cols != B.cols) {
            std::cout << "Ошибка: Размеры матриц не совпадают" << std::endl;
            return create(0, 0);
        }
        Matrix result(A.rows, A.cols);
        for (int row = 0; row < A.rows; row++) {
            for (int col = 0; col < A.cols; col++) {
                result.data[row][col] = A.data[row][col] - B.data[row][col];
            }
        }
        return result;
    }

    static Matrix mult(const Matrix& A, const Matrix& B) {
        if (A.cols != B.rows) {
            std::cout << "Ошибка: Невозможно умножить матрицы" << std::endl;
            return create(0, 0);
        }
        Matrix result(A.rows, B.cols);
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

    static Matrix transpose(const Matrix& A) {
        Matrix result(A.cols, A.rows);
        for (int row = 0; row < A.rows; row++) {
            for (int col = 0; col < A.cols; col++) {
                result.data[col][row] = A.data[row][col];
            }
        }
        return result;
    }

    static double determinant(const Matrix& A) {
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
            Matrix submat(A.rows - 1, A.cols - 1);
            for (int row = 1; row < A.rows; row++) {
                for (int k = 0; k < A.cols; k++) {
                    if (k < col) {
                        submat.data[row - 1][k] = A.data[row][k];
                    } else if (k > col) {
                        submat.data[row - 1][k - 1] = A.data[row][k];
                    }
                }
            }
            determinant += A.data[0][col] * determinant(submat) * (col % 2 == 0 ? 1 : -1);
            free(submat);
        }
        return determinant;
    }

    static Matrix matrixExp(const Matrix& A, int n) {
        if (A.rows != A.cols) {
            std::cout << "Ошибка: Матрица не является квадратной" << std::endl;
            return create(0, 0);
        }
        Matrix result(A.rows, A.cols);
        Matrix temp(A.rows, A.cols);
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
        free(temp);
        return result;
    }
};

int main() {
    // Example usage of the Matrix class
    Matrix A = Matrix::create(2, 2);
    A.data = {{1, 2}, {3, 4}};
    Matrix B = Matrix::create(2, 2);
    B.data = {{5, 6}, {7, 8}};

    Matrix C = Matrix::sum(A, B);
    std::cout << "Sum of matrices A and B:\n";
    C.print();

    Matrix D = Matrix::mult(A, B);
    std::cout << "Product of matrices A and B:\n";
    D.print();

    return 0;
}
