#pragma once
#include <iostream>
#include <iomanip>
#include <random>


#define FLOAT_MIN -100.
#define FLOAT_MAX 100.

using matrix_element = double;


enum class InfillPattern {
    RANDOM = 1,
    UNIT,
    BLANK,
    RAISING,
    NULL_MATRIX
};  //  infill patttern enumerate


enum MatrixErrors {
    MEMORY_ALLOCATION_ERROR = 1,
    DETERMINANT_ERROR,
    MATH_DOMAIN_ERROR,
    SIZE_ERROR,
    NULL_MATRIX_ERROR,
};  //  errors enumerate


class Matrix
{

private:
    size_t _rows, _cols;
    size_t _size;
    void random_infill();
    void unit_infill();
    void blank_infill();
    void raising_infill();

public:
    matrix_element * _data;

    Matrix();  //  default constructor
    Matrix(const size_t rows, const size_t cols);  //  regular constructor
    Matrix(const size_t rows, const size_t cols, const InfillPattern pattern);  //  filling constructor
    Matrix(const size_t rows, const size_t cols, const matrix_element * data);  //  external array filling constructor

    Matrix(const size_t dim);  //  squared matrix constructor
    Matrix(const size_t dim, const InfillPattern pattern);  //  squared matrix filling constructor
    Matrix(const size_t dim, const matrix_element * data);  //  squared matrix external array filling constructor

    Matrix(const Matrix &copy);  // copying constructor

    ~Matrix();  // destructor

    matrix_element & operator () (const size_t row, const size_t col);  // indexing operator overload
    Matrix& operator + (const Matrix & second_summand);  //  sum operator overload
    Matrix& operator - (const Matrix & deductible);  //  sub operator overload
    bool operator == (const Matrix & comparison);  //  eq operator overload
    Matrix& operator * (const Matrix & multi);  //  multiplication operator overload
    void operator *= (const matrix_element scalar);
    void operator += (const Matrix & summand);
    void operator -= (const Matrix & deductible);
    void operator *= (const Matrix * multi);


    void print();
    double det();
    size_t get_rows() {return this->_rows;}
    size_t get_cols() {return this->_cols;}
    size_t get_size() {return this->_size;}
    void transpose();

};  //  class Matrix