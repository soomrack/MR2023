#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <cstring>
#include <iostream>

typedef double MatrixItem;

class Matrix {
private:
    size_t rows;
    size_t cols;
    MatrixItem* data;
public:
    Matrix() : cols(0), rows(0), data(nullptr) {};
    Matrix(const size_t rows, const size_t cols);
    Matrix(const size_t cols, const size_t rows, const MatrixItem* values);
    Matrix(const Matrix& A);
    Matrix(Matrix&& A) noexcept;
    ~Matrix();
public:
    Matrix& operator+(const Matrix& A);
    Matrix& operator-(const Matrix& A);
    Matrix& operator*(const Matrix& A);
    Matrix& operator*(const MatrixItem k);
    Matrix& operator/(const MatrixItem k);
public:
    Matrix& operator=(const Matrix& A);
    Matrix& operator=(Matrix&& A) noexcept;
public:
    Matrix& operator+=(const Matrix& A);
    Matrix& operator-=(const Matrix& A);
    Matrix& operator*=(const Matrix& A);
    Matrix& operator/=(const MatrixItem k);
    Matrix& operator*=(const MatrixItem k);
public:
    void set_zero();
    void set_one();
    Matrix& trans();
    MatrixItem det(Matrix& A);
    Matrix& exp();
public:
    void print(const Matrix& A);
};


class Matrix_Exception : public  std::exception {
private:
    std::string msg;
public:
    Matrix_Exception(std::string msg) : msg(msg) {};
};


Matrix::Matrix(const size_t rows, const size_t cols)
    : cols(cols), rows(rows)
{
    if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols)
        throw Matrix_Exception("Matrix: Size Error");

    data = new MatrixItem[rows * cols];
}


Matrix::Matrix(const size_t cols, const size_t rows, const MatrixItem* values)
    : cols(cols), rows(rows)
{
    if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols)
        throw Matrix_Exception("Matrix: Size Error");

    data = new MatrixItem[rows * cols];
    std::memcpy(data, values, rows * cols * sizeof(MatrixItem));
}


Matrix::Matrix(const Matrix& A)
{
    if (A.data == nullptr || A.cols == 0 || A.rows == 0) {
        cols = 0;
        rows = 0;
        data = nullptr;
        return;
    };

    rows = A.rows;
    cols = A.cols;
    data = new MatrixItem[rows * cols];
    std::memcpy(data, A.data, sizeof(MatrixItem));
}


Matrix::Matrix(Matrix&& A) noexcept
{
    rows = A.rows;
    cols = A.cols;
    data = A.data;
    A.rows = 0;
    A.cols = 0;
    A.data = nullptr;
}


Matrix::~Matrix() {
    delete[] data;
}


void Matrix::set_zero() {
    if (data == nullptr) return;
    std::memset(data, 0, sizeof(MatrixItem) * rows * cols);
}


void Matrix::set_one()
{
    set_zero();
    for (size_t idx = 0; idx < rows * cols; idx += cols + 1)
        data[idx] = 1.;
}


void Matrix::print(const Matrix& A)
{
    if (data == nullptr) throw Matrix_Exception("Error in Matrix_print");

    std::cout << "\n";
    for (size_t row = 0; row < A.rows; ++row) {
        std::cout << "[ ";
        for (size_t col = 0; col < A.cols; ++col) {
            std::cout << " %4.2f " << A.data[A.cols * row + col];
        }
        std::cout << " [\n";
    }
    std::cout << "\n";
}


Matrix& Matrix::operator=(const Matrix& A)
{
    if (A.data == nullptr || A.cols == 0 || A.rows == 0) {
        cols = 0;
        rows = 0;
        data = nullptr;
        return *this;
    };

    if (this == &A) return *this;
 
    if (rows * cols == A.rows * A.cols) {
        rows = A.rows;
        cols = A.cols;
        memcpy(data, A.data, rows * cols * sizeof(MatrixItem));
        return *this;
    }

    delete[] data;
    rows = A.rows;
    cols = A.cols;
    data = new MatrixItem[rows * cols];
    std::memcpy(data, A.data, rows * cols * sizeof(MatrixItem));
    return *this;
}


Matrix& Matrix::operator=(Matrix&& A) noexcept
{
    delete[] data;
    rows = A.rows;
    cols = A.cols;
    data = A.data;
    A.rows = 0;
    A.cols = 0;
    A.data = nullptr;
    return *this;
};


// B += A
Matrix& Matrix::operator+=(const Matrix& A) {
    if (A.cols != cols || A.rows != rows)
        throw Matrix_Exception("Operator+=: Incorrect sizes");

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        data[idx] += A.data[idx];

    return *this;
}


// SUM = B + A
Matrix& Matrix::operator+(const Matrix& A) {
    if (A.cols != cols || A.rows != rows)
        throw Matrix_Exception("Operator+: Incorrect sizes");

    Matrix* SUM = new Matrix(*this);
    *SUM += A;
    return *SUM;
}


// B -= A
Matrix& Matrix::operator-=(const Matrix& A)
{
    if (A.cols != cols || A.rows != rows)
        throw Matrix_Exception("Operator-=: Incorrect sizes");

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        data[idx] -= A.data[idx];
    return *this;
}


// DIFF = B - A
Matrix& Matrix::operator-(const Matrix& A) {
    if (A.cols != cols || A.rows != rows)
        throw Matrix_Exception("Operator-: Incorrect sizes");

    Matrix* DIFF = new Matrix(*this);
    *DIFF -= A;

    return *DIFF;
}


// A^T
Matrix& Matrix::trans()
{
    Matrix* A = new Matrix(cols, rows);
    for (size_t row = 0; row < A->rows; ++row) {
        for (size_t col = 0; col < A->cols; ++col) {
            A->data[col * A->cols + row] = data[row * cols + col];
        }
    }
    return *A;
}


//C = B * A
Matrix& Matrix::operator*(const Matrix& A)
{
    if (A.cols != rows)
        throw Matrix_Exception("Operator*: Multiplication Error");

    Matrix* C = new Matrix(rows, A.cols);

    for (size_t col = 0; col < cols; ++col) {
        for (size_t rowA = 0; rowA < A.rows; ++rowA) {
            C->data[rowA * cols + col] = 0;
            for (size_t idx = 0; idx < A.cols; ++idx) {
                C->data[rowA * cols + col] += A.data[rowA * A.cols + idx]
                    * data[idx * cols + col];
            }
        }
    };
    return *C;
}


// B *= A
Matrix& Matrix::operator*=(const Matrix& A)
{
    *this = *this * A;
    return *this;
}


// A /= k
Matrix& Matrix::operator/=(const MatrixItem k)
{
    for (size_t idx = 0; idx < cols * rows; ++idx)
        data[idx] = data[idx] / k;
    return *this;
}


// C = A / k
Matrix& Matrix::operator/(const MatrixItem k)
{
    Matrix* C = new Matrix(rows, cols);

    for (size_t idx = 0; idx < cols * rows; ++idx)
        C->data[idx] = data[idx] / k;
    return *C;
}


// C = A * k
Matrix& Matrix::operator*(const MatrixItem k)
{
    Matrix* C = new Matrix(rows, cols);

    for (size_t idx = 0; idx < cols * rows; ++idx)
        C->data[idx] = data[idx] * k;
    return *C;
}


// A *= k
Matrix& Matrix::operator*=(const MatrixItem k)
{
    for (size_t idx = 0; idx < cols * rows; ++idx)
        data[idx] = data[idx] * k;
    return *this;
}


// DET (A)
MatrixItem Matrix::det(Matrix& A)
{
    if (A.rows != A.cols)
        throw Matrix_Exception("det: Not square");

    if (A.rows == 1) return A.data[0];

    if (A.rows == 2) {
        return (A.data[0] * A.data[3]
            - A.data[2] * A.data[1]);
    };
    if (A.rows == 3) {
        return (+A.data[0] * A.data[4] * A.data[8]
            + A.data[1] * A.data[5] * A.data[6]
            + A.data[3] * A.data[7] * A.data[2]
            - A.data[2] * A.data[4] * A.data[6]
            - A.data[1] * A.data[3] * A.data[8]
            - A.data[5] * A.data[7] * A.data[0]);
    };
    throw Matrix_Exception("det: Matrix size too large");
}


// exp = exp(A)
Matrix& Matrix::exp()
{
    if (cols != rows)
        throw Matrix_Exception("exp: Not square");
    if (cols == 0)
        throw Matrix_Exception("exp: ");

    Matrix term = Matrix(rows, cols);
    term.set_one();

    Matrix* exp = new Matrix(term);

    for (int idx = 1; idx < 100; ++idx) {

        term = term * (*this) / idx;
        *exp += term;

    }
    return *exp;
}


int main() {


}
