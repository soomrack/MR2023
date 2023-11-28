#include <stdio.h>
#include "..\task_2_lib.c\task_2_lib.c.h";

int main()
{
    struct Matrix A = matrix_create(3, 3);
    matrix_set_one(A);
    matrix_print(A, "Matrix A");
    matrix_delete(&A);
    
    return 0;
}
