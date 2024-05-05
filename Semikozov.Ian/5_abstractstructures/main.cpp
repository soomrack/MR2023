#include "dlinked_list.hpp"
#include "dynamic_array.hpp"
#include "linked_list.hpp"
#include "queue.hpp"
#include "stack.hpp"

#include <cstddef>

int main()
{
    structures::linked_list<double> list;

    list.push_back(0.112);
    list.push_back(0.113);
    list.push_back(0.114);
    list.push_back(0.115);
    list.push_back(0.117);
    auto temp = list.pop_back();
    std::cout << temp << std::endl;

    structures::stack<double> stack;
    stack.push(0.112);
    stack.push(0.113);
    stack.push(0.114);
    stack.push(0.115);
    stack.push(0.117);
    temp = stack.pop();
    std::cout << temp << std::endl;

    return 0;
}
