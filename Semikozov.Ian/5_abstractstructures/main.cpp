#include "dlinked_list.hpp"
#include "dynamic_array.hpp"
#include "linked_list.hpp"
#include "priority_queue.hpp"
#include "queue.hpp"
#include "stack.hpp"

int main()
{
    priority_queue<double> pqueue;

    pqueue.push(0.112, 0);
    pqueue.push(0.113, 3);
    pqueue.push(0.114, 0);
    pqueue.push(0.115, 0);
    pqueue.push(0.117, 0);
    auto temp_pqueue = pqueue.top();
    std::cout << temp_pqueue << std::endl;

    queue<double> queue;

    queue.push(0.112);
    queue.push(0.113);
    queue.push(0.114);
    queue.push(0.115);
    queue.push(0.117);
    auto temp_queue = queue.pop();
    std::cout << temp_queue << std::endl;
    temp_queue = queue.front();
    std::cout << temp_queue << std::endl;

    doubly_linked_list<double> dlist;

    dlist.push_back(0.112);
    dlist.push_back(0.113);
    dlist.push_back(0.114);
    dlist.push_back(0.115);
    dlist.push_back(0.117);
    auto temp_dlist = dlist.pop_back();
    std::cout << temp_dlist << std::endl;

    array<double> arr;

    arr.append(0.112);
    arr.append(0.113);
    arr.append(0.114);
    arr.append(0.115);
    arr.append(0.117);
    auto temp_arr = arr.pop_back();
    std::cout << temp_arr << std::endl;

    linked_list<double> list;

    list.push_back(0.112);
    list.push_back(0.113);
    list.push_back(0.114);
    list.push_back(0.115);
    list.push_back(0.117);
    auto temp = list.pop_back();
    std::cout << temp << std::endl;

    stack<double> stack;
    stack.push(0.112);
    stack.push(0.113);
    stack.push(0.114);
    stack.push(0.115);
    stack.push(0.117);
    temp = stack.pop();
    std::cout << temp << std::endl;

    return 0;
}
