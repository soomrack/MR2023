#include "DynamicArray/DynamicArray.hpp"
#include <iostream>

int main()
{
    
    DynArr::DynamicArray<int> A;
    
    DynArr::DynamicArray<double> B(12);
    
    A = {1, 2, 3, 4, 5, 6};
    DynArr::DynamicArray C = A;

    C[2] = 12;

    DynArr::DynamicArray<int> F;
    F.push_back(12);
    A.pop_back();
    A.erase(3);
    A.push_back(122);
    A.insert(1, 11);
    
    std::cout << A << B << C << F;
    
}