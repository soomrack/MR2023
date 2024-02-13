#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Matrix.h"

int test()
{
    Matrix mat1, mat2;

    printf("\n     First matrix\n");
    mat1 = matrix_memory(3, 3);
    matrix_fill_rand(&mat1);
    matrix_print(mat1);

    printf("     Second matrix\n");
    mat2 = matrix_memory(3, 3);
    matrix_fill_rand(&mat2);
    matrix_print(mat2);

    printf("     Sum\n");
    Matrix addition;
    addition = matrix_sum(mat1, mat2);
    matrix_print(addition);
    memory_clear(&addition);

    printf("     Sub\n");
    Matrix subtruction;
    subtruction = subtruct_matrices(mat1, mat2);
    matrix_print(subtruction);
    memory_clear(&subtruction);

    printf("     Multiply\n");
    Matrix multiplication_matrices;
    multiplication_matrices = matrix_multiply(mat1, mat2);
    matrix_print(multiplication_matrices);
    memory_clear(&multiplication_matrices);

    MatrixItem determinant;
    printf("     Det 1\n");
    determinant = matrix_det(mat1);
    printf("%.2f\n\n", determinant);

    printf("     Det 2\n");
    determinant = matrix_det(mat2);
    printf("%.2f\n\n", determinant);

    printf("     Transp 1\n");
    Matrix transpose1;
    transpose1 = transpose(mat1);
    matrix_print(transpose1);
    memory_clear(&transpose1);

    printf("     Transp 2\n");
    Matrix transpose2;
    transpose2 = transpose(mat2);
    matrix_print(transpose2);
    memory_clear(&transpose2);

    printf("     e\n");
    Matrix exponenta;
    exponenta = matrix_expo(mat1, 3);
    matrix_print(exponenta);
    memory_clear(&exponenta);
    memory_clear(&mat1);
    memory_clear(&mat2);
}