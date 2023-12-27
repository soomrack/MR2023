
#include "mat_lib.h";

int main()
{
    struct Matrix A = matrix_create(3, 3);
    struct Matrix B = matrix_create(3, 3);

    struct Matrix result_add = matrix_create(A.cols, A.rows);
    struct Matrix result_minus = matrix_create(A.cols, A.rows);
    struct Matrix result_mult = matrix_create(A.cols, A.rows);
    struct Matrix result_trans = matrix_create(A.cols, A.rows);
    struct Matrix result_exp = matrix_create(A.cols, A.rows);
    struct Matrix result_mult_on_number = matrix_create(A.cols, A.rows);
    struct Matrix result_div_on_number = matrix_create(A.cols, A.rows);

    matrix_fill(A, (double[])
    {
        11., 2., 3.,
            4., 5., 6.,
            7., 8., 9.,
    });

    matrix_fill(B, (double[])
    {
        1., 2., 1.,
            2., 1., 1.,
            1., 1., 1.,
    });

    printf("Matrix Add:\n");
    matrix_add(A, B);
    result_add = matrix_add(A, B);
    matrix_print(result_add);
    printf("\n");


    printf("Matrix Minus:\n");
    matrix_minus(A, B);
    result_minus = matrix_minus(A, B);
    matrix_print(result_minus);
    printf("\n");


    printf("Matrix Multiply:\n");
    matrix_mult(A, B);
    result_mult = matrix_mult(A, B);
    matrix_print(result_mult);
    printf("\n");


    printf("Matrix Multiply on number:\n");
    matrix_mult_on_number(A, 2);
    result_mult_on_number = matrix_mult_on_number(A, 2);
    matrix_print(result_mult_on_number);
    printf("\n");


    printf("Matrix Div on number:\n");
    matrix_div_on_number(A, 2);
    result_div_on_number = matrix_div_on_number(A, 2);
    matrix_print(result_div_on_number);
    printf("\n");


    printf("Matrix Transpose:\n");
    matrix_trans(A, B);
    result_trans = matrix_trans(A, B);
    matrix_print(result_trans);
    printf("\n");


    printf("Matrix Determinant:");
    printf("%4.2f\n", matrix_det(A));
    printf("\n");


    printf("Matrix Exponent:\n");
    matrix_exp(A, 15);
    result_exp = matrix_exp(A, 100);
    matrix_print(result_exp);
    printf("\n");


    matrix_delete(&A);
    matrix_delete(&B);
    matrix_delete(&result_add);
    matrix_delete(&result_minus);
    matrix_delete(&result_trans);
    matrix_delete(&result_mult);
    matrix_delete(&result_mult_on_number);
    matrix_delete(&result_div_on_number);
    matrix_delete(&result_exp);
    return 0;
}
