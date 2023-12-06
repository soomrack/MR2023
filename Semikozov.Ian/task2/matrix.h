#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

typedef struct __attribute__((visibility("hidden"))) { int _; } NoArg;
// use compound literal to form a dummy value for _Generic, only its type matters
#define NO_ARG ((const NoArg){0})

#define CREATE_MATRIX(args, rows, cols, type, ...) _Generic((type), \
                                                            NoArg:   _internal_create_default_matrix, \
                                                            default: _internal_create_type_matrix \
                                                           ) args
#define create_matrix(...) CREATE_MATRIX((__VA_ARGS__), __VA_ARGS__, NO_ARG, ~)

#define multiply_matrix(matrix, type) _Generic((type), \
                                               Matrix_Instance: _internal_multiply_matrices, \
                                               default:         _internal_multiply_matrix_scalar \
                                              ) (matrix, type)

typedef struct {
    int numRows;
    int numCols;
    double **pData;
} Matrix_Instance;

enum Matrix_Type {
    Zero_Matrix,
    Ones_Matrix,
    Identity_Matrix, 
    Random_Matrix
};

/************************ Basic matrix functions ************************/

Matrix_Instance _internal_create_default_matrix(int rows, int cols); // --> overloaded in create_matrix
Matrix_Instance _internal_create_type_matrix(int rows, int cols, enum Matrix_Type matrix_type); // --> overloaded in create_matrix
Matrix_Instance copy_matrix(const Matrix_Instance A, const Matrix_Instance B);
void free_matrix(Matrix_Instance matrix);
void fill_matrix_random(Matrix_Instance matrix);
void fill_matrix_values(Matrix_Instance matrix, double value); 
void print_matrix(Matrix_Instance matrix);

/************************ Math matrix functions ************************/

Matrix_Instance _internal_multiply_matrices(const Matrix_Instance A, const Matrix_Instance B); // --> overloaded in multiply_matrix
Matrix_Instance _internal_multiply_matrix_scalar(const Matrix_Instance matrix, const double scalar); // --> overloaded in multiply_matrix
Matrix_Instance substract_matrices(const Matrix_Instance A, const Matrix_Instance B);
Matrix_Instance sum_matrices(const Matrix_Instance A, const Matrix_Instance B);
Matrix_Instance transpose_matrix(const Matrix_Instance matrix);
Matrix_Instance exponent_matrix(const Matrix_Instance matrix, const unsigned int n);
double sum_elements_matrix(const Matrix_Instance A);
double determinant_matrix(const Matrix_Instance A);


#endif // MATRIX_H