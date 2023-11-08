#ifndef LIBMATRIX_H
#define LIBMATRIX_H

#include <cstring>
#include <iostream>
#include <random>
#include <iomanip>

typedef double matrix_item;

const matrix_item RANDOM_LOW = -100., RANDOM_HIGH = 100.;
std::uniform_real_distribution<matrix_item> uniform(RANDOM_LOW, RANDOM_HIGH);
std::default_random_engine random_engine(42);

enum MatrixType {
    ZEROS, ONES, RANDOM, IDENTITY, UNFILLED
};
enum ErrorType {
    MEMORY_ERROR, BAD_MATRIX_ERROR, COLS_ROWS_ERROR, DET_ERROR, EXP_LEVEl_ERROR
};


class Matrix {
private:
    size_t rows{0};
    size_t cols{0};
    matrix_item *data{nullptr};


    static void error(enum ErrorType error_type);

    void fill(enum MatrixType matrix_type);

public:
    Matrix(size_t rows_amount, size_t cols_amount, MatrixType matrix_type);

    matrix_item get(size_t row, size_t col);

    void set(size_t row, size_t col, matrix_item item);

    void print();


    Matrix(const Matrix &M);

    Matrix &operator=(const Matrix &M);


    Matrix operator+(const Matrix &M) const;

    Matrix operator-(const Matrix &M) const;

    Matrix operator*(double scalar) const;

    Matrix operator*(const Matrix &M) const;


    Matrix T();

    double det();

    Matrix exp(int n);

    ~Matrix() { delete[] this->data; }
};

#endif //LIBMATRIX_H