#pragma once
#include <ctime>
#include <iostream>
#include <windows.h>
#include <cmath>
#include <stdexcept>

const double EPS = 1e-6;

class MatrixException : public std::domain_error {
public:
    MatrixException(const char* const& msg) : domain_error(msg) {}
};

MatrixException notSquare("Error: the matrix must be square (should have nxn size)\n");
MatrixException notEqual("Error: the matrix should have the same size\n");
MatrixException multiplyError("Error: first matrix cols not equal to the second matrix row.\n");
MatrixException zeroDivision("Error: divide by zero\n");
MatrixException memError("Error: memory is not allocated\n");
MatrixException emptyMatrix("Error: Function can't return an empty matrix\n");
MatrixException sizeError("Error: size error\n");

class Matrix {
private:
    size_t rows;
    size_t cols;
    double* data;

public:
    Matrix(size_t rows, size_t cols, double* data);
    Matrix(size_t rows, size_t cols);
    Matrix();
    ~Matrix();
    Matrix(const Matrix& a);
    Matrix(Matrix&& a) noexcept;

public:
    void matrixPrint();

    size_t getRows();
    size_t getCols();
    double* getData();

    void setZero();
    void setIdentity();
    void transpose();
    Matrix exponent(const size_t step = 100);
    Matrix minor(const unsigned int minorRow, const unsigned int minorCol);
    Matrix reverse(const Matrix* matrix);

    double determinant(const Matrix* matrix);

    Matrix& operator=(Matrix&& a) noexcept;
    Matrix& operator=(const Matrix& a);
    void operator+=(const Matrix& a);
    void operator-=(const Matrix& a);
    void operator*=(const double k);
    void operator/=(const double k);
    void operator*=(const Matrix& a);

    Matrix operator+(const Matrix& a);
    Matrix operator-(const Matrix& a);
    Matrix operator*(const Matrix& a);
    Matrix operator*(const double k);
    Matrix operator/(const double k);

    bool operator!=(const Matrix& a);
    bool operator==(const Matrix& a);
    friend std::ostream& operator<<(std::ostream& out, const Matrix);
};

Matrix::Matrix() : rows(0), cols(0), data(nullptr) {}

Matrix::Matrix(const Matrix& matrix) {
    rows = matrix.rows;
    cols = matrix.cols;
    data = new double[rows * cols];
    memcpy(data, matrix.data, rows * cols * sizeof(double));
}

Matrix::Matrix(size_t numRows, size_t numCols) {
    if (numRows >= SIZE_MAX / sizeof(double) / numCols) {
        throw sizeError;
    }
    rows = numRows;
    cols = numCols;
    data = new double[rows * cols];
}

Matrix::Matrix(size_t numRows, size_t numCols, double* array) {
    rows = numRows;
    cols = numCols;
    data = new double[rows * cols];
    memcpy(data, array, rows * cols * sizeof(double));
}

Matrix::Matrix(Matrix&& mat) noexcept : data(mat.data), rows(mat.rows), cols(mat.cols) {
    mat.data = nullptr;
    mat.rows = 0;
    mat.cols = 0;
}

std::ostream& operator<<(std::ostream& out, const Matrix matrix) {
    for (size_t row = 0; row < matrix.rows; row++) {
        for (size_t col = 0; col < matrix.cols; col++) {
            out << matrix.data[row * matrix.cols + col] << "\t";
        }
        out << std::endl;
    }
    out << std::endl;
    return (out);
}

bool Matrix::operator==(const Matrix& a, double eps) {
    if (cols != a.cols || rows != a.rows)
        return false;
    for (unsigned int idx = 0; idx < cols * rows; idx++) {
        if (abs(data[idx] - a.data[idx]) > eps)
            return false;
    }
    return true;
}


void Matrix::setZero() {
    if (data != nullptr)
        memset(data, 0, rows * cols * sizeof(double));
}

void Matrix::setIdentity() {
    setZero();
    for (unsigned int idx = 0; idx < cols * rows; idx += rows + 1) {
        data[idx] = 1.0;
    }
}

void Matrix::transpose() {
    Matrix trans(cols, rows);
    for (unsigned int row = 0; row < trans.rows; row++) {
        for (unsigned int col = 0; col < trans.cols; col++) {
            trans.data[row * trans.cols + col] = data[col * trans.rows + row];
        }
    }
    *this = trans;
}

size_t Matrix::getRows() {
    return rows;
}

size_t Matrix::getCols() {
    return cols;
}

Matrix& Matrix::minor(const unsigned int minorRow, const unsigned int minorCol) {
    if (rows == 0 || cols == 0) {
        throw emptyMatrix;
    }
    Matrix* minor = new Matrix(rows - 1, cols - 1);
    unsigned int minorIndex = 0;
    for (unsigned int row = 0; row < rows; row++) {
        for (unsigned int col = 0; col < cols; col++) {
            if (row == minorRow || col == minorCol)
                continue;
            minor->data[minorIndex++] = data[row * cols + col];
        }
    }
    return *minor;
}

void Matrix::operator+=(const Matrix& matrix) {
    if (rows != matrix.rows || cols != matrix.cols)
        throw notEqual;
    for (unsigned int index = 0; index < rows * cols; ++index) {
        data[index] += matrix.data[index];
    }
}

void Matrix::operator-=(const Matrix& matrix) {
    if (rows != matrix.rows || cols != matrix.cols)
        throw notEqual;
    for (unsigned int index = 0; index < rows * cols; ++index) {
        data[index] -= matrix.data[index];
    }
}

void Matrix::operator*=(const double k) {
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        data[idx] *= k;
    }
}

void Matrix::operator/=(const double k) {
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        data[idx] /= k;
    }
}

void Matrix::operator*=(const Matrix& matrix) {
    if (cols != matrix.rows)
        throw multiplyError;

    Matrix multiplication(rows, matrix.cols);
    for (unsigned int row = 0; row < multiplication.rows; row++) {
        for (unsigned int col = 0; col < multiplication.cols; col++) {
            double sum = 0;
            for (unsigned int k = 0; k < matrix.rows; k++) {
                sum += data[row * cols + k] * matrix.data[k * matrix.cols + col];
            }
            multiplication.data[row * multiplication.cols + col] = sum;
        }
    }
    *this = multiplication;
}

Matrix& Matrix::operator=(const Matrix& a) {
    if (this == &a)
        return *this;

    if (rows * cols == a.rows * a.cols) {
        rows = a.rows;
        cols = a.cols;
        memcpy(data, a.data, rows * cols * sizeof(double));
        return *this;
    }
    delete[] data;
    rows = a.rows;
    cols = a.cols;
    data = new double[rows * cols];
    memcpy(data, a.data, rows * cols * sizeof(double));
    return *this;
}

Matrix& Matrix::operator=(Matrix&& a) noexcept {
    delete[] data;
    rows = a.rows;
    cols = a.cols;
    data = a.data;
    a.data = nullptr;
    a.rows = 0;
    a.cols = 0;
    return *this;
}

Matrix& Matrix::operator+(const Matrix& b) {
    Matrix* add = new Matrix(*this);
    *add += b;
    return *add;
}

Matrix& Matrix::operator-(const Matrix& b) {
    Matrix* sub = new Matrix(*this);
    *sub -= b;
    return *sub;
}

Matrix& Matrix::operator*(const double k) {
    Matrix* multiply = new Matrix(*this);
    *multiply *= k;
    return *multiply;
}

Matrix& Matrix::operator*(const Matrix& b) {
    Matrix* multiply = new Matrix(*this);
    *multiply *= b;
    return *multiply;
}

Matrix& Matrix::operator/(const double k) {
    Matrix* multiply = new Matrix(*this);
    *multiply /= k;
    return *multiply;
}

double Matrix::determinant(const Matrix* matrix) {
    if (matrix->rows != matrix->cols)
        throw notSquare;
    double det = 0;
    int k = 1;
    if (matrix->rows == 0)
        return NAN;
    if (matrix->rows == 1)
        return matrix->data[0];
    if (matrix->rows == 2) {
        return (matrix->data[0] * matrix->data[3] - matrix->data[2] * matrix->data[1]);
    }
    for (unsigned int idx = 0; idx < matrix->cols; idx++) {
        Matrix temp = minor(0, idx);
        det += k * matrix->data[idx] * determinant(&temp);
        k = -k;
    }
    return det;
}

Matrix& Matrix::reverse(const Matrix* matrix) {
    double d = determinant(matrix);
    if (matrix->rows != matrix->cols)
        throw notSquare;
    if (fabs(d) < EPS)
        throw zeroDivision;
    Matrix* reverse = new Matrix(matrix->rows, matrix->cols);
    int k = 1;
    for (unsigned int row = 0; row < reverse->rows; row++) {
        for (unsigned int col = 0; col < reverse->cols; col++) {
            Matrix temp = minor(row, col);
            reverse->data[row * matrix->cols + col] = k * determinant(&temp);
            k = -k;
        }
    }
    reverse->transpose();
    *reverse /= d;
    return *reverse;
}

Matrix& Matrix::exponent(const size_t accuracy) {
    if (cols != rows) {
        throw notSquare;
    }

    Matrix sum = Matrix(rows, cols);
    sum.setIdentity();

    Matrix* exp = new Matrix(sum);
    for (size_t degAcc = 1; degAcc <= accuracy; ++degAcc) {
        sum = sum * (*this) / degAcc;
        *exp += sum;
    }

    return *exp;
}
