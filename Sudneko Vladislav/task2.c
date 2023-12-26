#include <stdio.h>  
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>


#define MATRIX_MUST_BE_SQUARE "\nMatrix must be square!\n\n"
#define MULT_SHAPE_ERROR "\nError: The number of columns of matrix A must be equal to the number of rows of matrix B.\n\n"
#define SHAPE_NOT_EQUAL_ERROR "\nError: The shape of the matrices must be the same!\n\n"
#define MEMORY_ERROR "\nError: Memory error\n\n"


typedef struct {
    size_t rows;
    size_t cols;
    double** values;
    double* data;
} Matrix;


size_t matrix_memory(Matrix* matrix)
{
    matrix->data = (double*)malloc(matrix->rows * matrix->cols * sizeof(double) + matrix->rows * sizeof(double*));
    
    // Added a lot of allocation checks

    if (matrix->data == NULL) return 1;
    
    matrix->values = matrix->data + matrix->rows * matrix->cols;

    if (matrix->values == NULL) return 1;

    for (size_t row = 0; row < matrix->rows; row++) {
        matrix->values[row] = matrix->data + row * matrix->cols;
    }

    return 0;
}


void delete_from_memory(Matrix matrix)
{
    free(matrix.data);
}


void copy_matrix(Matrix* source, Matrix* destination) {

    // Added shape check
    if (source->cols != destination->cols || source->rows != destination->rows) {
        printf(SHAPE_NOT_EQUAL_ERROR);
    }

    memcopy(destination->data, source->data, sizeof(double)*source->cols*source->rows);
}


void output(Matrix matrix)
{
    for (size_t rows = 0; rows < matrix.rows; rows++)
    {
        for (size_t cols = 0; cols < matrix.cols; cols++)
        {
            printf("%lf ", matrix.values[rows][cols]);
        }
        printf("\n");
    }
    printf("\n");
}


Matrix zero_matrix(Matrix* matrix)
{
    matrix_memory(matrix);
    if (matrix->data == NULL){
        printf(MEMORY_ERROR);
        printf("The result is incorrect!");
        return matrix;
    } 


    for (size_t rows = 0; rows < matrix->rows; rows++)
    {
        for (size_t cols = 0; cols < matrix->cols; cols++)
        {
            matrix->values[rows][cols] = 0;
        }
    }
    return *matrix;
}


Matrix identity_matrix(Matrix* matrix)
{
    matrix_memory(matrix);
    if (matrix->data == NULL){
        printf(MEMORY_ERROR);
        printf("The result is incorrect!");
        return *matrix;
    } 

    for (size_t rows = 0; rows < matrix->rows; rows++)
    {
        for (size_t cols = 0; cols < matrix->cols; cols++)
        {
            if (rows == cols)
            {
                matrix->values[rows][cols] = 1.;
            }
            else
            {
                matrix->values[rows][cols] = 0.;
            }
        }
    }
    return *matrix;
}


Matrix* random_matrix(Matrix* matrix)
{
    matrix_memory(matrix);
    if (matrix->data == NULL){
        printf(MEMORY_ERROR);
        printf("The result is incorrect!");
        return matrix;
    } 

    for (size_t item = 0; item < matrix->rows*matrix->cols; item++)
    {
            matrix->data[item] = rand() % 10;
    }
    return matrix;
}


Matrix multiply_by_scalar(Matrix* matrix, double scalar)
{
    for (size_t item = 0; item < matrix->rows*matrix->cols; item++)
    {
            matrix->data[item] *= scalar;
    }

    return *matrix;
}


Matrix add(Matrix* A, Matrix* B)
{
    // Added shape check
    if (A->cols != B->cols || A->rows != B->rows) {
        printf(SHAPE_NOT_EQUAL_ERROR);
        printf("The result is incorrect!");
        return *A;
    }

    Matrix add_matrix = { A->rows, A->cols, NULL, NULL };
    matrix_memory(&add_matrix);
    if (add_matrix.data == NULL){
        printf(MEMORY_ERROR);
        printf("The result is incorrect!");
        return *A;
    } 

    for (size_t item = 0; item < add_matrix.rows*add_matrix.cols; item++)
    {
        add_matrix.data[item] = A->data[item] + B->data[item]
    }

    return add_matrix;
}


Matrix subtract(Matrix* A, Matrix* B)
{
    // Added shape check
    if (A->cols != B->cols || A->rows != B->rows) {
        printf(SHAPE_NOT_EQUAL_ERROR);
        printf("The result is incorrect!");
        return *A;
    }

    Matrix subtract_matrix = { A->rows, A->cols, NULL, NULL };
    matrix_memory(&subtract_matrix);

    for (size_t item = 0; item < subtract_matrix.rows*subtract_matrix.cols; item++)
    {
        subtract_matrix.data[item] = A->data[item] - B->data[item]
    }

    return subtract_matrix;
}


Matrix multiply(Matrix* A, Matrix* B)
{
    if (A->cols != B->rows) {
        printf(MULT_SHAPE_ERROR);
        printf("THe result is incorrect!");
        return *A;
    }

    Matrix multiply_matrix = { A->rows, B->cols, NULL, NULL };
    multiply_matrix = zero_matrix(&multiply_matrix);

    for (size_t rows = 0; rows < multiply_matrix.rows; rows++)
    {
        for (size_t cols = 0; cols < multiply_matrix.cols; cols++)
        {
            for (size_t k = 0; k < A->cols; k++)
            {
                multiply_matrix.values[rows][cols] += A->values[rows][k] * B->values[k][cols];
            }
        }
    }

    return multiply_matrix;
}


Matrix transpose(Matrix* A)
{
    Matrix transpose_matrix = { A->cols, A->rows, NULL, NULL }; // fixed shape
    transpose_matrix = zero_matrix(&transpose_matrix);

    for (size_t rows = 0; rows < transpose_matrix.rows; rows++)
    {
        for (size_t cols = 0; cols < transpose_matrix.cols; cols++)
        {
            transpose_matrix.values[rows][cols] = A->values[cols][rows];
        }
    }

    return transpose_matrix;
}


double determinant(Matrix* A)
{

    if (A->cols != A->rows) {
        printf(MATRIX_MUST_BE_SQUARE);
        return 1.;
    }

    Matrix triangular_matrix = { A->rows, A->cols, NULL, NULL };
    zero_matrix(&triangular_matrix);
    copy_matrix(A, &triangular_matrix);

    for (size_t current_row = 0; current_row < A->rows; current_row++) {
        for (size_t next_row = current_row + 1; next_row < A->rows; next_row++) {
            if (triangular_matrix.values[current_row][current_row] == 0) {
                triangular_matrix.values[current_row][current_row] = 1.0e-18;
            }

            double current_row_scaler = triangular_matrix.values[next_row][current_row] / triangular_matrix.values[current_row][current_row];

            for (size_t column = 0; column < A->rows; column++) {
                triangular_matrix.values[next_row][column] = triangular_matrix.values[next_row][column] - current_row_scaler * triangular_matrix.values[current_row][column];
            }
        }
    }


    double det = 1.0;
    for (size_t i = 0; i < A->rows; i++) {
        det *= triangular_matrix.values[i][i];
    }
    delete_from_memory(triangular_matrix);

    return det;
}


Matrix exponent(Matrix* A)
{
    if (A->cols != A->rows) {
        printf(MATRIX_MUST_BE_SQUARE);
        printf("THe result is incorrect!");
        return *A;
    }

    Matrix exp_matrix = { A->rows, A->cols, NULL, NULL };

    Matrix current_element = { A->rows, A->cols, NULL, NULL };

    exp_matrix = identity_matrix(&exp_matrix);
    if (exp_matrix.data == NULL){
        printf(MEMORY_ERROR);
        printf("The result is incorrect!");
        return *A;
    }  
    current_element = identity_matrix(&current_element);
    if (current_element.data == NULL){
        printf(MEMORY_ERROR);
        printf("The result is incorrect!");
        return *A;
    } 

    size_t number_of_terms_in_exponential_expansion = 50;

    for (size_t term = 1; term < number_of_terms_in_exponential_expansion; term++) {
        current_element = multiply(&current_element, A); // fix arguments
        current_element = multiply_by_scalar(&current_element, 1.0 / term);
        exp_matrix = add(&exp_matrix, &current_element);
    }

    delete_from_memory(current_element);
    return exp_matrix;
}


void function_testing()
{
    Matrix A = { 3, 3, NULL, NULL };
    Matrix B = { 3, 3, NULL, NULL };
    Matrix C = { 3, 3, NULL, NULL };
    double det = 0.0;
    random_matrix(&A);
    random_matrix(&B);
    random_matrix(&C);
    printf("Matrix A:\n");
    output(A);
    printf("Matrix B:\n");
    output(B);

    printf("Operations:\n");

    C = add(&A, &B);
    printf("\nSUM:\n");
    output(C);

    C = subtract(&A, &B);
    printf("\nDIFFERENCE:\n");
    output(C);

    C = multiply(&A, &B);
    printf("\nPRODUCT:\n");
    output(C);

    C = transpose(&A);
    printf("\nTRANSPOSITION:\n");
    output(C);

    det = determinant(&A);
    printf("\nDETERMINANT:\n");
    printf("%lf\n\n", det);

    C = exponent(&A);
    printf("\nEXPONENT:\n");
    output(C);

    
    delete_from_memory(A);
    delete_from_memory(B);
    delete_from_memory(C);
}


void main()
{
    srand(3);
    function_testing();
}
