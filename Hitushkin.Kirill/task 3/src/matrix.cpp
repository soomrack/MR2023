#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <algorithm>
#include <string.h>
#include "matrix.hpp"

#define INT_SWAP(a, b) {a ^= b; b ^= a; a ^= b;}
#define ALL_SWAP(a, b) {size_t size = sizeof(a); while (size--) {INT_SWAP(((char*)&a)[size], ((char*)&b)[size]);}}

using namespace std;


#define MATRIX_DEBUG_FLAG 0
static void print_debug(string mes)
{
    if (MATRIX_DEBUG_FLAG) {
        cout << mes << endl;
    }
}

typedef struct {
    string name;
} Error;

Error OUT_OF_RANGE = {"OUT_OF_RANGE"};
Error WRONG_CONDITIONS = {"WRONG_CONDITIONS"};
Error BAD_ALLOC = {"BAD_ALLOC"};
Error DOUBLE_FREE = {"DOUBLE_FREE"};
Error NO_MEMORY_ALLOCATED= {"NO_MEMORY_ALLOCATED"};

static void print_error(Error err, string mes = "")
{
    cerr << "[ERROR]: " << err.name << " " << mes << endl;
}


Matrix::Matrix() : rows{0}, cols{0}, items{} {}


Matrix::Matrix(const size_t& a, const size_t& b) 
    : rows{a}, cols{b}, items{}
{
    if (rows >= items.max_size() / cols) {
        print_error(BAD_ALLOC, "Not enough memory!");
        return;
    }

    try {
        items.resize(rows*cols);
    } 
    catch (std::exception const& e) {
        print_error(BAD_ALLOC, e.what());
        rows = 0; cols = 0;
    }
}


Matrix& Matrix::operator=(std::initializer_list<MatrixItem> lst) 
{
    items = lst;
    return *this;
}


Matrix::Matrix(const Matrix& A)
{
    rows = A.rows;
    cols = A.cols;

    try {
        items = A.items;
    } 
    catch (std::exception const& e) {
        print_error(BAD_ALLOC, e.what());
        rows = 0; cols = 0;
    }
}


Matrix& Matrix::operator=(const Matrix& A)
{
    try {
        items = A.items;
        rows = A.rows;
        cols = A.cols;
    } 
    catch (std::exception const& e) {
        print_error(BAD_ALLOC, e.what());
    }

    return *this;
}


Matrix::Matrix(Matrix&& A)
{
    try {
        items = move(A.items);
        rows = A.rows;
        cols = A.cols;
    } 
    catch (std::exception const& e) {
        print_error(BAD_ALLOC, e.what());
    }
}


Matrix& Matrix::operator=(Matrix&& A)
{
    try {
        items = move(A.items);
        rows = A.rows;
        cols = A.cols;
    } 
    catch (std::exception const& e) {
        print_error(BAD_ALLOC, e.what());
    }

    return *this;
}


void Matrix::set_zero()
{
    fill(items.begin(), items.end(), 0);
}


void Matrix::set_one()
{
    set_zero();

    for (size_t idx = 0; idx <cols; idx++)
        items[idx + idx * cols] = 1.0;
}


const MatrixItem& Matrix::operator()(const size_t& row, const size_t& col) const
{
    return items[row * cols + col];
}


MatrixItem& Matrix::operator()(const size_t& row, const size_t& col)
{
    return items[row * cols + col];
}


const size_t& Matrix::Rows() const
{
    return rows;
}


const size_t& Matrix::Cols() const
{
    return cols;
}


Matrix& Matrix::operator+=(const Matrix& A)
{
    if ((rows != A.rows) || (cols != A.cols))  {
        print_error(WRONG_CONDITIONS, "Sum error!");
        return *this;
    }
    
    for (size_t idx = 0; idx < (rows * cols); idx++) 
        items[idx] += A.items[idx];

    return *this;
}

Matrix operator+(const Matrix& A, const Matrix& B)
{
    if ((B.rows != A.rows) || (B.cols != A.cols))  {
        print_error(WRONG_CONDITIONS, "Sum error!");
        return Matrix();
    }
    
    Matrix Sum = A;
    
    if (Sum.items.size() == 0) {
        print_error(BAD_ALLOC, "Sum error!");
        return Matrix();
    }

    Sum += B;

    print_debug("simple +");

    return Sum;
}

Matrix& operator+(Matrix&& A, const Matrix& B)
{
    A += B;
    print_debug("opt1 +");
    return A;
}

Matrix& operator+(const Matrix& A, Matrix&& B)
{
    B += A;
    print_debug("opt2 +");
    return B;
}

Matrix& operator+(Matrix&& A, Matrix&& B)
{
    A += B;
    print_debug("opt3 +");
    return A;
}


Matrix& Matrix::operator-=(const Matrix& A)
{
    if ((rows != A.rows) || (cols != A.cols))  {
        print_error(WRONG_CONDITIONS, "Sum error!");
        return *this;
    }
    
    for (size_t idx = 0; idx < (rows * cols); idx++) 
        items[idx] -= A.items[idx];

    return *this;
}

Matrix operator-(const Matrix& A, const Matrix& B)
{
    if ((B.rows != A.rows) || (B.cols != A.cols))  {
        print_error(WRONG_CONDITIONS, "Sum error!");
        return Matrix();
    }
    
    Matrix Sum = A;
    
    if (Sum.items.size() == 0) {
        print_error(BAD_ALLOC, "Sum error!");
        return Matrix();
    }

    Sum -= B;

    print_debug("simple -");

    return Sum;
}

Matrix& operator-(Matrix&& A, const Matrix& B)
{
    A -= B;
    print_debug("opt1 -");
    return A;
}

Matrix& operator-(const Matrix& A, Matrix&& B)
{
    B -= A;
    print_debug("opt2 -");
    return B;
}

Matrix& operator-(Matrix&& A, Matrix&& B)
{
    A -= B;
    print_debug("opt3 -");
    return A;
}


Matrix& matrix_mult_to(Matrix& Save, const Matrix& A, const Matrix& B)
{
    if ((A.cols != B.rows) || (B.cols != Save.cols) || (A.rows != Save.rows)) {
        print_error(WRONG_CONDITIONS, "Mult error!");
        return Save;
    }

    for (size_t num_row = 0; num_row < A.rows; num_row++) {
        for (size_t num_col = 0; num_col < B.cols; num_col++) {
            MatrixItem sum = 0;

            for (size_t num_sum = 0; num_sum < B.rows; num_sum++) {
                sum += A.items[num_row * A.cols + num_sum] * B.items[num_sum * B.cols + num_col];
            }

            Save.items[num_row * Save.cols + num_col] = sum;
        }
    }

    return Save;
}


Matrix Matrix::operator*(const Matrix& A) const
{
    if (cols != A.rows) {
        print_error(WRONG_CONDITIONS);
        return Matrix();
    }
    
    Matrix Mult(rows, A.cols);

    if (Mult.items.size() == 0) {
        print_error(BAD_ALLOC, "Mult error!");
        return Matrix();
    }

    matrix_mult_to(Mult, *this, A);

    return Mult;
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
    Matrix Mult = *this;

    if (Mult.items.size() == 0) {
        print_error(BAD_ALLOC, "Mult error!");
        return Mult;
    }

    Mult *= factor;

    return Mult;
}


Matrix Matrix::T()
{
    Matrix Tran(cols, rows);

    if (Tran.items.size() == 0) {
        print_error(BAD_ALLOC, "Transpose error!");
        return Matrix();
    }

    for (size_t num_row = 0; num_row < cols; num_row++) 
        for (size_t num_col = 0; num_col < rows; num_col++) 
            Tran.items[num_row * Tran.cols + num_col] = items[num_col * cols + num_row];

    return Tran;
}


double Matrix::det() const
{
    if (cols != rows) {
        print_error(WRONG_CONDITIONS);
        return 0;
    }

    Matrix mat = *this;

    if (mat.items.size() == 0) {
        print_error(BAD_ALLOC, "Det error!");
        return 0;
    }

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
                ALL_SWAP(mat.items[num_col * mat.cols + idx], mat.items[pivot * mat.cols + idx]);

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


MatrixItem Matrix::max() const
{
    MatrixItem max = 0;
    MatrixItem num = 0;

    for (size_t idx = 0; idx < (rows * cols); idx++) {
        num = fabs(items[idx]);
        if (num > max) max = num;
    }

    return max;
}


Matrix Matrix::expm(const double& accuracy) const
{
    if (cols != rows) {
        print_error(WRONG_CONDITIONS, "Det error!");
        return Matrix();
    }

    Matrix sum(rows, cols);
    Matrix term(rows, cols);
    Matrix temp(rows, cols);

    if (sum.items.size() == 0 || term.items.size() == 0 || temp.items.size() == 0) {
        print_error(BAD_ALLOC, "Det error!");
        return Matrix();
    }

    term.set_one();
    sum.set_zero();

    sum += term;

    for(size_t count = 1; count < 200; count++) {
        term *= (1.0 / count);

        matrix_mult_to(temp, term, *this);
        term.items.swap(temp.items);

        sum += term;

        if (term.max() < accuracy) break;
    }

    return sum;
}


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


ostream& operator<<(ostream& os, const Matrix& A)
{
    for (size_t row = 0; row < A.Rows(); row++) {
        for (size_t col = 0; col < A.Cols(); col++) {
            os << A(row, col) << "\t";
        }
        os << endl;
    }

    os << endl;

    return os;
}


Matrix::~Matrix() {}
