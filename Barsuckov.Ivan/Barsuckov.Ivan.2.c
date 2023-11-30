#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdint.h>
#include <math.h>

struct Matrix {
    size_t cols;
    size_t rows;
    double* data;
};

const struct Matrix MATRIX_NULL = { .cols = 0, .rows = 0, .data = NULL };


struct Matrix matrix_init(const size_t rows, const size_t cols)
{
   /* if ((rows * cols) < (SIZE_MAX / sizeof(double))) {
        return MATRIX_NULL;
    }*/

    struct Matrix A = { .cols = cols, .rows = rows, .data = NULL };
    A.data = (double*)malloc(A.cols * A.rows * sizeof(double));
    if (A.data == NULL) {
        return MATRIX_NULL;
    }
    return A;
}


struct Matrix matrix_create(const size_t rows, const size_t cols, const double* values)
{
    struct Matrix A = matrix_init(rows, cols);
    if (A.data == NULL) return A;

    memcpy(A.data, values, rows * cols * sizeof(double));
    return A;
}


void matrix_free(struct Matrix* A)
{
    A->cols = 0;
    A->rows = 0;
    free(A->data);
    A->data = NULL;
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


/*
// A += B
int matrix_add(struct Matrix* A, struct Matrix* B)
{
    if (A->cols != B->cols || A->rows != B->rows) return 1;

    for (size_t idx = 0; idx < A->cols * A->rows; ++idx) {
        A->data[idx] += B->data[idx];
    }
    return 0;
}*/

typedef double MatrixItem;

void matrix_zero(struct Matrix A)
{
    memset(A.data, 0, A.cols * A.rows * sizeof(MatrixItem));
    return;
}

struct Matrix matrix_sum(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return MATRIX_NULL;

    struct Matrix C = matrix_init(A.cols, A.rows);
    for (size_t idx = 0; idx < C.cols * C.rows; ++idx) {
        C.data[idx] = A.data[idx] + B.data[idx];
    }
    return C;
}


struct Matrix matrix_scalar_mult(const struct Matrix A)
{
    double scalar = 5.;
    struct Matrix S = matrix_init(A.cols, A.rows);
    for (size_t idx = 0; idx < S.cols * S.rows; ++idx) {
        S.data[idx] = scalar * A.data[idx];
    }
    return S;
}


 struct Matrix matrix_mult(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.rows) {
        return MATRIX_NULL;
    }

    struct Matrix M = matrix_init(A.rows, B.cols);
    if (M.data == NULL)
        return M;

    matrix_zero(M);
        
        for (size_t rowA = 0; rowA < A.rows; ++rowA) {
            for (size_t colB = 0; colB < B.cols; ++colB) {
                for (size_t colAk = 0; colAk < A.cols; ++colAk) {
                    M.data[A.cols * rowA + colB] +=
                        A.data[colAk + (rowA * A.cols)] * B.data[B.cols * colAk + colB];
                }
            }
        }

    return M;
}


 struct Matrix matrix_tr(const struct Matrix A, const struct Matrix B)
 {
     struct Matrix T = matrix_init(A.rows, B.cols);

     for (size_t row = 0; row < A.rows; ++row)
         for (size_t col = 0; col < A.cols; ++col)
             T.data[row * A.cols + col] = A.data[row + col * A.cols];

     return T;
 }


 /*struct Matrix matrix_exp(const struct Matrix A, const double accuracy)  // accuracy - десятичная дробь)
 {
     
    if (A.cols != A.rows)
        return MATRIX_NULL;

    struct Matrix E = matrix_init(A.rows, B.cols);
    if (E.data == NULL)
        return E;
    matrix_zero(E);

    struct Matrix B = matrix_init(A.cols, A.rows);
    matrix_copy(B, A);

    int degree;
    degree = (int)(ceil(1.0 / accuracy));

    for (int trm = 2; trm <= degree; ++trm) {
       matrix_add_mult(B, A);
       matrix_mult_by_coeff(B, 1.0 / trm);
       matrix_add(E, B);
    };

    matrix_add(E, A);

    for (size_t diag = 0; diag < E.rows; ++diag)
        E.data[diag * E.cols + diag] += 1;

    matrix_free(&B);

    return E;
}
*/

 
 // проверяет наличие в матрице нулевых строк/столбцов (иначе возвращается 0)
 int matrix_det_if_zero(const struct Matrix A)
 {
     size_t count;

     for (size_t row = 0; row < A.rows; ++row) {  // суммы по строкам
         count = 0;
         for (size_t col = 0; col < A.cols; ++col) {
             count += 1;
             if (A.data[row * A.cols + col] != 0.0)
                 break;
         };

         if (count == A.cols)
             return 0;
     };

     for (size_t col = 0; col < A.cols; ++col) {  // суммы по строкам
         count = 0;
         for (size_t row = 0; row < A.rows; ++row) {
             count += 1;
             if (A.data[row * A.cols + col] != 0.0)
                 break;
         };

         if (count == A.rows)
             return 0;
     };

     return 1;
 }


 // меняет строки местами
 void matrix_det_prep(const struct Matrix A, size_t diag, double* coeff)
 {
     size_t row_number_buffer = diag;  // запоминается номер строки

     if (A.data[diag * A.cols + diag] == 0.0) {
         for (size_t row = diag; row < A.rows; ++row) {
             row_number_buffer += 1;
             if (A.data[row * A.cols] != 0.0)
                 break;
         };

         double cell_value_buffer = 0;  // запоминается значение в ячейке

         for (size_t col = diag; col < A.cols; ++col) {
             cell_value_buffer = A.data[diag * A.cols + col];
             A.data[diag * A.cols + col] = A.data[row_number_buffer * A.cols + col];
             A.data[row_number_buffer * A.cols + col] = cell_value_buffer;
         };

         *coeff *= -1;
     };

     return;
 }


    //преобразование к диагональному виду, вычисление определителя (перемножение элементов гл. диаг. и умножение на коэффициент преобразования) 
 double matrix_det(const struct Matrix A)
 {
     if (A.cols != A.rows)
         return NAN;

     struct Matrix D = matrix_init(A.cols, A.rows);
     if (D.data == NULL)
         return NAN;
     matrix_copy(D, A);

     if (A.cols == 1) {
         matrix_free(&D);
         return A.data[0];
     };

     if (matrix_det_if_zero(D) == 0) {
         matrix_free(&D);
         return 0.0;
     };

     double coeff = 1.0;
     double diagonal = 1.0;
     double row_number_buffer, cell_value_buffer;

     for (size_t diag = 0; diag < A.rows - 1; ++diag) {
         matrix_det_prep(D, diag, &coeff);
         coeff *= D.data[diag * A.cols + diag];
         row_number_buffer = D.data[diag * A.cols + diag];

         for (size_t col = diag; col < A.cols; ++col)
             D.data[diag * A.cols + col] /= row_number_buffer;

         for (size_t row = diag + 1; row < A.rows; ++row) {
             cell_value_buffer = D.data[row * A.cols + diag];
             for (size_t col = diag; col < A.cols; ++col) {
                 D.data[row * A.cols + col] = D.data[row * A.cols + col] - D.data[diag * A.cols + col] * cell_value_buffer;
             };
         };
     };

     for (size_t diag = 0; diag < A.rows; ++diag)
         diagonal *= D.data[diag * A.cols + diag];

     matrix_free(&D);

     double result = coeff * diagonal;

     return result;
} 


int main()
{
    struct Matrix A, B, C, S, M, T;  // +E (exp matrix) and +DET (not matrix)

    A = matrix_create(2, 2, (double[]) { 1., 2., 3., 4. });
    B = matrix_create(2, 2, (double[]) { 1., 0., 0., 1. });

    matrix_print(A);
    matrix_print(B);
  
    // matrix_add(&B, &A);

    C = matrix_sum(A, B);
    matrix_print(C);

    S = matrix_scalar_mult(A);
    matrix_print(S);

    M = matrix_mult(A, B);
    matrix_print(M);

    T = matrix_tr(A, B);
    matrix_print(T);

    double det;  // 
    det = matrix_det(A);
    printf("det A = %lf \n", det);
    //e = matrix_det(E);
    //printf("det E = %lf \n", e);

    matrix_free(&T);
    matrix_free(&M);
    matrix_free(&S);
    matrix_free(&C);
    matrix_free(&A);
    matrix_free(&B);
    return 0;
}
