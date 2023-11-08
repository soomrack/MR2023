#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>


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
    void matrix_fill(MatrixItem* values);
    void matrix_free();
    void print_matrix();
    void matrix_null();
    ~Matrix();
public:
    Matrix& operator=(const Matrix& A);
    Matrix& operator=(const Matrix&& A);
    Matrix& operator+(const Matrix& A);
    Matrix& operator-(const Matrix& A);
};


void Matrix::matrix_null()
{
    Matrix::cols = 0;
    Matrix::rows = 0;

    if (Matrix::data == NULL)
        return;

    Matrix::data = NULL;

    return;
}


Matrix::Matrix(const size_t cols, const size_t rows)
{
    if (cols == 0 || rows == 0) {
        Matrix::cols = cols;
        Matrix::rows = rows;
        Matrix::data = NULL;
        return;
    };

    if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols) {
        matrix_null();
        return;
    };

    Matrix::cols = cols;
    Matrix::rows = rows;
    Matrix::data = (MatrixItem*)malloc(Matrix::cols * Matrix::rows * sizeof(MatrixItem));
    if (Matrix::data == NULL) {
        matrix_null();
        return;
    };

    return;
}


void Matrix::matrix_fill(MatrixItem *values)
{
    if (Matrix::data == NULL)
        return;

    memcpy(Matrix::data, values, Matrix::rows * Matrix::cols * sizeof(MatrixItem));
    return;
}


void Matrix::matrix_free()
{
    if (Matrix::data == NULL)
        return;

    free(Matrix::data);
    Matrix::cols = 0;
    Matrix::rows = 0;
    Matrix::data = NULL;

    return;
}


void Matrix::print_matrix()
{
    std::cout << "_____________________________________________" << std::endl;

    for (size_t idx = 1; idx <= Matrix::cols * Matrix::rows; ++idx) {
        std::cout << Matrix::data[idx - 1] ;
        if (idx % Matrix::cols == 0 && idx >= Matrix::cols)
            std::cout << "" << std::endl;
    };

    return;
}


Matrix& Matrix::operator=(const Matrix& A)
{
    Matrix* result = new Matrix(*this);
    if (A.cols != Matrix::cols || A.rows != Matrix::rows) {
        result->matrix_null();
        return *result;
    };

    result->data = A.data;

    return *result;
}


Matrix& Matrix::operator=(const Matrix&& A)
{
    Matrix* result = new Matrix(*this);
    if (A.cols != Matrix::cols || A.rows != Matrix::rows) {
        result->matrix_null();
        return *result;
    };

    memcpy(result->data, A.data, A.cols * A.rows * sizeof(MatrixItem));
    //A.matrix_free();

    return *result;
}


Matrix::Matrix(Matrix& A)
{
    if (A.data == NULL) {
        matrix_free();
        matrix_null;
        return;
    };
    
    if (!(A.cols == Matrix::cols && A.rows == Matrix::rows)) {
        matrix_free();
        Matrix(A.cols, A.rows);
    };

    Matrix = A;

    return;
}


Matrix::Matrix(Matrix&& A)
{
    if (A.data == NULL) {
        matrix_free();
        matrix_null;
        return;
    };
    
    if (!(A.cols == Matrix::cols && A.rows == Matrix::rows)) {
        matrix_free();
        Matrix(A.cols, A.rows);
    };

    Matrix = A;

    return;
}


Matrix& Matrix::operator+(const Matrix& A)
{
    Matrix* result = new Matrix(*this);
    if (A.cols != Matrix::cols || A.rows != Matrix::rows) {
        result->matrix_null();
        return *result;
    };

    if (result->data == NULL)
        return *result;

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        result->data[idx] = Matrix::data[idx] + A.data[idx];

    return *result;
}


Matrix& Matrix::operator-(const Matrix& A)
{
    Matrix* result = new Matrix(*this);
    if (A.cols != Matrix::cols || A.rows != Matrix::rows) {
        result->matrix_null();
        return *result;
    };

    if (result->data == NULL)
        return *result;

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        result->data[idx] = Matrix::data[idx] - A.data[idx];

    return *result;
}


int main()
{
    Matrix A(3, 3);
    MatrixItem array[9] {1.0, 2.0, 3.0, 4.0, 5.0, 0.0, 2.0, 9.0, -3.0};
    A.matrix_fill(array);
    A.print_matrix();
    A.matrix_free();
}
