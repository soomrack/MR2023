#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct {
    unsigned int rows;
    unsigned int cols;
    double** values;
    double* data;
} Matrix;

void matrix_memory(Matrix* matrix)
{
    matrix->data = (double*)malloc(matrix->rows * matrix->cols * sizeof(double) + matrix->rows * sizeof(double*));
    matrix->values = matrix->data + matrix->rows * matrix->cols;
    for (int row = 0; row < matrix->rows; row++)
        matrix->values[row] = matrix->data + row * matrix->cols;
}

void delete_from_memory(Matrix* matrix)
{
    free(matrix->data);
}

void copy_matrix(Matrix* from, Matrix* to) {
    for (int rows = 0; rows < from->rows; rows++)
    {
        for (int cols = 0; cols < from->cols; cols++)
        {
            to->values[rows][cols] = from->values[rows][cols];
        }
    }
}

void output(Matrix* matrix)
{
    for (int rows = 0; rows < matrix->rows; rows++)
    {
        for (int cols = 0; cols < matrix->cols; cols++)
        {
            printf("%lf ", matrix->values[rows][cols]);
        }
        printf("\n");
    }
    printf("\n");
}

void null_array(Matrix* matrix)
{
    matrix_memory(matrix);

    for (int rows = 0; rows < matrix->rows; rows++)
    {
        for (int cols = 0; cols < matrix->cols; cols++)
        {
            matrix->values[rows][cols] = 0;
        }
    }
}

void identity_matrix(Matrix* matrix)
{
    matrix_memory(matrix);

    for (int rows = 0; rows < matrix->rows; rows++)
    {
        for (int cols = 0; cols < matrix->cols; cols++)
        {
            if (rows == cols)
            {
                matrix->values[rows][cols] = 1;
            }
            else
            {
                matrix->values[rows][cols] = 0;
            }
        }
    }
}


void random_matrix(Matrix* matrix)
{
    matrix_memory(matrix);

    for (int rows = 0; rows < matrix->rows; rows++)
    {
        for (int cols = 0; cols < matrix->cols; cols++)
        {
            matrix->values[rows][cols] = rand() % 10;
        }
    }
}

void multiply_by_scalar(Matrix* matrix, double scalar, int verbose)
{
    if (verbose)
        printf("MULTIPLICATION BY SCALAR:\n");

    for (int rows = 0; rows < matrix->rows; rows++)
    {
        for (int cols = 0; cols < matrix->cols; cols++)
        {
            matrix->values[rows][cols] *= scalar;
        }
    }
    if (verbose)
        output(matrix);
}

void add(Matrix* A, Matrix* B, Matrix* result, int verbose)
{
    if (verbose)
        printf("SUM:\n");

    Matrix add_matrix = { 2, 2, NULL, NULL };
    matrix_memory(&add_matrix);

    for (int rows = 0; rows < add_matrix.rows; rows++)
    {
        for (int cols = 0; cols < add_matrix.cols; cols++)
        {
            add_matrix.values[rows][cols] = A->values[rows][cols] + B->values[rows][cols];
        }
    }

    copy_matrix(&add_matrix, result);

    if (verbose)
        output(&add_matrix);
    delete_from_memory(&add_matrix);
}

void subtract(Matrix A, Matrix B, int verbose)
{
    if (verbose)
        printf("DIFFERENCE:\n");

    Matrix subtract_matrix = { 2, 2, NULL, NULL };
    matrix_memory(&subtract_matrix);

    for (int rows = 0; rows < subtract_matrix.rows; rows++)
    {
        for (int cols = 0; cols < subtract_matrix.cols; cols++)
        {
            subtract_matrix.values[rows][cols] = A.values[rows][cols] - B.values[rows][cols];
        }
    }
    if (verbose)
        output(&subtract_matrix);
    delete_from_memory(&subtract_matrix);
}

void multiply(Matrix* A, Matrix* B, Matrix* result, int verbose)
{
    if (A->cols != B->rows) {
        printf("Error: The number of columns of matrix A must be equal to the number of rows of matrix B.\n");
        return;
    }

    if (verbose)
        printf("PRODUCT:\n");

    Matrix multiply_matrix = { A->rows, B->cols, NULL, NULL };
    null_array(&multiply_matrix);

    for (int rows = 0; rows < multiply_matrix.rows; rows++)
    {
        for (int cols = 0; cols < multiply_matrix.cols; cols++)
        {
            for (int k = 0; k < A->cols; k++)
            {
                multiply_matrix.values[rows][cols] += A->values[rows][k] * B->values[k][cols];
            }
        }
    }
    if (verbose)
        output(&multiply_matrix);

    copy_matrix(&multiply_matrix, result);

    delete_from_memory(&multiply_matrix);
}


void transpose(Matrix* A, Matrix* result, int verbose)
{
    if (verbose)
        printf("TRANSPOSITION:\n");

    result->rows = A->cols;
    result->cols = A->rows;

    matrix_memory(result);

    for (int rows = 0; rows < result->rows; rows++)
    {
        for (int cols = 0; cols < result->cols; cols++)
        {
            result->values[rows][cols] = A->values[cols][rows];
        }
    }

    if (verbose)
        output(result);

    delete_from_memory(result);
}

void expose(Matrix* A, Matrix* result, int verbose)
{

    if (A->cols != A->rows) {
        printf("Error: Matrix A must be square in order to expose it\n");
        return;
    }

    if (verbose)
        printf("EXPONENT:\n");

    Matrix exp_matrix = { A->rows, A->cols, NULL, NULL };

    Matrix current_element = { A->rows, A->cols, NULL, NULL };

    identity_matrix(&exp_matrix);
    identity_matrix(&current_element);



    int number_of_terms_in_exponential_expansion = 50;

    for (int i = 1; i < number_of_terms_in_exponential_expansion; i++) {
        multiply(&current_element, A, &current_element, 0);
        multiply_by_scalar(&current_element, 1.0 / i, 0);
        add(&exp_matrix, &current_element, &exp_matrix, 0);
    }
    
    result->rows = exp_matrix.rows;
    result->cols = exp_matrix.cols;

    if (verbose)
        output(&exp_matrix);

    delete_from_memory(&exp_matrix);
}

void function_testing()
{
    Matrix A = { 2, 2, NULL, NULL };
    Matrix B = { 2, 2, NULL, NULL };
    Matrix C = { 2, 2, NULL, NULL };
    random_matrix(&A);
    random_matrix(&B);
    random_matrix(&C);
    printf("Matrix A:\n");
    output(&A);
    printf("Matrix B:\n");
    output(&B);

    printf("Operations:\n");
    add(&A, &B, &C, 1);
    subtract(A, B, 1);
    multiply(&A, &B, &C, 1);
    transpose(&A, &C, 1);
    expose(&A, &C, 1);
    delete_from_memory(&A);
    delete_from_memory(&B);
}

int main()
{
    srand(time(NULL));
    function_testing();
}
