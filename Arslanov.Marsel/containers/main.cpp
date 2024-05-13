#include <iostream>
#include <memory>
#include <vector>

// #include "include/vector.hpp"
#include "list.hpp"
#include "vector.hpp"

int main() {
    Vector<int> v(6, 5);
    v.push_back(8);
    v.push_back(10);
    v.pop_back();
    std::cout << v << std::endl;
    v.reserve(10);
    v.resize(9);
    std::cout << v << std::endl;

    // int a = 5;
    // int b = 6;

    // Node<int> node(3, nullptr, nullptr);
    // Node<int> node1(a, nullptr, nullptr);
    // Node<int> node2(b, nullptr, nullptr);
    // node.set_next(node1);
    // node.set_prev(node2);
    // std::cout << node << node.next() << node.prev() << std::endl;

    // // List<int> l;
    // // l.push_back(a);
    // // l.print();

    return 0;
}