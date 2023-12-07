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


const struct Matrix NULL_MATRIX = { .rows = 0, .cols = 0, .data = NULL };


struct Matrix matrix_create(const size_t rows, const size_t cols)
{
    if (cols == 0 || rows == 0) {
        struct Matrix A = { .rows = rows, .cols = cols, .data = NULL };
        return A;
    }
    if (cols >= SIZE_MAX / sizeof(MatrixItem) / rows) return NULL_MATRIX;

    struct Matrix A = { .rows = rows, .cols = cols, .data = NULL };
    A.data = (MatrixItem*)malloc(sizeof(MatrixItem) * A.cols * A.rows);
    if (A.data == NULL) return NULL_MATRIX;
    return A;
}


void matrix_delete(struct Matrix* A)
{
    A->rows = 0;
    A->cols = 0;
    if (A->data != 0) free(A->data);
    A->data = NULL;
}


void matrix_set_zero(struct Matrix A)
{
    if (A.data != NULL) return NULL_MATRIX;
        memset(A.data, 0, sizeof(MatrixItem) * A.rows * A.cols);
}


void matrix_set_one(const struct Matrix A)
{
    matrix_set_zero(A);
    for (size_t id = 0; id < A.rows * A.cols; id += A.cols + 1)
        A.data[id] = 1.;
}


void matrix_print(const struct Matrix A, const char* text)
{
    printf("%s\n", text);
    for (size_t row = 0; row < A.rows; ++row) {
        printf("[ ");
        for (size_t col = 0; col < A.cols; ++col) {
            printf(" %4.2f ", A.data[A.cols * row + col]);
        }
        printf(" ]\n");
    }
    printf("\n");
}


// A += B
int matrix_add(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return 1;

    for (size_t id = 0; id < A.cols * A.rows; ++id)
        A.data[id] += B.data[id];
    return 0;
}


// С = A + B
struct Matrix matrix_sum(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return NULL_MATRIX;

    struct Matrix sum = matrix_create(A.cols, A.rows);
    if (sum.data == NULL) return NULL_MATRIX;

    memcpy(sum.data, A.data, sizeof(MatrixItem) * A.cols * A.rows);
    matrix_add(sum, B);

    return sum;
}


// A -= B
int matrix_sub(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return 1;

    for (size_t id = 0; id < A.cols * A.rows; ++id)
        A.data[id] -= B.data[id];

    return 0;
}


// С = A - B
struct Matrix matrix_diff(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return NULL_MATRIX;

    struct Matrix diff = matrix_create(A.cols, A.rows);
    if (diff.data == NULL) return NULL_MATRIX;

    memcpy(diff.data, A.data, sizeof(MatrixItem) * A.cols * A.rows);
    matrix_sub(diff, B);

    return diff;
}


//C = A * B
struct Matrix matrix_mult(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.rows) return NULL_MATRIX;

    struct Matrix mult = matrix_create(A.rows, B.cols);
    if (mult.data == NULL) return mult;

    for (size_t rowA = 0; rowA < A.rows; ++rowA) {
        for (size_t colB = 0; colB < B.cols; ++colB) {
            MatrixItem sum = 0;
            for (size_t id = 0; id < A.cols; ++id) {
                sum += A.data[rowA * A.cols + id] * B.data[id * B.cols + colB];
            }
            mult.data[rowA * mult.cols + colB] = sum;
        }
    }

    return mult;
}


// A *= k
struct Matrix matrix_multk(const struct Matrix A, const MatrixItem k)
{
    struct Matrix multk = matrix_create(A.rows, A.cols);
    if (multk.data == NULL) return NULL_MATRIX;

    memcpy(multk.data, A.data, sizeof(MatrixItem) * A.cols * A.rows);

    for (size_t id = 0; id < A.cols * A.rows; ++id) {
        multk.data[id] *= k;
    }
    return multk;
}


// A /= k
struct Matrix matrix_divk(const struct Matrix A, const MatrixItem k)
{
    struct Matrix divk = matrix_create(A.rows, A.cols);
    if (divk.data == NULL) return NULL_MATRIX;
    if (k == 0) return NULL_MATRIX;

    memcpy(divk.data, A.data, sizeof(MatrixItem) * A.cols * A.rows);

    for (size_t id = 0; id < A.cols * A.rows; ++id) {
        divk.data[id] /= k;
    }
    return divk;
}


// TRANS = A^T
struct Matrix matrix_transpose(const struct Matrix A)
{
    struct Matrix transpose = matrix_create(A.cols, A.rows);
    if (transpose.data == NULL) return NULL_MATRIX;
    for (size_t row = 0; row < A.rows; ++row) {
        for (size_t col = 0; col < A.cols; ++col) {
            transpose.data[col * transpose.cols + row] = A.data[row * A.cols + col];
        }
    }
    return transpose;
}


// det (A)
MatrixItem matrix_determinant(const struct Matrix A)
{
    if (A.cols == 1 && A.rows == 1) {
        return A.data[0];
    }

    if (A.cols == 2 && A.rows == 2) {
        return A.data[0] * A.data[3] - A.data[1] * A.data[2];
    }

    if (A.cols == 3 && A.rows == 3) {
        return A.data[0] * A.data[4] * A.data[8]
            + A.data[1] * A.data[5] * A.data[6]
            + A.data[2] * A.data[7] * A.data[3]
            - A.data[2] * A.data[4] * A.data[6]
            - A.data[0] * A.data[5] * A.data[7]
            - A.data[1] * A.data[8] * A.data[3];
    }

    return NAN;
}


// EXP = e^A
struct Matrix matrix_exp(const struct Matrix A, const int k)
{
    if (A.cols != A.rows) return NULL_MATRIX;
    if (A.cols == 0) return NULL_MATRIX;

    struct Matrix exp = matrix_create(A.rows, A.cols);
    if (exp.data == NULL) return NULL_MATRIX;
    matrix_set_one(exp);

    struct Matrix temp = matrix_create(A.rows, A.cols);
    if (temp.data == 0) {
        matrix_destruction(&exp);
        return NULL_MATRIX;
    };

    memcpy(temp.data, A.data, sizeof(MatrixItem) * A.cols * A.rows);

    struct Matrix temp_more = matrix_create(A.rows, A.cols);
    if (temp_more.data == 0) {
        matrix_destruction(&exp);
        matrix_destruction(&temp);
        return NULL_MATRIX;
    };

    matrix_set_one(temp_more);
    int k0 = 1;

    for (int id = 1; id <= k; ++id) {
        matrix_divk_for_exp(temp, k0 * id);
        temp_more = matrix_mult(temp, A);
        matrix_add(exp, temp_more);
        matrix_destruction(&temp_more);
    }
    matrix_destruction(&temp_more);
    matrix_destruction(&temp);
    return exp;
}


int main()
{
    struct Matrix  A, B, C, D, E, F, G, H, J;
    MatrixItem values_A[] = {
    1., 2., 3.,
    4., 5., 6.,
    7., 8., 9.
    };

    MatrixItem values_B[] = {
    8., 5., 3.,
    1., 5., 1.,
    3., 6., 2.
    };

    MatrixItem I;

    A = matrix_create(3, 3, &values_A);
    B = matrix_create(3, 3, &values_B);
    C = matrix_create(3, 3);
    D = matrix_create(3, 3);
    E = matrix_create(3, 3);
    F = matrix_create(3, 3);
    G = matrix_create(3, 3);
    H = matrix_create(3, 3);
    J = matrix_create(3, 3);
     
    matrix_print(A, "Матрица A");
    matrix_print(B, "Матрица B");

    C = matrix_sum(A, B);
    matrix_print(C, "Сумма A и B");

    D = matrix_diff(A, B);
    matrix_print(D, "Разница A и B");

    E = matrix_mult(A, B);
    matrix_print(E, "Произведение A и B");

    F = matrix_multk(A, 2);
    matrix_print(F, "Матрица A, умноженная на 2");

    G = matrix_divk(A, 2);
    matrix_print(G, "Матрица A, деленная на 2");

    H = matrix_transpose(A);
    matrix_print(H, "Транспонированная матрица A");

    I = matrix_determinant(A);
    printf("Определитель матрицы A: %.2lf\n", I);

    J = matrix_exp(A, 2);
    matrix_print(J, "Экспонента матрицы A");

    matrix_delete(&A);
    matrix_delete(&B);
    matrix_delete(&C);
    matrix_delete(&D);
    matrix_delete(&E);
    matrix_delete(&F);
    matrix_delete(&G);
    matrix_delete(&H);
    matrix_delete(&J);

    return 0;
}
