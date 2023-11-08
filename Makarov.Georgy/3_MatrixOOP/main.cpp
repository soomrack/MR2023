#include "libmatrix.h"

int main() {
    Matrix A{3, 3, RANDOM};
    Matrix D = A;

    A.print();

    D = A.exp(4);
    D.print();

    A = A.T();
    A.print();

    Matrix B{3, 3, IDENTITY};

    B = A * (B*(-2));

    B.print();

    double det = B.det();

    printf("Determinant of the matrix B is %f\n", det);

    struct Matrix C = {4, 4, ZEROS};

    C.print();

    C.det();

    return 0;
}