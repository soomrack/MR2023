#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#define SUCCESS 0
#define FAIL 1
#pragma once

// #define RANDOM (char)'r'
// #define UNIT (char)'u'
// #define BLANK (char)'b'


/*
next to create:
1. Error message enum and error handler function


*/

enum InfillPattern {
    RANDOM,
    UNIT,
    BLANK,
    RAISING
};


enum MatrixErrors {
    MALLOC_ERROR,
    DETERMINANT_ERROR,
    MATH_DOMAIN_ERROR,
    SIZE_ERROR
};



/*  p[1]: - - - 
    p[2]: - - -   
    p[3]: - - -
    .
    .
    p[n]: - - -

so p[i] is a pointer, and data is a pointer to first column pointer

*/

typedef double matrix_element;

typedef struct {   
    size_t rows; 
    size_t cols; 
    matrix_element ** data; 
} Matrix; //  struct Matrix


void init_data(Matrix * this);
Matrix init_matrix(const size_t rows, const size_t cols);
void fill_matrix(Matrix * this, const enum InfillPattern pattern);
void random_pattern(Matrix * this, size_t size, matrix_element * fill_data);
void unit_pattern(Matrix * this, size_t size, matrix_element * fill_data);
void blank_pattern(Matrix * this, size_t size, matrix_element * fill_data);
void raising_pattern(Matrix * this, size_t size, matrix_element * fill_data);
void fill_with_data(Matrix * this, matrix_element* filling_array);
void delete_matrix(Matrix * this);
void print_matrix_element(const matrix_element val, const size_t counter, const  size_t cols);
void print_matrix(const Matrix * this);
void error_handler(const enum MatrixErrors error, const char * func_name);
Matrix matrix_sum(const Matrix * matrix_1, const Matrix * matrix_2);  //  done
Matrix matrix_sub(const Matrix * matrix_1, const Matrix * matrix_2);  //  done
void matrix_transposition(Matrix  *this);  // done
double matrix_determinant(const Matrix * this);  //  done 
Matrix get_submatrix(const Matrix * this, const size_t row_to_delete, const size_t col_to_delete);  //  done
Matrix matrix_multiplication(const Matrix * matrix_1, const Matrix * matrix_2);  //  done
Matrix matrix_power(const Matrix * this, const uint16_t power);
void constant_division(Matrix * this, double constant);
Matrix matrix_exponent(const Matrix * this, const int8_t degree);
uint64_t factorial(const uint16_t number);
static inline size_t matrix_size(const Matrix * this) {
    return this->cols * this->rows;
}







