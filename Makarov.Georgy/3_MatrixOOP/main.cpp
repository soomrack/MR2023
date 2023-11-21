#include "libmatrix.h"

int main() {
    Matrix A = {3, 3, RANDOM};
    Matrix B = {3, 3, IDENTITY};
    Matrix C = {3, 3, IDENTITY};
    Matrix D = {3, 3, IDENTITY};

    A.print();

    C = A*A;
    C = C*0.5;

    D = A*A;
    D = D*A;
    D = D*(1./6);


    B = B+A;
    B = B+C;
    B = B+D;


    A = A.exp(3);
    A.print();

    B.print();

    return 0;
}