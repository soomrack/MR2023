#include "MatrixHandler.h"
#include <string.h>

int main()
{   
    Matrix A  = create_matrix(3, 4);
    Matrix B = create_matrix(4, 3);

    double arr1[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
    double arr2[12] = {3, 3, 3, 3, 3, 12, 3, 3, 3, 3, 3, 30};
    
    fill_with_data(&A, arr1);
    fill_with_data(&B, arr2);


    Matrix C = matrix_multiplication(&A, &B);
    Matrix D = create_matrix(3, 3);
    fill_matrix(&D, UNIT);


    Matrix E = matrix_exponent(&D, 15);
    print_matrix(&A);
    matrix_transposition(&A);
    print_matrix(&A);
    print_matrix(&A);
    print_matrix(&B);
    print_matrix(&C);
    print_matrix(&D);
    print_matrix(&E);
    print_matrix(&D);


    delete_matrix(&A);
    delete_matrix(&B);
    delete_matrix(&C);
    delete_matrix(&D);
    delete_matrix(&E);
    return 0;
}
