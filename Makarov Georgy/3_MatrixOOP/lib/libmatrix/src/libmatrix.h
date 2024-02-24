#ifndef LIBMATRIX_H
#define LIBMATRIX_H

#include <cstring>
#include <iostream>
#include <random>
#include <iomanip>

typedef double matrix_item;

const matrix_item RANDOM_LOW = -10., RANDOM_HIGH = 10.;
std::uniform_real_distribution<matrix_item> uniform(RANDOM_LOW, RANDOM_HIGH);
std::default_random_engine random_engine(42);

enum MatrixType {
    ZEROS, ONES, RANDOM, IDENTITY, UNFILLED
};


class MatrixException : public std::exception {
private:
    std::string exception_msg;
public:
    explicit MatrixException(std::string msg) : exception_msg(std::move(msg)) {}
    const char *what() const noexcept override { return exception_msg.c_str(); }
};


class Matrix {
private:
    size_t rows{0};
    size_t cols{0};
    matrix_item *data{nullptr};
private:
    void fill(enum MatrixType matrix_type);
public:
    Matrix() = default;
    explicit Matrix(size_t n);
    Matrix(size_t rows_amount, size_t cols, MatrixType matrix_type);
    matrix_item get(size_t row, size_t col);
    void set(size_t row, size_t col, matrix_item item);
    void print();
    Matrix(const Matrix &M);
    Matrix(Matrix &&M) noexcept;
    Matrix &operator=(const Matrix &M);
    Matrix &operator=(Matrix &&M) noexcept;
    Matrix operator+(const Matrix &M) const;
    Matrix operator-(const Matrix &M) const;
    Matrix operator*(double scalar) const;
    Matrix operator*(const Matrix &M) const;
    void operator+=(const Matrix& M);
    void operator-=(const Matrix& M);
    void operator*=(double scalar);
    void operator*=(const Matrix& M);
    Matrix T();
    double det();
    Matrix exp(unsigned int n = 100) const;
    ~Matrix() { delete[] data; }  // deleting null pointer has no effect
};

#endif //LIBMATRIX_H