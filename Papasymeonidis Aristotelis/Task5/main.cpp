#include "din_arr/din_arr.hpp"
#include "linked_list/linked_list.hpp"
#include "queue/queue.hpp"
#include <iostream>


int main(){
    int data[5] = {3, 2, 3, 4, 5};
    Dynamic_array arr1(5, data);
    arr1.set_element(0,0);
    std::cout<<arr1.get_element(0);
    std::cout<<std::endl;

    linked_list<int> list;
    list.push_head(3);
    list.push_head(5);
    list.push_head(7);
    list.push_head(10);
    list.print();
    //list.pop_head();
    list.push_element(3,100);
    list.print();

    // PriorityQueue pq;
    // pq.push(Task("task1", 5));
    // pq.push(Task("task2", 1));
    // pq.push(Task("task3", 3));
    //
    // while (!pq.isEmpty()) {
    //     Task task = pq.pop();
    //     std::cout << "Task: " << task.name << ", Priority: " << task.priority << std::endl;
    // }
    //
    //
    queue<int> queue_atart;
    queue_atart.push_node_queue(23, 3);

    return 0;
}
