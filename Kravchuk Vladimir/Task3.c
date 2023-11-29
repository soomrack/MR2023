#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stdint.h>
#include <vector>

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
    ~Matrix();
public:
    Matrix& operator=(const Matrix& A);
    Matrix& operator=(Matrix&& A);
    Matrix& operator+=(const Matrix& A);
    Matrix& operator+(const Matrix& A);
    Matrix& operator-=(const Matrix& A);
    Matrix& operator-(const Matrix& A);
    Matrix& operator*= (const Matrix& B);
    Matrix& operator* (const Matrix& B);
    Matrix& operator*= (const double scalar);
    Matrix& operator* (const double scalar);
public:
    void free();
    void filling(std::vector <MatrixItem> values);
    void print();
    void transposition(const Matrix& A);
    void set_zero();
    double det(void);
    Matrix exp(const Matrix A, const unsigned int level = 5);
};



    void Matrix::free()
    {
        cols = 0;
        rows = 0;
        delete[] data;
        data = nullptr;
    }


    Matrix::Matrix() {
        rows = 0;
        cols = 0;
        data = nullptr;
    }


    Matrix::Matrix(const size_t cols, const size_t rows)
    {
        if (cols == 0 || rows == 0) {
            data = nullptr;
            return;
        };

        if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols) {
            free();
            return;
        };

        data = new MatrixItem[cols * rows];
    }


    class Matrix_Exception : public std::exception
    {
    private:
        std::string message;
    public:
        Matrix_Exception(std::string message) : message{ message } {}
        std::string get_message() const { return message; }
    };


    void Matrix::filling(std::vector <MatrixItem> values)
    {
        if (data == nullptr) throw Matrix_Exception("Error in Matrix_filling");

        if (values.size() >= rows * cols) {
            for (size_t idx = 0; idx < cols * rows; ++idx) {
                data[idx] = values[idx];
            }
        }
        else {
            auto idx = values.begin();
            for (; idx != values.end(); ++idx) {
                data[idx - values.begin()] = *idx;
            }
            for (; idx != values.end(); ++idx) {
                *idx = 0.0;
            }
        };
    }


    Matrix::Matrix(Matrix& A)
    {
        if (A.data == nullptr) {
            cols = 0;
            rows = 0;
            data = nullptr;
            return;
        };

        cols = A.cols;
        rows = A.rows;
        data = new MatrixItem[cols * rows];

        memcpy(data, A.data, A.cols * A.rows * sizeof(MatrixItem));
    }


    Matrix::Matrix(Matrix&& A)
    {
        cols = A.cols;
        rows = A.rows;
        data = A.data;
        A.cols = 0;
        A.rows = 0;
        A.data = nullptr;
    }


    Matrix::~Matrix() {
        free();
    }


    void Matrix::print() 
    {
        if (data == nullptr) throw Matrix_Exception("Error in Matrix_print");

        std::cout << "\n";
        for (size_t r = 0; r < rows; r++) {
            std::cout << "[";
            for (size_t c = 0; c < cols; c++) {
                std::cout << data[r * cols + c];
                if (cols != cols - 1)
                    std::cout << "\t";
            }
            std::cout << "]\n";
        }
        std::cout << "\n";
    }


    Matrix& Matrix::operator=(const Matrix& A)
    {
        if (this == &A) return *this;

        cols = A.cols;
        rows = A.rows;

        delete[] data;
        data = new MatrixItem[cols * rows];
        memcpy(data, A.data, A.cols * A.rows * sizeof(MatrixItem));
        return *this;
    }


    Matrix& Matrix::operator=(Matrix&& A)
    {
        if (this == &A) return *this;

        cols = A.cols;
        rows = A.rows;
        delete[] data;
        data = A.data;

        A.cols = 0;
        A.rows = 0;
        A.data = nullptr;

        return *this;
    }


    Matrix& Matrix::operator+= (const Matrix& A) {
        if (A.cols != cols || A.rows != rows) throw Matrix_Exception("Error in Matrix_sum");

        for (size_t idx = 0; idx < rows * cols; idx++) {
            data[idx] += A.data[idx];
        }
        return *this;
    }


    Matrix& Matrix::operator+(const Matrix& A) {
        if (A.cols != cols || A.rows != rows) throw Matrix_Exception("Error in Matrix_sum(cols/=rows)");

        Matrix* sum = new Matrix(*this);

        for (size_t idx = 0; idx < cols * rows; ++idx)
            sum->data[idx] += A.data[idx];

        return *sum;
    }


    Matrix& Matrix::operator-=(const Matrix& A) {
        if (A.cols != cols || A.rows != rows) throw Matrix_Exception("Error in Matrix_substr");

        for (size_t idx = 0; idx < rows * cols; idx++) {
            data[idx] -= A.data[idx];
        }
        return *this;
    }


    Matrix& Matrix::operator-(const Matrix& A)
    {
        if (A.cols != cols || A.rows != rows) throw Matrix_Exception("Error in Matrix_substr");

        Matrix *sub = new Matrix(*this);

        for (size_t idx = 0; idx < cols * rows; ++idx)
            sub->data[idx] -= A.data[idx];

        return *sub;
    }


    Matrix& Matrix::operator*=(const Matrix& B) {
        if (cols != B.rows) throw Matrix_Exception("Error in Matrix_mult");

        *this = *this * B;

        return *this;
    }


    Matrix& Matrix::operator* (const Matrix& B) {
        if (cols != B.rows) throw Matrix_Exception("Error in Matrix_mult");

        Matrix* res = new Matrix(*this);

        for (size_t rowA = 0; rowA < rows; ++rowA)
            for (size_t colB = 0; colB < B.cols; ++colB) {
                res->data[res->cols * rowA + colB] = 0.0;
                for (size_t colA = 0; colA < cols; ++colA)
                    res->data[res->cols * rowA + colB] += data[colA + rowA * cols] * B.data[B.cols * colA + colB];
            };

        return *res;
    }


    Matrix& Matrix::operator*= (const double scalar) {
        if (data == nullptr) throw Matrix_Exception("Error in Matrix_mult");

        Matrix* res = new Matrix(*this);

        for (size_t idx = 0; idx < cols * rows; ++idx)
            res->data[idx] = data[idx] * scalar;

        return *res;
    }


    Matrix& Matrix::operator* (const double scalar) {
        if (data == nullptr) throw Matrix_Exception("Error in Matrix_mult");

        for (size_t idx = 0; idx < rows * cols; idx++) {
            data[idx] *= scalar;
        }
        return *this;
    }


    void Matrix::transposition(const Matrix& A)
    {
        if (data == nullptr) throw Matrix_Exception("Error in Matrix_transposition");

        for (size_t row = 0; row < A.rows; row++)
            for (size_t col = 0; col < A.cols; col++)
                data[row * A.rows + col] = A.data[col * A.cols + row];
    }


    double Matrix::det(void)
    {
        if (rows != cols) throw Matrix_Exception("Error in Matrix_det(rows/=cols)");

        if (cols == 1) return data[0];

        if (cols == 2) return (data[0] * data[3] - data[1] * data[2]);

        if (cols == 3) {
            return (data[0] * data[4] * data[8]) + \
                (data[1] * data[5] * data[6]) + \
                (data[2] * data[3] * data[7]) - \
                (data[2] * data[4] * data[6]) - \
                (data[0] * data[5] * data[7]) - \
                (data[1] * data[3] * data[8]);
        }
        else throw Matrix_Exception("Error in Matrix_det");
    }


    void Matrix::set_zero()
    {
        if (data == nullptr) throw Matrix_Exception("Error in Matrix_zero");

        memset(data, 0, cols * rows * sizeof(MatrixItem));
    }


    Matrix Matrix::exp(Matrix A, const unsigned int level=5) {
        if (data == nullptr) throw Matrix_Exception("Error in Matrix_exp");

        if(A.cols != A.rows) throw Matrix_Exception("Error in Matrix_exp(cols/=rows)");

        Matrix exp = Matrix(A.cols, A.rows);

        exp.set_zero();

        Matrix sum = A;

        for (size_t idx = 0; idx < exp.rows; ++idx)
            exp.data[idx * exp.cols + idx] += 1;

        exp += A;

        for (int idx = 2; idx <= level; ++idx) {
            sum *= A;
            sum *= 1.0 / idx;
            exp += sum;
        };
        sum.free();

        return exp;
    }


int main()
{
    Matrix A(2, 2);
    std::vector <MatrixItem> array(1.0, 2.0, 3.0, 4.0, 5.0, 0.0, 2.0, 9.0, 10.0);
    A.filling(array);
    A.print();
    A.free();
}
