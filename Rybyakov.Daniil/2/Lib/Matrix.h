#pragma once
typedef double MatrixItem;


typedef struct Matrix {
    size_t cols;
    size_t rows;
    MatrixItem* data;
}Matrix;

Matrix matrix_memory(const size_t cols, const size_t rows);
void matrix_fill_rand(Matrix* matrix);
void matrix_print(const Matrix matrix);
void errorofsize(char* operation_name, char* error);
void memory_clear(Matrix* matrix);
Matrix matrix_sum(const Matrix A, const Matrix B);
Matrix subtruct_matrices(const Matrix A, const Matrix B);
Matrix multiply_on_number(const Matrix matrix, MatrixItem number);
Matrix matrix_multiply(const Matrix A, const Matrix B);
MatrixItem matrix_det(const Matrix matrix);
Matrix transpose(const Matrix matrix);
Matrix unit(size_t dimention);
Matrix matrix_copy(const Matrix matrix);
Matrix matrix_expo(const Matrix matrix, size_t accuracy);
int main();

