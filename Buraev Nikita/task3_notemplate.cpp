#include <iostream>
#include <stdexcept>

class MatrixException : public std::exception {
public:
    MatrixException(const std::string& message) : message(message) {}

    const char* what() const noexcept override {
        return message.c_str();
    }

private:
    std::string message;
};

template <typename Type>
class Matrix {
public:
    Matrix(std::initializer_list<std::initializer_list<Type>> matrix);
    Matrix(std::initializer_list<Type> matrix);
    Matrix(unsigned size);
    Matrix(const Matrix<Type> &original);
    ~Matrix();

    Matrix<Type> &operator=(const Matrix<Type> &right);
    Matrix<Type> operator+(const Matrix<Type> &right) const;
    Matrix<Type> &operator+=(const Matrix<Type> &right);
    Matrix<Type> operator-(const Matrix<Type> &right) const;
    Matrix<Type> &operator-=(const Matrix<Type> &right);
    Matrix<Type> operator*(const Matrix<Type> &right) const;
    Matrix<Type> &operator*=(const Matrix<Type> &right);
    Matrix<Type> operator+(const Type &right) const;
    Matrix<Type> operator/(const Type &right) const;
    Matrix<Type> operator-(const Type &right) const;
    Matrix<Type> operator*(const Type &right) const;
    Matrix<Type> &operator+=(const Type &right);
    Matrix<Type> &operator-=(const Type &right);
    Matrix<Type> &operator*=(const Type &right);
    Matrix<Type> &operator/=(const Type &right);

    Type &operator()(std::size_t i, std::size_t j);
    const Type &operator()(std::size_t i, std::size_t j) const;

    void print() const;
    Type &element(std::size_t i, std::size_t j);
    Type &element(std::size_t i);
    Type &element(std::size_t i, std::size_t j) const;
    Type &element(std::size_t i) const;

    Matrix<Type> transpose() const;
    Matrix<Type> power(unsigned n) const;
    bool is_square() const;
    std::size_t getRows() const;
    std::size_t getCols() const;

private:
    Type **elements;
    std::size_t rows;
    std::size_t cols;

    void initializeElements();
};

template <typename Type>
Matrix<Type>::Matrix(std::initializer_list<std::initializer_list<Type>> matrix) {
    rows = matrix.size();
    cols = (rows > 0) ? matrix.begin()->size() : 0;

    initializeElements();

    std::size_t i = 0;
    for (const auto &row : matrix) {
        std::size_t j = 0;
        for (const auto &element : row) {
            elements[i][j++] = element;
        }
        ++i;
    }
}

template <typename Type>
Matrix<Type>::Matrix(std::initializer_list<Type> matrix) {
    rows = 1;
    cols = matrix.size();

    initializeElements();

    std::size_t j = 0;
    for (const auto &element : matrix) {
        elements[0][j++] = element;
    }
}

template <typename Type>
Matrix<Type>::Matrix(unsigned size) : rows(size), cols(size) {
    initializeElements();

    for (unsigned i = 0; i < size; ++i) {
        elements[i][i] = Type{1};
    }
}

template <typename Type>
Matrix<Type>::Matrix(const Matrix<Type> &original) : rows(original.rows), cols(original.cols) {
    initializeElements();

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            elements[i][j] = original.elements[i][j];
        }
    }
}

template <typename Type>
Matrix<Type>::~Matrix() {
    for (std::size_t i = 0; i < rows; ++i) {
        delete[] elements[i];
    }
    delete[] elements;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::operator=(const Matrix<Type> &right) {
    if (&right == this) {
        return *this;
    }

    if (rows != right.rows || cols != right.cols) {
        throw MatrixException("Matrix assignment requires matrices of the same dimensions.");
    }

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            elements[i][j] = right.elements[i][j];
        }
    }

    return *this;
}

template <typename Type>
Matrix<Type> Matrix<Type>::operator+(const Matrix<Type> &right) const {
    if (rows != right.rows || cols != right.cols) {
        throw MatrixException("Matrix addition requires matrices of the same dimensions.");
    }

    Matrix result(rows, cols);

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            result.elements[i][j] = elements[i][j] + right.elements[i][j];
        }
    }

    return result;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::operator+=(const Matrix<Type> &right) {
    if (rows != right.rows || cols != right.cols) {
        throw MatrixException("Matrix addition requires matrices of the same dimensions.");
    }

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            elements[i][j] += right.elements[i][j];
        }
    }

    return *this;
}

template <typename Type>
Matrix<Type> Matrix<Type>::operator-(const Matrix<Type> &right) const {
    if (rows != right.rows || cols != right.cols) {
        throw MatrixException("Matrix subtraction requires matrices of the same dimensions.");
    }

    Matrix result(rows, cols);

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            result.elements[i][j] = elements[i][j] - right.elements[i][j];
        }
    }

    return result;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::operator-=(const Matrix<Type> &right) {
    if (rows != right.rows || cols != right.cols) {
        throw MatrixException("Matrix subtraction requires matrices of the same dimensions.");
    }

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            elements[i][j] -= right.elements[i][j];
        }
    }

    return *this;
}

template <typename Type>
Matrix<Type> Matrix<Type>::operator*(const Matrix<Type> &right) const {
    if (cols != right.rows) {
        throw MatrixException("Matrices are incompatible for multiplication.");
    }

    Matrix result(rows, right.cols);

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < right.cols; ++j) {
            Type sum = 0;

            for (std::size_t k = 0; k < cols; ++k) {
                sum += elements[i][k] * right.elements[k][j];
            }

            result.elements[i][j] = sum;
        }
    }

    return result;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::operator*=(const Matrix<Type> &right) {
    *this = *this * right;
    return *this;
}

template <typename Type>
Matrix<Type> Matrix<Type>::operator+(const Type &right) const {
    Matrix result(rows, cols);

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            result.elements[i][j] = elements[i][j] + right;
        }
    }

    return result;
}

template <typename Type>
Matrix<Type> Matrix<Type>::operator/(const Type &right) const {
    if (right == 0) {
        throw MatrixException("Division by zero.");
    }

    Matrix result(rows, cols);

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            result.elements[i][j] = elements[i][j] / right;
        }
    }

    return result;
}

template <typename Type>
Matrix<Type> Matrix<Type>::operator-(const Type &right) const {
    Matrix result(rows, cols);

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            result.elements[i][j] = elements[i][j] - right;
        }
    }

    return result;
}

template <typename Type>
Matrix<Type> Matrix<Type>::operator*(const Type &right) const {
    Matrix result(rows, cols);

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            result.elements[i][j] = elements[i][j] * right;
        }
    }

    return result;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::operator+=(const Type &right) {
    *this = *this + right;
    return *this;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::operator-=(const Type &right) {
    *this = *this - right;
    return *this;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::operator*=(const Type &right) {
    *this = *this * right;
    return *this;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::operator/=(const Type &right) {
    *this = *this / right;
    return *this;
}

template <typename Type>
Type &Matrix<Type>::operator()(std::size_t i, std::size_t j) {
    if (i >= rows || j >= cols) {
        throw MatrixException("Matrix index out of bounds!");
    }

    return elements[i][j];
}

template <typename Type>
const Type &Matrix<Type>::operator()(std::size_t i, std::size_t j) const {
    if (i >= rows || j >= cols) {
        throw MatrixException("Matrix index out of bounds!");
    }

    return elements[i][j];
}

template <typename Type>
void Matrix<Type>::print() const {
    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            std::cout << elements[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

template <typename Type>
Type &Matrix<Type>::element(std::size_t i, std::size_t j) {
    if (i >= rows || j >= cols) {
        throw MatrixException("Matrix index out of bounds! "
                              "Index (" + std::to_string(i) + ", " + std::to_string(j) + ")"
                              " exceeds matrix dimensions (" + std::to_string(rows) + ", " + std::to_string(cols) + ")"
                              " in file " + std::string(__FILE__) + " at line " + std::to_string(__LINE__));
    }
    return elements[i][j];
}

template <typename Type>
Type &Matrix<Type>::element(std::size_t i) {
    if (rows > 1) {
        throw MatrixException("Incorrect use of index! Matrix has more than one row\nUse Matrix::element(row, col) instead.");
    }

    if (i >= cols) {
        throw MatrixException("Matrix index out of bounds! "
                              "Index (" + std::to_string(i) + ")"
                              " exceeds matrix dimensions (" + std::to_string(rows) + ", " + std::to_string(cols) + ")"
                              " in file " + std::string(__FILE__) + " at line " + std::to_string(__LINE__));
    }

    if (rows == 0 && cols == 0) {
        throw MatrixException("Matrix is empty! Index out of bounds!");
    }

    return elements[0][i];
}

template <typename Type>
Type &Matrix<Type>::element(std::size_t i, std::size_t j) const {
    if (i >= rows || j >= cols) {
        throw MatrixException("Matrix index out of bounds! "
                              "Index (" + std::to_string(i) + ", " + std::to_string(j) + ")"
                              " exceeds matrix dimensions (" + std::to_string(rows) + ", " + std::to_string(cols) + ")"
                              " in file " + std::string(__FILE__) + " at line " + std::to_string(__LINE__));
    }
    return elements[i][j];
}

template <typename Type>
Type &Matrix<Type>::element(std::size_t i) const {
    if (rows > 1) {
        throw MatrixException("Incorrect use of index! Matrix has more than one row\nUse Matrix::element(row, col) instead.");
    }

    if (i >= cols) {
        throw MatrixException("Matrix index out of bounds! "
                              "Index (" + std::to_string(i) + ")"
                              " exceeds matrix dimensions (" + std::to_string(rows) + ", " + std::to_string(cols) + ")"
                              " in file " + std::string(__FILE__) + " at line " + std::to_string(__LINE__));
    }

    if (rows == 0 && cols == 0) {
        throw MatrixException("Matrix is empty! Index out of bounds!");
    }

    return elements[0][i];
}

template <typename Type>
Matrix<Type> Matrix<Type>::transpose() const {
    Matrix<Type> result(cols, rows);

    for
