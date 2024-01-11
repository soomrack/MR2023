#pragma once
#include <iostream>
#include <iomanip>
#include <random>
#include <map>

#define FLOAT_MIN -100.
#define FLOAT_MAX 100.



namespace MatrixHandler {

    using matrix_element = double;

    enum InfillPattern {
        RANDOM = 1,
        UNIT,
        BLANK,
        RAISING,
    };  //  infill patttern enum


    class MatrixException : public std::exception {

        friend class Matrix;

    private:
        enum MatrixError: int {
            ALLOCATION_ERROR = 1,
            OVERFLOW_ERROR,
            DETERMINANT_ERROR,
            MATH_DOMAIN_ERROR,
            BAD_INITIALIZER_ERROR,
            INDEX_ERROR,
            NULL_MATRIX_ERROR
        };

        std::map<int, std::string> error_map {
            {1, "ALLOCATION ERROR"},
            {2, "OVERFLOW ERROR"},
            {3, "DETERMINANT ERROR"},
            {4, "MATH DOMAIN ERROR"},
            {5, "BAD INITIALIZER ERROR"},
            {6, "INDEX ERROR"},
            {7, "NULL MATRIX ERROR"}
        };

        std::string exception_message;

    public:
        explicit MatrixException(MatrixError code): exception_message{error_map[code]} {}
        const char* what() const noexcept override {
            return exception_message.c_str();
        }

    };  //  class MatrixException


    class Matrix {

    private:
        size_t _rows{0}, _cols{0};
        // size_t _size{0};
        matrix_element* _data{nullptr};
        void random_infill();
        void unit_infill();
        void blank_infill();
        void raising_infill();
        void swap(Matrix& other);

    public:
        Matrix() = default;  //  default constructor
        Matrix(const size_t rows, const size_t cols);  //  regular constructor
        Matrix(const size_t rows, const size_t cols, const InfillPattern pattern);  //  filling constructor
        Matrix(const size_t rows, const size_t cols, std::initializer_list<matrix_element> l);  //  init list constructor
        Matrix(const size_t dim);  //  squared matrix constructor
        Matrix(const size_t dim, const InfillPattern pattern);  //  squared matrix filling constructor
        Matrix(const size_t dim, std::initializer_list<matrix_element> l);  //  squared matrix init list constructor
        Matrix(const Matrix &copy);  // copying constructor
        Matrix(Matrix&& other_rvalue);  //  moving constructor. Need to initialize matrix with rvalue
        ~Matrix();  // destructor

        matrix_element& operator()(const size_t row, const size_t col) const;  // indexing operator
        matrix_element& operator[](const size_t idx) const;
        Matrix& operator=(Matrix other);  //  assign operator. Use copy & swap. With that implementation
        // assign operator for rvalue-references is no longer needed.
        // Matrix& operator=(Matrix&& other_rvalue);
        Matrix& operator=(std::initializer_list<matrix_element> l);  //  assign operator for initializer list
        Matrix operator+(const Matrix & second_summand) const;  //  sum operator overload
        Matrix operator-(const Matrix & deductible) const;  //  sub operator overload
        Matrix operator*(const Matrix & multi) const;  //  multiplication operator overload
        Matrix operator*(matrix_element scalar) const;
        void operator*=(matrix_element scalar);
        void operator*=(const Matrix& multi);
        void operator+=(const Matrix & summand);
        void operator-=(const Matrix & deductible);
        bool operator==(const Matrix & comparison) const;  //  eq operator overload
        friend std::ostream& operator<<(std::ostream& stream, const Matrix& output);

        matrix_element determinant();
        void transpose();
        Matrix  exponent(unsigned int degree);

        inline size_t get_rows() const {return this->_rows;}
        inline size_t get_cols() const {return this->_cols;}
        inline size_t get_size() const {return this->_rows * this->_cols;}
    };  //  class Matrix

    std::ostream& operator << (std::ostream& stream, const Matrix& output);

};  //  namespace Matrix
