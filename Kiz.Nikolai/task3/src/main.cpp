#include "matrixHandler.hpp"



int main()
{
    matrix_element data1[6] {1.,2.,3.,4.,5.,6.};
    Matrix A(2, 3, data1);
    A(1,1) = 4;
    A.print();
    Matrix B(5, 5, InfillPattern::RANDOM);
    B.print();
    return 0;
}