#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


typedef double MatrixData;


struct Matrix{
    size_t cols;
    size_t rows;
    MatrixData *data;
};


const struct Matrix MATRIX_NULL = {.cols = 0, .rows = 0, .data = NULL}; 
enum ErrorType { MEM_ALLOC_ERROR, FALSE_MATRIX, FALSE_ROWS_COLS, EMPTY_MATRIX };


void matrix_error(enum ErrorType error)
{
    switch (error)
    {
        case MEM_ALLOC_ERROR:
            printf("memory wasn't allocated\n");
            break;
        case FALSE_MATRIX:
            printf("matrix input is incorrect or difficult to calculate\n");
            break;
        case FALSE_ROWS_COLS:
            printf("the number of rows or columns in the matrices is incorrect\n");
            break;
        case EMPTY_MATRIX:
            printf("Matrix are empty\n");
            break;
        default:
            printf("undeclared error\n");
            break;
    }
}


struct Matrix matrix_allocation(const size_t cols, const size_t rows)
{
    if (cols == 0 || rows == 0){
    struct Matrix A = {.cols = cols, .rows = rows, .data = NULL};
    return A;
    }

    if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols) {
        matrix_error(MEM_ALLOC_ERROR);
        return MATRIX_NULL; 
    }

    struct Matrix A = {.cols = cols, .rows = rows, .data = NULL};
    A.data = malloc(A.cols * A.rows * sizeof(MatrixData));
    
    if (M.data == NULL) {
        matrix_error(MEM_ALLOC_ERROR);
        return MATRIX_NULL;
    }
    
    return A;
}

struct Matrix matrix_create(const size_t cols, const size_t rows)
{
    struct Matrix A = matrix_allocation(cols, rows);
    return A;
}



struct Matrix matrix_fill(const size_t cols, size_t rows, const MatrixData *data)
{
    struct Matrix A = matrix_create(cols, rows);
    
    memcpy(A.data, data, rows * cols * sizeof(MatrixData));
    return A;
}


int matrix_add(struct Matrix A, struct Matrix B) // Adding second matrix to first matrix
{
    if (A.cols != B.cols || A.rows != B.rows){
        matrix_error(FALSE_ROWS_COLS);
        return MATRIX_NULL;
    }

    for (int pos = 0; pos != A.rows * A.cols; ++pos){
        A.data[pos]+=B.data[pos];
    }

}


struct Matrix matrix_sum(struct Matrix A, struct Matrix B, struct Matrix C) // Сreating a matrix containing the sum of the matrices
{
    if (A.cols != B.cols != C.cols || A.rows != B.rows != C.rows){ 
        matrix_error(FALSE_ROWS_COLS);
        return MATRIX_NULL; 
    }

    for (int pos = 0; pos < A.cols * A.rows; ++pos){
        C.data[pos] = A.data[pos] + B.data[pos];
    }

    return C;
}


int matrix_substraction(struct Matrix A, struct Matrix B) // Substracting second matrix from first matrix
{
    if (A.cols != B.cols || A.rows != B.rows){   
        matrix_error(FALSE_ROWS_COLS);
        return MATRIX_NULL;
    }

    for (int pos = 0; pos < A.cols * B.cols; ++pos){
        A.data[pos]-=B.data[pos];
    }
}


struct Matrix matrix_difference(struct Matrix A, struct Matrix B, struct Matrix C) // Сreating a matrix containing the difference of the matrices
{
    if (A.cols != B.cols != C.cols || A.rows != B.rows != C.rows){
        matrix_error(FALSE_ROWS_COLS);
        return MATRIX_NULL;;
    }

    for (int pos = 0; pos < A.cols * A.rows; ++pos){
        C.data[pos] = A.data[pos] - B.data[pos];
    }

    return C;   
}


struct Matrix matrix_multiplication() // Multiplication of one matrix by another
{

}


struct Matrix matrix_product() // Сreating a matrix containing the product of the matrices
{

}


struct Matrix matrix_division() // Dividing one matrix by another
{

}


struct Matrix matrix_quotient() // Сreating a matrix containing the quotient of the matrices
{

}


struct Matrix matrix_determinant()
{

}


struct Matrix matrix_transposition()
{

}


struct Matrix matrix_exp()
{

}


void matrix_print(const struct Matrix A)
{
    for (size_t row = 0; row < A.rows; ++row){
        printf("[");
        for (size_t col = 0; col < A.cols; ++col){
            printf("%f ", A.data[A.cols * row + col]);
        }
        printf("]\n");
    }
}


void matrix_free(struct Matrix *A)
{
    free(A->data);
    *A = MATRIX_NULL;
}


int main()
{
    struct Matrix A;
    struct Matrix B;
    struct Matrix C;
    A = matrix_create(2, 2, (double[]){1., 2., 3., 4.});
    B = matrix_create(2, 2, (double[]){1.5, 1., 2., 0.33});
    C = matrix_create(2, 2, (double[]){0., 0., 0., 0.});

    matrix_substraction(A, B);

    matrix_print(A);

    matrix_free(&A);
    matrix_free(&B);
    matrix_free(&C);

    return 0;
}