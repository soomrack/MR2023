#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stdint.h>
#include <vector>


typedef double MatrixItem;

class Matrix {
private:
    size_t rows;
    size_t cols;
    MatrixItem* data;
public:
    Matrix();
    Matrix(const size_t cols, const size_t rows);
    Matrix(Matrix& A);
    Matrix(Matrix&& A);
    ~Matrix();
public:
    Matrix& operator + (const Matrix& A);
    Matrix& operator - (const Matrix& A);
    Matrix& operator * (const Matrix& A);
    Matrix& operator / (const MatrixItem k);
    Matrix& operator = (const Matrix& A);
    Matrix& operator = (Matrix&& A) noexcept;
    Matrix& operator+=(const Matrix& A);
    Matrix& operator-=(const Matrix& A);
    Matrix& operator/=(const MatrixItem k);
public:
    void free();
    void fill(std::vector <MatrixItem> values);
    void set_zero();
    void set_one();
    void print();
    Matrix& trans();
    Matrix& exp(Matrix& A);
};


class Matrix_Exception : public  std::exception {
private:
    std::string msg;
public:
    Matrix_Exception(std::string msg) : msg(msg) {};
};


Matrix::Matrix() {
    rows = 0;
    cols = 0;
    data = nullptr;
}


Matrix::Matrix(const size_t cols, const size_t rows)
    : cols(cols), rows(rows)
{
    if (cols == 0 || rows == 0) {
        data = nullptr;
        return;
    };

    if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols) {
        free();
        return;
    };

    data = new MatrixItem[cols * rows];
}


Matrix::Matrix(Matrix& A)
{
    if (A.data == nullptr) {
        cols = 0;
        rows = 0;
        data = nullptr;
        return;
    };

    cols = A.cols;
    rows = A.rows;
    data = new MatrixItem[cols * rows];

    memcpy(data, A.data, A.cols * A.rows * sizeof(MatrixItem));
}


Matrix::Matrix(Matrix&& A)
{
    cols = A.cols;
    rows = A.rows;
    data = A.data;
    A.cols = 0;
    A.rows = 0;
    A.data = nullptr;
}


Matrix::~Matrix() {
    delete[] data;
}


void Matrix::set_zero() {
    if (data == nullptr) return;
    std::memset(data, 0, sizeof(MatrixItem) * rows * cols);
}


void Matrix::fill(std::vector <MatrixItem> values)
{
    if (data == nullptr) throw Matrix_Exception("Error in Matrix_filling");

    if (values.size() >= rows * cols) {
        for (size_t idx = 0; idx < cols * rows; ++idx) {
            data[idx] = values[idx];
        }
    }
    else {
        auto idx = values.begin();
        for (; idx != values.end(); ++idx) {
            data[idx - values.begin()] = *idx;
        }
        for (; idx != values.end(); ++idx) {
            *idx = 0.0;
        }
    };
}


void Matrix::set_one()
{
    set_zero();
    for (size_t idx = 0; idx < rows * cols; idx += cols + 1)
        data[idx] = 1.;
}


void Matrix::print()
{
    if (data == nullptr) throw Matrix_Exception("Error in Matrix_print");

    std::cout << "\n";
    for (size_t r = 0; r < rows; r++) {
        std::cout << "[";
        for (size_t c = 0; c < cols; c++) {
            std::cout << data[r * cols + c];
            if (cols != cols - 1)
                std::cout << "\t";
        }
        std::cout << "]\n";
    }
    std::cout << "\n";
}


Matrix& Matrix::operator=(const Matrix& A)
{
    if (rows == A.rows || cols == A.cols) {   
        rows = A.rows;
        cols = A.cols;
        memcpy(data, A.data, rows * cols * sizeof(MatrixItem));
        return *this;
    }
    
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


// SUM = B + A
Matrix& Matrix::operator+(const Matrix& A) {
    if (A.cols != cols || A.rows != rows)
        throw Matrix_Exception("Operator+: Incorrect sizes");

    Matrix* SUM = new Matrix(*this);
    *SUM += A;
    return *SUM;
}


//  SUB= B - A
Matrix& Matrix::operator-(const Matrix& A) {
    if (A.cols != cols || A.rows != rows)
        throw Matrix_Exception("Operator-: Incorrect sizes");

    Matrix* SUB = new Matrix(*this);
    *SUB -= A;

    return *SUB;
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


//MULT = B * A
Matrix& Matrix::operator*(const Matrix& A)
{
    if (A.cols != rows)
        throw Matrix_Exception("Operator*: Multiplication Error");

    Matrix* MULT = new Matrix(rows, A.cols);

    for (size_t col = 0; col < cols; ++col) {
        for (size_t rowA = 0; rowA < A.rows; ++rowA) {
            MULT->data[rowA * cols + col] = 0;
            for (size_t idx = 0; idx < A.cols; ++idx) {
                MULT->data[rowA * cols + col] += A.data[rowA * A.cols + idx]
                    * data[idx * cols + col];
            }
        }
    };
    return *MULT;
}


Matrix& Matrix::operator/(const MatrixItem k)
{
    Matrix* C = new Matrix(rows, cols);

    for (size_t idx = 0; idx < cols * rows; ++idx)
        C->data[idx] = data[idx] / k;
    return *C;
}


// B += A
Matrix& Matrix::operator+=(const Matrix& A) {
    if (A.cols != cols || A.rows != rows)
        throw Matrix_Exception("Operator+=: Incorrect sizes");

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        data[idx] += A.data[idx];

    return *this;
}


// A -= k
Matrix& Matrix::operator-=(const Matrix& A)
{
    if (A.cols != cols || A.rows != rows)
        throw Matrix_Exception("Operator-=: Incorrect sizes");

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        data[idx] -= A.data[idx];
    return *this;
}


// A /= k
Matrix& Matrix::operator/=(const MatrixItem k)
{
    for (size_t idx = 0; idx < cols * rows; ++idx)
        data[idx] = data[idx] / k;
    return *this;
}


// exp = exp(A)
Matrix& Matrix::exp(Matrix& A)
{
    if (A.cols != A.rows)
        throw Matrix_Exception("exp: Not square");
    if (A.cols == 0)
        throw Matrix_Exception("exp: ");

    Matrix* exp = new Matrix(A.rows, A.cols);
    exp->set_one();

    Matrix term(A.rows, A.cols);
    term.set_one();

    for (int idx = 1; idx < 100; ++idx) {

        term = term * A / idx;
        *exp += term;

    }
    return *exp;
}


int main()
{
    Matrix A(2, 2);
    std::vector <MatrixItem> array{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
    A.fill(array);
    A.print();
    A.free();
}
