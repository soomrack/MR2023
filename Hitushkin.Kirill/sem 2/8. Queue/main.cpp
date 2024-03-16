#include "Queue/Queue.hpp"
#include <iostream>

int main()
{
    queue::Queue<int> A;
    A.push(1);
    A.push(2);
    A.push(3);
    A.pop();
    A.push(4);
    A.push(5);
    A.push(8);
    
    while (A.get_size()) {
        std::cout << A.pop() << std::endl;
    }
    
}