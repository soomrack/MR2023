#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <cstring>
#include <iostream>


using namespace std;


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

    Matrix& operator+(const Matrix& A);
    Matrix& operator-(const Matrix& A);
    Matrix& operator*(const Matrix& A);
    Matrix& operator*(const MatrixItem k);
    Matrix& operator/(const MatrixItem k);
    Matrix& operator=(const Matrix& A);
    Matrix& operator=(Matrix&& A) noexcept;
    Matrix& operator+=(const Matrix& A);
    Matrix& operator-=(const Matrix& A);
    Matrix& operator*=(const Matrix& A);
    Matrix& operator/=(const MatrixItem k);
    Matrix& operator*=(const MatrixItem k);

    void set_zero();
    void set_one();
    Matrix& trans();
    MatrixItem det(Matrix& A);
    Matrix& exp(int idx);
    void print(const Matrix& A);
};


class Matrix_Exception : public  exception {
private:
    string msg;
public:
    Matrix_Exception(string msg) : msg(msg) {};
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
    memcpy(data, values, rows * cols * sizeof(MatrixItem));
}


Matrix::Matrix(const Matrix& A)
{
    rows = A.rows;
    cols = A.cols;
    data = new MatrixItem[rows * cols];
    memcpy(data, A.data, sizeof(MatrixItem));
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
    memset(data, 0, sizeof(MatrixItem) * rows * cols);
}


void Matrix::set_one()
{
    set_zero();
    for (size_t idx = 0; idx < rows * cols; idx += cols + 1) data[idx] = 1;
}


void Matrix::print(const Matrix& A)
{
    for (size_t row = 0; row < A.rows; ++row) {
        cout << "[ ";
        for (size_t col = 0; col < A.cols; ++col) {
            cout << " %4.2f " << A.data[A.cols * row + col];
        }
        cout << " [\n";
    }
    cout << "\n";
}


Matrix& Matrix::operator=(const Matrix& A)
{
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
    memcpy(data, A.data, rows * cols * sizeof(MatrixItem));
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
Matrix& Matrix::exp(unsigned int idx = 100)
{

    Matrix* exp = new Matrix(*this);
    exp->set_one();

    Matrix term(*this);
    term.set_one();

    for (unsigned int k = 1; k < idx; ++k) {

        term = term * *this / idx;
        *exp += term;

    }
    return *exp;
}


int main() {


    return 0;
}
