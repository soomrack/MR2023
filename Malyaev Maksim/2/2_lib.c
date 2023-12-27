#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

struct Matrix {
	unsigned int rows;
	unsigned int cols;
	double* data;
};


const struct Matrix MATRIX_NULL = { .rows = 0, .cols = 0, .data = NULL };

struct Matrix matrix_allocate(const unsigned int cols, const unsigned int rows)
{
	if (cols == 0 || rows == 0) {
		struct Matrix A = { .rows = rows, .cols = cols, .data = NULL };
		return A;
	};

	if (rows >= SIZE_MAX / sizeof(double) / cols)
		return MATRIX_NULL;

	struct Matrix A = { .rows = rows, .cols = cols, .data = NULL };
	A.data = (double*)malloc(A.cols * A.rows * sizeof(double));
	if (A.data == NULL) {
		return MATRIX_NULL;
	}
	return A;
}

void matrix_set_zero(struct Matrix A)
{
	if (A.data == NULL) return;
	memset(A.data, 0, sizeof(double) * A.rows * A.cols);
}

void matrix_set_one(struct Matrix A)
{
	matrix_set_zero(A);
	for (unsigned int idx = 0; idx < A.rows * A.cols; idx += A.cols + 1)
		A.data[idx] = 1.;
}

void matrix_error()
{
	printf("Error: different number of columns or rows\n");
}

int matrix_fill(struct Matrix A, const double* values)
{
	for (unsigned int idx = 0; idx < A.cols * A.rows; ++idx)
		A.data[idx] = values[idx];
	return 0;
}


void matrix_delete(struct Matrix* A)
{
	A->rows = 0;
	A->cols = 0;
	free(A->data);
	A->data = NULL;
}


// SUM = A + B
struct Matrix matrix_sum(struct Matrix A, struct Matrix B)
{
	if (A.cols != B.cols || A.rows != B.rows) return MATRIX_NULL;

	struct Matrix sum = matrix_allocation(A.cols, A.rows);
	if (sum.data == NULL) return MATRIX_NULL;

	memcpy(sum.data, A.data, sizeof(double) * A.cols * A.rows);
	matrix_add(sum, B);

	return sum;
}


// SUB = A - B
struct Matrix matrix_sub(struct Matrix A, struct Matrix B)
{
	if (A.cols != B.cols || A.rows != B.rows) return MATRIX_NULL;

	struct Matrix sub = matrix_allocation(A.cols, A.rows);
	if (sub.data == NULL) return MATRIX_NULL;

	memcpy(sub.data, A.data, sizeof(double) * A.cols * A.rows);
	matrix_add(sub, B);

	return sub;
}


// MULT = A * B
struct Matrix matrix_multip(struct Matrix A, struct Matrix B)
{
	if (A.cols != B.rows) return MATRIX_NULL;

	struct Matrix mult = matrix_allocate(A.rows, B.cols);
	if (mult.data == NULL) return MATRIX_NULL;

	for (unsigned int rowA = 0; rowA < A.rows; ++rowA) {
		for (unsigned int colB = 0; colB < B.cols; ++colB) {
			double sum = 0;
			for (unsigned int idx = 0; idx < A.cols; ++idx) {
				sum += A.data[rowA * A.cols + idx] * B.data[idx * B.cols + colB];
			}
			mult.data[rowA * mult.cols + colB] = sum;
		}
	}
	return mult;
}


// T = A ^ T
struct Matrix matrix_trans(struct Matrix A)
{
	struct Matrix tpose = matrix_allocate(A.rows, A.cols);
	if (tpose.data == NULL) return tpose;

	for (unsigned int row = 0; row < tpose.rows; row++) {
		for (unsigned int col = 0; col < tpose.cols; col++) {
			tpose.data[col * tpose.cols + row] = A.data[row * A.cols + col];
		}
	}
	return tpose;
}



// A /= k
void matrix_div_k(struct Matrix A, const double k)
{
	for (unsigned int idx = 0; idx < A.cols * A.rows; ++idx) {
		A.data[idx] /= k;
	}
	return;
}


// A += B
int matrix_add(struct Matrix A, struct Matrix B)
{
	if (A.cols != B.cols || A.rows != B.rows) return 1;

	for (unsigned int idx = 0; idx < A.cols * A.rows; ++idx)
		A.data[idx] += B.data[idx];
	return 0;
}


// EXP = e^A
struct Matrix matrix_exp(struct Matrix A)
{
	if (A.cols != A.rows) return MATRIX_NULL;
	if (A.cols == 0) return MATRIX_NULL;

	struct Matrix exp = matrix_allocate(A.rows, A.cols);
	if (exp.data == NULL) return MATRIX_NULL;
	matrix_set_one(exp);

	struct Matrix term_prev = matrix_allocate(A.rows, A.cols);
	if (term_prev.data == 0) {
		matrix_delete(&exp);
		return MATRIX_NULL;
	};
	matrix_set_one(term_prev);

	struct Matrix term_next;

	for (int idx = 1; idx < 100; ++idx) {

		term_next = matrix_multip(A, term_prev);
		if (term_next.data == NULL) {
			matrix_delete(&term_prev);
			matrix_delete(&exp);
			return MATRIX_NULL;
		}
		matrix_div_k(term_next, idx);
		memcpy(term_prev.data, term_next.data, sizeof(double) * term_prev.rows * term_prev.cols);
		matrix_delete(&term_next);
		matrix_add(exp, term_prev);
	}
	matrix_delete(&term_prev);
	return exp;
}


void matrix_print(const struct Matrix A, const char* text)
{
	printf("%s\n", text);
	for (unsigned int col = 0; col < A.cols; ++col)
	{
		printf("[");

		for (unsigned int row = 0; row < A.rows; ++row)
		{
			printf("%4.2f ", A.data[A.cols * row + col]);
		}
		printf("]\n");
	}
	printf("\n");
}
