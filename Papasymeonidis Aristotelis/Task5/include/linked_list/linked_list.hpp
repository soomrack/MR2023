//
// Created by simeonidi03 on 17.03.24.
//

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP
#include <iostream>

template<typename T>
class node {
public:
    T data;
    node<T>* next;
    node(const T& data) : data(data), next(nullptr) {}
};

template<typename T>
class linked_list {
private:
    node<T>* head;
public:
    linked_list() : head(nullptr) {}
    ~linked_list();

    void push_head(const T& value);
    void print() const;
};


#endif //LINKED_LIST_HPP
