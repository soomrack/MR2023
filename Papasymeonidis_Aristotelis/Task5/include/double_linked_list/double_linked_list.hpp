//
// Created by simeonidi03 on 3/25/24.
//

#ifndef DOUBLE_LINKED_LIST_HPP
#define DOUBLE_LINKED_LIST_HPP

#include <iostream> 
#include "container_exception/container_exception.hpp" 

template<typename T>
class node {
public:
    node<T>* preview; 
    T data;
    node<T>* next;

    node(const T& data, node<T>* prev = nullptr, node<T>* next = nullptr) 
        : data(data), preview(prev), next(next) {}
};

template<typename T>
class double_linked_list {
private:
    node<T>* head;
    node<T>* tail;

public:
    double_linked_list() : head(nullptr), tail(nullptr) {}
    ~double_linked_list();

    void push_head(const T& value);
    T pop_first();
    T pop_head();
    void pop_element(size_t index);
    void print() const;
    void push_element(size_t index, const T& value);
};

template<typename T>
double_linked_list<T>::~double_linked_list() {
    while (head != nullptr) {
        node<T>* del_node = head;
        head = head->next;
        delete del_node;
    }
    tail = nullptr; 
}

template<typename T>
void double_linked_list<T>::push_head(const T& value) {
    node<T>* new_node = new node<T>(value, nullptr, head);
    if (head == nullptr) {
        tail = new_node;
    } else {
        head->preview = new_node;
    }
    head = new_node;
}

template<typename T>
void double_linked_list<T>::print() const {
    node<T>* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template<typename T>
T double_linked_list<T>::pop_first() {
    if (head == nullptr) throw container_exception("Empty list!");
    T data = head->data;
    node<T>* to_delete = head;
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    } else {
        head->preview = nullptr;
    }
    delete to_delete;
    return data;
}

template<typename T>
T double_linked_list<T>::pop_head() {
    return pop_first(); 
}

template<typename T>
void double_linked_list<T>::pop_element(size_t index) {
    if (index == 0) {
        pop_head();
        return;
    }
    node<T>* current = head;
    for (size_t i = 0; i < index; ++i) {
        if (current == nullptr) throw container_exception("Index out of bounds");
        current = current->next;
    }
    node<T>* to_delete = current;
    if (to_delete == nullptr) throw container_exception("Index out of bounds");

    if (to_delete->next != nullptr) to_delete->next->preview = to_delete->preview;
    if (to_delete->preview != nullptr) to_delete->preview->next = to_delete->next;

    if (to_delete == tail) tail = to_delete->preview;
    if (to_delete == head) head = to_delete->next;

    delete to_delete;
}

template<typename T>
void double_linked_list<T>::push_element(size_t index, const T& value) {
    if (index == 0) {
        push_head(value);
        return;
    }
    node<T>* current = head;
    for (size_t i = 0; i < index - 1; ++i) {
        if (current == nullptr) throw container_exception("Index out of bounds");
        current = current->next;
    }
    if (current == tail) {
        node<T>* new_node = new node<T>(value, tail, nullptr);
        tail->next = new_node;
        tail = new_node;
    } else {
        node<T>* new_node = new node<T>(value, current, current->next);
        if (current->next != nullptr) current->next->preview = new_node;
        current->next = new_node;
    }
}

#endif // DOUBLE_LINKED_LIST_HPP
