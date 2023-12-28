#include "matrix.hpp"
#include <cmath>
#include <iostream>
#include <vector>

Matrix::Matrix() : rows(0), cols(0)
{
}

Matrix::Matrix(const Matrix& other)
    : rows(other.rows), cols(other.cols), data(other.data)
{
}

Matrix::Matrix(size_t rows, size_t cols)
    : rows(rows), cols(cols), data(rows, std::vector<int>(cols, 0))
{
}

Matrix::Matrix(Matrix&& other) noexcept
    : rows(std::exchange(other.rows, 0)), cols(std::exchange(other.cols, 0)),
    data(std::move(other.data))
{
}

Matrix::Matrix(std::initializer_list<std::initializer_list<int>> list)
{
    rows = list.size();
    cols = list.begin()->size();

    data.reserve(rows);
    for (const auto& row : list) {
        data.emplace_back(row);
    }
}

Matrix* Matrix::operator+(const Matrix& other) const
{
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument(
            "Matrix dimensions do not match for addition");
    }

    auto result = new Matrix(rows, cols);

    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            result->data[row][col] = data[row][col] + other.data[row][col];
        }
    }

    return result;
}

Matrix* Matrix::operator*(const Matrix& other) const
{
    if (cols != other.rows) {
        throw std::invalid_argument(
            "Matrix dimensions are not suitable for multiplication");
    }

    auto result = new Matrix(rows, other.cols);

    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < other.cols; ++col) {
            for (size_t k = 0; k < cols; ++k) {
                result->data[row][col] += data[row][k] * other.data[k][col];
            }
        }
    }

    return result;
}

Matrix* Matrix::operator*(int scalar) const
{
    auto result = new Matrix(rows, cols);

    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            result->data[row][col] = data[row][col] * scalar;
        }
    }

    return result;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept
{
    if (this != &other) {
        data = std::move(other.data);
        rows = other.rows;
        cols = other.cols;

        other.rows = 0;
        other.cols = 0;
    }

    return *this;
}

Matrix& Matrix::operator+=(const Matrix& other)
{
    auto temp = *this + other;
    *this = std::move(*temp);
    delete temp;
    return *this;
}

Matrix& Matrix::operator/=(int scalar)
{
    for (size_t row = 0; row < rows; ++row) {
        for (size_t cols = 0; cols < cols; ++cols) {
            data[row][cols] /= scalar;
        }
    }
    return *this;
}

void Matrix::display() const
{
    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            std::cout << data[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix* Matrix::transpose() const
{
    auto result = new Matrix(cols, rows);

    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            result->data[col][row] = data[row][col];
        }
    }

    return result;
}

int Matrix::determinant() const
{
    if (rows != cols) {
        throw std::domain_error(
            "Determinant is defined only for square matrices");
    }

    if (rows == 1) {
        return data[0][0];
    }

    if (rows == 2) {
        return data[0][0] * data[1][1] - data[0][1] * data[1][0];
    }

    int det = 0;
    for (size_t row = 0; row < rows; ++row) {
        det += data[0][row] * cofactor(0, row);
    }

    return det;
}

int Matrix::cofactor(size_t row, size_t col) const
{
    auto submatrix = new Matrix(rows - 1, cols - 1);

    for (size_t row = 0, r = 0; row < rows; ++row) {
        if (row == row) {
            continue;
        }

        for (size_t col = 0, c = 0; col < cols; ++col) {
            if (col == col) {
                continue;
            }

            submatrix->data[r][c] = data[row][col];
            ++c;
        }

        ++r;
    }

    int sign = ((row + col) % 2 == 0) ? 1 : -1;
    int result = sign * submatrix->determinant();
    delete submatrix;
    return result;
}

Matrix Matrix::exp() const
{
    Matrix result(rows, cols);
    for (size_t row = 0; row < rows; ++row) {
        result.data[row][row] = 1;
    }

    Matrix A = *this;

    const int numTerms = 20;

    for (int n = 1; n <= numTerms; ++n) {
        Matrix* term = &A;
        for (int k = 2; k <= n; ++k) {
            term = *term * A;
        }
        *term /= n;
        result += *term;
    }
    return result;
}

