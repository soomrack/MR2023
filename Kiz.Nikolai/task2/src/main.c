#include "MatrixHandler.h"


int main()
{   
    Matrix a = {
        .rows = 3,
        .cols = 3,
    };
    Matrix b = {
        .rows = 3,
        .cols = 3
    };
    init_data(&a);
    init_data(&b);
    fill_matrix(&a, RAISING, false);
    double  arr[9] = {0, 1, 2, 3, 4, 5, 6, 7, 7};
    fill_with_data(&b, arr, false, false);
    print_matrix(&a);
    print_matrix(&b);
    double b_det = matrix_determinant(&b);
    double a_det = matrix_determinant(&a);
    // Matrix  new = matrix_sum(&a, &b);
    // print_matrix(&new);
    // matrix_transposition(&new);
    // print_matrix(&new);
    // delete_data(&new);
    delete_data(&b);
    delete_data(&a);
    return 0;
}
