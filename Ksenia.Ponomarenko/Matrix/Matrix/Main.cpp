#include <stdio.h>
#include "Matrix.h";

int main()
{
    Matrix A = matrix_allocation(3, 3);
    Matrix B = matrix_allocation(3, 3);
    matrix_set_one(A);
    matrix_set_one(B);
    Matrix C = matrix_sum(A, B);
    matrix_print(C, "Matrix");
}