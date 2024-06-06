#include <iostream>
#include <memory>
#include <vector>

// #include "include/vector.hpp"
#include "array.hpp"
#include "list.hpp"
#include "priority_queue.hpp"
#include "single_linked_list.hpp"
#include "vector.hpp"

int main() {
    Array arr = {1, 5, 7, 8, 45, 3, 2};
    std::cout << arr;
    arr.resize(20, 666);
    std::cout << arr;

    std::cout << "\n\n\n";

    single_linked_list::Single_linked_list slist = {3, 5, 7, 2, 1};
    std::cout << slist;
    slist.push_back(333);
    std::cout << slist;
    slist.push_back(123).push_back(234);
    std::cout << slist;
    slist.pop_back().pop_front();
    std::cout << slist;
    slist.insertt(0, 66);
    std::cout << slist;
    slist.remove(2);
    std::cout << slist;
    single_linked_list::Single_linked_list slist2 = slist;
    std::cout << slist2;
    slist.push_back(33);
    std::cout << slist;
    std::cout << slist2;

    std::cout << "\n\n\n";

    List<int32_t> list = {3, 5, 7, 2, 1};
    std::cout << list;
    list.push_back(333);
    std::cout << list;
    list.push_back(123).push_back(234);
    std::cout << list;
    list.pop_back().pop_front();
    std::cout << list;
    list.insert(0, 66);
    std::cout << list;
    list.remove(2);
    std::cout << list;
    List<int32_t> list2 = list;
    std::cout << list2;
    list.push_back(33);
    std::cout << list;
    std::cout << list2;

    std::cout << "\n\n\n";

    priority_queue::Priority_queue queue;
    queue.push(3, 1).push(4, 3).push(5, 2);
    // queue.push(30, 2).push(40, 2).push(50, 2);
    // queue.push(300, 3).push(400, 3).push(500, 3);

    priority_queue::data_type data = queue.top();
    std::cout << data << std::endl;
    queue.pop();
    data = queue.top();
    std::cout << data << std::endl;

    return 0;
}