#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct Matrix {
    unsigned int rows;
    unsigned int cols;
    double *data;
};


const struct Matrix MATRIX_NULL = { .rows = 0, .cols = 0, .data = NULL };
struct Matrix matrix_create(const unsigned int rows, const unsigned int cols)
{
    struct Matrix A = {
        .rows = rows,
        .cols = cols,
        .data = NULL, };
    A.data = (double*)malloc(sizeof(double) * A.cols * A.rows);
    if (A.data == NULL) return MATRIX_NULL;
    return A;    
}

void matrix_set_zero(struct Matrix A)
{
	if (A.data == NULL) return;
    memset( A.data, 0, sizeof(double) * A.rows * A.cols );
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

void matrix_fill(struct Matrix A, const double values[])
{
	if (A.data == NULL) {
		matrix_error;
		return;
	}
	else memcpy(A.data, values, A.rows * A.cols * sizeof(double));
}

void matrix_sum(const struct Matrix A, const struct Matrix B, const struct Matrix C)
{
    if (A.cols != B.cols || A.rows != B.rows) {
        matrix_error;
		return;
    }
    for (unsigned int idx = 0; idx < A.cols * A.rows; ++idx)
    {
        C.data[idx] = A.data[idx] + B.data[idx];
    }
}

void matrix_delete(struct Matrix *A)
{
    A->rows = 0;
    A->cols = 0;
    free(A->data);
    A->data = NULL;
}

void matrix_sub(const struct Matrix A, const struct Matrix B, const struct Matrix C)
{
	if (A.cols != B.cols || A.rows != B.rows) {
		matrix_error;
		return;
	}
	for (unsigned int idx = 0; idx < A.cols * A.rows; ++idx)
	{
		C.data[idx] = A.data[idx] - B.data[idx];
	}
}

void matrix_multip(const struct Matrix A, const struct Matrix B, const struct Matrix C)
{
	if (A.cols != B.cols || A.rows != B.rows) {
		matrix_error;
		return;
	}
	for (unsigned int idx = 0; idx < A.cols * A.rows; ++idx)
	{
		C.data[idx] = A.data[idx] * B.data[idx];
	}
}

void matrix_trans(struct Matrix A, struct Matrix T)
{
	for (unsigned int row = 0; row < A.rows; row++) {
		for (unsigned int col = 0; col < A.cols; col++) {
			T.data[col * A.rows + row] = A.data[row * A.cols + col];
		}
	}
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


int main()
{
	double values_A[] =
	{ 1., 2., 3.,
	  4., 5., 6.,
	  7., 8., 9.
	};

	struct Matrix A = matrix_create(3, 3);
	matrix_set_one(A);
	struct Matrix B = matrix_create(3, 3);
	matrix_set_one(B);
	struct Matrix C = matrix_create(3, 3);
	struct Matrix D = matrix_create(3, 3);
	struct Matrix P = matrix_create(3, 3);
	struct Matrix T = matrix_create(3, 3);

	matrix_fill(A, values_A);
	matrix_fill(B, values_A);

	matrix_sum(A, B, C);

	matrix_sub(A, B, D);

	matrix_multip(A, B, P);

	matrix_trans(A, T);

	matrix_print(A, "Matrix A");
	matrix_print(B, "Matrix B");
	matrix_print(C, "C = A + B");
	matrix_print(D, "D = A - B");
	matrix_print(P, "P = A * B");
	matrix_print(T, "T = A^T");

	matrix_delete(&A);
	matrix_delete(&B);
	matrix_delete(&C);
	matrix_delete(&D);
	matrix_delete(&P);
	matrix_delete(&T);

	return(0);
}
