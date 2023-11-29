#pragma once
#include <ctime>
#include <iostream>
#include <windows.h>
#include <cmath>
#include <stdexcept>
const double EPS = 1e-6;


class Matrix_Exception : public std::domain_error
{
public:
    Matrix_Exception(const char *const &msg) : domain_error(msg) {}
};


Matrix_Exception NOTSQUARE("Error: the matrix must be square(should have nxn size)\n");
Matrix_Exception NOTEQUAL("Error: the matrix should have the same size\n");
Matrix_Exception MULTIPLYERROR("Error: first matrix cols not equal to the second matrix row.\n");
Matrix_Exception ZERODIVISION("Error: divide by zero\n");
Matrix_Exception MEM_ERROR("Error: memory is not allocated\n");
Matrix_Exception EMPTY_MATRIX("Error: Function can't return an empty matrix\n");


class Matrix {
private:
    size_t rows;
    size_t cols;
    double *data;

public:
    Matrix(size_t rows, size_t cols, double *data);
    Matrix(size_t rows, size_t cols);
    Matrix();
    ~Matrix();
    Matrix(const Matrix &A);
    Matrix(Matrix &&A) noexcept;

public:
    void matrix_print();

    size_t get_row();
    size_t get_col();
    double* get_data();

    void set_zero();
    void set_identity();
    void transpose();
    Matrix exponent(const size_t step = 100);
    Matrix minor(const unsigned int minor_row, const unsigned int minor_col);
    Matrix reverse(const Matrix *matrix);
    
    double determinant(const Matrix *matrix);

    Matrix& operator=(Matrix &&A) noexcept;
    Matrix& operator=(const Matrix &A);
    void operator+=(const Matrix &A);
    void operator-=(const Matrix &A);
    void operator*=(const double k);
    void operator/=(const double k);
    void operator*=(const Matrix &A);

    Matrix operator+(const Matrix &A);
    Matrix operator-(const Matrix &A);
    Matrix operator*(const Matrix &A);
    Matrix operator*(const double k);
    Matrix operator/(const double k);

    bool operator!=(const Matrix &A);
    bool operator==(const Matrix &A);
    friend std::ostream &operator<<(std::ostream &, const Matrix);

private:
    Matrix sum_for_exp(const size_t accuracy);    
};


Matrix::Matrix() : rows(0), cols(0), data(nullptr) {}


Matrix::Matrix(const Matrix &matrix) {   
    rows = matrix.rows;
    cols = matrix.cols;
    data = new double[rows * cols];
    memcpy(data, matrix.data, rows * cols * sizeof(double));
}


Matrix::Matrix(size_t num_row, size_t num_col)
{
    rows = num_row;
    cols = num_col;
    data = new double[rows * cols];
}


Matrix::Matrix(size_t num_row, size_t num_col, double *array)
{   
    rows = num_row;
    cols = num_col;
    data = new double[rows * cols];
    if (!data)
        throw MEM_ERROR;
    memcpy(data, array, rows * cols * sizeof(double));
}


Matrix::Matrix(Matrix &&mat) noexcept : data(mat.data), rows(mat.rows), cols(mat.cols) // Конструктор перемещения
{
    mat.data = nullptr;
    mat.rows = 0;
    mat.cols = 0;
}


std::ostream &operator<<(std::ostream &out, const Matrix matrix)
{
    for (size_t row = 0; row < matrix.rows; row++)
    {
        for (size_t col = 0; col < matrix.cols; col++)
        {
            out << matrix.data[row * matrix.cols + col] << "\t";
        }
        out << std::endl;
    }
    out << std::endl;
    return (out);
}


bool Matrix::operator==(const Matrix &A, double EPS = 0.0001)
{
    if (cols != A.cols || rows != A.rows)
        return false;
    for (unsigned int idx = 0; idx < cols * rows; idx++){
        if (abs(data[idx] - A.data[idx]) > EPS)
            return false;
    }
    return true;
}


bool Matrix::operator!=(const Matrix &matrix)
{
    return !(*this == matrix);
}


void Matrix::set_zero()
{
    if (data != nullptr)
    memset(data, 0, rows * cols * sizeof(double));
}


void Matrix::set_identity()
{
    set_zero();
    for (unsigned int idx = 0; idx < cols * rows; idx += rows + 1){
        data[idx] = 1.0;
    }
}


void Matrix::transpose()
{
    Matrix trans(cols, rows);
    for (unsigned int row = 0; row < trans.rows; row++){
        for (unsigned int col = 0; col < trans.cols; col++){
            trans.data[row * trans.cols + col] = data[col * trans.rows + row];
        }
    }
    *this = trans;
}


size_t Matrix::get_row()
{
    return rows;
}


size_t Matrix::get_col()
{
    return cols;
}


Matrix& Matrix::minor(const unsigned int minor_row, const unsigned int minor_col)
{
    if (rows == 0 || cols == 0){
        throw EMPTY_MATRIX;
    }
    Matrix *minor = new Matrix(rows - 1, cols - 1);
    unsigned int minor_index = 0;
    for (unsigned int row = 0; row < rows; row++) {
        for (unsigned int col = 0; col < cols; col++){
            if (row == minor_row || col == minor_col)
                continue;
            minor.data[minor_index++] = data[row * cols + col];
        }
    }
    return minor;
}


void Matrix::operator+=(const Matrix &matrix)
{
    if (rows != matrix.rows || cols != matrix.cols)
        throw NOTEQUAL;
    for (unsigned int index = 0; index < rows * cols; ++index){
        data[index] += matrix.data[index];
    }
}


void Matrix::operator-=(const Matrix &matrix)
{
    if (rows != matrix.rows || cols != matrix.cols)
        throw NOTEQUAL;
    for (unsigned int index = 0; index < rows * cols; ++index){
        data[index] -= matrix.data[index];
    }
}


void Matrix::operator*=(const double k)
{
    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] *= k;
    }
}


void Matrix::operator/=(const double k)
{
    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] /= k;
    }
}


void Matrix::operator*=(const Matrix &matrix)
{
    if (cols != matrix.rows)
        throw MULTIPLYERROR;

    Matrix multiplication(rows, matrix.cols);
    for (unsigned int row = 0; row < multiplication.rows; row++){
        for (unsigned int col = 0; col < multiplication.cols; col++){
            double sum = 0;
            for (unsigned int k = 0; k < matrix.rows; k++){
                sum += data[row * cols + k] * matrix.data[k * matrix.cols + col];
            }
            multiplication.data[row * multiplication.cols + col] = sum;
        }
    }
    *this = multiplication;
}


Matrix &Matrix::operator=(const Matrix &A)
{
    if (this == &A)
        return *this;
    if (rows * cols == A.rows * A.cols)
        memcpy(A);
    delete[] data;                                
    rows = A.rows;
    cols = A.cols;
    data = new double[rows * cols];
    memcpy(data, A.data, rows * cols * sizeof(double));
    return *this;
}


Matrix& Matrix::operator=(Matrix &&A) noexcept 
{
    delete[] data;
    rows = A.rows;
    cols = A.cols;
    data = A.data;
    A.data = nullptr;
    A.rows = 0;
    A.cols = 0;
    return *this;
}


Matrix& Matrix::operator+(const Matrix &B)
{
    Matrix add(*this);
    add += B;
    return add;
}


Matrix& Matrix::operator-(const Matrix &B)
{
    Matrix sub(*this);
    sub -= B;
    return sub;
}


Matrix& Matrix::operator*(const double k)
{
    Matrix multiply(*this);
    multiply *= k;
    return multiply;
}


Matrix& Matrix::operator*(const Matrix &B)
{
    Matrix multiply(*this);
    multiply *= B;
    return multiply;
}


Matrix& Matrix::operator/(const double k)
{
    Matrix multiply(*this);
    multiply /= k;
    return multiply;
}


double Matrix::determinant(const Matrix *matrix) // Из-за рекурсии принимает снова себя
{
    if (matrix->rows != matrix->cols)
        throw NOTSQUARE;
    double det = 0;
    int k = 1;
    if (matrix->rows == 0)
        return NAN;
    if (matrix->rows == 1)
        return matrix->data[0];
    if (matrix->rows == 2){
        return (matrix->data[0] * matrix->data[3] - matrix->data[2] * matrix->data[1]);
    }
    for (unsigned int idx = 0; idx < matrix->cols; idx++){
        Matrix temp = minor(0, idx);
        det += k * matrix->data[idx] * determinant(&temp);
        k = -k;
    }
    return det;
}


Matrix Matrix::reverse(const Matrix *matrix) // Из-за рекурсии принимает снова себя
{ 
    double d = determinant(matrix);
    if (matrix->rows != matrix->cols)
        throw NOTSQUARE;
    if (fabs(d) < EPS)
        throw ZERODIVISION;
    Matrix reverse(matrix->rows, matrix->cols);
    int k = 1;
    for (unsigned int row = 0; row < reverse.rows; row++){
        for (unsigned int col = 0; col < reverse.cols; col++){
            Matrix temp = minor(row, col);
            reverse.data[row * matrix->cols + col] = k * determinant(&temp);
            k = -k;
        }
    }
    reverse.transpose();
    reverse /= d;
    return reverse;
}


Matrix Matrix::sum_for_exp(const size_t accuracy)
{
    Matrix E = Matrix(rows, cols);
    if(accuracy == 0){
       E.set_identity();
       return E;
    } 
    
    if(accuracy == 1){
        return (*this + E);
    }
    
    E = Matrix(*this);
    for(size_t id = 2; id < accuracy; ++id){
            E = E * (*this) / id;
    }
    return E;
}


Matrix Matrix::exponent(const size_t accuracy = 30)
{
    if(cols != rows){
        throw NOTSQUARE;
    }

    Matrix sum = Matrix(rows, cols);
    sum.set_identity();

    Matrix exp = sum;
    for(size_t deg_acc = 1; deg_acc <= accuracy ; ++deg_acc){
        sum = sum * (*this) / deg_acc;
        exp += sum;
    }

    return exp;
}