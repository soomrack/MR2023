#include "linkedList.hpp"
#include "doublyLinkedList.hpp"
#include "dynamicArray.hpp"
#include "stack.hpp"
#include "priorityQueue.hpp"



int main() {

    /*single linked list*/

    SingleLinkedList<float> sll = {1,2,3,4,5};
    SingleLinkedList<float> sll2(sll);
    SingleLinkedList<float> sll3;
    sll3 = std::move(sll2);
    std::cout << sll << sll2 << sll3 << "\n";

    /*doubly linked list*/

    DoublyLinkedList<int> dll = {0,1,0,1,0};
    DoublyLinkedList<int> dll2(dll);
    dll.clear();
    DoublyLinkedList<int> dll3(std::move(dll2));
    try {
        dll.pop_at(1);
    }
    catch (...) {
        std::cout << "caught an exception" << std::endl;
    }
    dll.push_back(100);
    std::cout << dll << dll2 << dll3 <<  "\n";

    /*dynamic array*/

    DynamicArray<double> v;
    v.insert(100, {1,2,3,4});
    std::cout << v << v.size() << v.capacity() << "\n";
    v.insert(1, 2);
    std::cout << v << v.size() << v.capacity() << "\n";
    v.shrink_to_fit();
    std::cout << v.size() << v.capacity() << "\n";
    v.push_back(5);
    v.erase(1);
    std::cout << v << v.size() << v.capacity() << "\n";

    /*stack*/

    Stack<char> s;
    s.push(98);
    s.push(67);
    s.pop();
    s.push(101);
    s.push('h');
    s.pop();
    s.push_range({'b','r','a'});
    std::cout << s << s.size() << s.top() << "\n";

    /*priority queue*/

    PriorityQueue<int> pq({{1,2}, {1,1}, {3,4}, {100,1}});
    pq.push(1,100);
    pq.push(200,0);
    pq.push(2,2);
    pq.push(0,20);
    pq.push(100,1);
    std::cout << pq;
    pq.push_range({{0,0}, {0,2}, {0,4}, {0,5}});
    std::cout << pq;
    int t = pq.pop();
    PriorityQueue<int> pq2 = pq;
    std::cout << pq2 << pq2.size();
}
