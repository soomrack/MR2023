#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
      .data = NULL };
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
struct Matrix Sum(struct Matrix A, struct Matrix B) {
   if (A.cols != B.cols || A.rows != B.rows) return NULL_MATRIX;
   struct Matrix C = matrix_create(A.rows, A.cols);

   for (unsigned int idx = 0; idx < C.rows * C.cols; idx +=1) {
      C.data[idx] = A.data[idx] + B.data[idx];
   }
   return C;
}


//C=A-B
struct Matrix Sub(struct Matrix A, struct Matrix B) {
   if (A.cols != B.cols || A.rows != B.rows) return NULL_MATRIX;
   struct Matrix C = matrix_create(A.rows, A.cols);

   for (unsigned int idx = 0; idx < C.rows * C.cols; idx += 1) {
      C.data[idx] = A.data[idx] - B.data[idx];
   }
   return C;
}


//C=A*B
struct Matrix Sub(struct Matrix A, struct Matrix B) {
   if (A.cols != B.rows) return NULL_MATRIX;
   struct Matrix C = matrix_create(A.rows, B.cols);

   for (unsigned int row = 0; row < C.rows; row += 1) {
      for (unsigned int cols = 0; cols < C.cols; row += 1) {

      }
   }
   
   return C;
}


int main()
{
   struct Matrix A = matrix_create(3, 3);
   matrix_set_onetonum(A);
   matrix_print(A);

   struct Matrix B = matrix_create(3, 3);
   matrix_set_numtoone(B);
   matrix_print(B);

   struct Matrix C = Sum(A, B);
   matrix_print(C);

   struct Matrix D = Sub(A, B);
   matrix_print(D);

}