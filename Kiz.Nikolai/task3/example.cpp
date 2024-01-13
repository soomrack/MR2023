#include "matrixHandler.hpp"


using MatrixHandler::Matrix;
using MatrixHandler::InfillPattern;

int main()
{
    Matrix A;  //  default constructor
    Matrix B(3,3, InfillPattern::UNIT);  //  regular constructor
    Matrix C(3,4, {1,2,3,4,5,6,7,8,9,10,11,12});  //  init list constructor
    Matrix D(3,4, InfillPattern::RANDOM);
    A = B;

    A = B * C;

    A += D;

    A = D - C;

    A *= 2.5;

    Matrix X(3,3, InfillPattern::RANDOM);
    std::cout << X.determinant() << "\n";

    Matrix E = B.exponent(10);

    std::cout << A;
    A.transpose();
    std::cout << A;
    std::cout << (A == B) << "\n";
    std::cout << E;
    const Matrix R(std::move(A));
    std::cout << R(2,2);
    // R(3,2) = 1;  //  CE
    // std::cout << A;  //  CE

    D = {2,2,2,2,2,2,2,2,2,2,2,2};
    Matrix L(D = C);
    
    return 0;
}