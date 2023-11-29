#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct { int _; } NoArg;
// use compound literal to form a dummy value for _Generic, only its type matters
#define NO_ARG ((const NoArg){0})

// #define create_matrix(rows, cols, ...) \
//     _Generic((__VA_ARGS__), \
//         enum Matrix_Type: create_type_matrix, \
//         default: create_default_matrix \
// ) (rows, cols, ##__VA_ARGS__)

#define CREATE_MATRIX(args, rows, cols, type, ...) \
  _Generic((type), \
           NoArg: create_default_matrix, \
           default: create_type_matrix \
           ) args
#define create_matrix(...) CREATE_MATRIX((__VA_ARGS__), __VA_ARGS__, NO_ARG, ~)

#define multiply_matrix(matrix, type) _Generic((type), \
    Matrix_Instance: multiply_matrixes, \
    default: multiply_matrix_scalar \
    ) (matrix, type)

typedef struct {
    size_t numRows;
    size_t numCols;
    double **pData;
} Matrix_Instance;

enum Matrix_Type {
    Zero_Matrix,
    Identity_Matrix, 
    Random_Matrix, 
    Ones_Matrix
};

/************************ Basic matrix functions ************************/
Matrix_Instance create_default_matrix(int rows, int cols); // --> overloaded in create_matrix
Matrix_Instance create_type_matrix(int rows, int cols, enum Matrix_Type matrix_type); // --> overloaded in create_matrix

Matrix_Instance matrix_copy(const Matrix_Instance A, const Matrix_Instance B);
void free_matrix(Matrix_Instance matrix);
void fill_matrix_random(Matrix_Instance matrix);
void fill_matrix_values(Matrix_Instance matrix, double value); 
void print_matrix(Matrix_Instance matrix);

/************************ Math matrix functions ************************/
static Matrix_Instance multiply_matrixes(const Matrix_Instance A, const Matrix_Instance B); // --> overloaded in multiply_matrix
static Matrix_Instance multiply_matrix_scalar(const Matrix_Instance A, const double scalar); // --> overloaded in multiply_matrix
Matrix_Instance substract_matrix(const Matrix_Instance A, const Matrix_Instance B);
Matrix_Instance sum_matrix(const Matrix_Instance A, const Matrix_Instance B);
Matrix_Instance transpose_matrix(const Matrix_Instance A);
Matrix_Instance exponent_matrix(const Matrix_Instance A, const unsigned int n);
double sum_elements_matrix(const Matrix_Instance A);
double determinant_matrix(const Matrix_Instance A);


#endif // MATRIX_H