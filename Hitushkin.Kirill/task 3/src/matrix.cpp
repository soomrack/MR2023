#include <math.h>
#include <iostream>
#include <algorithm>
#include <string>
#include "matrix.hpp"


class MatrixException : public std::exception {
    private:
    std::string message;

    public:
    MatrixException(std::string msg) : message(msg) {}
    std::string what () {
        return message;
    }
};

MatrixException OUT_OF_RANGE("OUT_OF_RANGE");
MatrixException WRONG_CONDITIONS("WRONG_CONDITIONS");
MatrixException NO_MEMORY_ALLOCATED("NO_MEMORY_ALLOCATED");


Matrix::Matrix() : rows{0}, cols{0}, items{nullptr} {}


Matrix::Matrix(const size_t a, const size_t b) 
    : rows{a}, cols{b}, items{nullptr}
{
    if (rows == 0 || cols == 0) {
        rows = 0;
        cols = 0;
        return;
    }

    items = new MatrixItem[rows * cols];
}


Matrix::Matrix(const Matrix& A)
    : rows{A.rows}, cols{A.cols}, items{nullptr}
{
    if (A.items == nullptr) return;

    items = new MatrixItem[rows * cols];

    std::copy(A.begin(), A.end(), begin());
}


Matrix::Matrix(Matrix&& A) : rows{A.rows}, cols{A.cols}, items{A.items} {}


Matrix& Matrix::operator=(std::initializer_list<MatrixItem> lst) 
{
    if (lst.size() != rows * cols) 
        throw OUT_OF_RANGE;

    std::copy(lst.begin(), lst.end(), begin());
    
    return *this;
}


Matrix& Matrix::operator=(const Matrix& A)
{
    if (this == &A) return *this;
    
    if (items == nullptr) {
        items = new MatrixItem[A.rows * A.cols];
    } 
    else if (rows*cols != A.cols*A.rows) {
        delete[] items;
        items = new MatrixItem[A.rows * A.cols];
    }

    rows = A.rows;
    cols = A.cols;

    std::copy(A.begin(), A.end(), begin());
        
    return *this;
}


Matrix& Matrix::operator=(Matrix&& A)
{
    if (this == &A) return *this;
    
    if (items != nullptr)
        delete[] items;

    rows = A.rows;
    cols = A.cols;
    items = A.items;

    return *this;
}


void Matrix::set_zero()
{
    std::fill(begin(), end(), 0);
}


void Matrix::set_one()
{
    set_zero();

    for (size_t idx = 0; idx < cols; idx++)
        items[idx + idx * cols] = 1.0;
}


const MatrixItem& Matrix::operator[](const size_t row, const size_t col) const
{
    if (row >= rows || col >= cols)
        throw WRONG_CONDITIONS;

    return items[row * cols + col];
}


MatrixItem& Matrix::operator[](const size_t row, const size_t col)
{
    if (row >= rows || col >= cols)
        throw WRONG_CONDITIONS;
    
    return items[row * cols + col];
}


const size_t Matrix::get_rows() const
{
    return rows;
}


const size_t Matrix::get_cols() const
{
    return cols;
}

Matrix& Matrix::operator+=(const Matrix& A)
{
    if ((rows != A.rows) || (cols != A.cols))
        throw WRONG_CONDITIONS;
    
    for (size_t idx = 0; idx < (rows * cols); idx++) 
        items[idx] += A.items[idx];

    return *this;
}

Matrix operator+(const Matrix& A, const Matrix& B)
{
    Matrix sum = A;
    sum += B;
    return sum;
}

Matrix operator+(Matrix&& A, const Matrix& B)
{
    Matrix sum = A;
    sum += B;
    return sum;
}

Matrix operator+(const Matrix& A, Matrix&& B)
{
    Matrix sum = B;
    sum += A;
    return sum;
}

Matrix operator+(Matrix&& A, Matrix&& B)
{
    Matrix sum = A;
    sum += B;
    return sum;
}


Matrix& Matrix::operator-=(const Matrix& A)
{
    if ((rows != A.rows) || (cols != A.cols))  
        throw WRONG_CONDITIONS;
    
    for (size_t idx = 0; idx < (rows * cols); idx++) 
        items[idx] -= A.items[idx];

    return *this;
}

Matrix operator-(const Matrix& A, const Matrix& B)
{
    Matrix sub = A;
    sub -= B;
    return sub;
}

Matrix operator-(Matrix&& A, const Matrix& B)
{
    Matrix sub = A;
    sub -= B;
    return sub;
}

Matrix operator-(const Matrix& A, Matrix&& B)
{
    Matrix sub = B;
    sub -= A;
    return sub;
}

Matrix operator-(Matrix&& A, Matrix&& B)
{
    Matrix sub = A;
    sub -= B;
    return sub;
}


Matrix& Matrix::mult_to(Matrix& trg, const Matrix& A) const
{
    if (&trg == this || &trg == &A)
        throw WRONG_CONDITIONS;
    
    if ((cols != A.rows) || (A.cols != trg.cols) || (rows != trg.rows))
        throw WRONG_CONDITIONS;

    for (size_t num_row = 0; num_row < rows; num_row++) {
        for (size_t num_col = 0; num_col < A.cols; num_col++) {
            MatrixItem sum = 0;

            for (size_t num_sum = 0; num_sum < A.rows; num_sum++) {
                sum += items[num_row * cols + num_sum] * A.items[num_sum * A.cols + num_col];
            }

            trg.items[num_row * trg.cols + num_col] = sum;
        }
    }

    return trg;
}


Matrix Matrix::operator*(const Matrix& A) const
{
    Matrix mult(rows, A.cols);
    mult_to(mult, A);
    return mult;
}


Matrix& Matrix::operator*=(const Matrix& A)
{
    *this = *this * A;
    return *this;
}


Matrix& Matrix::operator*=(const MatrixItem& factor)
{
    for (size_t idx = 0; idx < (rows * cols); idx++)
        items[idx] *= factor;
    
    return *this;
}


Matrix Matrix::operator*(const MatrixItem& factor)
{
    Matrix mult = *this;
    mult *= factor;
    return mult;
}


Matrix Matrix::T()
{
    Matrix trn(cols, rows);

    for (size_t num_row = 0; num_row < cols; num_row++) 
        for (size_t num_col = 0; num_col < rows; num_col++) 
            trn.items[num_row * trn.cols + num_col] = items[num_col * cols + num_row];

    return trn;
}


double Matrix::det() const
{
    if (cols != rows) 
        throw WRONG_CONDITIONS;

    if (items == nullptr)
        throw WRONG_CONDITIONS;

    Matrix mat = *this;

    double det = 1.0;
    int pivot = 0;
    double factor = 0;

    for (size_t num_col = 0; num_col < mat.cols; num_col++) {
        pivot = num_col;

        for (size_t num_row = num_col + 1; num_row < mat.rows; num_row++) {
            if (fabs(mat.items[num_row * mat.cols + num_col]) > fabs(mat.items[pivot * mat.cols + num_col]))
                pivot = num_row;
        }

        if (pivot != num_col) {
            for (size_t idx = 0; idx < mat.rows; idx++) 
                std::swap(mat.items[num_col * mat.cols + idx], mat.items[pivot * mat.cols + idx]);

            det *= -1;
        }

        if (mat.items[num_col * mat.cols + num_col] == 0) {
            det = 0;
            break;
        }

        det *= mat.items[num_col * mat.cols + num_col];

        for (size_t num_row = num_col + 1; num_row < mat.rows; num_row++) {
            factor = mat.items[num_row * mat.cols + num_col] / mat.items[num_col * mat.cols + num_col];

            for (size_t idx = num_col + 1; idx < mat.cols; idx++)
                mat.items[num_row * mat.cols + idx] -= factor * mat.items[num_col * mat.cols + idx];
        }
    }

    return det;
}


Matrix Matrix::expm(const MatrixItem& accuracy) const
{
    if (cols != rows) 
        throw WRONG_CONDITIONS;

    if (items == nullptr)
        throw WRONG_CONDITIONS;

    Matrix sum(rows, cols);
    Matrix term(rows, cols);
    Matrix temp(rows, cols);

    term.set_one();
    sum.set_one();

    for(size_t count = 1; count < 200; count++) {
        term *= (1.0 / count);
        mult_to(temp, term);
        std::swap(term.items, temp.items);

        sum += term;

        if (*std::max_element(term.begin(), term.end(), [](const MatrixItem& a, const MatrixItem& b) {return std::fabs(a) < std::fabs(b);}) < accuracy) 
            return sum;
    }

    return sum;
}


MatrixItem* Matrix::begin() {return items;}
MatrixItem* Matrix::end() {return items + rows * cols;}
const MatrixItem* Matrix::begin() const {return items;}
const MatrixItem* Matrix::end() const {return items + rows * cols;}


bool Matrix::operator==(const Matrix& A) const
{
    if ((cols != cols) || (rows != rows)) 
        return false;
    
    for (size_t idx = 0; idx < (rows * cols); idx++) {
        if ((int)(items[idx]*10) != (int)(A.items[idx]*10))
            return false;
    }
            
    return true;
}


std::ostream& operator<<(std::ostream& os, const Matrix& A)
{
    for (size_t row = 0; row < A.get_rows(); row++) {
        for (size_t col = 0; col < A.get_cols(); col++) {
            os << A[row, col] << "\t";
        }
        os << std::endl;
    }

    os << std::endl;

    return os;
}


Matrix::~Matrix() 
{
    delete[] items;
}
