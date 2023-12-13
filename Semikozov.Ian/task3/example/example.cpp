#include "matrix.hpp"

using namespace MatrixSpace;

int main() 
{
    Matrix matrix(5, 5, Matrix_Type::Identity_Matrix);
    std::cout << matrix << std::endl;
    Matrix matrix1(3, 3, Matrix_Type::Random_Matrix);
    std::cout << matrix1 << std::endl;
    matrix = matrix1;
    std::cout << matrix << std::endl;

    Matrix A(3, 3);
    Matrix B(3, 3, Matrix_Type::Identity_Matrix);
    Matrix C(3, 3, Matrix_Type::Identity_Matrix);
    Matrix D(3, 3, Matrix_Type::Identity_Matrix);


    C = A * A;
    C = C * 0.5;

    D = A * A;
    D = D * A;
    D = D * (1./6);


    B = B + A;
    B = B + C;
    B = B + D;


    A = A.exponent(5);
    std::cout << A << std::endl;

    std::cout << B << std::endl;

    return 0;
}