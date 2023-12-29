#include <stdio.h>
#include "matrix.h";


int main()
{
MatrixItem a[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
struct Matrix C = matrix_create(3, 3);
struct Matrix D = matrix_create(3, 3);
matrix_fill(C, a);
D = matrix_exponent(C);
matrix_print(D, "exp");
matrix_delete(&C);
matrix_delete(&D);
return 0;
}