#ifndef LIBMATRIX_H
#define LIBMATRIX_H

#include <cstring>
#include <iostream>
#include <random>
#include <iomanip>
#include <cmath>

typedef double matrix_item;

const matrix_item RANDOM_LOW = -100., RANDOM_HIGH = 100.;
std::uniform_real_distribution<matrix_item> uniform(RANDOM_LOW, RANDOM_HIGH);
std::default_random_engine random_engine(42);

enum MatrixType {
    ZEROS, ONES, RANDOM, IDENTITY, UNFILLED
};


class MatrixException : public std::exception {
    std::string _msg;
public:
    explicit MatrixException(std::string msg) : _msg(std::move(msg)) {}
    const char *what() const noexcept override { return _msg.c_str(); }
};


class Matrix {
private:
    size_t rows{0};
    size_t cols{0};
    matrix_item *data{nullptr};
    void fill(enum MatrixType matrix_type);

public:
    Matrix() = default;
    explicit Matrix(unsigned int n = 3);
    Matrix(size_t rows_amount, size_t cols_amount, MatrixType matrix_type);
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
    Matrix T();
    double det();
    static unsigned long long factorial(unsigned int value);
    Matrix exp(unsigned int n) const;
    ~Matrix() { delete[] data; }
};

#endif //LIBMATRIX_H