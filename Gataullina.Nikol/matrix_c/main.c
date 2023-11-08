#include "matrix_lib.h"
int main()
{
    // Matrix A;
    // A = memory_allocation(3,3);
    // A = fill_random(A);
    // output("A",A);
    // Matrix B;
    // B = memory_allocation(3,3);
    // B = fill_random(B);
    // output("B",B);
    Matrix sum = addition(A, B);
    output("SUM", sum);
    Matrix mult = multiplication(A, B);
    output("Mult", mult);
    // double array[9] = {1,2,3,4,5,6,7,8,9};
    // A = fill_from_array(array, 3, 3);
    printf("det %lf", determinant(A,A.rows));
    Matrix revers = reverse_matrix(A, A.rows);
    output("revers", revers);
    Matrix exp = exponent_matrix(A, 30);
    output("exponent", exp);
    // A = memory_initial(3,3);
    // fill_random(A);
    matrix_free(&A);
    matrix_free(&B);
    matrix_free(&sum);
    matrix_free(&mult);
    matrix_free(&exp);
    return 0;
}