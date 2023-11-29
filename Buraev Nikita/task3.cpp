#include "matrix.hpp"
#include <iostream>
#include <stdexcept>

template <typename Type>
Matrix<Type>::Matrix(std::initializer_list<std::initializer_list<Type>> matrix)
{
    for (const auto &mat : matrix)
    {
        std::vector<Type> row(mat);
        elements.push_back(row);
    }

    rows = elements.size();
    cols = (rows > 0) ? elements[0].size() : 0;
}

template <typename Type>
Matrix<Type>::Matrix(std::initializer_list<Type> matrix)
{
    std::vector<Type> row(matrix);
    elements.push_back(row);

    rows = 1;
    cols = (rows > 0) ? elements[0].size() : 0;
}

template <typename Type>
Matrix<Type>::Matrix(unsigned size)
{
    elements.resize(size, std::vector<Type>(size, Type{0}));

    for (unsigned i = 0; i < size; ++i)
        elements[i][i] = Type{1};

    rows = cols = size;
}

template <typename Type>
Matrix<Type>::Matrix(const Matrix<Type> &original) : elements(original.elements), rows(original.rows), cols(original.cols)
{
}

template <typename Type>
Matrix<Type> &Matrix<Type>::operator=(const Matrix<Type> &right)
{
    if (&right == this)
        return *this;

    elements = right.elements;
    rows = right.rows;
    cols = right.cols;

    return *this;
}

template <typename Type>
Matrix<Type> Matrix<Type>::operator+(const Matrix<Type> &right) const
{
    if (rows != right.rows || cols != right.cols)
    {
        throw std::invalid_argument("Matrix addition requires matrices of the same dimensions.");
    }

    Matrix result(rows, cols, elements[0][0]);

    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            result.elements[i][j] = elements[i][j] + right.elements[i][j];

    return result;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::operator+=(const Matrix<Type> &right)
{
    if (rows != right.rows || cols != right.cols)
    {
        throw std::invalid_argument("Matrix addition requires matrices of the same dimensions.");
    }

    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            elements[i][j] += right.elements[i][j];

    return *this;
}

template <typename Type>
Matrix<Type> Matrix<Type>::operator-(const Matrix<Type> &right) const
{
    if (rows != right.rows || cols != right.cols)
    {
        throw std::invalid_argument("Matrix subtraction requires matrices of the same dimensions.");
    }

    Matrix result(rows, cols, elements[0][0]);

    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            result.elements[i][j] = elements[i][j] - right.elements[i][j];

    return result;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::operator-=(const Matrix<Type> &right)
{
    if (rows != right.rows || cols != right.cols)
    {
        throw std::invalid_argument("Matrix subtraction requires matrices of the same dimensions.");
    }

    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            elements[i][j] -= right.elements[i][j];

    return *this;
}

template <typename Type>
Matrix<Type> Matrix<Type>::operator*(const Matrix<Type> &right) const
{
    if (cols != right.rows)
    {
        throw std::invalid_argument("Matrices are incompatible for multiplication");
    }

    Matrix result(rows, right.cols, elements[0][0]);

    for (std::size_t i = 0; i < rows; ++i)
    {
        for (std::size_t j = 0; j < right.cols; ++j)
        {
            Type sum = 0;

            for (std::size_t k = 0; k < cols; ++k)
                sum += elements[i][k] * right.elements[k][j];

            result.elements[i][j] = sum;
        }
    }

    return result;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::operator*=(const Matrix<Type> &right)
{
    *this = *this * right;
    return *this;
}

template <typename Type>
Matrix<Type> Matrix<Type>::operator+(const Type &right) const
{
    Matrix result(rows, cols, elements[0][0]);

    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            result.elements[i][j] = this->elements[i][j] + right;

    return result;
}

template <typename Type>
Matrix<Type> Matrix<Type>::operator/(const Type &right) const
{
    if (right == 0)
    {
        throw std::invalid_argument("Division by zero.");
    }

    Matrix result(rows, cols, elements[0][0]);

    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            result.elements[i][j] = this->elements[i][j] / right;

    return result;
}

template <typename Type>
Matrix<Type> Matrix<Type>::operator-(const Type &right) const
{
    Matrix result(rows, cols, elements[0][0]);

    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            result.elements[i][j] = this->elements[i][j] - right;

    return result;
}

template <typename Type>
Matrix<Type> Matrix<Type>::operator*(const Type &right) const
{
    Matrix result(rows, cols, elements[0][0]);

    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            result.elements[i][j] = this->elements[i][j] * right;

    return result;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::operator+=(const Type &right)
{
    *this = *this + right;
    return *this;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::operator-=(const Type &right)
{
    *this = *this - right;
    return *this;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::operator*=(const Type &right)
{
    *this = *this * right;
    return *this;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::operator/=(const Type &right)
{
    *this = *this / right;
    return *this;
}

template <typename Type>
Type &Matrix<Type>::operator()(std::size_t i, std::size_t j)
{
    if (i >= rows || j >= cols)
    {
        throw std::out_of_range("Matrix index out of bounds!");
    }

    return elements[i][j];
}

template <typename Type>
const Type &Matrix<Type>::operator()(std::size_t i, std::size_t j) const
{
    if (i >= rows || j >= cols)
    {
        throw std::out_of_range("Matrix index out of bounds!");
    }

    return elements[i][j];
}

template <typename Type>
void Matrix<Type>::print() const
{
    for (std::size_t i = 0; i < rows; ++i)
    {
        for (std::size_t j = 0; j < cols; ++j)
            std::cout << elements[i][j] << " ";

        std::cout << std::endl;
    }
}

template <typename Type>
Type &Matrix<Type>::element(std::size_t i, std::size_t j)
{
    if (i >= rows || j >= cols)
    {
        throw std::out_of_range("Matrix index out of bounds!");
    }
    return elements[i][j];
}

template <typename Type>
Type &Matrix<Type>::element(std::size_t i)
{
    if (rows > 1)
    {
        throw std::invalid_argument("Incorrect use of index! Matrix has more than one row\nUse Matrix::element(row, col) instead.");
    }

    if (i >= cols)
    {
        throw std::out_of_range("Matrix index out of bounds!");
    }

    if (rows == 0 && cols == 0)
    {
        throw std::runtime_error("Matrix is empty! Index out of bounds!");
    }

    return elements[0][i];
}

template <typename Type>
Type &Matrix<Type>::element(std::size_t i, std::size_t j) const
{
    if (i >= rows || j >= cols)
    {
        throw std::out_of_range("Matrix index out of bounds!");
    }
    return elements[i][j];
}

template <typename Type>
Type &Matrix<Type>::element(std::size_t i) const
{
    if (rows > 1)
    {
        throw std::invalid_argument("Incorrect use of index! Matrix has more than one row\nUse Matrix::element(row, col) instead.");
    }

    if (i >= cols)
    {
        throw std::out_of_range("Matrix index out of bounds!");
    }

    if (rows == 0 && cols == 0)
    {
        throw std::runtime_error("Matrix is empty! Index out of bounds!");
    }

    return elements[0][i];
}

template <typename Type>
Matrix<Type> Matrix<Type>::transpose() const
{
    Matrix<Type> result(cols, rows, elements[0][0]);

    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            result.elements[j][i] = elements[i][j];

    return result;
}

template <typename Type>
Matrix<Type> Matrix<Type>::power(unsigned n) const
{
    if (!is_square())
    {
        throw std::invalid_argument("Matrix is incompatible for power() | rows != cols\n");
    }

    if (n == 0)
    {
        Matrix result(rows);
        return result;
    }

    Matrix result(rows, cols, elements[0][0]);
    result = *this;

    for (unsigned i = 1; i < n; ++i)
    {
        result *= *this;
    }

    return result;
}

template <typename Type>
bool Matrix<Type>::is_square() const
{
    return rows == cols;
}

template <typename Type>
std::size_t Matrix<Type>::getRows() const
{
    return rows;
}

template <typename Type>
std::size_t Matrix<Type>::getCols() const
{
    return cols;
}
