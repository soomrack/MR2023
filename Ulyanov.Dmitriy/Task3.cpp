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
	Matrix(const size_t cols, const size_t rows, const MatrixItem* data);
	Matrix(Matrix& A);
	Matrix(Matrix&& A);
	~Matrix();

private:
	MatrixItem* allocate(const size_t cols, const size_t rows);
public:
	
    Matrix& operator=(const Matrix& A);    // как отличать эти две перегрузки
    Matrix& operator=(const Matrix&& A);   // и использовать их выборочно?
    Matrix& operator+(const Matrix& A) const;
    Matrix& operator+=(const Matrix& A);
    Matrix& operator-=(const Matrix& A);
    Matrix& operator-(const Matrix& A) const;
    Matrix& operator*=(const Matrix& A);
    Matrix& operator*(const Matrix& A) const;
    Matrix& operator/(const MatrixItem k) const;
	
	Matrix& operator*(const Matrix& A);
public:
	//Matrix prod(const Matrix A, const Matrix B);
	//Matrix prod(const Matrix A, const MatrixItem b);
	//Matrix sum(const Matrix A, const Matrix B);

    void set_zero();
    void set_one();
    Matrix& trans();
    //Matrix(const Matrix& A) : rows(A.rows), cols(A.cols) {};
    Matrix(size_t rows, size_t cols);

    MatrixItem det1x1(Matrix& A);
    MatrixItem det2x2(Matrix& A);
    MatrixItem det3x3(Matrix& A);
    MatrixItem det(Matrix& A);

    Matrix& exp(Matrix& A);

    void print(const Matrix& A);
};


//const struct Matrix MATRIX_NULL = { .cols = 0, .rows = 0, .data = NULL };

MatrixItem* Matrix::allocate(const size_t cols, const size_t rows)
{
    if (cols == 0 || rows == 0) return nullptr;
    if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols) return nullptr;

    data = new MatrixItem[cols * rows];

    return data;
}

// matrix_create
Matrix::Matrix(const size_t cols, const size_t rows, const MatrixItem* data)
{
    this->cols = cols;
    this->rows = rows;
    this->data = new MatrixItem[rows * cols];
    if (!data) throw (10);
    std::memcpy(this->data, data, rows * cols * sizeof(MatrixItem*));
}


Matrix::~Matrix() {
    delete[] data;
}


void Matrix::set_zero() {
    std::memset(data, 0, sizeof(MatrixItem) * rows * cols);
}

void Matrix::set_one()
{
    set_zero();
    for (size_t idx = 0; idx < this->rows * this->cols; idx += this->cols + 1)
        this->data[idx] = 1.;
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


Matrix& Matrix::operator=(const Matrix& A)
{
    delete[] data;
    rows = A.rows;
    cols = A.cols;
    this->data = new MatrixItem[rows * cols];
    memcpy(this->data, A.data, rows * cols * sizeof(MatrixItem));
    return *this;
}


Matrix& Matrix::operator=(const Matrix&& A) {
    return *this;
};


Matrix& Matrix::operator+=(const Matrix& A) {
    if (A.cols != cols || A.rows != rows) throw (10);

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        data[idx] += A.data[idx];

    return *this;
}


Matrix& Matrix::operator+(const Matrix& A) const {
    if (A.cols != cols || A.rows != rows) throw (10);

    Matrix C(rows, cols);
    /*for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        C.data[idx] = data[idx] + A.data[idx];*/

    memcpy(C.data, A.data, C.cols * C.rows * sizeof(MatrixItem));
    C += A;
    return C;
}


Matrix& Matrix::operator-=(const Matrix& A)
{
    if (A.cols != cols || A.rows != rows) throw(10);

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        data[idx] -= A.data[idx];
    return *this;
}

Matrix& Matrix::operator-(const Matrix& A) const {
    if (A.cols != cols || A.rows != rows) throw (10);

    Matrix C(rows, cols);
    /*for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        C.data[idx] = data[idx] - A.data[idx];*/

    memcpy(C.data, A.data, C.cols * C.rows * sizeof(MatrixItem));
    C -= A;

    return C;
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

    return C;
}

Matrix& Matrix::operator*(const Matrix& A) const {
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
    if (A.rows != A.cols) throw (10);

    if (A.rows == 1) {
        return det1x1(A);
    };
    if (A.rows == 2) {
        return det2x2(A);
    };
    if (A.rows == 3) {
        return det3x3(A);
    }
    else throw(11);
}


// exp = exp(A)
Matrix& Matrix::exp(Matrix& A)
{
    if (A.cols != A.rows) throw(10);
    if (A.cols == 0) throw(10);

    Matrix exp (A.rows, A.cols);
    
    exp.set_one();

    Matrix term_prev (A.rows, A.cols);  // член a_n
    
    term_prev.set_one();

    Matrix term_next;  // член a_n+1 

    for (int idx = 1; idx < 100; ++idx) {

        term_next = term_prev * A;
        delete[] &term_prev;
        term_prev = term_next / idx;
        delete[] &term_next;
        exp += term_prev;

    }
    delete[] &term_prev;
    return exp;
}

//#endif
