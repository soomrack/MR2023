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
    Matrix& operator=(const Matrix& A);
    Matrix& operator=(const Matrix&& A);
    Matrix& operator+(const Matrix& A);
    Matrix& operator+=(const Matrix& A);
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
    void transp(const Matrix A);
    Matrix exponent(const Matrix A, const unsigned int degree = 10);
    double determinant();
private:
    int det_if_zero();
    void det_prep(size_t diag, double *coeff);
};


class Matrix_Exception: public std::exception {
private:
    std::string msg;
public:
    Matrix_Exception(std::string msg) : message{ msg } {}
    std::string get_message() const { return msg; }
};

Matrix_Exception INCORRECT_SIZE_OF_MATRIX("The matrix has an incorrect size\n");
Matrix_Exception NULL_MATRIX("Your matrix is empty\n");


void Matrix::free()
{
    cols = 0;
    rows = 0;

    if (data == nullptr) return;

    delete[] data;
    data = nullptr;
}


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

    if (values.size() > rows * cols - 1)
        for (size_t idx = 0; idx < cols* rows; ++idx)
            data[idx] = values[idx];
    else {
        set_zero();
        for (size_t idx = 0; idx < values.size(); ++idx)
            data[idx] = values[idx];
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

    if (!(A.cols == cols && A.rows == rows)) {
        cols = A.cols;
        rows = A.rows;
        data = new MatrixItem[cols * rows];
    };

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
    if (cols == A.cols && rows == A.rows && data == A.data) return;

    cols = A.cols;
    rows = A.rows;
    delete[] data;
    this->data = new MatrixItem[cols * rows];
    memcpy(data, A.data, A.cols * A.rows * sizeof(MatrixItem));
}


Matrix& Matrix::operator=(const Matrix&& A)
{
    if (cols == A.cols && rows == A.rows && data == A.data) return;
    
    cols = A.cols;
    rows = A.rows;
    delete[] data;
    data = A.data;
}


Matrix& Matrix::operator+(const Matrix& A)
{
    Matrix* result = new Matrix(*this);
    if (A.cols != cols || A.rows != rows) {
        result->free();
        throw INCORRECT_SIZE_OF_MATRIX;
    };

    if (result->data == nullptr) throw NULL_MATRIX;

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        result->data[idx] += A.data[idx]; 

    return *result;
}


Matrix& Matrix::operator+=(const Matrix& A)
{
    if (A.cols != cols || A.rows != rows) throw INCORRECT_SIZE_OF_MATRIX;

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        this->data[idx] += A.data[idx];
    
    return *this;
}


Matrix& Matrix::operator-(const Matrix& A)
{
    Matrix* result = new Matrix(*this);
    if (A.cols != cols || A.rows != rows) {
        result->free();
        throw INCORRECT_SIZE_OF_MATRIX;
    };

    if (result->data == nullptr) throw NULL_MATRIX;

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        result->data[idx] -= A.data[idx]; 

    return *result;
}


Matrix& Matrix::operator-=(const Matrix& A)
{
    if (A.cols != cols || A.rows != rows) throw INCORRECT_SIZE_OF_MATRIX;

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        this->data[idx] -= A.data[idx];

    return *this;
}


Matrix& Matrix::operator*(const Matrix& B)
{
    Matrix* result = new Matrix(*this);
    if (result->data == nullptr) return throw NULL_MATRIX;

    if (cols != B.rows) {
        result->free();
        throw INCORRECT_SIZE_OF_MATRIX;
    };
    
    result->set_zero();

    for (size_t rowA = 0; rowA < rows; ++rowA)
        for (size_t colB = 0; colB < B.cols; ++colB)
            for (size_t colA = 0; colA < cols; ++colA)
                result->data[result->cols * rowA + colB] += data[colA + rowA * cols] * B.data[B.cols * colA + colB];
    
    return *result;
}


Matrix& Matrix::operator*=(const Matrix& B)
{
    Matrix C(cols, rows);
    C = *this * B;

    if (C.data == nullptr) throw NULL_MATRIX;
    
    this->free();
    cols = C.cols;
    rows = C.rows;
    data = C.data;

    return *this;
}


Matrix& Matrix::operator*(const double& coeff)
{
    if (data == nullptr) throw NULL_MATRIX;

    Matrix *result = new Matrix(*this);

    for (size_t idx = 0; idx < cols * rows; ++idx)
        result->data[idx] = data[idx] * coeff;
    
    return *result;
}


Matrix& Matrix::operator*=(const double& coeff)
{
    if (data == nullptr) throw NULL_MATRIX;

    for (size_t idx = 0; idx < cols * rows; ++idx)
        data[idx] = data[idx] * coeff;
    
    return *this;
}


void Matrix::transp(const Matrix A)
{
    if (A.data == nullptr) throw NULL_MATRIX;

    if (!(cols == A.rows && rows == A.cols)) {
        free();
        *this(A.rows, A.cols);
    };

    for (size_t row = 0; row < A.rows; ++row)
        for (size_t col = 0; col < A.cols; ++col)
            data[row * A.cols + col] = A.data[row + col * A.cols];
}


Matrix Matrix::exponent(const Matrix A, const unsigned int degree = 10)
{
    Matrix result;

    if (A.cols != A.rows) throw INCORRECT_SIZE_OF_MATRIX;

    result(A.cols, A.rows);

    result.set_zero();

    Matrix B(A.cols, A.rows);
    B = A;

    for (size_t diag = 0; diag < result.rows; ++diag)
        result.data[diag * result.cols + diag] += 1;
    
    result += A;

    for (int trm = 2; trm <= degree; ++trm) {
       B *= A;
       B *= 1.0 / trm;
       result += B;
    };
    
    B.free();

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
    
    Matrix C(cols, rows);
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
