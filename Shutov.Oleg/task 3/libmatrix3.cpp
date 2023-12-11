#include <ctime>
#include <iostream>
#include <windows.h>
#include <cmath>
#include <stdexcept>

typedef double MatrixItem;

class Matrix
{
private:
    size_t rows;
    size_t cols;
    MatrixItem* data;
 
public:
    Matrix(size_t, size_t, MatrixItem*);
    Matrix(size_t, size_t);
    Matrix();
    ~Matrix();
    Matrix(const Matrix&);
    Matrix(Matrix&&) noexcept;

    void set_zero();
    void set_one();
    Matrix& matrix_transpose();
    Matrix& matrix_exponent(Matrix&);
    MatrixItem matrix_determinant(Matrix&);

    Matrix& print(const Matrix&);

    Matrix& operator=(Matrix&&) noexcept;
    Matrix& operator=(const Matrix&);
    Matrix& operator+=(const Matrix&);
    Matrix& operator-=(const Matrix&);
    Matrix& operator*=(const MatrixItem);
    Matrix& operator/=(const MatrixItem);
    Matrix& operator*=(const Matrix&);

    Matrix& operator+(const Matrix&);
    Matrix& operator-(const Matrix&);
    Matrix& operator*(const Matrix&); 
    Matrix& operator*(const MatrixItem);
    Matrix& operator/(const MatrixItem);
 };


Matrix::Matrix() : rows(0), cols(0), data(nullptr) {}


class Matrix_Exception : public std::domain_error
{
public:
    Matrix_Exception(const char* const& msg) : domain_error(msg)
    {
    }
};


Matrix_Exception NOTSQUARE("Error: the matrix should have nxn size\n");
Matrix_Exception NOTEQUAL("Error: the matrix should have the same size\n");
Matrix_Exception MULTIPLYERROR("Error: first matrix cols not equal to the second matrix row.\n");
Matrix_Exception ZERODIVISION("Error: divide by zero\n");
Matrix_Exception EMPTY_MATRIX("Error: Function can't return an empty matrix\n");
Matrix_Exception LARGESIZE("Error: Size of the matrix is too big\n");



Matrix::Matrix(const Matrix& matrix) {
    rows = matrix.rows;
    cols = matrix.cols;
    if (rows * cols == 0) {
        data = nullptr;
        return;
    }
    data = new MatrixItem[rows * cols];
    memcpy(data, matrix.data, rows * cols * sizeof(MatrixItem));
}


Matrix::Matrix(size_t num_row, size_t num_col, MatrixItem* array)
{

    rows = num_row;
    cols = num_col;
    if (rows * cols == 0) {
        data = nullptr;
        return;
    }
    data = new MatrixItem[rows * cols];
     memcpy(data, array, rows * cols * sizeof(MatrixItem));
}


Matrix::Matrix(Matrix&& mat) noexcept : data(mat.data), rows(mat.rows), cols(mat.cols) // Конструктор перемещения
{
    mat.data = nullptr;
    mat.rows = 0;
    mat.cols = 0;
}


Matrix::~Matrix()
{
    delete[] data;
    cols = 0;
    rows = 0;
    data = nullptr;
   
}


void Matrix::set_zero()
{
    if (data = nullptr) return;
    memset(data, 0, rows * cols * sizeof(MatrixItem));
    
}


void Matrix::set_one()
{
    set_zero();
    for (unsigned int idx = 0; idx < cols * rows; idx += rows + 1)
    {
        data[idx] = 1.0;
    }
}


Matrix& Matrix::print(const Matrix& A)
{
    for (size_t row = 0; row < A.rows; ++row) {
        std::cout << "[ ";
        for (size_t col = 0; col < A.cols; ++col) {
            std::cout << " %4.2f " << A.data[A.cols * row + col];
        }
        std::cout << " [\n";
    }
    std::cout << "\n";
}


// A^T
Matrix& Matrix::matrix_transpose()
{
    Matrix* A = new Matrix(cols, rows);
    for (size_t row = 0; row < A->rows; ++row) {
        for (size_t col = 0; col < A->cols; ++col) {
            A->data[col * A->cols + row] = data[row * cols + col];
        }
    }
    return *A;
}


Matrix& Matrix::operator+=(const Matrix& matrix)
{
    if (rows != matrix.rows || cols != matrix.cols)
        throw NOTEQUAL;
    for (unsigned int index = 0; index < rows * cols; ++index)
    {
        data[index] += matrix.data[index];
    }
    return *this;
}


Matrix& Matrix::operator-=(const Matrix& matrix)
{
    if (rows != matrix.rows || cols != matrix.cols)
        throw NOTEQUAL;
    for (unsigned int index = 0; index < rows * cols; ++index)
    {
        data[index] -= matrix.data[index];
    }
    return *this;
}


Matrix& Matrix::operator*=(const MatrixItem k)
{
    for (unsigned int idx = 0; idx < rows * cols; idx++)
    {
        data[idx] *= k;
    }
    return *this;
}


Matrix& Matrix::operator/=(const MatrixItem k)
{
    for (unsigned int idx = 0; idx < rows * cols; idx++)
    {
        data[idx] /= k;
    }
    return *this;
}


Matrix& Matrix::operator*=(const Matrix& matrix)
{
    if (cols != matrix.rows)
        throw MULTIPLYERROR;
    Matrix multiplication(rows, matrix.cols);
    for (unsigned int row = 0; row < multiplication.rows; row++)
    {
        for (unsigned int col = 0; col < multiplication.cols; col++)
        {
            MatrixItem sum = 0;
            for (unsigned int k = 0; k < matrix.rows; k++)
            {
                sum += data[row * cols + k] * matrix.data[k * matrix.cols + col];
            }
            multiplication.data[row * multiplication.cols + col] = sum;
        }
    }
    return *this;
}


Matrix& Matrix::operator=(const Matrix& A)
{
    if (this == &A)
        return *this;
    delete[] data;
    rows = A.rows;
    cols = A.cols;
    if (data == nullptr) data = nullptr;
        return;
    data = new MatrixItem[rows * cols];
    memcpy(data, A.data, rows * cols * sizeof(MatrixItem));
    return *this;
}


Matrix& Matrix::operator=(Matrix&& A) noexcept
{
    if (this == &A)
        return *this;
    delete[] data;
    rows = A.rows;
    cols = A.cols;
    data = A.data;
    A.data = nullptr;
    A.rows = 0;
    A.cols = 0;
    return *this;
}


// A += B
Matrix& Matrix::operator+(const Matrix& B)
{
    Matrix *add = new Matrix (*this);
    *add += B;
    return *add;
}


// A -= B
Matrix& Matrix::operator-(const Matrix& B)
{
    Matrix *sub = new Matrix (*this);
    *sub -= B;
    return *sub;
}


// A *= k
Matrix& Matrix::operator*(const MatrixItem k)
{
    Matrix *multiply = new Matrix (*this); //через new 
    *multiply *= k;
    return *multiply;
}


// C = A * B
Matrix& Matrix::operator*(const Matrix& B)
{
    Matrix *multiply = new Matrix (*this);
    *multiply *= B;
    return *multiply;
}


// A /= k
Matrix& Matrix::operator/(const MatrixItem k)
{
    Matrix *multiply = new Matrix (*this);
    *multiply /= k;
    return *multiply;
}


// det(A)
MatrixItem Matrix::matrix_determinant(Matrix& A)
{
    if (A.rows != A.cols)
        throw NOTSQUARE;
    if (A.rows == 1) return A.data[0];

    if (A.rows == 2) {
        return (A.data[0] * A.data[3]
            - A.data[2] * A.data[1]);
    };
    if (A.rows == 3) {
        return (+A.data[0] * A.data[4] * A.data[8]
            + A.data[1] * A.data[5] * A.data[6]
            + A.data[3] * A.data[7] * A.data[2]
            - A.data[2] * A.data[4] * A.data[6]
            - A.data[1] * A.data[3] * A.data[8]
            - A.data[5] * A.data[7] * A.data[0]);
    };
    throw LARGESIZE;
}


// A = exp(A)
Matrix& Matrix::matrix_exponent(Matrix& A)
{
    if (A.cols != A.rows)
        throw NOTSQUARE;
    if (A.cols == 0)
        throw EMPTY_MATRIX;

    Matrix* exp = new Matrix(A.rows, A.cols);
    exp->set_one();

    Matrix term(A.rows, A.cols);
    term.set_one();

    for (int idx = 1; idx < 100; ++idx) {

        term = term * A / idx;
        *exp += term;
        A = *exp;
    }
    return A;
}
