#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"


#define INT_SWAP(a, b) {a ^= b; b ^= a; a ^= b;}
#define ALL_SWAP(a, b) {size_t size = sizeof(a); while (size--) {INT_SWAP(((char*)&a)[size], ((char*)&b)[size]);}}

const Matrix MATRIX_NULL = {.cols = 0, .rows = 0, .items = NULL};


typedef struct {
    char mes[20];
} Error;

Error OUT_OF_RANGE = {"out_of_range"};
Error WRONG_CONDITIONS = {"wrong_conditions"};
Error MEMORY_ERROR = {"memory_error"};
Error DOUBLE_FREE = {"double_free"};


static void print_error(Error err)
{
    printf("[ERROR]: %s\n", err.mes);
}


Matrix matrix_allocate(const size_t rows, const size_t cols)
{ 
    if (rows == 0 || cols == 0) {
        return MATRIX_NULL;
    }

    if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols) {
        print_error(MEMORY_ERROR);
        return MATRIX_NULL;
    }

    Matrix mat = {.rows = rows, .cols = cols, .items = NULL};
    mat.items = (MatrixItem*) malloc(rows * cols * sizeof(MatrixItem));

    if (mat.items == NULL) {
        print_error(MEMORY_ERROR);
        return MATRIX_NULL;
    } 

    return mat;
}


void matrix_set_items(const Matrix mat, const double *values)
{
    memcpy(mat.items, values, mat.rows * mat.cols * sizeof(MatrixItem));
}


void matrix_set_zero(const Matrix mat)
{
    memset(mat.items, 0, sizeof(MatrixItem) * mat.cols * mat.rows);
}


void matrix_set_one(const Matrix mat)
{
    matrix_set_zero(mat);
    for (size_t idx = 0; idx < mat.cols; idx++)
        mat.items[idx + idx * mat.cols] = 1.0;
}


double* matrix_get_element(const Matrix mat, const size_t row, const size_t col)
{   
    if (row < 0 || row > (mat.rows - 1) || col < 0 || col > (mat.cols-1)) {
        print_error(OUT_OF_RANGE);
        return NULL;
    }

    if (row >= SIZE_MAX / sizeof(MatrixItem) / col) {
        print_error(MEMORY_ERROR);
        return NULL;
    }

    return mat.items + row * mat.cols + col;
}


void matrix_del(Matrix *mat)
{
    if (mat->items == NULL) {
        print_error(DOUBLE_FREE);
        return;
    }
    
    free(mat->items);
    *mat = MATRIX_NULL;
}


void matrix_add(const Matrix a, const  Matrix b)
{
    if ((a.rows != b.rows) || (a.cols != b.cols))  {
        print_error(WRONG_CONDITIONS);
        return;
    }

    for (size_t idx = 0; idx < (a.rows * a.cols); idx++) 
        a.items[idx] += b.items[idx];
}


Matrix matrix_sum(const Matrix a, const Matrix b)
{    
    if ((a.rows != b.rows) || (a.cols != b.cols))  {
        print_error(WRONG_CONDITIONS);
        return MATRIX_NULL;
    }
    
    Matrix sum = matrix_allocate(a.rows, a.cols);

    if (sum.items == NULL) {
        print_error(MEMORY_ERROR);
        return MATRIX_NULL;
    }

    memcpy(sum.items, a.items, sum.cols * sum.rows * sizeof(MatrixItem));
    matrix_add(sum, b);

    return sum;
}


void matrix_sub_from(const Matrix a, const  Matrix b)
{
    if ((a.rows != b.rows) || (a.cols != b.cols))  {
        print_error(WRONG_CONDITIONS);
        return;
    }
        
    for (size_t idx = 0; idx < (a.rows * a.cols); idx++) 
        a.items[idx] -= b.items[idx];
}


Matrix matrix_sub(const Matrix a, const  Matrix b)
{
    if ((a.rows != b.rows) || (a.cols != b.cols)) {
        print_error(WRONG_CONDITIONS);
        return MATRIX_NULL;
    }
    
    Matrix sub = matrix_allocate(a.rows, a.cols);

    if (sub.items == NULL) {
        print_error(MEMORY_ERROR);
        return MATRIX_NULL;
    }
    
    memcpy(sub.items, a.items, sub.cols * sub.rows * sizeof(MatrixItem));
    matrix_sub_from(sub, b);

    return sub;
}


void matrix_mult_to(const Matrix target_mat, const Matrix a, const Matrix b)
{
    if ((a.cols != b.rows) || (b.cols != target_mat.cols) || (a.rows != target_mat.rows)) {
        print_error(WRONG_CONDITIONS);
        return;
    }

    for (size_t num_row = 0; num_row < a.rows; num_row++) {
        for (size_t num_col = 0; num_col < b.cols; num_col++) {
            double sum = 0;

            for (size_t num_sum = 0; num_sum < b.rows; num_sum++) {
                sum += a.items[num_row * a.cols + num_sum] * b.items[num_sum * b.cols + num_col];
            }

            target_mat.items[num_row * target_mat.cols + num_col] = sum;
        }
    }
}


Matrix matrix_mult(const Matrix a, const Matrix b)
{
    if (a.cols != b.rows) {
        print_error(WRONG_CONDITIONS);
        return(MATRIX_NULL);
    }
    
    Matrix mult = matrix_allocate(a.rows, b.cols);

    if (mult.items == NULL) {
        print_error(MEMORY_ERROR);
        return MATRIX_NULL;
    }

    matrix_mult_to(mult, a, b);

    return mult;
}


Matrix matrix_tran(const Matrix a)
{
    Matrix tran = matrix_allocate(a.cols, a.rows);

    for (size_t num_row = 0; num_row < a.cols; num_row++) 
        for (size_t num_col = 0; num_col < a.rows; num_col++) 
            tran.items[num_row * tran.cols + num_col] = a.items[num_col * a.cols + num_row];

    return tran;
}


double matrix_det(const Matrix mat_one) {
    if (mat_one.cols != mat_one.rows) {
        print_error(WRONG_CONDITIONS);
        return 0;
    }

    Matrix mat = matrix_allocate(mat_one.rows, mat_one.cols);

    if (mat.items == NULL) {
        print_error(MEMORY_ERROR);
        return 0;
    }

    memcpy(mat.items, mat_one.items, sizeof(MatrixItem) * mat_one.rows * mat_one.cols);

    double det = 1.0;
    int pivot = 0;
    double factor = 0;

    for (size_t num_col = 0; num_col < mat.cols; num_col++) {
        pivot = num_col;

        for (size_t num_row = num_col + 1; num_row < mat.rows; num_row++) {
            if (fabs(mat.items[num_row * mat.cols + num_col]) > fabs(mat.items[pivot * mat.cols + num_col]))
                pivot = num_row;
        }

        if (pivot != num_col) {
            for (size_t idx = 0; idx < mat.rows; idx++) 
                ALL_SWAP(mat.items[num_col * mat.cols + idx], mat.items[pivot * mat.cols + idx]);

            det *= -1;
        }

        if (mat.items[num_col * mat.cols + num_col] == 0) {
            det = 0;
            break;
        }

        det *= mat.items[num_col * mat.cols + num_col];

        for (size_t num_row = num_col + 1; num_row < mat.rows; num_row++) {
            factor = mat.items[num_row * mat.cols + num_col] / mat.items[num_col * mat.cols + num_col];

            for (size_t idx = num_col + 1; idx < mat.cols; idx++)
                mat.items[num_row * mat.cols + idx] -= factor * mat.items[num_col * mat.cols + idx];
        }
    }

    matrix_del(&mat);

    return det;
}


void matrix_scalar_mult(const Matrix mat, const double factor)
{
    for (size_t idx = 0; idx < (mat.rows * mat.cols); idx++)
        mat.items[idx] *= factor;
}


double max_matrix(const Matrix mat)
{
    double max = 0;
    double num = 0;

    for (size_t idx = 0; idx < (mat.rows * mat.cols); idx++) {
        num = fabs(mat.items[idx]);
        if (num > max) max = num;
    }

    return max;
}


Matrix matrix_expm(const Matrix a, const double accuracy)
{
    if (a.cols != a.rows) {
        print_error(WRONG_CONDITIONS);
        return MATRIX_NULL;
    }

    Matrix sum = matrix_allocate(a.rows, a.cols);
    Matrix term = matrix_allocate(a.rows, a.cols);
    Matrix temp = matrix_allocate(a.rows, a.cols);

    if (sum.items == NULL || term.items == NULL || temp.items == NULL) {
        print_error(MEMORY_ERROR);
        return MATRIX_NULL;
    }

    matrix_set_one(term);
    matrix_set_zero(sum);

    matrix_add(sum, term);

    for(size_t count = 1; count < 200; count++) {
        matrix_scalar_mult(term, (1.0 / count));

        matrix_mult_to(temp, term, a);
        ALL_SWAP(term.items, temp.items);

        matrix_add(sum, term);

        if (max_matrix(term) < accuracy) break;
    }

    matrix_del(&term);
    matrix_del(&temp);

    return sum;
}


int matrix_compare(const Matrix one, const Matrix two)
{
    int compare_flag = 1;

    if ((one.cols != two.cols) || (one.rows != two.rows)) 
        compare_flag = 0;

    for (size_t idx = 0; idx < (one.rows * one.cols); idx++) {
        if ((int)(one.items[idx]*10) != (int)(two.items[idx]*10)) {
            compare_flag = 0;
            break;
        }
    }
            
    return compare_flag;
}


void matrix_print(const Matrix mat)
{
    for (size_t idx = 0; idx < (mat.rows * mat.cols); idx++)
    {
        printf(" %8.2f", mat.items[idx]);
        //printf(" %5.2g", mat.items[idx]);
        if (!((idx + 1) % mat.cols)) printf("\n");
    }

    printf("\n");
}
