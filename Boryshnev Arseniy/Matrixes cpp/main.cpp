#include "matrix.hpp"

int main()
{
    Matrix A{ {1, 2, 3}, {4, 5, 6} };
    Matrix B1{ {1, 2, 3}, {4, 5, 6} };
    Matrix B{ {7, 8}, {9, 10}, {11, 12} };

    std::cout << "Matrix A:" << std::endl;
    A.display();

    std::cout << "Matrix B:" << std::endl;
    B.display();

    Matrix* C = A + B1;
    std::cout << "Matrix C = A + B:" << std::endl;
    C->display();

    Matrix* D = A * B;
    std::cout << "Matrix D = A * B:" << std::endl;
    D->display();

    Matrix E{ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };

    std::cout << "Matrix E:" << std::endl;
    E.display();

    Matrix* E_transpose = E.transpose();
    std::cout << "Transpose of E:" << std::endl;
    E_transpose->display();

    try {
        int det = E.determinant();
        std::cout << "Determinant of E: " << det << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
