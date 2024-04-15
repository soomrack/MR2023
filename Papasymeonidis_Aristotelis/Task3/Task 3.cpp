#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>


typedef double MatrixItem;


//DO NOT USE!
//NE UTILISER PAS!

typedef double MatrixItem;

class MatrixException : public std::exception
{
private:
    std::string message;

public:
    MatrixException(std::string msg) : message(msg.c_str()) {}
    std::string what() { return message; }
};

MatrixException ERRONEOUS_MESSAGE("erroneous message");
MatrixException WRONG_CONDITIONS("wrong_conditions");
MatrixException NO_MEMORY_ALLOCATED("no_memory_allocated");

class Matrix
{
private:
    size_t cols;
    size_t rows;
    MatrixItem *data;

public:
    Matrix();
    Matrix(const size_t rows, const size_t cols, const double *values);
    // Matrix(size_t cols, size_t rows, MatrixItem *data);
    Matrix(const size_t rows, const size_t cols);
    Matrix(const Matrix &A);
    Matrix(Matrix&& A);
    ~Matrix();

public:
    Matrix& operator= (const Matrix& M);
    Matrix& operator= (Matrix &&M);
    Matrix& operator+= (const Matrix& M);
    Matrix& operator-= (const Matrix& M);
    Matrix& operator*= (const double k);
    Matrix& operator*= (const Matrix& M);
    Matrix& operator+(const Matrix& M);
    Matrix& operator-(const Matrix& M);
    Matrix& operator*(const Matrix& M);
    Matrix& operator*(const double k);

public:
    void print();
    Matrix& make_ident(size_t rows, size_t cols);
    Matrix& sum(const Matrix &A, const Matrix &B);
    void add(const Matrix &B);
    Matrix& mult(const Matrix &A);
    Matrix& transp();
    double matrix_det();
    Matrix& exp(Matrix &A, const size_t accuracy);

private:
Matrix sum_for_e(const size_t deg_acc, const Matrix &A);
};


Matrix::Matrix()
{
    cols = 0;
    rows = 0;
    data = nullptr;
}

Matrix::Matrix(const size_t rows, const size_t cols)
{
    if (rows == 0 || cols == 0)
    {
        throw MatrixException("The matrix is not initialized");
    }

    // rows * cols < MAX_SIZE / sizeof(MatrixItem)
    if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols) throw MatrixException("The matrix is not initialized");

    this->cols = cols;
    this->rows = rows;
    data = new double[cols * rows * sizeof(MatrixItem)];
}

Matrix::Matrix(const size_t rows, const size_t cols, const double *values)
{
    this->cols = cols;
    this->rows = rows;
    this->data = nullptr;
    this->data = new double[cols * rows * sizeof(MatrixItem)];
    memcpy(this->data, values, rows * cols * sizeof(double));
}

Matrix::Matrix(Matrix &&A){
    rows = A.rows;
    cols = A.cols;
    data = A.data;

    A.rows = 0;
    A.cols = 0;
    A.data = nullptr;
}

Matrix& Matrix::operator= (const Matrix& M) {
    if (this == &M) return *this;    
    delete[] data;

    rows = M.rows;
    cols = M.cols;

    data = new MatrixItem[rows * cols];
    memcpy(data, M.data, cols * rows * sizeof(MatrixItem));

    return *this;
}

Matrix& Matrix::operator= (Matrix &&M) {
    if (this == &M) return *this;    
    delete[] data;

    rows = M.rows;
    cols = M.cols;
    data = M.data;
    M.data = nullptr;

    return *this;
}

Matrix::~Matrix()
{
    cols = 0;
    rows = 0;
    delete[] data;
    data = nullptr;
}

Matrix& Matrix::sum(const Matrix &A, const Matrix &B)
{
    if (A.cols != B.cols || A.rows != B.rows) throw MatrixException("The matrices do not match in size");

    Matrix *C = new Matrix(A.cols, A.rows);
    for (size_t idx = 0; idx < C->cols * C->rows; ++idx)
    {
        C->data[idx] = A.data[idx] + B.data[idx];
    }
    return *C;
}

Matrix& Matrix::exp(Matrix &A, const size_t accuracy)
{
    if (data == nullptr) throw ERRONEOUS_MESSAGE;

    if (A.cols != A.rows)
    {
        throw MatrixException("Error! The matrix is not square!");
    }

    Matrix *exp = new Matrix(A.rows, A.cols);
    Matrix item = make_ident(A.rows, A.cols);
    for (double deg_acc = 1; deg_acc <= accuracy; ++deg_acc)
    {
        item =  (item * A * (1/deg_acc));
        *exp += item;
    }
    return *exp;
}

Matrix& Matrix::make_ident(size_t rows, size_t cols)
{
    Matrix *I = new Matrix(rows, cols);
    if (I->data == nullptr)
    {
        throw MatrixException("The matrix is not initialized");
    }
    for (size_t idx = 0; idx < rows * cols; idx++)
    {
        if (idx % (rows + 1) == 0)
        {
            I->data[idx] = 1.;
        }
        else
        {
            I->data[idx] = 0;
        }
    }
    return *I;
}

void Matrix::add(const Matrix &B) // public
{
    if (cols != B.cols || rows != B.rows)
        throw "The matrices do not match in size";
    for (size_t idx = 0; idx < cols * rows; ++idx)
    {
        data[idx] += B.data[idx];
    }
}

Matrix& Matrix::mult(const Matrix &A)
{
    if (A.cols != rows)
        throw "Size mismatch for multiplication";
    Matrix *C = new Matrix(A.cols, rows);

    if (C->data == nullptr)
    {
        throw "The matrix is not initialized";
    }

    for (size_t rowA = 0; rowA < A.rows; ++rowA)
    {
        for (size_t colsB = 0; colsB < cols; ++colsB)
        {
            C->data[rowA * (A.cols) + colsB] = 0;
            for (size_t idx = 0; idx < A.cols; ++idx)
            {
                C->data[rowA * (A.cols) + colsB] += (A.data[(rowA * A.cols) + idx]) * (data[(idx * cols) + colsB]);
            }
        }
    }

    return *C;
}

double Matrix::matrix_det()
{
    if (cols != rows)
    {
        throw(WRONG_CONDITIONS);
        return NAN;
    }

    if (cols == 1)
    {
        return data[0];
    }

    if (cols == 2)
    {
        double matr_det = (data[0]) * (data[3]) - (data[1]) * (data[2]);
        return matr_det;
    }

    if (cols == 3)
    {
        double matr_det = (data[0]) * (data[4]) * (data[8]) + (data[1]) * (data[5]) * (data[6]) + (data[3]) * (data[7]) * (data[2]);
        matr_det -= ((data[2]) * (data[4]) * (data[6]) + (data[1]) * (data[3]) * (data[8]) + (data[0]) * (data[5]) * (data[7]));
        return matr_det;
    }
    throw(ERRONEOUS_MESSAGE);
    return NAN;
}

void Matrix::print()
{
    if (data != nullptr || cols != 0 || rows != 0)
    {
        for (size_t row = 0; row < rows; ++row)
        {
            printf("[ ");
            for (size_t col = 0; col < cols; ++col)
            {
                printf("%4.2f ", data[cols * row + col]);
            }
            printf("]\n");
        }
        printf("\n");
    }
    else
    {
        throw(WRONG_CONDITIONS);
    }
}

Matrix::Matrix(const Matrix &A)
{
    cols = A.cols;
    rows = A.rows;
    data = new double[cols * rows * sizeof(MatrixItem)];
    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
    {
        data[idx] = A.data[idx];
    }
}


Matrix& Matrix::transp()
{
    Matrix *C = new Matrix(rows, cols);

    for (size_t rowA = 0; rowA < rows; ++rowA)
    {
        for (size_t colsA = 0; colsA < cols; ++colsA)
        {
            C->data[(rows)*colsA + rowA] = data[colsA + rowA * cols];
        }
    }
    return *C;
}

Matrix& Matrix::operator+= (const Matrix& M) { 
    if ((rows != M.rows) || (cols != M.cols)) 
        throw ERRONEOUS_MESSAGE;

    for (size_t idx = 0; idx < rows * cols; idx++) {
        data[idx] += M.data[idx];
    }
    return *this;
}


Matrix& Matrix::operator-= (const Matrix& M) {
    if ((rows != M.rows) || (cols != M.cols))
        throw WRONG_CONDITIONS;

    for (size_t idx = 0; idx < rows * cols; idx++) {
        data[idx] -= M.data[idx];
    }
    return *this;
}


Matrix& Matrix::operator*= (const double k) {
    if (data == nullptr) throw ERRONEOUS_MESSAGE;

    for (size_t idx = 0; idx < rows * cols; idx++) {
        data[idx] *= k;
    }
    return *this;
}


Matrix& Matrix::operator*= (const Matrix& M) {
    if (cols != M.rows)
        throw ERRONEOUS_MESSAGE;

    Matrix R(rows, M.cols);
    for (size_t row = 0; row < R.rows; row++){
        for (size_t col = 0; col < R.cols; col++){
            for (size_t idx = 0; idx < M.rows; idx++){
                R.data[row * R.cols + col] += data[row * cols + idx] * M.data[idx * M.cols + col]; 
            }
        }
    }
    cols = R.cols;
    rows = R.rows;
    delete[] data;
    data = R.data;
    R.data = nullptr;
    return *this;
}

Matrix& Matrix::operator+(const Matrix& M) {
    Matrix *rez = new Matrix(M.cols, M.rows);
    *rez = *this;
    *rez += M;
    return *rez;
}


Matrix& Matrix::operator-(const Matrix& M) {
    Matrix *rez = new Matrix(M.cols, M.rows);
    *rez = *this;
    *rez -= M;
    return *rez;
}


Matrix& Matrix::operator*(const Matrix& M) {
    Matrix *rez = new Matrix(M.cols, M.rows);
    *rez = *this;
    *rez *= M;
    return *rez;
}


Matrix& Matrix::operator*(const double k) {
    Matrix *rez = new Matrix(cols, rows);
    *rez = *this;
    *rez *= k;
    return *rez;
}



int main()
{
    Matrix A, B, C, E, N;
    double deter;

    try
    {
        double array[9]{3., 2., 1., 1., 6., 7., 2., 6., 8.};
        double array2[9]{1., 0., 0., 1., 7., 2., 6., 6., 8.};
        double array3[4]{3., 2., 1., 1.};

        A = Matrix(3, 3, array);
        A.print();
        B = Matrix(3, 3, array2);
        C = Matrix(2, 2, array3);

        A.print();
        B.print();
        B.add(A);
        B.print();

        C = A.mult(B);
        C.print();

        C = C.transp();
        C.print();

        deter = C.matrix_det();
        printf("%f \n", deter);

        // N = matrix_init(3,3);
        N = A.make_ident(3, 3);
        N.print();

        A.print();
        A = A.exp(A, 3);
        A.print();
    }
    catch (MatrixException error)
    {
        std::cerr << error.what() << std::endl;
    }
}
