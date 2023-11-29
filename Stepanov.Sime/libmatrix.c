#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

struct Matrix {
	size_t rows;
	size_t cols;
	double* data;
};

const struct Matrix NULL_MATRIX = { .rows = 0, .cols = 0, .data = NULL };


struct Matrix matrix_create(const unsigned int rows, const unsigned int cols)
{
	struct Matrix A = {
	   .rows = rows,
	   .cols = cols,
	   .data = NULL
	};
	if (rows >= SIZE_MAX / sizeof(double) / cols) return NULL_MATRIX;

	A.data = malloc(sizeof(double) * A.cols * A.rows);
	if (A.data == NULL) return NULL_MATRIX;
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
	memset(A.data, 0, sizeof(double) * A.rows * A.cols);
}


//fills a matrix from 1 to the number of elements in the matrix
void matrix_set_onetonum(struct Matrix A)
{
	matrix_set_zero(A);
	for (size_t idx = 0; idx < A.rows * A.cols; idx += 1)
		A.data[idx] = idx + 1;
}

//fills a matrix from the number of elements in the matrix to 1
void matrix_set_numtoone(struct Matrix A)
{
	matrix_set_zero(A);
	for (size_t idx = 0; idx < A.rows * A.cols; idx += 1)
		A.data[idx] = A.rows * A.cols - idx;
}


void matrix_set_one(struct Matrix A)
{
	matrix_set_zero(A);
	for (size_t idx = 0; idx < A.rows * A.cols; idx += A.cols + 1)
		A.data[idx] = 1.;
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


//C=A+B
struct Matrix marix_sum(struct Matrix A, struct Matrix B)
{
	if (A.cols != B.cols || A.rows != B.rows) return NULL_MATRIX;
	struct Matrix C = matrix_create(A.rows, A.cols);
	if (C.data == NULL) return NULL_MATRIX;

	for (size_t idx = 0; idx < C.rows * C.cols; idx += 1) {
		C.data[idx] = A.data[idx] + B.data[idx];
	}
	return C;
}


//C=A-B
struct Matrix matrix_sub(struct Matrix A, struct Matrix B)
{
	if (A.cols != B.cols || A.rows != B.rows) return NULL_MATRIX;
	struct Matrix C = matrix_create(A.rows, A.cols);
	if (C.data == NULL) return NULL_MATRIX;

	for (size_t idx = 0; idx < C.rows * C.cols; idx += 1) {
		C.data[idx] = A.data[idx] - B.data[idx];
	}
	return C;
}


// A += B
// Function returns 0 if success
int matrix_add(struct Matrix A, struct Matrix B) {
	if (A.cols != B.cols || A.rows != B.rows) return 1;

	for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
		A.data[idx] += B.data[idx];
	return 0;
}


//C=A*B
struct Matrix matrix_mult(struct Matrix A, struct Matrix B)
{
	if (A.cols != B.rows) return NULL_MATRIX;

	struct Matrix C = matrix_create(A.rows, B.cols);
	if (C.data == NULL) return NULL_MATRIX;

	for (size_t colB = 0; colB < B.cols; ++colB) {
		for (size_t rowA = 0; rowA < A.rows; ++rowA) {
			C.data[rowA * C.cols + colB] = 0;
			for (size_t idx = 0; idx < A.cols; ++idx) {
				C.data[rowA * C.cols + colB] += A.data[rowA * A.cols + idx] * B.data[idx * B.cols + colB];
			}
		}
	};
	return C;
}


struct Matrix matrix_division(struct Matrix A, const double k)
{
	struct Matrix C = matrix_create(A.rows, A.cols);
	if (C.data == NULL) return NULL_MATRIX;

	for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
		C.data[idx] = A.data[idx] / k;
	return C;
}


struct Matrix matrix_trans(struct Matrix A)
{
	struct Matrix C = matrix_create(A.cols, A.rows);
	if (C.data == NULL) return NULL_MATRIX;

	for (size_t row = 0; row < A.rows; ++row) {
		for (size_t col = 0; col < A.cols; ++col) {
			C.data[col * A.cols + row] = A.data[row * A.cols + col];
		}
	}
	return C;
}


double matrix_det1x1(struct Matrix A)
{
	if (A.rows != 1 || A.cols != 1) return NAN;
	double det = A.data[0];
	return det;
}


// det(A), A[2][2]
// Function return det(A) or NAN if fail
double matrix_det2x2(struct Matrix A)
{
	if (A.rows != 2 || A.cols != 2) return NAN;

	double det = A.data[0] * A.data[3] - A.data[1] * A.data[2];
	return det;
}


// det(A), A[3][3]
// Function return det(A) or NAN if fail
double matrix_det3x3(struct Matrix A)
{
	if (A.rows != 3 || A.cols != 3) return NAN;

	double det =
		+A.data[0] * A.data[4] * A.data[8]
		+ A.data[1] * A.data[5] * A.data[6]
		+ A.data[3] * A.data[7] * A.data[2]
		- A.data[2] * A.data[4] * A.data[6]
		- A.data[1] * A.data[3] * A.data[8]
		- A.data[5] * A.data[7] * A.data[0];
	return det;
}


double matrix_det(struct Matrix A)
{
	if (A.rows != A.cols) return NAN;

	if (A.rows == 1) {
		return matrix_det1x1(A);
	};
	if (A.rows == 2) {
		return matrix_det2x2(A);
	};
	if (A.rows == 3) {
		return matrix_det3x3(A);
	}
	return NAN;
}


// exp = exp(A)
// Function return exp = exp(A) or MATRIX_NULL if fail
struct Matrix matrix_exp(struct Matrix A)
{
	if (A.cols != A.rows) return NULL_MATRIX;
	if (A.cols == 0) return NULL_MATRIX;

	struct Matrix exp = matrix_create(A.rows, A.cols);
	if (exp.data == NULL) return NULL_MATRIX;
	matrix_set_one(exp);

	struct Matrix term = matrix_create(A.rows, A.cols);  // член a_n
	if (term.data == 0) {
		matrix_delete(&exp);
		return NULL_MATRIX;
	};
	matrix_set_one(term);

	struct Matrix term_next;  // член a_n+1 
	for (int idx = 1; idx < 100; ++idx) {

		term_next = matrix_mult(term, A);
		matrix_delete(&term);
		term = matrix_division(term_next, idx);
		matrix_delete(&term_next);
		matrix_add(exp, term);

	}
	matrix_delete(&term);
	return exp;
}
