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
    void matrix_transpose();
    Matrix matrix_exponent(Matrix&);
    MatrixItem matrix_determinant(Matrix&);

    void print(const Matrix&);

    Matrix& operator=(Matrix&&) noexcept;
    Matrix& operator=(const Matrix&);
    void operator+=(const Matrix&);
    void operator-=(const Matrix&);
    void operator*=(const MatrixItem);
    void operator/=(const MatrixItem);
    void operator*=(const Matrix&);

    Matrix operator+(const Matrix&);
    Matrix operator-(const Matrix&);
    Matrix operator*(const Matrix&);
    Matrix operator*(const MatrixItem);
    Matrix operator/(const MatrixItem);
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
Matrix_Exception MEM_ERROR("Error: memory is not allocated\n");
Matrix_Exception EMPTY_MATRIX("Error: Function can't return an empty matrix\n");
Matrix_Exception LARGESIZE("Error: Size of the matrix is too big\n");



Matrix::Matrix(const Matrix& matrix) {
    this->rows = matrix.rows;
    this->cols = matrix.cols;
    this->data = new MatrixItem[this->rows * this->cols];
    if (!this->data)
        throw MEM_ERROR;
    memcpy(this->data, matrix.data, this->rows * this->cols * sizeof(MatrixItem));
}


Matrix::Matrix(size_t num_row, size_t num_col, MatrixItem* array)
{

    this->rows = num_row;
    this->cols = num_col;
    this->data = new MatrixItem[rows * cols];
    if (!this->data)
        throw MEM_ERROR;
    memcpy(this->data, array, rows * cols * sizeof(MatrixItem));
}


Matrix::Matrix(Matrix&& mat) noexcept : data(mat.data), rows(mat.rows), cols(mat.cols) // Конструктор перемещения
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


void Matrix::set_zero()
{
    memset(this->data, 0, this->rows * this->cols * sizeof(MatrixItem));
}


void Matrix::set_one()
{
    set_zero();
    for (unsigned int idx = 0; idx < this->cols * this->rows; idx += rows + 1)
    {
        this->data[idx] = 1.0;
    }
}


void Matrix::print(const Matrix& A)
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


void Matrix::operator+=(const Matrix& matrix)
{
    if (this->rows != matrix.rows || this->cols != matrix.cols)
        throw NOTEQUAL;
    for (unsigned int index = 0; index < rows * cols; ++index)
    {
        this->data[index] += matrix.data[index];
    }
}


void Matrix::operator-=(const Matrix& matrix)
{
    if (this->rows != matrix.rows || this->cols != matrix.cols)
        throw NOTEQUAL;
    for (unsigned int index = 0; index < rows * cols; ++index)
    {
        this->data[index] -= matrix.data[index];
    }
}


void Matrix::operator*=(const MatrixItem k)
{
    for (unsigned int idx = 0; idx < this->rows * this->cols; idx++)
    {
        this->data[idx] *= k;
    }
}


void Matrix::operator/=(const MatrixItem k)
{
    for (unsigned int idx = 0; idx < this->rows * this->cols; idx++)
    {
        this->data[idx] /= k;
    }
}


void Matrix::operator*=(const Matrix& matrix)
{
    if (this->cols != matrix.rows)
        throw MULTIPLYERROR;
    Matrix multiplication(this->rows, matrix.cols);
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
    *this = multiplication;
}


Matrix& Matrix::operator=(const Matrix& A)
{
    if (this == &A)
        return *this;
    delete[] this->data;
    this->rows = A.rows;
    this->cols = A.cols;
    this->data = new MatrixItem[rows * cols];
    if (!data)
        throw MEM_ERROR;
    memcpy(this->data, A.data, rows * cols * sizeof(MatrixItem));
    return *this;
}


Matrix& Matrix::operator=(Matrix&& A) noexcept
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


// A += B
Matrix Matrix::operator+(const Matrix& B)
{
    Matrix add(*this);
    add += B;
    return add;
}


// A -= B
Matrix Matrix::operator-(const Matrix& B)
{
    Matrix sub(*this);
    sub -= B;
    return sub;
}


// A *= k
Matrix Matrix::operator*(const MatrixItem k)
{
    Matrix multiply(*this);
    multiply *= k;
    return multiply;
}


// C = A * B
Matrix Matrix::operator*(const Matrix& B)
{
    Matrix multiply(*this);
    multiply *= B;
    return multiply;
}


// A /= k
Matrix Matrix::operator/(const MatrixItem k)
{
    Matrix multiply(*this);
    multiply /= k;
    return multiply;
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


// exp = exp(A)
Matrix Matrix::matrix_exponent(Matrix& A)
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

    }
    return *exp;
}
