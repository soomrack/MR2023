#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include <math.h>

using namespace std;


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
    ~Matrix();
public:
    Matrix& operator=(const Matrix& A);
    Matrix& operator=(const Matrix&& A);
    Matrix& operator+(const Matrix& A);
    Matrix& operator-(const Matrix& A);
};


Matrix::Matrix(const size_t cols, const size_t rows)
{
    if (cols == 0 || rows == 0) {
        Matrix::cols = cols;
        Matrix::rows = rows;
        Matrix::data = NULL;
        return;
    };

    if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols) {
        Matrix::cols = 0;
        Matrix::rows = 0;
        Matrix::data = NULL;
        return;
    };

    Matrix::cols = cols;
    Matrix::rows = rows;
    Matrix::data = (MatrixItem*)malloc(Matrix::cols * Matrix::rows * sizeof(MatrixItem));
    if (Matrix::data == NULL) {
        Matrix::cols = 0;
        Matrix::rows = 0;
        Matrix::data = NULL;
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
    cout << "_____________________________________________" << endl;

    for (size_t idx = 1; idx <= Matrix::cols * Matrix::rows; ++idx) {
        cout << Matrix::data[idx - 1] ;
        if (idx % Matrix::cols == 0 && idx >= Matrix::cols)
            cout << "" << endl;
    };

    return;
}


int main()
{
    Matrix A(3, 3);
    MatrixItem array[9] {1.0, 2.0, 3.0, 4.0, 5.0, 0.0, 2.0, 9.0, -3.0};
    A.matrix_fill(array);
    A.print_matrix();
    A.matrix_free();
}