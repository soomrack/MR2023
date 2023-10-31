#include <stdio.h>
#include "matrix.h"


void test(char *name, int success)
{
    printf("%s test: ", name);
    (success) ? printf("SUCCESS\n") : printf("FAIL\n");
}


int main()
{   
    Matrix A = matrix_allocate(3, 2);
    matrix_set_items(A, (double[]){2.5, 3, 4, 5, 1, 1});

    Matrix B = matrix_allocate(2, 2);
    matrix_set_items(B, (double[]){2.5, 3, 4, 5});

    Matrix C = matrix_allocate(2, 2);
    matrix_set_items(C, (double[]){5, 8, 9, 1});
    
    *matrix_get_element(A, 2, 1) = 12;

    
    Matrix S = matrix_sum(C, B);
    Matrix ans_S = matrix_allocate(2, 2);
    matrix_set_items(ans_S, (double[]){7.5, 11, 13, 6});
    int sum_test = matrix_compare(S, ans_S);
    test("Sum", sum_test);
    
    
    Matrix M = matrix_allocate(2, 2);
    matrix_set_zero(M);
    matrix_sub_from(M, B);
    Matrix MM = matrix_sub(C, B);
    Matrix ans_M = matrix_allocate(2, 2);
    matrix_set_items(ans_M, (double[]){2.5, 5, 5, -4});
    int minus_test = matrix_compare(MM, ans_M);
    test("Minus", minus_test);
    
    Matrix F = matrix_allocate(2, 3);
    matrix_set_items(F, (double[]){2.5, 3, 4,
                             5,   6, 2});
    Matrix FF = matrix_allocate(3, 4);
    matrix_set_items(FF, (double[]){2.5, 3, 4, 5,
                              2,   4, 2, 7,
                              1,   4, 7, 9});
    Matrix ans_Mult = matrix_allocate(2, 4);
    matrix_set_items(ans_Mult, (double[]){16.25, 35.50, 44.00, 69.50, 26.50, 47.00, 46.00, 85.00});
    Matrix Mult = matrix_mult(F, FF);
    int mult_test = matrix_compare(Mult, ans_Mult);
    test("Mult", mult_test);
    
    Matrix T = matrix_allocate(4, 2);
    matrix_set_items(T, (double[]){2, 6, 3, 7, 4, 8, 5, 9});
    Matrix ans_T = matrix_allocate(2, 4);
    Matrix TT = matrix_tran(T);
    matrix_set_items(ans_T, (double[]){2, 3, 4, 5, 6, 7, 8, 9});
    int tran_test = matrix_compare(matrix_tran(T), ans_T);
    test("Tran", tran_test);
    
    Matrix D = matrix_allocate(3, 3);
    matrix_set_items(D, (double[]){2, 6, 3, 7.6, 4, 8, 5, 9, 1});
    double ans_D = 2036;
    int Det_test = ((int)(matrix_det(D)*10) == ans_D) ? 1 : 0;
    test("Det", Det_test);
    
    Matrix ans_expm = matrix_allocate(3, 3);
    matrix_set_items(ans_expm, (double[]){1325081.25, 1594499.47, 1153925.02, 2100825.48, 2527969.84, 1829469.26, 1760956.08, 2118997.52, 1533499.65});
    Matrix EE = matrix_expm(D, 0.01);
    int expm_test = matrix_compare(EE, ans_expm);
    test("Expm", expm_test);

    printf("Result tests: %d%%\n", ((sum_test + minus_test + mult_test + tran_test + Det_test + expm_test) * 100) / 6);
    
    return 0;
}
