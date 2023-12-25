#pragma once 

#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <random>
#include <iomanip>

namespace MatrixSpace 
{
enum class MatrixType : uint8_t 
{
    Zero_Matrix,
    Ones_Matrix,
    Identity_Matrix, 
    Random_Matrix
};

class Matrix
{
private:
    class MatrixException : public std::exception 
    {
    private:
        MatrixException(std::string msg) : exception_msg(std::move(msg)) {}
        std::string exception_msg;
    public:
        const char *what() const noexcept override 
        { 
            return exception_msg.c_str(); 
        }
        friend class Matrix;
    };

    size_t m_rows{0};
    size_t m_cols{0};
    MatrixType m_type;
    double *m_data{nullptr};
public:
    Matrix(size_t rows, size_t cols);
    Matrix(size_t rows, size_t cols, MatrixType type);
    Matrix(const Matrix &other);
    Matrix(Matrix &&M) noexcept;
    ~Matrix();

    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);
    double &operator()(size_t rows, size_t cols);
    Matrix &operator=(const Matrix &M);
    Matrix &operator=(Matrix &&M);
    Matrix operator+(const Matrix &M) const;
    Matrix operator-(const Matrix &M) const;
    Matrix operator*(double scalar) const;
    Matrix operator*(const Matrix &M) const;
    void operator+=(const Matrix &M);
    void operator-=(const Matrix &M);
    void operator*=(double scalar);
    void operator*=(const Matrix &M);

    Matrix transpose();
    double determinant();
    Matrix exponent(unsigned int n) const;
    void fill_matrix(MatrixType type);
    void random();
}; // Matrix
}; // MatrixSpace