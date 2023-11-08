#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include <math.h>

typedef double MatrixData;


struct Matrix {
	size_t cols;
	size_t rows;
	MatrixData* data;
};


const struct Matrix Matrix_NULL = { .cols = 0, .rows = 0,.data = NULL };


struct Matrix matrix_allocation(const size_t cols, const size_t rows)
{
	if (rows == 0 || cols == 0) {
		struct Matrix A = { .cols = cols, .rows = rows, .data = NULL };
		return A;
	}
	if (rows >= SIZE_MAX / sizeof(MatrixData) / cols) return Matrix_NULL;

	struct Matrix A = { .cols = cols, .rows = rows, .data = NULL };
	A.data = (MatrixData*)malloc(A.cols * A.rows * sizeof(MatrixData));
	if (A.data == NULL) return Matrix_NULL;
	return A;
}


struct Matrix matrix_filling(const size_t cols, const size_t rows, const MatrixData* data)
{
	struct Matrix A = matrix_allocation(cols, rows);
	if (A.data == NULL) return A;

	memcpy(A.data, data, cols * rows * sizeof(MatrixData));
	return A;
}


void matrix_free(struct Matrix *A)
{
	if(A->data != NULL) free(A->data);
	*A = Matrix_NULL;
}


int matrix_sum1(const struct Matrix A, const struct Matrix B)
{
	if (A.rows != B.rows || A.cols != B.cols) return 1;

	for (size_t idx = 0; idx < A.cols * A.rows; idx++) {
		A.data[idx] += B.data[idx];
	}
	return 0;
}


struct Matrix matrix_sum2(const struct Matrix A, const struct Matrix B)
{
	if (A.rows != B.rows || A.cols != B.cols) return Matrix_NULL;

	struct Matrix C = matrix_allocation(A.rows, A.cols);
	if (C.data == NULL) return Matrix_NULL;

	memcpy(C.data, A.data, C.cols * C.rows * sizeof(MatrixData));
	matrix_sum1(C, B);
	return C;
}


int matrix_subtraction1(const struct Matrix A, const struct Matrix B)
{
	if (A.rows != B.rows || A.cols != B.cols) return 1;

	for (size_t idx = 0; idx < A.cols * A.rows; idx++) {
		A.data[idx] -= B.data[idx];
	}
	return 0;
}


struct Matrix matrix_subtraction2(const struct Matrix A, const struct Matrix B)
{
	if (A.rows != B.rows || A.cols != B.cols) return Matrix_NULL;

	struct Matrix C = matrix_allocation(A.rows, A.cols);
	if (C.data == NULL) return Matrix_NULL;
	
	memcpy(C.data, A.data, C.cols * C.rows * sizeof(MatrixData));
	matrix_subtraction1(C, B);
	return C;
}


struct Matrix matrix_mult_scalar(const struct Matrix A, const double scalar)
{
	struct Matrix C = matrix_allocation(A.rows, A.cols);

	for (size_t idx = 0; idx < A.cols * A.rows; idx++) {
		C.data[idx] = scalar *A.data[idx];
	}
	return C;
}


struct Matrix matrix_mult(const struct Matrix A, const struct Matrix B)
{
	if (A.rows != B.rows ) return Matrix_NULL;

	struct Matrix C = matrix_allocation(A.rows, B.cols);
	if (C.data == NULL) return C;

	for (size_t rowA = 0; rowA < A.rows; rowA++) 
		for (size_t colB = 0; colB < B.cols; colB++) 
			for (size_t idx = 0; idx < A.cols; idx++) 
				C.data[rowA * B.cols + colB] += A.data[rowA * A.cols + idx] * B.data[idx * B.cols + colB];
	return C;
}


struct Matrix transposition(const struct Matrix A)
{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
	struct Matrix C = matrix_allocation(A.cols, A.rows);

	for (size_t rows = 0; rows < A.rows; rows++)
		for (size_t cols = 0; cols < A.cols; cols++)
			C.data[rows * A.rows + cols] = A.data[cols * A.cols + rows];
	return C;
}


double det(const struct Matrix A)
{
	if ((A.rows != A.rows) || (A.cols > 3) || (A.rows > 3)) return 1;

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


struct Matrix matrix_exponential_part1(struct Matrix A, unsigned int level)
{
	struct Matrix C;
	unsigned int n = 1;

	for (unsigned int counter = 1; counter <= level; counter++) n *= counter;

	for (unsigned int counter = 1; counter <= level; counter++) {
		if (counter == 1) C = matrix_mult(A, A);
		else matrix_mult(C, A);
	}
	return matrix_mult_scalar(C, 1 / (double)n);
}


struct Matrix matrix_exponential_part2(struct Matrix A, unsigned long int level)
{
	struct Matrix C, C2;

	if (A.rows != A.rows) return Matrix_NULL;

	for (unsigned int count = 0; count <= level; count++) {
		if (count == 0) {
			C2 = matrix_allocation(A.rows, A.cols);
			continue;
		}

		C = matrix_exponential_part1(A, count);
		matrix_sum1(C2, C);
		matrix_free(&C);
	}
	return C2;
}


void matrix_print(const struct Matrix A)
{
	for (size_t row = 0; row < A.rows; ++row) {
		printf("[ ");
		for (size_t col = 0; col < A.cols; ++col) {
			printf("%4.2f ", A.data[A.cols * row + col]);
		}
		printf("]\n");
	}
	printf("\n");
}


int main()
{
	struct Matrix A, B, C, C2;


	printf("\nFirst matrix\n");
	A = matrix_filling(2, 2, (double[]) { 1., 1., 1., 1. });
	matrix_filling(A.cols, A.rows, &A);
	matrix_print(A);

	printf("Second matrix\n");
	B = matrix_filling(2, 2, (double[]) { 1., 0., 0., 1. });
	matrix_filling(B.cols, B.rows, &B);
	matrix_print(B);

	printf("Sum1 of matrices\n");
	matrix_sum1(A, B);
	matrix_print(A);

	printf("Sum2 of matrices\n");
	matrix_sum2(A, B);
	C = matrix_sum2(A, B);
	matrix_print(C);

	printf("Sub1 of matrices\n");
	matrix_subtraction1(A, B);
	matrix_print(A);

	printf("Sub2 of matrices\n");
	C = matrix_subtraction2(A, B);
	matrix_print(C);

	printf("Multiplying the first matrix by a scalar\n");
	C = matrix_mult_scalar(A, 2);
	matrix_print(C);

	printf("Multiplying the first matrix by a second matrix\n");
	C = matrix_mult(A, B);
	matrix_print(C);

	printf("Transposed first matrix\n");
	C = transposition(A);
	matrix_print(C);

	printf("Determinant of the first matrix\n");
	det(A);
	printf("%4.2f \n", det(A));
	
	printf("Exponent of the first matrix\n");
	matrix_exponential_part1(A, 2);
	C2 = matrix_exponential_part2(A, 2);
	matrix_print(C2);
	return 0;
}
