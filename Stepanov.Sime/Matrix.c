#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Matrix {
   unsigned int rows;
   unsigned int cols;
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
   A.data = malloc(sizeof(double) * A.cols * A.rows);
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
   memset(A.data, 0, sizeof(double) * A.rows * A.cols);
}


//fills a matrix from 1 to the number of elements in the matrix
void matrix_set_onetonum(struct Matrix A)
{
   matrix_set_zero(A);
   for (unsigned int idx = 0; idx < A.rows * A.cols; idx += 1)
      A.data[idx] = idx + 1;
}

//fills a matrix from the number of elements in the matrix to 1
void matrix_set_numtoone(struct Matrix A)
{
   matrix_set_zero(A);
   for (unsigned int idx = 0; idx < A.rows * A.cols; idx += 1)
      A.data[idx] = A.rows * A.cols - idx;
}


void matrix_print(const struct Matrix A)
{
   for (unsigned int row = 0; row < A.rows; ++row) {
      printf("[ ");
      for (unsigned int col = 0; col < A.cols; ++col) {
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

   for (unsigned int idx = 0; idx < C.rows * C.cols; idx +=1) {
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

   for (unsigned int idx = 0; idx < C.rows * C.cols; idx += 1) {
      C.data[idx] = A.data[idx] - B.data[idx];
   }
   return C;
}


//C=A*B
struct Matrix matrix_mult(struct Matrix A, struct Matrix B)
{
   if (A.cols != B.rows) return NULL_MATRIX;

   struct Matrix C = matrix_create(A.rows, B.cols);
   if (C.data == NULL) return NULL_MATRIX;

   for (unsigned int colB = 0; colB < B.cols; ++colB) {
      for (unsigned int rowA = 0; rowA < A.rows; ++rowA) {
         C.data[rowA * C.cols + colB] = 0;
         for (unsigned int idx = 0; idx < A.cols; ++idx) {
            C.data[rowA * C.cols + colB] += A.data[rowA * A.cols + idx] * B.data[idx * B.cols + colB];
         }
      }
   };
   return C;
}


struct Matrix matrix_trans(struct Matrix A)
{
   struct Matrix C = matrix_create(A.cols, A.rows);
   if (C.data == NULL) return NULL_MATRIX;

   for (unsigned int row = 0; row < A.rows; ++row) {
      for (unsigned int col = 0; col < A.cols; ++col) {
         C.data[col * A.cols + row] = A.data[row * A.cols + col];
      }
   }
   return C;
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



int main()
{
   struct Matrix A = matrix_create(3, 3);
   matrix_set_onetonum(A);
   matrix_print(A);

   struct Matrix B = matrix_create(3, 3);
   matrix_set_numtoone(B);
   matrix_print(B);

   struct Matrix C = marix_sum(A, B);
   matrix_print(C);

   struct Matrix D = matrix_sub(A, B);
   matrix_print(D);

   struct Matrix E = matrix_mult(A, B);
   matrix_print(E);


   struct Matrix F = matrix_trans(A);
   matrix_print(F);

   printf(matrix_det3x3(A));
   
   return 0;
}