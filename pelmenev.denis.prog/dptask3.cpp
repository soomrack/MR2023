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
    Matrix() : rows(0), cols(0), data(nullptr) {};
    Matrix(const size_t cols, const size_t rows);
    Matrix(Matrix& A);
    Matrix(Matrix&& A);
    ~Matrix();
public:
    Matrix& operator=(const Matrix& A);
    Matrix& operator=(const Matrix&& A);
    Matrix& operator+(const Matrix& A);
    Matrix& operator+=(const Matrix& A); //Matrix&& A
    Matrix& operator-(const Matrix& A);
    Matrix& operator-=(const Matrix& A);
    Matrix& operator*(const Matrix& B);
    Matrix& operator*=(const Matrix& B);
    Matrix& operator*(const double& coeff);
    Matrix& operator*=(const double& coeff);
public:
    void fill(std::vector <MatrixItem> values);
    void free();
    void print();
    void set_zero();
    Matrix transp();
    Matrix exponent(const Matrix A, const unsigned int degree = 10);
    double determinant();
private:
    int det_if_zero();
    void det_prep(size_t diag, double *coeff);
};


class MatrixException: public std::exception {
private:
    std::string msg;
public:
    Matrix_Exception(std::string msg) : msg{ msg } {}
    std::string get_message() const { return msg; }
};

MatrixException INCORRECT_SIZE_OF_MATRIX("The matrix has an incorrect size\n");
MatrixException NULL_MATRIX("Your matrix is empty\n");


void Matrix::free()
{
    cols = 0;
    rows = 0;
    delete[] data;
    data = nullptr;
}


Matrix::Matrix(const size_t cols, const size_t rows)
    : cols(cols), rows(rows), data(nullptr)
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


Matrix::~Matrix() {
    free();
}


void Matrix::set_zero()
{
    if (data == nullptr) throw NULL_MATRIX;

    memset(data, 0, cols * rows * sizeof(MatrixItem));
}


void Matrix::fill(std::vector <MatrixItem> values)
{
    if (data == nullptr) throw NULL_MATRIX;

    if (values.size() > rows * cols)
        for (size_t idx = 0; idx < cols * rows; ++idx)
            data[idx] = values[idx];
    else {
        for (auto idx = values.begin(); idx != values.end(); ++idx)
            data[idx] = values[idx];
        if (values.size() < cols * rows)
            for (auto idx = values.end(); idx < cols * rows - 1; ++idx)
                data[idx] = 0.0;
    };
}


void Matrix::print()
{
    if (data == nullptr) throw NULL_MATRIX;

    std::cout << "_____________________________________________" << std::endl;

    for (size_t idx = 1; idx <= cols * rows; ++idx) {
        std::cout << data[idx - 1];
        if (idx % cols == 0 && idx >= cols)
            std::cout << "" << std::endl;
    };
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


Matrix& Matrix::operator=(const Matrix&& A)
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


Matrix& Matrix::operator+(const Matrix& A)
{
    if (A.cols != cols || A.rows != rows) throw INCORRECT_SIZE_OF_MATRIX;

    Matrix* result = new Matrix(*this);

    for (size_t idx = 0; idx < cols * rows; ++idx)
        result->data[idx] += A.data[idx];

    return *result;
}


Matrix& Matrix::operator+=(const Matrix& A)
{
    if (A.cols != cols || A.rows != rows) throw INCORRECT_SIZE_OF_MATRIX;

    for (size_t idx = 0; idx < cols * rows; ++idx)
        data[idx] += A.data[idx];
    
    return *this;
}


Matrix& Matrix::operator-(const Matrix& A)
{
    if (A.cols != cols || A.rows != rows) throw INCORRECT_SIZE_OF_MATRIX;

    Matrix* result = new Matrix(*this);

    for (size_t idx = 0; idx < cols * rows; ++idx)
        result->data[idx] -= A.data[idx];

    return *result;
}


Matrix& Matrix::operator-=(const Matrix& A)
{
    if (A.cols != cols || A.rows != rows) throw INCORRECT_SIZE_OF_MATRIX;

    for (size_t idx = 0; idx < cols * rows; ++idx)
        data[idx] -= A.data[idx];

    return *this;
}


Matrix& Matrix::operator*(const Matrix& B)
{
    if (cols != B.rows) throw INCORRECT_SIZE_OF_MATRIX;

    Matrix* result = new Matrix(*this);

    for (size_t rowA = 0; rowA < rows; ++rowA)
        for (size_t colB = 0; colB < B.cols; ++colB) {
            result->data[result->cols * rowA + colB] = 0.0;
            for (size_t colA = 0; colA < cols; ++colA)
                result->data[result->cols * rowA + colB] += data[colA + rowA * cols] * B.data[B.cols * colA + colB];
        };
    
    return *result;
}


Matrix& Matrix::operator*=(const Matrix& B)
{
    *this = *this * B;

    return *this;
}


Matrix& Matrix::operator*(const double& coeff)
{
    Matrix *result = new Matrix(*this);

    for (size_t idx = 0; idx < cols * rows; ++idx)
        result->data[idx] = data[idx] * coeff;
    
    return *result;
}


Matrix& Matrix::operator*=(const double& coeff)
{
    for (size_t idx = 0; idx < cols * rows; ++idx)
        data[idx] = data[idx] * coeff;
    
    return *this;
}


Matrix Matrix::transp()
{
    Matrix result = Matrix(*this);

    for (size_t row = 0; row < rows; ++row)
        for (size_t col = 0; col < cols; ++col)
            result.data[row * cols + col] = data[row + col * cols];
    
    return result;
}


Matrix Matrix::exponent(const Matrix A, const unsigned int degree = 10)
{
    if (A.cols != A.rows) throw INCORRECT_SIZE_OF_MATRIX;
    
    Matrix result = Matrix(A.cols, A.rows);

    result.set_zero();

    Matrix B = Matrix(A);

    for (size_t diag = 0; diag < result.rows; ++diag)
        result.data[diag * result.cols + diag] += 1;
    
    result += A;

    for (int trm = 2; trm <= degree; ++trm) {
       B *= A;
       B *= 1.0 / trm;
       result += B;
    };

    return result;
}


int Matrix::det_if_zero()
{
    size_t count;

    for (size_t row = 0; row < rows; ++row) { // суммы по строкам
        count = 0;
        for (size_t col = 0; col < cols; ++col) {
            count += 1;
            if (data[row * cols + col] != 0.0)
                break;
        };
        
        if (count == cols)
            return 0;
    };
    
    for (size_t col = 0; col < cols; ++col) { // суммы по строкам
        count = 0;
        for (size_t row = 0; row < rows; ++row) {
            count += 1;
            if (data[row * cols + col] != 0.0)
                break;
        };
        
        if (count == rows)
            return 0;
    };
    
    return 1;
}


void Matrix::det_prep(size_t diag, double *coeff)
{
    size_t buff_one = diag; // запоминается номер строки

    if (data[diag * cols + diag] == 0.0) {
        for (size_t row = diag; row < rows; ++row) {
            buff_one += 1;
            if (data[row * cols] != 0.0)
                break;
        };

        double buff_two = 0; // запоминается значение в ячейке
        
        for (size_t col = diag; col < cols; ++col) {
            buff_two = data[diag * cols + col];
            data[diag * cols + col] = data[buff_one * cols + col];
            data[buff_one * cols + col] = buff_two;
        };

        *coeff *= -1;
    };
}


double Matrix::determinant()
{
    if (cols != rows) throw INCORRECT_SIZE_OF_MATRIX;
    
    Matrix C = Matrix(cols, rows);
    if (C.data == nullptr) throw NULL_MATRIX;
    C = *this;

    if (cols == 1) {
        C.free();
        return data[0];
    };

    if (C.det_if_zero() == 0) {
        C.free();
        return 0.0;
    };
    
    double coeff = 1.0;
    double diagonal = 1.0;
    double buff_one, buff_two;

    for (size_t diag = 0; diag < rows - 1; ++diag) {
        C.det_prep(diag, &coeff);
        coeff *= C.data[diag * cols + diag];
        buff_one = C.data[diag * cols + diag];

        for (size_t col = diag; col < cols; ++col)
            C.data[diag * cols + col] /= buff_one;

        for (size_t row = diag + 1; row < rows; ++row) {
            buff_two = C.data[row * cols + diag];
            for (size_t col = diag; col < cols; ++col) {
                C.data[row * cols + col] = C.data[row * cols + col] - C.data[diag * cols + col] * buff_two;
            };  
        };
    };

    for (size_t diag = 0; diag < rows; ++diag)
        diagonal *= C.data[diag * cols + diag];
    
    C.free();

    double result = coeff * diagonal;
    
    return result;
}


int main()
{
    Matrix A(3, 3);
    std::vector <MatrixItem> array(1.0, 2.0, 3.0, 4.0, 5.0, 0.0, 2.0, 9.0, -3.0);
    A.fill(array);
    A.print();
    A.free();
}
