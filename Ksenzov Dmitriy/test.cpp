#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <iostream>
#include <math.h>

typedef double MatrixItem;

class Matrix {
private:
    size_t cols;
    size_t rows;
    MatrixItem *data;
public:
    Matrix() : cols(0), rows(0), data(nullptr) {};
    Matrix(const size_t cols, const size_t rows);
    Matrix(const size_t cols, const size_t rows, const MatrixItem *values);
    Matrix(Matrix& A);
    Matrix(Matrix&& A);
    ~Matrix();
public:
    void print();
public:
    Matrix& operator=(const Matrix& A);
    Matrix& operator+(const Matrix& A);
    Matrix& operator-(const Matrix& A);
    Matrix& operator*(const Matrix& A);
    Matrix& transposition();
    MatrixItem determinant();
    Matrix& exponent();
};


class MatrixExeption : public std::exception {
private:
    std::string msg;
public:
    MatrixExeption(std::string msg) : msg{msg} {};
};


void print_determinant(const MatrixItem a)
{
    printf("\nMatrix determinant = %4.2lf\n", a);
}
// Можно ли добавить в класс матикс?

Matrix::Matrix(const size_t cols, const size_t rows) 
    : cols(cols), rows(rows)
{
     if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols)
        throw MatrixExeption("too large object");
    data = new MatrixItem[rows * cols];
}


Matrix::Matrix(const size_t cols, const size_t rows, const MatrixItem *values)
    : cols(cols), rows(rows)
{
    if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols)
        throw MatrixExeption("too large object");
    data = new MatrixItem[rows * cols];
   memcpy(data, values, rows * cols * sizeof(MatrixItem));
}


Matrix::~Matrix()
{
    if (data != nullptr) {
        delete[] data;
    }
}


Matrix::Matrix(Matrix& A)
{
    rows = A.rows;
    cols = A.cols;
    data = new MatrixItem[rows * cols];
    memcpy(data, A.data, rows * cols * sizeof(MatrixItem)); 
}


Matrix::Matrix(Matrix&& A)
{
    rows = A.rows;
    cols = A.cols;
    data = A.data;
    A.rows = 0;
    A.cols = 0;
    A.data = nullptr; 
}


void Matrix::print()
{
printf("\n");
for (size_t col = 0; col < rows; ++col) {
    printf("[ ");
    for (size_t row = 0; row < cols; ++row) {
        printf(" %4.2f", data[row + col * cols ]);
    }
    printf("]\n");
}
}

// C = A
Matrix& Matrix::operator=(const Matrix& A)
{
    if (&A == this) return *this;
 
    delete[] data;
    cols = A.cols;
    rows = A.rows;
    data = new MatrixItem[A.cols * A.rows];
    memcpy(this->data, A.data, rows * cols * sizeof(MatrixItem));
    return *this;
}


// C = A + B
Matrix& Matrix::operator+(const Matrix& A)
{
    if (A.cols != this->cols || A.rows != this->rows)
        throw MatrixExeption("Matrix A and B are not proportional");
    
    Matrix *C = new Matrix(A.cols, A.rows);

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx) 
        C->data[idx] = A.data[idx] + this->data[idx];
    return *C;
}


// C = A - B
Matrix& Matrix::operator-(const Matrix& A)
{
    if (A.cols != this->cols || A.rows != this->rows)
        throw MatrixExeption("Matrix A and B are not proportional");
    
    Matrix *C = new Matrix(A.cols, A.rows);

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx) 
        C->data[idx] = A.data[idx] - this->data[idx];
    return *C;
}


// C = A * B
Matrix& Matrix::operator*(const Matrix& A)
{
    if (A.cols != this->rows)
    throw MatrixExeption("The rows of the matrix A are not equal to the columns of matrix B");

    Matrix *C = new Matrix(this->rows, A.cols);

    for (size_t C_col = 0; C_col < this->rows; ++C_col) {
        for (size_t C_row = 0; C_row < A.cols; ++C_row) {
            C->data[C_row + C_col * A.cols] = 0;
            for (size_t idx = 0; idx < this->cols; ++idx) {
                C->data[C_row + C_col * A.cols] += this->data[idx + (C_col * this->cols)]
                * A.data[idx * A.cols + C_row];
            };
        };
    };
    return *C;
}


// C = A^T
Matrix& Matrix::transposition()
{
    Matrix *C = new Matrix(rows, cols);
    for (size_t C_row = 0; C_row < cols; ++C_row) {
        for (size_t C_col = 0; C_col < rows; ++C_col) {
            C->data[C_col + C_row * rows] = data[C_col * cols + C_row];
        };
    };
    return *C;
}


// C = |A| (A[1x1], A[2x2], A[3x3])
MatrixItem Matrix::determinant()
{
    if (cols != rows) 
    throw MatrixExeption ("the numbers of columns and rows of the matrix do not match");
    MatrixItem C; 
    switch (rows)
    {
    case 1:
        C = data[0];
        return C;
        break;
    case 2:
        C = data[0] * data[3] - data[1] * data[2];
        return C;
        break;
    case 3:
        C =
        + data[0] * data[4] * data[8]
        + data[6] * data[1] * data[5]
        + data[3] * data[7] * data[2]
        - data[2] * data[4] * data[6]
        - data[5] * data[7] * data[0]
        - data[3] * data[1] * data[8];
        return C;
        break;    
    default:
        throw MatrixExeption ("valid matrix size 1x1, 2x2, 3x3") ;
        break;
    };
}


// C = e^A
Matrix& Matrix::exponent()
{
    if (cols != rows) 
    throw MatrixExeption ("the numbers of columns znd rows of the matrix do not match");

    Matrix *Previous_step = new Matrix(rows, cols);
    memset(Previous_step->data, 0, sizeof(MatrixItem) * rows * cols);
    for (size_t idx = 0; idx < rows * cols; idx += cols + 1) Previous_step->data[idx] = 1;
    for (size_t idx = 0; idx < cols * rows; ++idx) Previous_step->data[idx] += this->data[idx];

    Matrix *Exp = new Matrix(rows, cols);

    Matrix *Power = new Matrix(rows, cols);
    
    for (unsigned int k = 2; k <= 5; ++k) { 

        for (size_t Power_col = 0; Power_col < rows; ++Power_col) {
            for (size_t Power_row = 0; Power_row < cols; ++Power_row) {
                for (size_t idx = 0; idx < cols; ++idx) {
                    Power->data[Power_row + Power_col * cols] += Previous_step->data[idx + (Power_col * cols)]
                    * this->data[idx * cols + Power_row];
                };
            };
        };
        
        for (unsigned int idx = 0; idx < cols * rows; ++idx)
            Exp->data[idx] = Power->data[idx] / k;

        memcpy(Previous_step->data, Exp->data, rows * cols * sizeof(MatrixItem));
    };
    return *Previous_step;
}


int main () {
    MatrixItem values[] = {24., 15., 2., 40.,
                           5., 7., 1., 33.,
                           21., 20., 51., 1.};
    MatrixItem values2[] = {24., 15., 2.,
                           40., 5., 7.,
                           1., 33., 21.,
                           4., 13., 23.};
    MatrixItem values3[] = {24., 15., 2.,
                           40., 5., 7.,
                           1., 33., 21.};
    Matrix A(4, 3, values);
    Matrix B(A);
    Matrix C(4, 3);
    Matrix D(4, 3);
    Matrix E(3, 4, values2);
    Matrix F(3, 3);
    Matrix G(3, 4);
    Matrix I(3, 3, values3);
    MatrixItem a;
    Matrix H(3, 3);
    C = A + B;
    D = A - B;
    F = A * E;
    G = A.transposition();
    a = I.determinant();
    H = I.exponent();
    A.print();
    B.print();
    C.print();
    D.print();
    E.print();
    F.print();
    G.print();
    I.print();
    print_determinant(a);
    H.print();
    return 0;
}