#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef NAN
#endif

#define MATRIX_MUST_BE_SQUARE "\nMatrix must be square!\n\n"
#define MULT_SHAPE_ERROR                                                      \
    "\nError: The number of columns of matrix A must be equal to the number " \
    "of rows of matrix B.\n\n"
#define SHAPE_NOT_EQUAL_ERROR \
    "\nError: The shape of the matrices must be the same!\n\n"
#define MEMORY_ERROR "\nError: Memory error\n\n"

typedef struct {
    size_t rows;
    size_t cols;
    double** values;
    double* data;
} Matrix;

const Matrix matrix_null = {0, 0, NULL, NULL};

size_t matrix_memory(Matrix* matrix) {
    matrix->data =
        (double*)malloc(matrix->rows * matrix->cols * sizeof(double) +
                        matrix->rows * sizeof(double*));

    if (matrix->data == NULL) return 1;

    matrix->values = matrix->data + matrix->rows * matrix->cols;

    if (matrix->values == NULL) return 1;

    for (size_t row = 0; row < matrix->rows; row++) {
        matrix->values[row] = matrix->data + row * matrix->cols;
    }

    return 0;
}

void matrix_error(const char* error_message) { printf("%s", error_message); }

void matrix_delete_from_memory(Matrix* matrix) {
    free(matrix->data);
    matrix->rows = 0;
    matrix->cols = 0;
    matrix = NULL;  // is this necessary?
}

void matrix_copy(Matrix* source, Matrix* destination) {
    if (source->cols != destination->cols ||
        source->rows != destination->rows) {
        matrix_error(SHAPE_NOT_EQUAL_ERROR);
    }

    memcpy(destination->data, source->data,
           sizeof(double) * source->cols * source->rows);
}

void matrix_print(Matrix matrix) {
    for (size_t rows = 0; rows < matrix.rows; rows++) {
        for (size_t cols = 0; cols < matrix.cols; cols++) {
            printf("%lf ", matrix.values[rows][cols]);
        }
        printf("\n");
    }
    printf("\n");
}

void matrix_zero(Matrix* matrix) {
    matrix_memory(matrix);
    if (matrix->data == NULL) {
        matrix_error(MEMORY_ERROR);
        return;
    }

    memset(matrix->data, 0, matrix->rows * matrix->cols * sizeof(double));
}

void matrix_identity(Matrix* matrix) {
    matrix_memory(matrix);
    if (matrix->data == NULL) {
        matrix_error(MEMORY_ERROR);
        return;
    }

    for (size_t rows = 0; rows < matrix->rows; rows++) {
        for (size_t cols = 0; cols < matrix->cols; cols++) {
            if (rows == cols) {
                matrix->values[rows][cols] = 1.;
            } else {
                matrix->values[rows][cols] = 0.;
            }
        }
    }
}

void matrix_from_array(Matrix* matrix, double* array) {
    matrix_memory(matrix);
    if (matrix->data == NULL) {
        printf("%d", sizeof(array) / sizeof(array[0]));
        matrix_error(MEMORY_ERROR);
        return;
    }

    size_t index = 0;
    memcpy(matrix->data, array, matrix->cols * matrix->rows * sizeof(double));
}

void matrix_random(Matrix* matrix) {
    matrix_memory(matrix);
    if (matrix->data == NULL) {
        matrix_error(MEMORY_ERROR);
        return;
    }

    for (size_t item = 0; item < matrix->rows * matrix->cols; item++) {
        matrix->data[item] = rand() % 10;
    }
}

Matrix matrix_multiplication_by_scalar(Matrix matrix, double scalar) {
    Matrix scaled_matrix = {matrix.rows, matrix.cols, NULL, NULL};
    matrix_memory(&scaled_matrix);
    matrix_copy(&matrix, &scaled_matrix);

    if (scaled_matrix.data == NULL) {
        printf(MEMORY_ERROR);
        return matrix_null;
    }

    for (size_t item = 0; item < matrix.rows * matrix.cols; item++) {
        scaled_matrix.data[item] *= scalar;
    }

    return scaled_matrix;
}

Matrix matrix_addition(Matrix A, Matrix B) {
    if (A.cols != B.cols || A.rows != B.rows) {
        printf(SHAPE_NOT_EQUAL_ERROR);
        return matrix_null;
    }

    Matrix add_matrix = {A.rows, A.cols, NULL, NULL};
    matrix_memory(&add_matrix);
    if (add_matrix.data == NULL) {
        printf(MEMORY_ERROR);
        return matrix_null;
    }

    for (size_t item = 0; item < add_matrix.rows * add_matrix.cols; item++) {
        add_matrix.data[item] = A.data[item] + B.data[item];
    }

    return add_matrix;
}

Matrix matrix_subtraction(Matrix A, Matrix B) {
    if (A.cols != B.cols || A.rows != B.rows) {
        printf(SHAPE_NOT_EQUAL_ERROR);
        return matrix_null;
    }

    Matrix subtract_matrix = {A.rows, A.cols, NULL, NULL};
    matrix_memory(&subtract_matrix);
    if (subtract_matrix.data == NULL) {
        printf(MEMORY_ERROR);
        return matrix_null;
    }

    for (size_t item = 0; item < subtract_matrix.rows * subtract_matrix.cols;
         item++) {
        subtract_matrix.data[item] = A.data[item] - B.data[item];
    }

    return subtract_matrix;
}

Matrix matrix_multiplication(Matrix A, Matrix B) {
    if (A.cols != B.rows) {
        matrix_error(MULT_SHAPE_ERROR);
        return matrix_null;
    }

    Matrix multiply_matrix = {A.rows, B.cols, NULL, NULL};
    matrix_zero(&multiply_matrix);
    if (multiply_matrix.data == NULL) {
        printf(MEMORY_ERROR);
        return matrix_null;
    }

    for (size_t rows = 0; rows < multiply_matrix.rows; rows++) {
        for (size_t cols = 0; cols < multiply_matrix.cols; cols++) {
            for (size_t k = 0; k < A.cols; k++) {
                multiply_matrix.values[rows][cols] +=
                    A.values[rows][k] * B.values[k][cols];
            }
        }
    }

    return multiply_matrix;
}

Matrix matrix_transpose(Matrix A) {
    Matrix transpose_matrix = {A.cols, A.rows, NULL, NULL};
    matrix_zero(&transpose_matrix);
    if (transpose_matrix.data == NULL) {
        printf(MEMORY_ERROR);

        return matrix_null;
    }

    for (size_t rows = 0; rows < transpose_matrix.rows; rows++) {
        for (size_t cols = 0; cols < transpose_matrix.cols; cols++) {
            transpose_matrix.values[rows][cols] = A.values[cols][rows];
        }
    }

    return transpose_matrix;
}

double matrix_determinant(Matrix A) {
    if (A.cols != A.rows) {
        matrix_error(MATRIX_MUST_BE_SQUARE);
        return NAN;
    }

    Matrix triangular_matrix = {A.rows, A.cols, NULL, NULL};
    matrix_zero(&triangular_matrix);
    if (triangular_matrix.data == NULL) {
        printf(MEMORY_ERROR);
        return NAN;
    }
    matrix_copy(&A, &triangular_matrix);

    for (size_t current_row = 0; current_row < A.rows; current_row++) {
        for (size_t next_row = current_row + 1; next_row < A.rows; next_row++) {
            if (triangular_matrix.values[current_row][current_row] == 0) {
                triangular_matrix.values[current_row][current_row] = 1.0e-18;
            }

            double current_row_scaler =
                triangular_matrix.values[next_row][current_row] /
                triangular_matrix.values[current_row][current_row];

            for (size_t column = 0; column < A.rows; column++) {
                triangular_matrix.values[next_row][column] =
                    triangular_matrix.values[next_row][column] -
                    current_row_scaler *
                        triangular_matrix.values[current_row][column];
            }
        }
    }

    double det = 1.0;
    for (size_t diagonal_element = 0; diagonal_element < A.rows;
         diagonal_element++) {
        det *= triangular_matrix.values[diagonal_element][diagonal_element];
    }
    matrix_delete_from_memory(&triangular_matrix);

    return det;
}

static void matrix_exp_multiplication(Matrix* A, Matrix* B) {
    if (A->cols != B->rows) {
        matrix_error(MULT_SHAPE_ERROR);
        return;
    }

    Matrix multiply_matrix = {A->rows, A->cols, NULL, NULL};
    matrix_memory(&multiply_matrix);
    matrix_copy(A, &multiply_matrix);
    
    if (multiply_matrix.data == NULL) {
        matrix_error(MEMORY_ERROR);
        return;
    }
    
    for (size_t rows = 0; rows < multiply_matrix.rows; rows++) {
        for (size_t cols = 0; cols < multiply_matrix.cols; cols++) {
            for (size_t k = 0; k < multiply_matrix.cols; k++) {
                A->values[rows][cols] +=
                    multiply_matrix.values[rows][k] * B->values[k][cols];
            }
        }
    }
    
    matrix_delete_from_memory(&multiply_matrix);
}

static void matrix_exp_multiplication_by_scalar(Matrix* matrix, double scalar) {
    for (size_t item = 0; item < matrix->rows * matrix->cols; item++) {
        matrix->data[item] *= scalar;
    }
}

static void matrix_exp_addition(Matrix* A, Matrix* B) {
    if (A->cols != B->cols || A->rows != B->rows) {
        matrix_error(SHAPE_NOT_EQUAL_ERROR);
        return;
    }

    for (size_t item = 0; item < A->rows * A->cols; item++) {
        A->data[item] = A->data[item] + B->data[item];
    }
}


Matrix matrix_exponent(Matrix A) {
    if (A.cols != A.rows) {
        matrix_error(MATRIX_MUST_BE_SQUARE);
        return matrix_null;
    }

    Matrix exp_matrix = {A.rows, A.cols, NULL, NULL};

    Matrix current_element = {A.rows, A.cols, NULL, NULL};

    matrix_identity(&exp_matrix);
    if (exp_matrix.data == NULL) {
        matrix_error(MEMORY_ERROR);
        return matrix_null;
    }
    matrix_identity(&current_element);
    if (current_element.data == NULL) {
        matrix_error(MEMORY_ERROR);
        return matrix_null;
    }

    size_t number_of_terms_in_matrix_exponential_expansion = 50;

    for (size_t term = 1;
         term < number_of_terms_in_matrix_exponential_expansion; term++) {
        matrix_exp_multiplication(&current_element, &A);
        matrix_exp_multiplication_by_scalar(&current_element, 1.0 / term);
        matrix_exp_addition(&exp_matrix, &current_element);
    }

    matrix_delete_from_memory(&current_element);
    return exp_matrix;
}

void function_testing() {
    Matrix A = {3, 3, NULL, NULL};
    Matrix B = {3, 3, NULL, NULL};
    Matrix C = {3, 3, NULL, NULL};
    double det = NAN;

    matrix_from_array(&A, (double[]){1, -2, 3, 4, 0, 6, -7, 8, 9});
    matrix_from_array(&B, (double[]){1., 2., 3., 4., 5., 6., 7., 8., 9.});
    matrix_memory(&C);

    printf("Matrix A:\n");
    matrix_print(A);
    printf("Matrix B:\n");
    matrix_print(B);

    printf("Operations:\n");

    C = matrix_addition(A, B);
    printf("\nSUM:\n");
    matrix_print(C);

    C = matrix_subtraction(A, B);
    printf("\nDIFFERENCE:\n");
    matrix_print(C);

    C = matrix_multiplication(A, B);
    printf("\nPRODUCT:\n");
    matrix_print(C);

    C = matrix_transpose(A);
    printf("\nTRANSPOSITION:\n");
    matrix_print(C);

    det = matrix_determinant(A);
    printf("\nDETERMINANT:\n");
    printf("%lf\n\n", det);

    C = matrix_exponent(A);
    printf("\nEXPONENT:\n");
    matrix_print(C);

    matrix_delete_from_memory(&A);
    matrix_delete_from_memory(&B);
    matrix_delete_from_memory(&C);
}

void main() {
    srand(3);
    function_testing();
}
