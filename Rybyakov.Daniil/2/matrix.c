#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef double MatrixItem;


typedef struct Matrix {
    unsigned int cols;
    unsigned int rows;
    MatrixItem *data;
}Matrix;


const Matrix ZERO = { 0, 0, NULL };


Matrix matrix_memory(const unsigned int cols, const unsigned int rows) {
    Matrix matrix;
    matrix.cols = cols;
    matrix.rows = rows;

    unsigned int n_data = matrix.cols * matrix.rows;

    matrix.data = malloc(n_data * sizeof(MatrixItem));
    return matrix;
}


void fill_matrix(Matrix* matrix) 
{
    for (unsigned int index = 0; index < matrix->cols * matrix->rows; ++index) {
        matrix->data[index] = ((int)rand()%10);
    }
}


void print_matrix(const Matrix matrix) 
{
    for (int row = 0; row < matrix.rows; ++row) {
        for (int col = 0; col < matrix.cols; ++col) {
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


Matrix matrix_sum(const Matrix matrix1, const Matrix matrix2) 
{
    if (matrix1.rows != matrix2.rows || matrix1.cols != matrix2.cols) {
        errorofsize("Addition", "Matrixes should have equal sizes");
        return ZERO;
    }

    Matrix result = matrix_memory(matrix1.cols, matrix1.rows);
    unsigned int n_data = result.cols * result.rows;

    for (unsigned int index = 0; index < n_data; ++index) {
        result.data[index] = matrix1.data[index] + matrix2.data[index];
    }
    return result;
}


Matrix subtruct_matrices(const Matrix matrix1, const Matrix matrix2) 
{
    if (matrix1.rows != matrix2.rows && matrix1.cols != matrix2.cols) {
        errorofsize("Subtruction", "Matrixes should have equal sizes");
        return ZERO;
    }

    Matrix result = matrix_memory(matrix1.cols, matrix1.rows);
    unsigned int n_data = result.cols * result.rows;

    for (unsigned int index = 0; index < n_data; ++index) {
        result.data[index] = matrix1.data[index] - matrix2.data[index];
    }
    return result;
}


Matrix multiply_on_number(const Matrix matrix, MatrixItem number) 
{
    Matrix result = matrix_memory(matrix.cols, matrix.rows);
    unsigned int n_data = result.cols * result.rows;

    for (int index = 0; index < n_data; ++index) {
        result.data[index] = matrix.data[index] * number;
    }
    return result;
}


Matrix multiply_matrices(const Matrix matrix1, const Matrix matrix2) 
{
    if (matrix1.cols != matrix2.rows) {
        errorofsize("Multiplication", "Matrixes should have certain sizes");
        return ZERO;
    }

    unsigned int n_cols = matrix2.cols;
    unsigned int n_rows = matrix1.rows;
    Matrix result = matrix_memory(n_cols, n_rows);

    for (unsigned int row = 0; row < n_rows; ++row) {
        for (unsigned int col = 0; col < n_cols; ++col) {
            double summa = 0.0;
            for (unsigned int k = 0; k < matrix1.cols; ++k) {
                summa +=
                    matrix1.data[row * matrix1.cols + k] *
                    matrix2.data[k * matrix2.cols + col];
            }
            result.data[row * n_cols + col] = summa;
        }
    }
    return result;
}


MatrixItem det_matrix(const Matrix matrix) 
{
    if (matrix.cols != matrix.rows) {
        errorofsize("Getting determinant", "Matrix should be square");
        return 0.;
    }

    MatrixItem result = 0;
    unsigned int n = matrix.cols;

    if (n == 1) {
        result = matrix.data[0];
        return result;
    }

    for (int row = 0; row < n; ++row) {
        int col = 0;
        Matrix submatrix = matrix_memory(n - 1, n - 1);
        unsigned int row_offset = 0;
        unsigned int col_offset = 0;

        for (unsigned int sub_row = 0; sub_row < n - 1; ++sub_row) {
            for (unsigned int sub_col = 0; sub_col < n - 1; ++sub_col) {
                if (sub_row == row) { row_offset = 1; }
                if (sub_col == col) { col_offset = 1; }

                submatrix.data[sub_row * (n - 1) + sub_col] =
                    matrix.data[(sub_row + row_offset) * n + (sub_col + col_offset)];
            }
        }
        result += pow(-1, row + col) * matrix.data[row * n + col] * det_matrix(submatrix);
        memory_clear(&submatrix);
    }
    return result;
}


Matrix transpose(const Matrix matrix) 
{
    Matrix result = matrix_memory(matrix.rows, matrix.cols);

    for (unsigned int row = 0; row < result.rows; ++row) {
        for (unsigned int col = 0; col < result.cols; ++col) {
            result.data[row * result.cols + col] = matrix.data[col * result.rows + row];
        }
    }
    return result;
}


Matrix unit(unsigned int dimention) 
{
    Matrix result = matrix_memory(dimention, dimention);

    for (unsigned int row = 0; row < result.rows; ++row) {
        for (unsigned int col = 0; col < result.cols; ++col) {
            result.data[row * result.cols + col] = (row == col) ? 1. : 0.;
        }
    }
    return result;
}


Matrix matrix_copy(const Matrix matrix) 
{
    Matrix result = matrix_memory(matrix.cols, matrix.rows);

    for (unsigned int index = 0; index < matrix.cols * matrix.rows; ++index) {
        result.data[index] = matrix.data[index];
    }
    return result;
}


Matrix expo(const Matrix matrix, int accuracy) 
{
    if (matrix.cols != matrix.rows) {
        errorofsize("Exp", "Matrix should be square");
        return ZERO;
    }

    Matrix result_, pow_, multiplied;
    Matrix result = unit(matrix.rows);
    Matrix pow = unit(matrix.rows);
    int factorial = 1;

    for (int acc = 1; acc <= accuracy; ++acc) {
        factorial *= acc;

        pow_ = multiply_matrices(pow, matrix);
        pow = matrix_copy(pow_);
        memory_clear(&pow_);

        multiplied = multiply_on_number(pow, 1. / factorial);
        result_ = matrix_sum(result, multiplied);
        result = matrix_copy(result_);

        memory_clear(&result_);
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
    fill_matrix(&mat1);
    print_matrix(mat1);

    printf("     Second matrix\n");
    mat2 = matrix_memory(3, 3);
    fill_matrix(&mat2);
    print_matrix(mat2);

    printf("     Sum\n");
    Matrix addition;
    addition = matrix_sum(mat1, mat2);
    print_matrix(addition);
    memory_clear(&addition);

    printf("     Sub\n");
    Matrix subtruction;
    subtruction = subtruct_matrices(mat1, mat2);
    print_matrix(subtruction);
    memory_clear(&subtruction);

    printf("     Multiply\n");
    Matrix multiplication_matrices;
    multiplication_matrices = multiply_matrices(mat1, mat2);
    print_matrix(multiplication_matrices);
    memory_clear(&multiplication_matrices);

    MatrixItem determinant;
    printf("     Det 1\n");
    determinant = det_matrix(mat1);
    printf("%.2f\n\n", determinant);

    printf("     Det 2\n");
    determinant = det_matrix(mat2);
    printf("%.2f\n\n", determinant);

    printf("     Transp 1\n");
    Matrix transpose1;
    transpose1 = transpose(mat1);
    print_matrix(transpose1);
    memory_clear(&transpose1);

    printf("     Transp 2\n");
    Matrix transpose2;
    transpose2 = transpose(mat2);
    print_matrix(transpose2);
    memory_clear(&transpose2);

    printf("     e\n");
    Matrix exponenta;
    exponenta = expo(mat1, 3);
    print_matrix(exponenta);
    memory_clear(&exponenta);
    memory_clear(&mat1);
    memory_clear(&mat2);

}