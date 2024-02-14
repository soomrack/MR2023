#include <iostream>
#include <string>
#include "matrix.hpp"


void test(std::string name, bool success)
{
    std::cout << name << " test: ";
    std::cout << ((success) ? "SUCCESS\n" : "FAIL\n");
}

int main()
{   
    Matrix A(3, 2);
    A = {2.5, 3, 4, 5, 1, 1};

    Matrix B(2, 2);
    B = {2.5, 3, 4, 5};

    Matrix C(2, 2);
    C = {5, 8, 9, 1};
    
    A[2, 1] = 12;
    
    Matrix S = C + B;
    Matrix ans_S(2, 2);
    ans_S = {7.5, 11, 13, 6};
    test("Sum", S == ans_S);
    
    Matrix M(2, 2);
    M.set_zero();
    M -= B;
    Matrix MM = C - B;
    Matrix ans_M(2, 2);
    ans_M ={2.5, 5, 5, -4};
    test("Minus", MM == ans_M);
    
    Matrix F(2, 3);
    F = {2.5, 3, 4, 5,   6, 2};
    Matrix FF(3, 4);
    FF = {2.5, 3, 4, 5, 2, 4, 2, 7, 1, 4, 7, 9};
    Matrix ans_Mult(2, 4);
    ans_Mult = {16.25, 35.50, 44.00, 69.50, 26.50, 47.00, 46.00, 85.00};
    Matrix Mult = F * FF;
    test("Mult", Mult == ans_Mult);

    
    Matrix T(4, 2);
    T = {2, 6, 3, 7, 4, 8, 5, 9};
    Matrix ans_T(2, 4);
    ans_T = {2, 3, 4, 5, 6, 7, 8, 9};
    test("Tran", T.T() == ans_T);
    
    
    Matrix D(3, 3);
    D = {2, 6, 3, 7.6, 4, 8, 5, 9, 1};
    double ans_D = 2036;
    test("Det", (int)(D.det()*10) == ans_D);

    Matrix ans_expm(3, 3);
    ans_expm = {1325081.25, 1594499.47, 1153925.02, 2100825.48, 2527969.84, 1829469.26, 1760956.08, 2118997.52, 1533499.65};
    Matrix EE = D.expm(0.01);
    test("Expm", EE == ans_expm);
    
    return 0;
}

