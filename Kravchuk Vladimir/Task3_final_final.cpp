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
    Matrix(const size_t col, const size_t row);
    Matrix(const Matrix& A);
    Matrix(Matrix&& A);
    ~Matrix();
public:
    Matrix& operator=(const Matrix& A);
    Matrix& operator=(Matrix&& A);
    Matrix& operator+=(const Matrix& A);
    Matrix& operator+(const Matrix& A);
    Matrix& operator-=(const Matrix& A);
    Matrix& operator-(const Matrix& A);
    Matrix& operator*= (const Matrix& B);
    Matrix& operator* (const Matrix& B);
    Matrix& operator*= (const double scalar);
    Matrix& operator* (const double scalar);
public:
    void filling(std::vector <MatrixItem> values);
    void print();
    void transposition();
    void set_one();
    double det(void);
    Matrix exp(const unsigned int level);
};


class Matrix_Exception : public std::exception
{
private:
    std::string message;
public:
    Matrix_Exception(std::string message) : message{ message } {}
    std::string get_message() const { return message; }
};


Matrix::Matrix() {
    rows = 0;
    cols = 0;
    data = nullptr;
}


Matrix::Matrix(size_t col, size_t row)
{
    rows = row;
    cols = col;

    if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols) {
        cols = 0;
        rows = 0;
        data = nullptr;
        return;
    };

    data = new MatrixItem[cols * rows];
}



void Matrix::filling(std::vector <MatrixItem> values)
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
            data[idx - values.begin()] = values[idx - values.begin()];
        }
    };
}


Matrix::Matrix(const Matrix& A)
{
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
    cols = 0;
    rows = 0;
    delete[] data;
    data = nullptr;
}


void Matrix::print()
{
    if (data == nullptr) throw Matrix_Exception("Error in Matrix_print");

    std::cout << "\n";
    for (size_t r = 0; r < rows; r++) {
        std::cout << "[";
        for (size_t c = 0; c < cols; c++) {
            std::cout << data[r * cols + c];
            if (c != cols - 1)
                std::cout << "\t";
        }
        std::cout << "]\n";
    }
    std::cout << "\n";
}


Matrix& Matrix::operator=(const Matrix& A)
{
    if (this == &A) return *this;

    cols = A.cols;
    rows = A.rows;

    delete[] data;
    data = new MatrixItem[cols * rows];
    memcpy(data, A.data, A.cols * A.rows * sizeof(MatrixItem));
    return *this;
}


Matrix& Matrix::operator=(Matrix&& A)
{
    if (this == &A) return *this;

    cols = A.cols;
    rows = A.rows;
    delete[] data;
    data = A.data;

    A.cols = 0;
    A.rows = 0;
    A.data = nullptr;

    return *this;
}


Matrix& Matrix::operator+= (const Matrix& A) {
    if (A.cols != cols || A.rows != rows) throw Matrix_Exception("Error in Matrix_sum");

    for (size_t idx = 0; idx < rows * cols; idx++) {
        data[idx] += A.data[idx];
    }
    return *this;
}


Matrix& Matrix::operator+(const Matrix& A) {
    if (A.cols != cols || A.rows != rows) throw Matrix_Exception("Error in Matrix_sum(cols/=rows)");

    Matrix* sum = new Matrix(*this);

    for (size_t idx = 0; idx < cols * rows; ++idx)
        sum->data[idx] += A.data[idx];

    return *sum;
}


Matrix& Matrix::operator-=(const Matrix& A) {
    if (A.cols != cols || A.rows != rows) throw Matrix_Exception("Error in Matrix_substr");

    for (size_t idx = 0; idx < rows * cols; idx++) {
        data[idx] -= A.data[idx];
    }
    return *this;
}


Matrix& Matrix::operator-(const Matrix& A)
{
    if (A.cols != cols || A.rows != rows) throw Matrix_Exception("Error in Matrix_substr");

    Matrix* sub = new Matrix(*this);

    for (size_t idx = 0; idx < cols * rows; ++idx)
        sub->data[idx] -= A.data[idx];

    return *sub;
}


Matrix& Matrix::operator*= (const Matrix& B) {
    if (cols != B.rows) throw Matrix_Exception("Error in Matrix_mult");

    *this = *this * B;

    return *this;
}


Matrix& Matrix::operator* (const Matrix& B) {
    if (cols != B.rows) throw Matrix_Exception("Error in Matrix_mult");

    Matrix* res = new Matrix(*this);

    for (size_t rowA = 0; rowA < rows; ++rowA)
        for (size_t colB = 0; colB < B.cols; ++colB) {
            res->data[res->cols * rowA + colB] = 0.0;
            for (size_t colA = 0; colA < cols; ++colA)
                res->data[res->cols * rowA + colB] += data[colA + rowA * cols] * B.data[B.cols * colA + colB];
        };

    return *res;
}


Matrix& Matrix::operator* (const double scalar) {
    if (data == nullptr) throw Matrix_Exception("Error in Matrix_mult");

    Matrix* res = new Matrix(*this);

    for (size_t idx = 0; idx < cols * rows; ++idx)
        res->data[idx] = data[idx] * scalar;

    return *res;
}


Matrix& Matrix::operator*= (const double scalar) {
    if (data == nullptr) throw Matrix_Exception("Error in Matrix_mult");

    for (size_t idx = 0; idx < rows * cols; idx++) {
        data[idx] *= scalar;
    }
    return *this;
}


void Matrix::transposition()
{
    if (data == nullptr) throw Matrix_Exception("Error in Matrix_transposition");

    for (size_t row = 0; row < rows; row++)
        for (size_t col = 0; col < cols; col++)
            data[row * rows + col] = data[col * cols + row];
}


double Matrix::det(void)
{
    if (rows != cols) throw Matrix_Exception("Error in Matrix_det(rows/=cols)");

    if (cols == 1) return data[0];

    if (cols == 2) return (data[0] * data[3] - data[1] * data[2]);

    if (cols == 3) {
        return (data[0] * data[4] * data[8]) + \
            (data[1] * data[5] * data[6]) + \
            (data[2] * data[3] * data[7]) - \
            (data[2] * data[4] * data[6]) - \
            (data[0] * data[5] * data[7]) - \
            (data[1] * data[3] * data[8]);
    }
    throw Matrix_Exception("Error in Matrix_det");
}


void Matrix::set_one()
{
    if (data == nullptr) throw Matrix_Exception("Error in Matrix_one");
    if (cols != rows) throw Matrix_Exception("Error in set_one with size");

    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            if (row = col) data[row * cols + col] = 1.0;
            else data[row * cols + col] = 0.0;
        }
    }
        
}


Matrix Matrix::exp(const unsigned int level = 10) {
    if (data == nullptr) throw Matrix_Exception("Error in Matrix_exp");

    if (cols != rows) throw Matrix_Exception("Error in Matrix_exp(cols/=rows)");

    Matrix* exp = new Matrix(cols, rows);

    exp->set_one();

    *exp += *this;
    Matrix* sum = new Matrix(*this);

    for (int idx = 2; idx <= level; ++idx) {
        *sum *= (*this)*(1.0/idx);
        *exp += *sum;
    };

    return *exp;
}


int main()
{
    Matrix A(2, 2);
    std::vector <MatrixItem> array{ 1.0, 2.0, 3.0, 4.0, 5.0, 0.0, 2.0, 9.0, 10.0 };
    A.filling(array);
    A.print();
}
