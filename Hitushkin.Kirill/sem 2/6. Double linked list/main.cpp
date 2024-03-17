#include "DoubleLinkedList/DoubleLinkedList.hpp"
#include <iostream>

int main()
{
    DoubleLinkList::DoubleLinkedList<int> list = {1, 2, 4, 5, 6};
    std::cout << list << std::endl;

    list.insert_after(2, 10);
    std::cout << list << std::endl;

    list.erase_this(4);
    std::cout << list << std::endl;

    list.push_back(11);
    std::cout << list << std::endl;

    list.pop_back();
    std::cout << list << std::endl;

    std::cout << list[4] << std::endl;
}