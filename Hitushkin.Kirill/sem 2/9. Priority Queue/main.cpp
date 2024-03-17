#include "PriorityQueue/PriorityQueue.hpp"
#include <iostream>


int main()
{
    
    priority_queue::PriorityQueue<int> A;
    A.push(12);
    A.push(-3);
    A.push(12);
    A.push(13);
    A.push(0);
    A.push(1);
    A.pop();
    A.push(24);
    
    while (A.get_size()) {
        std::cout << A.top() << std::endl;
        A.pop();
    }
    
}