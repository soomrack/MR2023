#include "linkedListNode.hpp"
#include "linkedList.hpp"



int main(void) {
    LinkedList<int> list1({1,2,3,4});
    list1.insert(2, 4);
    std::cout << list1 << list1.size() << "\n";
    list1.pop_back();
    std::cout << list1 << list1.size() << "\n";
    list1.push_back(9);
    std::cout << list1 << list1.size() << "\n";
    list1.clear();
    std::cout << list1 << list1.size() << "\n";


    LinkedList<float> list2;
    std::cout << list2 << list2.size() << "\n";
    list2.push_back(12.);
    std::cout << list2 << list2.size() << "\n";
    list2.push_front(22.);
    std::cout << list2 << list2.size() << "\n";
    list2.insert(1, 32);
    std::cout << list2 << list2.size() << "\n";
    list2.pop_at(1);
    std::cout << list2 << list2.size() << "\n";
    list2.pop_front();
    std::cout << list2 << list2.size() << "\n";
    list2.push_back(122);
    std::cout << list2 << list2.size() << "\n";
    LinkedListNode<float>* l = list2[0].next();
    *l = 1;
    std::cout << list2 << list2.size() << "\n";

    try {
        LinkedList<int> list3;  
        list3.pop_at(1);  // exception
    }
    catch (std::runtime_error& e) {
        std::cout << "caught: " << e.what();
    }

}
