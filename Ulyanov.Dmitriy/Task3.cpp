#pragma once
//#ifdef LIBMATRIX_H
//#define LIBATRIX_H
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <cstring>
#include <iostream>


typedef double MatrixItem;

class Matrix {
private:
    size_t cols;
    size_t rows;
    MatrixItem* data;
public:
    Matrix() : cols(0), rows(0), data(nullptr) {};  
    Matrix(const size_t rows, const size_t cols);  
	Matrix(const size_t cols, const size_t rows, const MatrixItem* values);  
	Matrix(Matrix& A);  
	Matrix(Matrix&& A) noexcept;  
	~Matrix();
public:
    Matrix& operator=(Matrix& A);    
    Matrix& operator=(Matrix&& A) noexcept; 
    Matrix& operator+(const Matrix& A) const;
    Matrix& operator+=(const Matrix& A);
    Matrix& operator-=(const Matrix& A);
    Matrix& operator-(const Matrix& A) const;
    Matrix& operator*=(const Matrix& A);
    Matrix& operator*(const Matrix& A) const;
    Matrix& operator/(const MatrixItem k) const;
public:
    void set_zero();
    void set_one();
    void print(const Matrix& A);
    Matrix& trans();
private:
    MatrixItem det1x1(Matrix& A);  
    MatrixItem det2x2(Matrix& A);
    MatrixItem det3x3(Matrix& A);
public:
    MatrixItem det(Matrix& A);
    Matrix& exp(Matrix& A);
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
        throw Matrix_Exception("");

    data = new MatrixItem[rows * cols];
}


Matrix::Matrix(const size_t cols, const size_t rows, const MatrixItem *values)
    : cols(cols), rows(rows)
{
    if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols) 
        throw Matrix_Exception("");

    data = new MatrixItem[rows * cols];
    std::memcpy(data, values, rows * cols * sizeof(MatrixItem));
}


Matrix::Matrix(Matrix& A)
{
    rows = A.rows;
    cols = A.cols;
    data = A.data;
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
    for (size_t row = 0; row < A.rows; ++row) {
        std::cout << "[ ";
        for (size_t col = 0; col < A.cols; ++col) {
            std::cout << " %4.2f " << A.data[A.cols * row + col];
        }
        std::cout << " [\n";
    }
    std::cout << "\n";
}


Matrix& Matrix::operator=(Matrix& A)
{
    if (this == &A) return *this;
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


Matrix& Matrix::operator+=(const Matrix& A) 
{
    if (A.cols != cols || A.rows != rows) 
        throw Matrix_Exception("Operator+=: Incorrect sizes");

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        data[idx] += A.data[idx];

    return *this;
}


Matrix& Matrix::operator+(const Matrix& A) const {
    if (A.cols != cols || A.rows != rows) 
        throw Matrix_Exception("Operator+: Incorrect sizes");

    Matrix *C = new Matrix(rows, cols);

    std::memcpy(C->data, A.data, C->cols * C->rows * sizeof(MatrixItem));
    *C += A;
    return *C;
}


Matrix& Matrix::operator-=(const Matrix& A)
{
    if (A.cols != cols || A.rows != rows) 
        throw Matrix_Exception("Operator-=: Incorrect sizes");

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        data[idx] -= A.data[idx];
    return *this;
}


Matrix& Matrix::operator-(const Matrix& A) const 
{
    if (A.cols != cols || A.rows != rows) 
        throw Matrix_Exception("Operator-: Incorrect sizes");

    Matrix *C = new Matrix(rows, cols);

    memcpy(C->data, A.data, C->cols * C->rows * sizeof(MatrixItem));
    *C -= A;

    return *C;
}


// matrix_trans
Matrix& Matrix::trans()
{
    Matrix A (this->cols, this->rows);
    for (size_t row = 0; row < A.rows; ++row) {
        for (size_t col = 0; col < A.cols; ++col) {
            A.data[col * A.cols + row] = this->data[row * this->cols + col];
        }
    }
    return A;
}


//C = A * B
Matrix& Matrix::operator*=(const Matrix& A) {
    if (A.cols != cols || A.rows != rows) throw (10);

    Matrix C(rows, A.cols);
 
    for (size_t colC = 0; colC < C.cols; ++colC) {
        for (size_t rowA = 0; rowA < A.rows; ++rowA) {
            C.data[rowA * C.cols + colC] = 0;
            for (size_t idx = 0; idx < A.cols; ++idx) {
                C.data[rowA * C.cols + colC] += A.data[rowA * A.cols + idx] * C.data[idx * C.cols + colC];
            }
        }
    };
    *this = C;
    return *this;
}

Matrix& Matrix::operator*(const Matrix& A) const 
{
    Matrix B(cols, rows);
    B *= A;
    
    return B;
}


Matrix& Matrix::operator/(const MatrixItem k) const
{
    Matrix C(this->rows, this->cols);

    for (size_t idx = 0; idx < cols * rows; ++idx)
        C.data[idx] = this->data[idx] / k;
    return C;
}


// det(A), A[1][1]
MatrixItem Matrix::det1x1(Matrix& A) 
{
    if (A.rows != A.cols) throw (10);
    return A.data[0];
}


// det(A), A[2][2]
MatrixItem Matrix::det2x2(Matrix& A) 
{
    if (A.rows != A.cols) throw (10);
    return (A.data[0] * A.data[3] - A.data[2] * A.data[1]);
}


// det(A), A[3][3]
MatrixItem Matrix::det3x3(Matrix& A)
{
    if (A.rows != A.cols) throw (10);
    return (+ A.data[0] * A.data[4] * A.data[8]
            + A.data[1] * A.data[5] * A.data[6]
            + A.data[3] * A.data[7] * A.data[2]
            - A.data[2] * A.data[4] * A.data[6]
            - A.data[1] * A.data[3] * A.data[8]
            - A.data[5] * A.data[7] * A.data[0]);
}


MatrixItem Matrix::det(Matrix& A)
{
    if (A.rows != A.cols) 
        throw Matrix_Exception("det: Not square");

    if (A.rows == 1) {
        return det1x1(A);
    };
    if (A.rows == 2) {
        return det2x2(A);
    };
    if (A.rows == 3) {
        return det3x3(A);
    }
    else throw Matrix_Exception("det: Matrix size too large");
}


// exp = exp(A)
Matrix& Matrix::exp(Matrix& A)
{
    if (A.cols != A.rows) 
        throw Matrix_Exception("exp: Not square");
    if (A.cols == 0) 
        throw Matrix_Exception("exp: Matrix not created");

    Matrix exp (A.rows, A.cols);
    exp.set_one();

    Matrix term_prev (A.rows, A.cols);  // член a_n
    term_prev.set_one();

    Matrix term_next;  // член a_n+1 

    for (int idx = 1; idx < 100; ++idx) {

        term_next = term_prev * A / idx;
        exp += term_next;

    }
    delete[] &term_prev;
    return exp;
}

//#endif
