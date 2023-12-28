#include "./matrix.h"
#include <stdio.h>
#include <stdlib.h>

Matrix Matrix_create(int rows, int cols)
{
    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;

    mat.data = (double*)malloc(rows * cols * sizeof(double));
    if (!mat.data)
        mat.valid = -1;

    return mat;
}

Matrix Matrix_create_invalid()
{
    Matrix mat = { 0, 0, -1, 0 };
    return mat;
}

void Matrix_free(Matrix mat)
{
    free(mat.data);
}

int get_value(const Matrix* mat, int row, int col)
{
    return mat->data[row * mat->cols + col];
}

void set_value(Matrix* mat, int row, int col, int value)
{
    mat->data[row * mat->cols + col] = value;
}

void Matrix_display(Matrix* mat)
{
    for (size_t row = 0; row < mat->rows; ++row) {
        for (size_t col = 0; col < mat->cols; ++col) {
            printf("%d ", get_value(mat, row, col));
        }
        printf("\n");
    }
}

Matrix Matrix_add(Matrix* mat1, Matrix* mat2)
{
    if (mat1->rows != mat2->rows || mat1->cols != mat2->cols) {
        fprintf(stderr, "Matrix dimensions do not match for addition\n");
        return Matrix_create_invalid();
    }

    Matrix result = Matrix_create(mat1->rows, mat1->cols);

    for (size_t row = 0; row < mat1->rows; ++row) {
        for (size_t col = 0; col < mat1->cols; ++col) {
            set_value(&result, row, col,
                get_value(mat1, row, col) + get_value(mat2, row, col));
        }
    }

    return result;
}

Matrix Matrix_multiply(Matrix* mat1, Matrix* mat2)
{
    if (mat1->cols != mat2->rows) {
        fprintf(stderr, "Matrix dimensions do not match for addition\n");
        return Matrix_create_invalid();
    }

    Matrix result = Matrix_create(mat1->rows, mat2->cols);

    for (size_t row = 0; row < mat1->rows; ++row) {
        for (size_t col = 0; col < mat2->cols; ++col) {
            size_t sum = 0;
            for (size_t col2 = 0; col2 < mat1->cols; ++col2) {
                sum += get_value(mat1, row, col2) * get_value(mat2, col2, col);
            }
            set_value(&result, row, col, sum);
        }
    }

    return result;
}

Matrix Matrix_multiply_num(const Matrix* mat, int num)
{
    Matrix result = Matrix_create(mat->rows, mat->cols);

    for (size_t row = 0; row < mat->rows; ++row) {
        for (size_t col = 0; col < mat->cols; ++col) {
            set_value(&result, row, col, get_value(mat, row, col) * num);
        }
    }

    return result;
}

static int Matrix_determinant_recursive(const Matrix* mat, int size)
{
    if (size == 1) {
        return get_value(mat, 0, 0);
    }
    else if (size == 2) {
        return (get_value(mat, 0, 0) * get_value(mat, 1, 1)) -
            (get_value(mat, 0, 1) * get_value(mat, 1, 0));
    }
    else {
        int determinant = 0;
        int sign = 1;

        for (size_t i = 0; i < size; ++i) {
            Matrix submatrix = Matrix_create(size - 1, size - 1);

            for (size_t j = 1; j < size; ++j) {
                for (size_t k = 0, l = 0; k < size; ++k) {
                    if (k == i) {
                        continue;
                    }
                    set_value(&submatrix, j - 1, l++, get_value(mat, j, k));
                }
            }

            determinant += sign * get_value(mat, 0, i) *
                Matrix_determinant_recursive(&submatrix, size - 1);
            sign = -sign;
            Matrix_free(submatrix);
        }

        return determinant;
    }
}

int Matrix_determinant(const Matrix* mat)
{
    if (mat->rows != mat->cols) {
        fprintf(stderr, "Matrix is not square for determinant calculation\n");
        return 0;
    }

    return Matrix_determinant_recursive(mat, mat->rows);
}

Matrix Matrix_exponential(const Matrix* mat)
{
    if (mat->rows != mat->cols) {
        fprintf(stderr, "Matrix is not square for matrix exponential\n");
        return Matrix_create_invalid();
    }

    size_t size = mat->rows;
    Matrix result = Matrix_create(size, size);
    Matrix term = Matrix_create(size, size);
    Matrix identity = Matrix_create(size, size);

    for (size_t row = 0; row < size; ++row) {
        for (size_t col = 0; col < size; ++col) {
            set_value(&identity, row, col, (row == col) ? 1 : 0);
        }
    }

    for (size_t row = 0; row < size; ++row) {
        for (size_t col = 0; col < size; ++col) {
            set_value(&result, row, col, get_value(&identity, row, col));
        }
    }

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            set_value(&term, i, j, get_value(mat, i, j));
        }
    }
    size_t k = 1;
    while (1) {
        Matrix temp = Matrix_multiply_num(&term, 1.0 / k);

        Matrix result_temp = Matrix_add(&result, &temp);
        Matrix_free(result);
        result = result_temp;

        Matrix_free(temp);

        if (k > 50)
            break;
        k++;
    }

    Matrix_free(term);
    Matrix_free(identity);

    return result;
}
