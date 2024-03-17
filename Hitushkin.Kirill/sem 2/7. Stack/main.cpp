#include "Stack/Stack.hpp"
#include <iostream>

int main()
{
    stack::Stack<int> A;
    A.push(1);
    A.push(2);
    A.push(3);
    A.push(4);
    A.push(5);
    A.pop();
    A.push(8);
    
    while (A.get_size()) {
        std::cout << A.top() << std::endl;
        A.pop();
    }
    
}