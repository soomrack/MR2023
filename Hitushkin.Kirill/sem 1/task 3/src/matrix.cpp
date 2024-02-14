#include <math.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include "matrix.hpp"

// TODO Заменить char*
class MatrixException : public std::exception {
private:
    const char* message;

public:
    MatrixException(std::string msg) : message(msg.c_str()) {}
    const char* what () { return message; }
};
MatrixException OUT_OF_RANGE("out_of_range");
MatrixException WRONG_CONDITIONS("wrong_conditions");
MatrixException NO_MEMORY_ALLOCATED("no_memory_allocated");


Matrix::Matrix() : rows{0}, cols{0}, items{nullptr} {}


Matrix::Matrix(const size_t a, const size_t b) 
    : rows{a}, cols{b}, items{nullptr}
{   
    // TODO except если не ноль
    if (rows == 0 && cols == 0)
        return;

    if (rows == 0 || cols == 0)
        throw WRONG_CONDITIONS;

    items = new MatrixItem[rows * cols];
}


Matrix::Matrix(const Matrix& A)
    : rows{A.rows}, cols{A.cols}, items{nullptr}
{
    if (A.items == nullptr) return;

    items = new MatrixItem[rows * cols];

    // TODO заменить на memcpy
    // std::copy(A.begin(), A.end(), begin());
    memcpy(begin(), A.begin(), rows * cols * sizeof(MatrixItem));
}

// TODO Надо удалить в A items
Matrix::Matrix(Matrix&& A) : rows{A.rows}, cols{A.cols}, items{A.items} 
{
    A.set_null();
}


void Matrix::set_null()
{
    items = nullptr;
    rows = 0;
    cols = 0;
}


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
    
    // TODO в отдельные if construction

    if (items == nullptr) {
        items = new MatrixItem[A.rows * A.cols];
        rows = A.rows;
        cols = A.cols;
        memcpy(begin(), A.begin(), rows * cols * sizeof(MatrixItem));
        return *this;
    }

    if (rows*cols == A.cols*A.rows) {
        memcpy(begin(), A.begin(), rows * cols * sizeof(MatrixItem));
        return *this;
    }

    delete[] items;
    items = new MatrixItem[A.rows * A.cols];

    rows = A.rows;
    cols = A.cols;

    memcpy(begin(), A.begin(), rows * cols * sizeof(MatrixItem));
        
    return *this;
}


Matrix& Matrix::operator=(Matrix&& A)
{  
    if (items != nullptr)
        delete[] items;

    rows = A.rows;
    cols = A.cols;
    items = A.items;

    // TODO delete A
    A.set_null();

    return *this;
}


void Matrix::set_zero()
{
    // TODO mem
    // std::fill(begin(), end(), 0);
    memset(items, 0, sizeof(MatrixItem) * cols * rows);
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
        throw OUT_OF_RANGE;

    return items[row * cols + col];
}


MatrixItem& Matrix::operator[](const size_t row, const size_t col)
{
    if (row >= rows || col >= cols)
        throw OUT_OF_RANGE;
    
    return items[row * cols + col];
}


size_t Matrix::get_rows() const
{
    return rows;
}


size_t Matrix::get_cols() const
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

Matrix operator+(const Matrix& A, Matrix&& B)
{
    Matrix sum = B;
    sum += A;
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

Matrix operator-(const Matrix& A, Matrix&& B)
{
    Matrix sub = B;
    sub -= A;
    return sub;
}


Matrix& Matrix::mult_to(Matrix& trg, const Matrix& A) const
{
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
    if (cols != A.rows)
        throw WRONG_CONDITIONS;
    
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

        // TODO вернуть свою функцию
        if (term.max() < accuracy) 
            return sum;
    }

    return sum;
}


MatrixItem Matrix::max()
{
    MatrixItem max = 0;
    MatrixItem num = 0;

    for (size_t idx = 0; idx < (rows * cols); idx++) {
        num = std::fabs(items[idx]);
        if (num > max) max = num;
    }

    return max;
}


MatrixItem* Matrix::begin() {return items;}
MatrixItem* Matrix::end() {return items + rows * cols;}
const MatrixItem* Matrix::begin() const {return items;}
const MatrixItem* Matrix::end() const {return items + rows * cols;}


bool Matrix::operator==(const Matrix& A) const
{
    if ((cols != A.cols) || (rows != A.rows)) 
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
    if (items != nullptr) {
        delete[] items;
    }
}
