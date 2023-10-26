#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef double MatrixItem;

struct Matrix {
    size_t rows;  // строки
    size_t cols;  // столбцы
    MatrixItem *data;
};


const struct Matrix NULL_MATRIX = {.rows = 0, .cols = 0, .data = NULL };


struct Matrix matrix_allocation(const size_t rows, const size_t cols)
{
    if (cols == 0 || rows == 0) {
        struct Matrix A = { .rows = rows, .cols = cols, .data = NULL };
        return A;
    }
    if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols) return NULL_MATRIX;

    struct Matrix A = {.rows = rows, .cols = cols, .data = NULL };
    A.data = (MatrixItem*)malloc(sizeof(MatrixItem) * A.cols * A.rows);
    if (A.data == NULL) return NULL_MATRIX;
    return A;
}


void matrix_delete(struct Matrix *A)
{
    A->rows = 0;
    A->cols = 0;
    free(A->data);
    A->data = NULL;
}


void matrix_set_zero(struct Matrix A) 
{
    if (A.data == NULL) return;
    memset(A.data, 0, sizeof(MatrixItem) * A.rows * A.cols);
}


void matrix_set_one(struct Matrix A)
{
    matrix_set_zero(A);
    for (size_t idx = 0; idx < A.rows * A.cols; idx += A.cols + 1)
        A.data[idx] = 1.;

}


void matrix_print(const struct Matrix A, const char *text)
{
    printf("%s\n", text);
    for (size_t col = 0; col < A.cols; ++col) {
        printf("[ ");
        for (size_t row = 0; row < A.rows; ++row) {
            printf("%4.2f ", A.data[A.cols * row + col]);
        }
        printf("]\n");
    }
    printf("\n");
}


void value_print(MatrixItem A, const char* text)
{
    printf("%s\n", text);
    
    printf("%4.2f ", A);
}


// A += B
int matrix_add(struct Matrix A, struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return 1;

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        A.data[idx] += B.data[idx];
    return 0;
}


// SUM = A + B
struct Matrix matrix_sum(struct Matrix A, struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return NULL_MATRIX;
 
    struct Matrix sum = matrix_allocation(A.cols, A.rows);
    if (sum.data == NULL) return NULL_MATRIX;

    memcpy(sum.data, A.data, sizeof(MatrixItem) * A.cols * A.rows);
    matrix_add(sum,B);

    return sum;
    matrix_delete(&sum);
} 


// A -= B
int matrix_sub(struct Matrix A, struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return 1;

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        A.data[idx] -= B.data[idx];
    return 0;
}


// DIFF = A - B
struct Matrix matrix_diff(struct Matrix A, struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return NULL_MATRIX;

    struct Matrix diff = matrix_allocation(A.cols, A.rows);
    if (diff.data == NULL) return NULL_MATRIX;

    memcpy(diff.data, A.data, sizeof(MatrixItem) * A.cols * A.rows);
    matrix_add(diff, B);

    return diff;
    matrix_delete(&diff);
}


// MULT = A * B
struct Matrix matrix_mult(struct Matrix A, struct Matrix B)
{
    if (A.cols != B.rows) return NULL_MATRIX;
    
    struct Matrix mult = matrix_allocation(A.rows, B.cols);
    if (mult.data == NULL) return NULL_MATRIX;

    for (size_t rowA = 0; rowA < A.rows; ++rowA) {
        for (size_t colB = 0; colB < B.cols; ++colB) {
            MatrixItem sum = 0;
            for (size_t idx = 0; idx < A.cols; ++idx) {
                sum += A.data[rowA * A.cols + idx] * B.data[idx * B.cols + colB];
            }
            mult.data[rowA * mult.cols + colB] = sum;
        }
    }
    return mult;
    matrix_delete(&mult);
}


// A *= k
int matrix_multk(struct Matrix A, const size_t k)
{
    for (size_t idx = 0; idx < A.cols * A.rows; ++idx) {
        A.data[idx] *= k;
    }
    return 0;
}


// A /= k
int matrix_divk(struct Matrix A, const size_t k)
{
    for (size_t idx = 0; idx < A.cols * A.rows; ++idx) {
        A.data[idx] /= k;
    }
    return 0;
}


// TPOSE = A^T
struct Matrix matrix_transpose(struct Matrix A)
{
    struct Matrix tpose = matrix_allocation(A.rows, A.cols);
    if (tpose.data == NULL) return NULL_MATRIX;

    for (size_t row = 0; row < tpose.rows; row++) {
        for (size_t col = 0; col < tpose.cols; col++) {
            tpose.data[col * tpose.cols + row] = A.data[row * A.cols + col];
        }
    }
    return tpose;
    matrix_delete(&tpose);
}

// A = A^T
int matrix_tpose(struct Matrix A)
{ 
    struct Matrix tpose = matrix_transpose(A);
    memcpy(A.data, tpose.data, sizeof(MatrixItem) * A.cols * A.rows);

    return 0;
    matrix_delete(&tpose);
}

// det (A)
int matrix_determinant(struct Matrix A)
{
    MatrixItem det;

    if (A.cols == 1 && A.rows == 1) {
        det = A.data[0];
        return det;
    }
        
    if (A.cols == 2 && A.rows == 2) {
        det = A.data[0] * A.data[3] - A.data[1] * A.data[2];
        return det;
    }
        
    if (A.cols == 3 && A.rows == 3) {
        det =
            A.data[0] * A.data[4] * A.data[8]
            + A.data[1] * A.data[5] * A.data[6]
            + A.data[2] * A.data[7] * A.data[3]
            - A.data[2] * A.data[4] * A.data[6]
            - A.data[0] * A.data[5] * A.data[7]
            - A.data[1] * A.data[8] * A.data[3];
        return det;
    }
       
    return 1;
}

// EXP = e^A
struct Matrix matrix_exp(struct Matrix A) 
{
    struct Matrix exp = matrix_allocation(A.rows, A.cols);
    if (exp.data == NULL) return NULL_MATRIX;

    struct Matrix temp = matrix_allocation(A.rows, A.cols);
    if (temp.data == NULL) return NULL_MATRIX;

    struct Matrix A_stepen = matrix_allocation(A.rows, A.cols);
    if (A_stepen.data == NULL) return NULL_MATRIX;

    MatrixItem k = 2;
    MatrixItem fac = 1;

    matrix_set_one(exp);

    memcpy(A_stepen.data, A.data, sizeof(MatrixItem) * A.cols * A.rows); //  скопировали в А_степень матрицу А
    memcpy(temp.data, A.data, sizeof(MatrixItem) * A.cols * A.rows);// скопировали в temp матрицу А

    matrix_divk(temp, fac); // Разделили матрицу temp на факториал
    matrix_add(exp, temp); // прибавили к матрице exp матрицу temp
    
    while (k <= 98)
    {
        for (size_t idx = 1; idx < k; ++idx) fac *= idx; // нашли факториал для данной итерации в цикле идут со 2-го по 100-й компонент

        temp = matrix_mult(A_stepen, A_stepen); // присвоили temp матрицу А_степень в степени
        matrix_divk(temp, fac);// Разделили матрицу temp на факториал
        matrix_add(exp, temp);// прибавили к матрице exp матрицу temp     
    }
    return exp;
    matrix_delete(&exp);
    matrix_delete(&temp);
    matrix_delete(&A_stepen);
}


int matrix_fill(struct Matrix A, const double* values)
{
    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        A.data[idx] = values[idx];
    return 0;
}


int main()
{
    double values_A[] = {
    1., 4., 7.,
    2., 5., 8.,
    3., 6., 9.
    };

    struct Matrix A = matrix_allocation(3, 3);
    struct Matrix B = matrix_allocation(3, 3);

    matrix_set_one(A);
    matrix_set_one(B);

    matrix_fill(A, values_A);
    matrix_print(A, "Matrix A");
    
    matrix_exp(A);
    matrix_print(B, "Matrix EXP");

    matrix_delete(&A);
    matrix_delete(&B);

    return 0;
}
