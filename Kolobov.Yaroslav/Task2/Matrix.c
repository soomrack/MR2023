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

    if (rows >= SIZE_MAX / sizeof(MatrixData) / cols) {
        matrix_error(MEM_ALLOC_ERROR);
        return MATRIX_NULL; 
    }

    struct Matrix A = {.cols = cols, .rows = rows, .data = NULL};
    A.data = malloc(A.cols * A.rows * sizeof(MatrixData));
    
    if (A.data == NULL) {
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


struct Matrix matrix_add(struct Matrix A, struct Matrix B) // Adding second matrix to first matrix
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


struct Matrix matrix_substraction(struct Matrix A, struct Matrix B) // Substracting second matrix from first matrix
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
        return MATRIX_NULL;
    }

    for (int pos = 0; pos < A.cols * A.rows; ++pos){
        C.data[pos] = A.data[pos] - B.data[pos];
    }

    return C;   
}


struct Matrix matrix_scalar_multiplication(const struct Matrix A, const double scalar)
{
	for (size_t idx = 0; idx < A.cols * A.rows; idx++) {
		A.data[idx] *= scalar;
	}
	return A;    
}

struct Matrix matrix_multiplication(const struct Matrix A, const struct Matrix B, const struct Matrix C) // Multiplication of one matrix by another
{
    if (A.rows != B.cols){
        matrix_error(FALSE_ROWS_COLS);
        return MATRIX_NULL;
    }

    if (C.cols != B.cols || C.rows != B.rows){
        matrix_error(FALSE_ROWS_COLS);
        return MATRIX_NULL;
    }
	
    for (int row = 0; row < C.rows; row++){
        for (int col = 0; col < C.cols; col++){
            for (int idx = 0; idx < A.cols; idx++){
                C.data[row * C.cols + col] += A.data[row * A.cols + idx] * B.data[idx * B.cols + col];
                };
        }
    }
    return C;
}

struct Matrix matrix_division() // Dividing one matrix by another
{

}


double matrix_determinant(const struct Matrix A)
{
	if ((A.rows != A.rows) || (A.cols > 3) || (A.rows > 3)){
        matrix_error(FALSE_MATRIX);
        return 1;
    }

	if (A.cols == 2) return (A.data[0] * A.data[3] - A.data[1] * A.data[2]);

	if (A.cols == 3) {
		return (A.data[0] * A.data[4] * A.data[8]) + \
			(A.data[1] * A.data[5] * A.data[6]) + \
			(A.data[2] * A.data[3] * A.data[7]) - \
			(A.data[2] * A.data[4] * A.data[6]) - \
			(A.data[0] * A.data[5] * A.data[7]) - \
			(A.data[1] * A.data[3] * A.data[8]);
	}
}


struct Matrix matrix_transposition(const struct Matrix A, const struct Matrix C)
{
	for (size_t rows = 0; rows < A.rows; rows++)
		for (size_t cols = 0; cols < A.cols; cols++)
			C.data[rows * A.rows + cols] = A.data[cols * A.cols + rows];
	return C;
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
    A = matrix_fill(2, 2, (double[]){1., 2., 3., 4.});
    B = matrix_fill(2, 2, (double[]){2., 1., 2., 3.});
    C = matrix_fill(2, 2, (double[]){0., 0., 0., 0.});
    // C = matrix_create(2, 2);

    matrix_multiplication(A, B, C);
    // double det = matrix_determinant(A);

    // matrix_print(A);
    // printf("Matrix determinant = %f\n", det);
    
    // matrix_transposition(A, C);

    // matrix_print(A);    
    // matrix_print(B);
    matrix_print(C);

    matrix_free(&A);
    matrix_free(&B);
    matrix_free(&C);

    return 0;
}