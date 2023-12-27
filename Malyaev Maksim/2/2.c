#include <stdio.h>
#include "2_lib.h";

int main()
{
    struct Matrix A = matrix_allocation(3, 3);
    matrix_set_zero(A);
    matrix_print(A, "Matrix b");
}
