#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<string.h>


typedef double MatrixItem;


typedef struct Matrix {
    size_t cols;
    size_t rows;
    MatrixItem* data;
}Matrix;


const Matrix MATRIX_ZERO = { 0, 0, NULL };


Matrix matrix_memory(const size_t cols, const size_t rows) 
{
    Matrix matrix;
    matrix.cols = cols;
    matrix.rows = rows;

    if (cols == 0 || rows == 0) {
        struct Matrix A = { .cols = cols, .rows = rows, .data = NULL };
        return A;
    }

    if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols) return MATRIX_ZERO;

    size_t n_data = matrix.cols * matrix.rows;

    matrix.data = malloc(n_data * sizeof(MatrixItem));

    if (matrix.data == NULL) {
        return MATRIX_ZERO;
    }


    return matrix;
}


void matrix_fill_rand(Matrix* matrix)
{
    for (size_t index = 0; index < matrix->cols * matrix->rows; ++index) {
        matrix->data[index] = ((int)rand() % 10);
    }
}


void matrix_print(const Matrix matrix)
{
    for (size_t row = 0; row < matrix.rows; ++row) {
        for (size_t col = 0; col < matrix.cols; ++col) {
            printf("%.2f ", matrix.data[row * matrix.cols + col]);
        }
        printf("\n");
    }
    printf("\n");
}


void errorofsize(char* operation_name, char* error)
{
    printf("%s is impossible. %s\n", operation_name, error);
}


void memory_clear(Matrix* matrix)
{
    free(matrix->data);
}


Matrix matrix_sum(const Matrix A, const Matrix B)
{
    if (A.rows != B.rows || A.cols != B.cols) {
        errorofsize("Addition", "Matrixes should have equal sizes");
        return MATRIX_ZERO;
    }

    Matrix result = matrix_memory(A.cols, A.rows);
    if (result.data == NULL) return MATRIX_ZERO;

    for (size_t index = 0; index < (result.cols * result.rows); ++index) {
        result.data[index] = A.data[index] + B.data[index];
    }
    return result;
}


Matrix subtruct_matrices(const Matrix A, const Matrix B)
{
    if (A.rows != B.rows && A.cols != B.cols) {
        errorofsize("Subtruction", "Matrixes should have equal sizes");
        return MATRIX_ZERO;
    }

    Matrix result = matrix_memory(A.cols, A.rows);
    size_t n_data = result.cols * result.rows;

    if (result.data == NULL) return MATRIX_ZERO;

    for (size_t index = 0; index < n_data; ++index) {
        result.data[index] = A.data[index] - B.data[index];
    }
    return result;
}


Matrix multiply_on_number(const Matrix matrix, MatrixItem number)
{
    Matrix result = matrix_memory(matrix.cols, matrix.rows);
    size_t n_data = result.cols * result.rows;

    if (result.data == NULL) return MATRIX_ZERO;

    for (size_t index = 0; index < n_data; ++index) {
        result.data[index] = matrix.data[index] * number;
    }
    return result;
}


Matrix matrix_multiply(const Matrix A, const Matrix B)
{
    if (A.cols != B.rows) {
        errorofsize("Multiplication", "Matrixes should have certain sizes");
        return MATRIX_ZERO;
    }

    size_t n_cols = B.cols;
    size_t n_rows = A.rows;
    Matrix result = matrix_memory(n_cols, n_rows);

    if (result.data == NULL) return MATRIX_ZERO;

    for (size_t rowA = 0; rowA < n_rows; ++rowA) {
        for (size_t colB = 0; colB < n_cols; ++colB) {
            double summa = 0.0;
            for (size_t k = 0; k < A.cols; ++k) {
                summa +=
                    A.data[rowA * A.cols + k] *
                    B.data[k * B.cols + colB];
            }
            result.data[rowA * n_cols + colB] = summa;
        }
    }
    return result;
}


MatrixItem matrix_det(const Matrix matrix)
{
    if (matrix.cols != matrix.rows) {
        errorofsize("Getting determinant", "Matrix should be square");
        return 0.;
    }

    MatrixItem result = 0;
    size_t n = matrix.cols;

    if (n == 1) {
        result = matrix.data[0];
        return result;
    }

    for (size_t row = 0; row < n; ++row) {
        size_t col = 0;
        Matrix submatrix = matrix_memory(n - 1, n - 1);
        size_t row_offset = 0;
        size_t col_offset = 0;

        for (size_t sub_row = 0; sub_row < n - 1; ++sub_row) {
            for (size_t sub_col = 0; sub_col < n - 1; ++sub_col) {
                if (sub_row == row) { row_offset = 1; }
                if (sub_col == col) { col_offset = 1; }

                submatrix.data[sub_row * (n - 1) + sub_col] =
                    matrix.data[(sub_row + row_offset) * n + (sub_col + col_offset)];
            }
        }
        result += pow(-1, row + col) * matrix.data[row * n + col] * matrix_det(submatrix);
        memory_clear(&submatrix);
    }
    return result;
}


Matrix transpose(const Matrix matrix)
{
    Matrix result = matrix_memory(matrix.rows, matrix.cols);

    if (result.data == NULL) return MATRIX_ZERO;

    for (size_t row = 0; row < result.rows; ++row) {
        for (size_t col = 0; col < result.cols; ++col) {
            result.data[row * result.cols + col] = matrix.data[col * result.rows + row];
        }
    }
    return result;
}


Matrix unit(size_t dimention)
{
    Matrix result = matrix_memory(dimention, dimention);

    if (result.data == NULL) return MATRIX_ZERO;

    for (size_t row = 0; row < result.rows; ++row) {
        for (size_t col = 0; col < result.cols; ++col) {
            result.data[row * result.cols + col] = (row == col) ? 1. : 0.;
        }
    }
    return result;
}


Matrix matrix_copy(const Matrix matrix)
{
    Matrix result = matrix_memory(matrix.cols, matrix.rows);
    if (result.data == NULL) return MATRIX_ZERO;
    memcpy(result.data, matrix.data, matrix.rows * matrix.cols * sizeof(MatrixItem));

    return result;
}


Matrix matrix_expo(const Matrix matrix, size_t accuracy)
{
    if (matrix.cols != matrix.rows) {
        errorofsize("Exp", "Matrix should be square");
        return MATRIX_ZERO;
    }

    Matrix result_help, pow_help, multiplied;
    Matrix result = unit(matrix.rows);
    Matrix pow = unit(matrix.rows);
    if (result.data == NULL) return MATRIX_ZERO;
    if (pow.data == NULL) return MATRIX_ZERO;
    int factorial = 1;

    for (size_t acc = 1; acc <= accuracy; ++acc) {
        factorial *= acc;

        pow_help = matrix_multiply(pow, matrix);
        if (pow_help.data == NULL) return MATRIX_ZERO;
        pow = matrix_copy(pow_help);
        if (pow.data == NULL) return MATRIX_ZERO;

        memory_clear(&pow_help);

        multiplied = multiply_on_number(pow, 1. / factorial);
        if (multiplied.data == NULL) return MATRIX_ZERO;
        result_help = matrix_sum(result, multiplied);
        if (result_help.data == NULL) return MATRIX_ZERO;
        result = matrix_copy(result_help);
        if (result.data == NULL) return MATRIX_ZERO;

        memory_clear(&result_help);
        memory_clear(&multiplied);
    }
    memory_clear(&pow);
    return result;
}

int main()
{
    Matrix mat1, mat2;

    printf("\n     First matrix\n");
    mat1 = matrix_memory(3, 3);
    matrix_fill_rand(&mat1);
    matrix_print(mat1);

    printf("     Second matrix\n");
    mat2 = matrix_memory(3, 3);
    matrix_fill_rand(&mat2);
    matrix_print(mat2);

    printf("     Sum\n");
    Matrix addition;
    addition = matrix_sum(mat1, mat2);
    matrix_print(addition);
    memory_clear(&addition);

    printf("     Sub\n");
    Matrix subtruction;
    subtruction = subtruct_matrices(mat1, mat2);
    matrix_print(subtruction);
    memory_clear(&subtruction);

    printf("     Multiply\n");
    Matrix multiplication_matrices;
    multiplication_matrices = matrix_multiply(mat1, mat2);
    matrix_print(multiplication_matrices);
    memory_clear(&multiplication_matrices);

    MatrixItem determinant;
    printf("     Det 1\n");
    determinant = matrix_det(mat1);
    printf("%.2f\n\n", determinant);

    printf("     Det 2\n");
    determinant = matrix_det(mat2);
    printf("%.2f\n\n", determinant);

    printf("     Transp 1\n");
    Matrix transpose1;
    transpose1 = transpose(mat1);
    matrix_print(transpose1);
    memory_clear(&transpose1);

    printf("     Transp 2\n");
    Matrix transpose2;
    transpose2 = transpose(mat2);
    matrix_print(transpose2);
    memory_clear(&transpose2);

    printf("     e\n");
    Matrix exponenta;
    exponenta = matrix_expo(mat1, 3);
    matrix_print(exponenta);
    memory_clear(&exponenta);
    memory_clear(&mat1);
    memory_clear(&mat2);
}