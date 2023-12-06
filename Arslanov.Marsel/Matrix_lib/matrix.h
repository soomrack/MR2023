#ifndef MATRIX_H
#define MATRIX_H

#include <malloc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include <math.h>
#include <stdio.h>

typedef double matrix_element;

typedef struct
{
    size_t rows;
    size_t cols;
    matrix_element *data;
} matrix;

typedef enum
{
    ZERO,
    INCREASING,
    UNIT,
    RANDOM
}MATRIX_TYPE;

typedef enum {
    MEMORY_ERROR, 
    BAD_MATRIX_ERROR, 
    COLS_ROWS_ERROR, 
    FREE_ERROR, 
    COPY_ERROR, 
    DET_ERROR,
    ZERO_DIV
}ERROR_TYPE;

matrix* matrix_new(size_t rows, size_t cols);

void matrix_error(ERROR_TYPE error);

void matrix_free(matrix* m);

void matrix_print(matrix* m);

void matrix_fill(matrix* m, MATRIX_TYPE type);

uint8_t matrices_sizes_equal(const matrix* a, const matrix* b);

matrix* matrix_sum(matrix* a, matrix* b);

matrix* matrix_sub(matrix* a, matrix* b);

matrix* matrix_transposition(matrix *m);

double matrix_determinant(const matrix* m);

matrix* matrix_mult(const matrix* a, const matrix* b);

matrix* matrix_increase(matrix* m, const matrix* increase_matrix);

uint64_t factorial(const uint16_t value);

matrix* matrix_scalar_division(matrix* m, const double value);

void matrix_copy(matrix* dest, const matrix* src);

matrix* matrix_exp(const matrix* m, const uint8_t accuracy);


#endif // MATRIX_H