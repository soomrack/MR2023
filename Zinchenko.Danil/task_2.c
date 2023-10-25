#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const int n = 2;

typedef double MatrixItem;

typedef struct Matrix
{
	size_t cols;
	size_t rows;
	MatrixItem* data;
};

const struct Matrix Matrix_null = { .cols = 0,  .rows = 0, .data = NULL };

struct Matrix matrix_create(const size_t cols, const size_t rows)
{
	if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols) return Matrix_null;
	struct Matrix A = { .cols = cols, .rows = rows, .data = NULL };
	A.data = malloc(sizeof(MatrixItem) * A.cols * A.rows);
	if (A.data == NULL) return Matrix_null;
	return A;
}


void matrix_set_zero(struct Matrix A)
{
	memset(A.data, 0, sizeof(MatrixItem) * A.cols * A.rows);
}


void matrix_set_one(struct Matrix A)
{
	matrix_set_zero(A);
	for (size_t idx = 0; idx < A.cols * A.rows; idx += A.cols + 1) A.data[idx] = 1;
}


void matrix_error()
{
	printf("Error: different number of columns or rows\n");
}


void matrix_fill(struct Matrix A, const MatrixItem values[])
{
	for (size_t row = 0; row < A.rows; row++) {
		for (size_t col = 0; col < A.cols; col++) {
			A.data[col * A.rows + row] = values[row * A.cols + col];
		}
	}
}


void matrix_sum(const struct Matrix A, const struct Matrix B, const struct Matrix C)
{
	if (B.cols != C.cols || B.rows != C.rows) matrix_error();
	for (size_t idx = 0; idx < B.cols * B.rows; ++idx)
	{
		A.data[idx] = B.data[idx] + C.data[idx];
	}
}


void matrix_add(const struct Matrix A, const struct Matrix B, const struct Matrix C)
{
	if (B.cols != C.cols || B.rows != C.rows) matrix_error();
	for (size_t idx = 0; idx < B.cols * B.rows; ++idx)
	{
		A.data[idx] = B.data[idx] - C.data[idx];
	}
}


void matrix_mult(const struct Matrix A, const struct Matrix B, const struct Matrix C)
{
	if (B.cols != C.rows || B.rows != C.cols) matrix_error();
	for (size_t row = 0; row < B.rows; row++) {
		for (size_t col = 0; col < C.cols; col++) {
			A.data[row * B.cols + col] = B.data[row * B.cols + col] * C.data[col * C.rows + row];
		}
	}
}



void matrix_trans(struct Matrix A, struct Matrix T)
{
	for (size_t row = 0; row < A.rows; row++)
	{
		for (size_t col = 0; col < A.cols; col++)
		{
			T.data[col * A.rows + row] = A.data[row * A.cols + col];
		}
	}
}


void matrix_delete(struct Matrix* A)
{
	A->rows = 0;
	A->cols = 0;
	free(A->data);
	A->data = NULL;
}


struct Matrix Minor(const struct Matrix A, const size_t size, const size_t row, const size_t col)
{
	struct Matrix Minor = matrix_create(A.rows - 1, A.cols - 1);
	unsigned int shiftrow = 0;
	unsigned int shiftcol = 0;
	for (unsigned int rows = 0; rows < size - 1; rows++) {
		if (rows == row) shiftrow = 1;
		shiftcol = 0;
		for (unsigned int cols = 0; cols < size - 1; cols++) {
			if (cols == col) shiftcol = 1;
			Minor.data[rows * (size - 1) + cols] = A.data[(rows + shiftrow) * size + (cols + shiftcol)];
		}
	}
	return Minor;
}


double matrix_determinant(const struct Matrix A, const size_t size) {
	if (A.rows != A.cols) matrix_error();
	double det = 0;
	int k = 1;
	if (size == 0) return 0;
	if (size == 1) return A.data[0];
	if (size == 2) return (A.data[0] * A.data[3] - A.data[2] * A.data[1]);
	for (unsigned int idx = 0; idx < size; idx++) {
		struct Matrix temp = Minor(A, size, 0, idx);
		det += k * A.data[idx] * matrix_determinant(temp, size - 1);
		k = -k;
		matrix_delete(&temp);
	}
	return det;
}

void determinant_print(struct Matrix A, const char* text)
{
	printf("%s\n", text);
	printf("%f\n", matrix_determinant(A, A.rows));
}


struct Matrix matrix_exponent(struct Matrix A, struct Matrix AA)
{
	struct Matrix E = matrix_create(A.cols, A.cols);
	matrix_set_one(E);
	struct Matrix exp = matrix_create(A.cols, A.cols);
	struct Matrix Exp = matrix_create(A.cols, A.cols);
	matrix_sum(exp, E, A);
	struct Matrix AAA = matrix_create(A.cols, A.cols);
	struct Matrix AAD = matrix_create(A.cols, A.cols);
	if (n > 1) {
		for (unsigned int i = 2; i < n + 1; ++i) {
			matrix_mult(AAA, AA, A);
			matrix_mult(AA, AAA, A);
			unsigned int k = 1;
			int s = 1;
			for (unsigned int k = 1; k != i; ++k) {
				s *= k;
			}
			for (size_t row = 0; row < A.rows; row++) {
				for (size_t col = 0; col < A.cols; col++) {
					AAD.data[col * A.rows + row] = AAA.data[col * A.rows + row] / s;
				}
			}
			matrix_sum(Exp, exp, AAD);
		}
		return(Exp);
	}
	else {
		matrix_sum(Exp, E, A);
		return(Exp);
	}
	matrix_delete(&E);
	matrix_delete(&exp);
	matrix_delete(&E);
	matrix_delete(&AAA);
	matrix_delete(&AAD);
}


void matrix_print(const struct Matrix A, const char* text)
{
	printf("%s\n", text);
	for (size_t col = 0; col < A.cols; ++col)
	{
		printf("[");

		for (size_t row = 0; row < A.rows; ++row)
		{
			printf("%4.2f ", A.data[A.cols * row + col]);
		}
		printf("]\n");
	}
	printf("\n");
}


int main()
{
	MatrixItem values_A[] =
	{ 1., 8., 3.,
	  4., 5., 6.,
	  7., 8., 9.
	};

	MatrixItem values_B[] =
	{ 1., 1., 1.,
	  2., 2., 2.,
	  3., 3., 3.
	};

	struct Matrix A = matrix_create(3, 3);
	matrix_set_one(A);

	struct Matrix AA = matrix_create(3, 3);
	matrix_set_one(AA);

	struct Matrix B = matrix_create(3, 3);
	matrix_set_one(B);

	struct Matrix E = matrix_create(3, 3);
	matrix_set_one(E);

	struct Matrix C = matrix_create(3, 3);
	struct Matrix D = matrix_create(3, 3);
	struct Matrix P = matrix_create(3, 3);
	struct Matrix T = matrix_create(3, 3);

	matrix_fill(A, values_A);
	matrix_fill(AA, values_A);
	matrix_fill(B, values_B);

	matrix_sum(C, A, B);

	matrix_add(D, A, B);

	matrix_mult(P, A, B);

	matrix_trans(A, T);

	matrix_determinant(A, A.rows);

	struct Matrix Exp = matrix_exponent(A, AA);

	matrix_print(A, "Matrix A");
	matrix_print(B, "Matrix B");
	matrix_print(C, "C = A + B");
	matrix_print(D, "D = A - B");
	matrix_print(P, "P = A * B");
	matrix_print(T, "T = A^T");
	matrix_print(E, "Matrix E");
	determinant_print(A, "detA = ");
	matrix_print(Exp, "Matrix Exp^A=");

	matrix_delete(&A);
	matrix_delete(&B);
	matrix_delete(&C);
	matrix_delete(&D);
	matrix_delete(&P);
	matrix_delete(&T);
	matrix_delete(&E);

	return 0;
}
