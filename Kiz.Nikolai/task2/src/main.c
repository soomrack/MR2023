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
    initMatrix(&a);
    initMatrix(&b);
    fillMatrix(&a, UNIT, false);
    double  arr[9] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    fillWithData(&b, arr, false);
    // printMatrix(&a);
    Matrix  new = matrixSum(&a, &b);
    printMatrix(&new);
    return 0;
}
