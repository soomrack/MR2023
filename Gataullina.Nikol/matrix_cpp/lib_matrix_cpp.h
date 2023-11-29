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
    Matrix_Exception(const char *const &msg) : domain_error(msg)
    {
    }
};


Matrix_Exception NOTSQUARE("Error: the matrix must be square(should have nxn size)\n");
Matrix_Exception NOTEQUAL("Error: the matrix should have the same size\n");
Matrix_Exception MULTIPLYERROR("Error: first matrix cols not equal to the second matrix row.\n");
Matrix_Exception ZERODIVISION("Error: divide by zero\n");
Matrix_Exception MEM_ERROR("Error: memory is not allocated\n");
Matrix_Exception EMPTY_MATRIX("Error: Function can't return an empty matrix\n");


class Matrix
{
private:
    size_t rows;
    size_t cols;
    double *data;
    Matrix sum_for_exp(const size_t accuracy);

public:
    Matrix(size_t, size_t, double *);
    Matrix(size_t, size_t);
    Matrix();
    ~Matrix();
    Matrix(const Matrix &);
    Matrix(Matrix &&) noexcept;
    

    void matrix_print();

    size_t get_row();
    size_t get_col();
    double* get_data();

    void matrix_zero();
    void matrix_identity();
    void matrix_transpose();
    Matrix matrix_exponent(const size_t);
    Matrix matrix_minor(const unsigned int, const unsigned int);
    Matrix matrix_reverse(const Matrix *);
    
    double matrix_determinant(const Matrix *);

    Matrix &operator=(Matrix &&) noexcept;
    Matrix &operator=(const Matrix &);
    void operator+=(const Matrix &);
    void operator-=(const Matrix &);
    void operator*=(const double);
    void operator/=(const double);
    void operator*=(const Matrix &);

    Matrix operator+(const Matrix &);
    Matrix operator-(const Matrix &);
    Matrix operator*(const Matrix &);
    Matrix operator*(const double);
    Matrix operator/(const double);

    bool operator!=(const Matrix &);
    bool operator==(const Matrix &);
    friend std::ostream &operator<<(std::ostream &, const Matrix);
};


Matrix::Matrix() : rows(0), cols(0), data(nullptr) {}

Matrix::Matrix(const Matrix &matrix) {   
    this->rows = matrix.rows;
    this->cols = matrix.cols;
    this->data = new double[this->rows * this->cols];
    if (!this->data)
        throw MEM_ERROR;
    memcpy(this->data, matrix.data, this->rows * this->cols * sizeof(double));
}


Matrix::Matrix(size_t num_row, size_t num_col)
{
    this->rows = num_row;
    this->cols = num_col;
    this->data = new double[rows * cols];
    if (!this->data)
        throw MEM_ERROR;
}

Matrix::Matrix(size_t num_row, size_t num_col, double *array)
{   
    
    this->rows = num_row;
    this->cols = num_col;
    this->data = new double[rows * cols];
    if (!this->data)
        throw MEM_ERROR;
    memcpy(this->data, array, rows * cols * sizeof(double));
}

Matrix::Matrix(Matrix &&mat) noexcept : data(mat.data), rows(mat.rows), cols(mat.cols) // Конструктор перемещения
{
    mat.data = nullptr;
    mat.rows = 0;
    mat.cols = 0;
}

Matrix::~Matrix()
{
    if (this->data != nullptr)
    {
        delete[] this->data;
        this->cols = 0;
        this->rows = 0;
        this->data = nullptr;
    }
}

std::ostream &operator<<(std::ostream &out, const Matrix matrix)
{
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
}

bool Matrix::operator==(const Matrix &A)
{
    if (this->cols != A.cols || this->rows != A.rows)
        return false;
    for (unsigned int idx = 0; idx < this->cols * this->rows; idx++)
    {
        if (abs(this->data[idx] - A.data[idx]) > EPS)
            return false;
    }
    return true;
}

bool Matrix::operator!=(const Matrix &matrix)
{
    return !(*this == matrix);
}


void Matrix::matrix_zero()
{
    memset(this->data, 0, this->rows * this->cols * sizeof(double));
}

void Matrix::matrix_identity()
{
    matrix_zero();
    for (unsigned int idx = 0; idx < this->cols * this->rows; idx += rows + 1)
    {
        this->data[idx] = 1.0;
    }
}

void Matrix::matrix_transpose()
{
    Matrix trans(this->cols, this->rows);
    for (unsigned int row = 0; row < trans.rows; row++)
    {
        for (unsigned int col = 0; col < trans.cols; col++)
        {
            trans.data[row * trans.cols + col] = this->data[col * trans.rows + row];
        }
    }
    *this = trans;
}


size_t Matrix::get_row()
{
    return (this->rows);
}

size_t Matrix::get_col()
{
    return (this->cols);
}

double* Matrix::get_data() {
    return (this->data);
}

Matrix Matrix::matrix_minor(const unsigned int minor_row, const unsigned int minor_col)
{
    if (this->rows == 0 || this->cols == 0)
    {
        throw EMPTY_MATRIX;
    }
    Matrix minor(this->rows - 1, this->cols - 1);
    unsigned int minor_index = 0;
    for (unsigned int row = 0; row < this->rows; row++)
    {
        for (unsigned int col = 0; col < this->cols; col++)
        {
            if (row == minor_row || col == minor_col)
                continue;
            minor.data[minor_index++] = this->data[row * this->cols + col];
        }
    }
    return minor;
}

void Matrix::operator+=(const Matrix &matrix)
{
    if (this->rows != matrix.rows || this->cols != matrix.cols)
        throw NOTEQUAL;
    for (unsigned int index = 0; index < rows * cols; ++index)
    {
        this->data[index] += matrix.data[index];
    }
}

void Matrix::operator-=(const Matrix &matrix)
{
    if (this->rows != matrix.rows || this->cols != matrix.cols)
        throw NOTEQUAL;
    for (unsigned int index = 0; index < rows * cols; ++index)
    {
        this->data[index] -= matrix.data[index];
    }
}

void Matrix::operator*=(const double k)
{
    for (unsigned int idx = 0; idx < this->rows * this->cols; idx++)
    {
        this->data[idx] *= k;
    }
}

void Matrix::operator/=(const double k)
{
    for (unsigned int idx = 0; idx < this->rows * this->cols; idx++)
    {
        this->data[idx] /= k;
    }
}


void Matrix::operator*=(const Matrix &matrix)
{
    if (this->cols != matrix.rows)
        throw MULTIPLYERROR;
    Matrix multiplication(this->rows, matrix.cols);
    for (unsigned int row = 0; row < multiplication.rows; row++)
    {
        for (unsigned int col = 0; col < multiplication.cols; col++)
        {
            double sum = 0;
            for (unsigned int k = 0; k < matrix.rows; k++)
            {
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
    delete[] this->data;
    this->rows = A.rows;
    this->cols = A.cols;
    this->data = new double[rows * cols];
    if (!data)
        throw MEM_ERROR;
    memcpy(this->data, A.data, rows * cols * sizeof(double));
    return *this;
}

Matrix &Matrix::operator=(Matrix &&A) noexcept
{
    if (this == &A)
        return *this;
    delete[] this->data;
    this->rows = A.rows;
    this->cols = A.cols;
    this->data = A.data;
    A.data = nullptr;
    A.rows = 0;
    A.cols = 0;
    return *this;
}

Matrix Matrix::operator+(const Matrix &B)
{
    Matrix add(*this);
    add += B;
    return add;
}

Matrix Matrix::operator-(const Matrix &B)
{
    Matrix sub(*this);
    sub -= B;
    return sub;
}

Matrix Matrix::operator*(const double k)
{
    Matrix multiply(*this);
    multiply *= k;
    return multiply;
}

Matrix Matrix::operator*(const Matrix &B)
{
    Matrix multiply(*this);
    multiply *= B;
    return multiply;
}

Matrix Matrix::operator/(const double k)
{
    Matrix multiply(*this);
    multiply /= k;
    return multiply;
}


double Matrix::matrix_determinant(const Matrix *matrix) // Из-за рекурсии принимает снова себя
{
    if (matrix->rows != matrix->cols)
        throw NOTSQUARE;
    double det = 0;
    int k = 1;
    if (matrix->rows == 0)
        return 0;
    if (matrix->rows == 1)
        return matrix->data[0];
    if (matrix->rows == 2)
    {
        return (matrix->data[0] * matrix->data[3] - matrix->data[2] * matrix->data[1]);
    }
    for (unsigned int idx = 0; idx < matrix->cols; idx++)
    {
        Matrix temp = matrix_minor(0, idx);
        det += k * matrix->data[idx] * matrix_determinant(&temp);
        k = -k;
    }
    return det;
}

Matrix Matrix::matrix_reverse(const Matrix *matrix) // Из-за рекурсии принимает снова себя
{ 
    double d = matrix_determinant(matrix);
    if (matrix->rows != matrix->cols)
        throw NOTSQUARE;
    if (fabs(d) < EPS)
        throw ZERODIVISION;
    Matrix reverse(matrix->rows, matrix->cols);
    int k = 1;
    for (unsigned int row = 0; row < reverse.rows; row++)
    {
        for (unsigned int col = 0; col < reverse.cols; col++)
        {
            Matrix temp = matrix_minor(row, col);
            reverse.data[row * matrix->cols + col] = k * matrix_determinant(&temp);
            k = -k;
        }
    }
    reverse.matrix_transpose();
    reverse /= d;
    return reverse;
}

Matrix Matrix::sum_for_exp(const size_t accuracy)
{
    Matrix E = Matrix(this->rows, this->cols);
    if(accuracy == 1){
       E.matrix_identity();
       return E;
    } 
    
    if(accuracy == 2){
        return *this;
    }
    
    if(accuracy > 2){
        E = Matrix(*this);
        for(size_t id = 2; id < accuracy; ++id){
            Matrix buf = Matrix(E);
            E = buf * (*this);
            E /= id;
        }
    }
    return E;
}

Matrix Matrix::matrix_exponent(const size_t accuracy = 30)
{
    if(this->cols != this->rows){
        throw NOTSQUARE;
    }

    Matrix E = Matrix(this->rows, this->cols);
    Matrix matrix_transfer;

    for(size_t deg_acc = 1; deg_acc <= accuracy ; ++deg_acc){
        matrix_transfer = this->sum_for_exp(deg_acc);
         Matrix buf1 = E;
        E = buf1 + matrix_transfer;
    }

    return E;
}