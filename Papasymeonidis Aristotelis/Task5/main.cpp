#include "din_arr/din_arr.hpp"
#include "linked_list/linked_list.hpp"
#include "queue/queue.hpp"
#include <iostream>


int main(){
    try {
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
        list.pop_head();
        list.push_element(3,100);
        list.print();
        
        queue<int> queue_atart;
        queue_atart.push(23, 9);
        queue_atart.push(24, 9);
        queue_atart.push(25, 10);
        queue_atart.print();

    }catch (ContainerException error)
    {
        std::cerr << error.what() << std::endl;
    }catch (...) {
        std::cerr << "Some other exception\n";
        return 1;
    }
    return 0;
}
