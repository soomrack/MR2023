#include "din_arr/din_arr.hpp"
#include "linked_list/linked_list.hpp"


int main(){
    int data[5] = {3, 2, 3, 4, 5};
    Dynamic_array arr1(5, data);
    arr1.set_element(0,0);
    std::cout<<arr1.get_element(0);

    linked_list<int> list;
    list.push_head(3);
    list.push_head(5);
    list.push_head(7);
    list.print();

    return 0;
}