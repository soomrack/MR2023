#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Matrix {
    size_t cols;
    size_t rows;
    double* values;
} Matrix;

const Matrix MATRIX_NULL = { 0, 0, NULL };

Matrix matrix_init(const size_t cols, const size_t rows) {
    Matrix matrix;
    matrix.cols = cols;
    matrix.rows = rows;
    size_t n_values = matrix.cols * matrix.rows;
    matrix.values = malloc(n_values * sizeof(double));

    if (matrix.values == NULL) {
        printf("Failed to allocate memory for matrix\n");
        return MATRIX_NULL;
    }

    return matrix;
}

void matrix_set_values(Matrix* matrix) {
    if (matrix == NULL || matrix->values == NULL) {
        printf("Matrix is not properly initialized\n");
        return;
    }

    for (size_t index = 0; index < matrix->cols * matrix->rows; ++index) {
        matrix->values[index] = (double)rand();
    }
}

void matrix_error_size(char* operation_name, char* error) {
    printf("%s is impossible. %s\n", operation_name, error);
}

int matrix_is_null(const Matrix matrix) {
    return matrix.cols == 0 && matrix.rows == 0 ? 1 : 0;
}

void matrix_print(const Matrix matrix) {
    if (matrix_is_null(matrix)) {
        printf("The matrix doesn't exist\n\n");
        return;
    }

    for (size_t row = 0; row < matrix.rows; ++row) {
        for (size_t col = 0; col < matrix.cols; ++col) {
            printf("%.2f ", matrix.values[row * matrix.cols + col]);
        }
        printf("\n");
    }
    printf("\n");
}

void matrix_free(Matrix* matrix) {
    free(matrix->values);
}

Matrix matrix_add(const Matrix matrix1, const Matrix matrix2) {
    if (matrix1.rows != matrix2.rows || matrix1.cols != matrix2.cols) {
        matrix_error_size("Addition", "Matrixes should have equal sizes");
        return MATRIX_NULL;
    }

    Matrix result = matrix_init(matrix1.cols, matrix1.rows);

    if (result.values == NULL) {
        return MATRIX_NULL;
    }

    size_t n_values = result.cols * result.rows;

    for (size_t index = 0; index < n_values; ++index) {
        result.values[index] = matrix1.values[index] + matrix2.values[index];
    }

    return result;
}

Matrix matrix_subtract(const Matrix matrix1, const Matrix matrix2) {
    if (matrix1.rows != matrix2.rows && matrix1.cols != matrix2.cols) {
        matrix_error_size("Subtraction", "Matrixes should have equal sizes");
        return MATRIX_NULL;
    }

    Matrix result = matrix_init(matrix1.cols, matrix1.rows);

    if (result.values == NULL) {
        return MATRIX_NULL;
    }

    size_t n_values = result.cols * result.rows;

    for (size_t index = 0; index < n_values; ++index) {
        result.values[index] = matrix1.values[index] - matrix2.values[index];
    }

    return result;
}

Matrix matrix_multiply_by_double(const Matrix matrix, double number) {
    Matrix result = matrix_init(matrix.cols, matrix.rows);

    if (result.values == NULL) {
        return MATRIX_NULL;
    }

    size_t n_values = result.cols * result.rows;

    for (size_t index = 0; index < n_values; ++index) {
        result.values[index] = matrix.values[index] * number;
    }

    return result;
}

Matrix matrix_multiply(const Matrix A, const Matrix B) {
    if (A.cols != B.rows) {
        matrix_error_size("Multiplication", "Matrix A cols should be equal to Matrix B rows");
        return MATRIX_NULL;
    }

    Matrix C = matrix_init(B.cols, A.rows);

    if (C.values == NULL) {
        return MATRIX_NULL;
    }

    for (size_t rowA = 0; rowA < A.rows; ++rowA) {
        for (size_t colsB = 0; colsB < B.cols; ++colsB) {
            C.values[rowA * C.cols + colsB] = 0;
            for (size_t idx = 0; idx < A.cols; ++idx) {
                C.values[rowA * C.cols + colsB] += A.values[rowA * A.cols + idx] * B.values[idx * B.cols + colsB];
            }
        }
    }

    return C;
}

double matrix_det(const Matrix matrix) {
    if (matrix.cols != matrix.rows) {
        matrix_error_size("Getting determinant", "Matrix should be square");
        return 0.0;
    }

    double result = 0.0;
    size_t n = matrix.cols;

    if (n == 1) {
        result = matrix.values[0];
        return result;
    }

    for (size_t row = 0; row < n; ++row) {
        size_t col = 0;
        Matrix submatrix = matrix_init(n - 1, n - 1);

        if (submatrix.values == NULL) {
            matrix_free(&submatrix);
            return 0.0;
        }

        size_t row_offset = 0;
        size_t col_offset = 0;

        for (size_t sub_row = 0; sub_row < n - 1; ++sub_row) {
            for (size_t sub_col = 0; sub_col < n - 1; ++sub_col) {
                if (sub_row == row) {
                    row_offset = 1;
                }
                if (sub_col == col) {
                    col_offset = 1;
                }

                submatrix.values[sub_row * (n - 1) + sub_col] =
                    matrix.values[(sub_row + row_offset) * n + (sub_col + col_offset)];
            }
        }

        result += pow(-1, row + col) * matrix.values[row * n + col] * matrix_det(submatrix);
        matrix_free(&submatrix);
    }

    return result;
}

Matrix matrix_transpose(const Matrix matrix) {
    Matrix result = matrix_init(matrix.rows, matrix.cols);

    if (result.values == NULL) {
        return MATRIX_NULL;
    }

    for (size_t row = 0; row < result.rows; ++row) {
        for (size_t col = 0; col < result.cols; ++col) {
            result.values[row * result.cols + col] = matrix.values[col * result.rows + row];
        }
    }

    return result;
}

Matrix matrix_identity(size_t dimension) {
    Matrix result = matrix_init(dimension, dimension);

    if (result.values == NULL) {
        return MATRIX_NULL;
    }

    for (size_t row = 0; row < result.rows; ++row) {
        for (size_t col = 0; col < result.cols; ++col) {
            result.values[row * result.cols + col] = (row == col) ? 1. : 0.;
        }
    }

    return result;
}

Matrix matrix_invertible(const Matrix matrix) {
    if (matrix.cols != matrix.rows) {
        matrix_error_size("Getting invertible matrix", "Matrix should be square");
        return MATRIX_NULL;
    }

    Matrix transponent = matrix_transpose(matrix);

    if (transponent.values == NULL) {
        return MATRIX_NULL;
    }

    Matrix result = matrix_init(matrix.cols, matrix.rows);

    if (result.values == NULL) {
        matrix_free(&transponent);
        return MATRIX_NULL;
    }

    for (size_t row = 0; row < transponent.rows; ++row) {
        for (size_t col = 0; col < transponent.cols; ++col) {
            Matrix submatrix = matrix_init(transponent.cols - 1, transponent.rows - 1);

            if (submatrix.values == NULL) {
                matrix_free(&submatrix);
                matrix_free(&transponent);
                matrix_free(&result);
                return MATRIX_NULL;
            }

            size_t row_offset = 0;
            size_t col_offset = 0;

            for (size_t sub_row = 0; sub_row < submatrix.rows; ++sub_row) {
                if (row == sub_row) {
                    row_offset = 1;
                }
                for (size_t sub_col = 0; sub_col < submatrix.cols; ++sub_col) {
                    if (col == sub_col) {
                        col_offset = 1;
                    }

                    submatrix.values[sub_row * (transponent.cols - 1) + sub_col] =
                        transponent.values[(sub_row + row_offset) * transponent.cols + (sub_col + col_offset)];
                }
            }

            result.values[row * matrix.cols + col] = pow(-1, row + col) * matrix_det(submatrix);
            matrix_free(&submatrix);
        }
    }

    matrix_free(&transponent);

    Matrix multiplied_result = matrix_multiply_by_double(result, 1 / matrix_det(result));
    matrix_free(&result);

    return multiplied_result;
}

Matrix matrix_copy(const Matrix matrix) {
    Matrix result = matrix_init(matrix.cols, matrix.rows);

    if (result.values == NULL) {
        return MATRIX_NULL;
    }

    memcpy(result.values, matrix.values, matrix.cols * matrix.rows * sizeof(double));

    return result;
}

Matrix matrix_exp(const Matrix matrix, int accuracy) {
    if (matrix.cols != matrix.rows) {
        matrix_error_size("Exp", "Matrix should be square");
        return MATRIX_NULL;
    }

    Matrix new_result, new_powered, multiplied;
    Matrix result = matrix_identity(matrix.rows);
    Matrix powered = matrix_copy(matrix);
    int factorial = 1;

    for (int acc = 1; acc <= accuracy; ++acc) {
        factorial *= acc;

        new_powered = matrix_multiply(powered, matrix);
        matrix_free(&powered);
        powered = matrix_copy(new_powered);
        matrix_free(&new_powered);

        multiplied = matrix_multiply_by_double(powered, 1. / factorial);

        new_result = matrix_add(result, multiplied);
        matrix_free(&result);
        result = matrix_copy(new_result);
        matrix_free(&new_result);
        matrix_free(&multiplied);
    }

    matrix_free(&powered);
    return result;
}

int main() {
    Matrix m1, m2;

    m1 = matrix_init(3, 3);
    matrix_set_values(&m1);
    printf("\nMatrix 1\n");
    matrix_print(m1);

    m2 = matrix_init(3, 3);
    matrix_set_values(&m2);
    printf("Matrix 2\n");
    matrix_print(m2);

    Matrix addition;
    addition = matrix_add(m1, m2);
    printf("\nMatrix addition\n");
    matrix_print(addition);
    matrix_free(&addition);

    Matrix subtraction;
    subtraction = matrix_subtract(m1, m2);
    printf("Matrix subtraction\n");
    matrix_print(subtraction);
    matrix_free(&subtraction);

    double determinant;
    determinant = matrix_det(m1);
    printf("Matrix 1 determinant\n");
    printf("%.2f\n\n", determinant);
    determinant = matrix_det(m2);
    printf("Matrix 2 determinant\n");
    printf("%.2f\n\n", determinant);

    Matrix multiplication1;
    multiplication1 = matrix_multiply_by_double(m1, 5.);
    printf("Matrix 1 multiplication\n");
    matrix_print(multiplication1);
    matrix_free(&multiplication1);

    Matrix multiplication2;
    multiplication2 = matrix_multiply(m1, m2);
    printf("Matrix 1 and 2 multiplication\n");
    matrix_print(multiplication2);
    matrix_free(&multiplication2);

    Matrix trans;
    trans = matrix_transpose(m1);
    printf("Matrix 1 transposed\n");
    matrix_print(trans);
    matrix_free(&trans);

    Matrix invert;
    invert = matrix_invertible(m1);
    printf("Matrix 1 inverted\n");
    matrix_print(invert);
    matrix_free(&invert);

    Matrix exponent;
    exponent = matrix_exp(m1, 3);
    printf("Matrix 1 exponential\n");
    matrix_print(exponent);
    matrix_free(&exponent);

    matrix_free(&m1);
    matrix_free(&m2);

    return 0;
}
