#include "matrix.hpp"

int main() 
{
    Matrix::Matrix<int> matrix(5, 5, Matrix::Matrix_Type::Identity_Matrix);
    std::cout << matrix << std::endl;
    Matrix::Matrix<int> matrix1(3, 3, Matrix::Matrix_Type::Random_Matrix);
    std::cout << matrix1 << std::endl;
    matrix = matrix1;
    std::cout << matrix << std::endl;
    return 0;
}