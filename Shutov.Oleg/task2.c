#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

typedef double MatrixItem;

struct Matrix {
	size_t rows;
	size_t cols;
	MatrixItem* data;
};

const struct Matrix MATRIX_NULL = { .rows = 0, .cols = 0, .data = NULL };


// Function returns MATRIX_NULL if fail
struct Matrix matrix_allocate(const size_t rows, const size_t cols)
{
    if (cols == 0 || rows == 0) {
        struct Matrix A = { .rows = rows, .cols = cols, .data = NULL};
        return A;
    }
    if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols) return MATRIX_NULL;  // rows * cols < MAX_SIZE / sizeof(double)
    
    struct Matrix A = { .rows = rows, .cols = cols, .data = NULL};
    A.data = (MatrixItem*)malloc(A.cols * A.rows * sizeof(MatrixItem));
    if (A.data == NULL) {
        return MATRIX_NULL;
    }
    return A;
}


// Function returns MATRIX_NULL if fail
struct Matrix matrix_create(const size_t rows, const size_t cols, const MatrixItem* values)
{
	struct Matrix A = matrix_allocate(rows, cols);
	if (A.data == NULL) return A;

	memcpy(A.data, values, rows * cols * sizeof(MatrixItem));
	return A;
}


void matrix_delete(struct Matrix* A)
{
	A->rows = 0;
	A->cols = 0;
	free(A->data);
	A->data = NULL;
}


void matrix_set_zero(struct Matrix A)
{
	if (A.data == NULL) return;
	memset(A.data, 0, sizeof(MatrixItem) * A.cols * A.rows);
}


void matrix_set_one(struct Matrix A)
{
	matrix_set_zero(A);
	for (size_t idx = 0; idx < A.rows * A.cols; idx += A.cols + 1)
		A.data[idx] = 1.;
}


// B += A
// Function returns 0 if success
int matrix_add(const struct Matrix A, const struct Matrix B)
{
	if (A.cols != B.cols || A.rows != B.rows) return 1;

	for (size_t idx = 0; idx < A.cols * A.rows; ++idx) {
		A.data[idx] += B.data[idx];
	}
	return 0;
}


// C = A + B
struct Matrix matrix_sum(struct Matrix A, struct Matrix B) 
{
	if (A.cols != B.cols || A.rows != B.rows) return MATRIX_NULL;

	struct Matrix C = matrix_allocate(A.cols, A.rows);
	if (C.data == NULL) return MATRIX_NULL;

	memcpy(C.data, A.data, C.cols * C.rows * sizeof(MatrixItem));
	matrix_add(C, B);
	return C;
}


// B -= A
// Function returns 0 if success
int matrix_remove(const struct Matrix A, const struct Matrix B)
{
	if (A.cols != B.cols || A.rows != B.rows) return 1;

	for (size_t idx = 0; idx < A.cols * A.rows; ++idx) {
		A.data[idx] -= B.data[idx];
	}
	return 0;
}


// C = A - B
struct Matrix matrix_subtract(struct Matrix A, struct Matrix B) 
{
	if (A.cols != B.cols || A.rows != B.rows) return MATRIX_NULL;

	struct Matrix C = matrix_allocate(A.cols, A.rows);
	if (C.data == NULL) return MATRIX_NULL;

	memcpy(C.data, A.data, C.cols * C.rows * sizeof(MatrixItem));
	matrix_remove(C, B);
	return C;
}


struct Matrix matrix_multiplication(struct Matrix A, struct Matrix B) 
{
	if (A.rows != B.cols) return MATRIX_NULL;

	struct Matrix C = matrix_allocate(A.rows, B.cols);
	if (C.data == NULL) return MATRIX_NULL;

	for (size_t colC = 0; colC < A.rows; ++colC) {
		for (size_t rowC = 0; rowC < B.cols; ++rowC) {
			C.data[rowC + colC * B.cols] = 0;
			for (size_t idx = 0; idx < B.cols; ++idx) {
				C.data[rowC + colC * A.rows] += A.data[idx + colC * A.rows]
					* B.data[idx * B.cols + rowC];
			};
		};
	};
	return C;
}


// A /= k
int matrix_divk(struct Matrix A, const size_t k)
{
	for (size_t idx = 0; idx < A.cols * A.rows; ++idx) {
		A.data[idx] /= k;
	}
	return 0;
}


// Function returns new matrix C = A^T or MATRIX_NULL if fail
struct Matrix matrix_transposition(struct Matrix A)
{
	struct Matrix C = matrix_allocate(A.cols, A.rows);
	if (C.data == NULL) return MATRIX_NULL;

	for (size_t rowC = 0; rowC < A.cols; ++rowC) {
		for (size_t colC = 0; colC < A.rows; ++colC) {
			C.data[colC + rowC * A.rows] = A.data[colC * A.cols + rowC];
		};
	};
	return C;
}


// Function returns new matrix C = |A| (A[1x1]) or MATRIX_NULL if fail
struct Matrix matrix_determinant_1x1(struct Matrix A)
{
	if (A.cols != 1 && A.rows != 1) return MATRIX_NULL;

	struct Matrix C = matrix_allocate(1, 1);
	if (C.data == NULL) return MATRIX_NULL;

	C.data[0] = A.data[0];
	return C;
}


// Function returns new matrix C = |A| (A[2x2]) or MATRIX_NULL if fail
struct Matrix matrix_determinant_2x2(struct Matrix A)
{
	if (A.cols != 2 && A.rows != 2) return MATRIX_NULL;

	struct Matrix C = matrix_allocate(1, 1);
	if (C.data == NULL) return MATRIX_NULL;

	C.data[0] = A.data[0] * A.data[3] - A.data[1] * A.data[2];
	return C;
}


// Function returns new matrix C = |A| (A[3x3]) or MATRIX_NULL if fail
struct Matrix matrix_determinant_3x3(struct Matrix A)
{
	if (A.cols != 3 && A.rows != 3) return MATRIX_NULL;

	struct Matrix C = matrix_allocate(1, 1);
	if (C.data == NULL) return MATRIX_NULL;

	C.data[0] = A.data[0] * A.data[4] * A.data[8] + A.data[6] * A.data[1] * A.data[5] + 
		A.data[3] * A.data[7] * A.data[2] - A.data[2] * A.data[4] * A.data[6] -
		A.data[5] * A.data[7] * A.data[0] - A.data[3] * A.data[1] * A.data[8];
	return C;
}


void matrix_fill(struct Matrix A, const MatrixItem values[])
{
	for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
		A.data[idx] = values[idx];
}


void matrix_print(const struct Matrix A, const char *text)
{
	printf("%s\n", text);
	for (size_t col = 0; col < A.cols; ++col) {
		printf("[ ");
		for (size_t row = 0; row < A.rows; ++row) {
			printf("%4.2f ", A.data[A.cols * row + col]);
		}
		printf(" ]\n");
	}
	printf("\n");
}


int main()
{
	struct Matrix A, B, C, D, E, F, G;

	MatrixItem values_A[] = {
		1., 1., 1.,
		2., 2., 2.,
		3., 3., 3.
	};
	MatrixItem values_B[] = {
		1., 2., 3.,
		1., 2., 3.,
		1., 2., 3.
	};

	A = matrix_create(3, 3, values_A);
	B = matrix_create(3, 3, values_B);

	matrix_print(A, "A");
	matrix_print(B, "B");


	C = matrix_sum(A, B);
	matrix_print(C,"matrix SUM");


	D = matrix_subtract(A, B);
	matrix_print(D, "matrix SUB");


	E = matrix_multiplication(A, B);
	matrix_print(E, "matrix MULT");


	F = matrix_transposition(A);
	matrix_print(F, "matrix TRANS");


	G = matrix_determinant_3x3(A);
	matrix_print(G, "matrix DET");


	/*H = matrix_exp(A);
	matrix_print(H, "matrix EXP");  */

	matrix_delete(&A);
	matrix_delete(&B);
	matrix_delete(&C);
	matrix_delete(&D);
	matrix_delete(&E);
	matrix_delete(&F);
	matrix_delete(&G);
	//matrix_delete(&H);
	return 0;
}
