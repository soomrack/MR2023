#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>
#include "container_exception/container_exception.hpp"

template<typename T>
class node {
public:
    T data;
    node<T>* next;

    node(const T& data, node<T>* next = nullptr) : data(data), next(next) {}
};

template<typename T>
class linked_list {
private:
    node<T>* head;

public:
    linked_list() : head(nullptr) {}
    ~linked_list();

    void push_head(const T& value);
    node<T>* pop_head();
    void pop_element(size_t index);
    void print() const;
    void push_element(size_t index, const T& value);
};

template<typename T>
linked_list<T>::~linked_list() {
    while (head != nullptr) {
        node<T>* temp = head;
        head = head->next;
        delete temp;
    }
}

template<typename T>
void linked_list<T>::push_head(const T& value) {
    head = new node<T>(value, head);
}

template<typename T>
node<T>* linked_list<T>::pop_head() {
    if (head == nullptr) throw ContainerException("List is empty");
    node<T>* temp = head;
    head = head->next;
    T data = temp->data; // save data to return
    delete temp;
    return new node<T>(data); // return the data wrapped in a node for consistency
}

template<typename T>
void linked_list<T>::pop_element(size_t index) {
    if (index == 0) {
        node<T>* temp = pop_head();
        delete temp; // we only need to delete the node, data is not used
        return;
    }

    node<T>* current = head;
    for (size_t i = 0; current != nullptr && i < index - 1; ++i) {
        current = current->next;
    }

    if (current == nullptr || current->next == nullptr) {
        throw ContainerException("Index out of bounds");
    }

    node<T>* temp = current->next;
    current->next = temp->next;
    delete temp;
}

template<typename T>
void linked_list<T>::print() const {
    for (node<T>* current = head; current != nullptr; current = current->next) {
        std::cout << current->data << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void linked_list<T>::push_element(size_t index, const T& value) {
    if (index == 0) {
        push_head(value);
        return;
    }

    node<T>* current = head;
    for (size_t i = 0; i < index - 1; ++i) {
        if (current == nullptr) {
            throw ContainerException("Index out of bounds");
        }
        current = current->next;
    }

    if (current == nullptr) {
        throw ContainerException("Index out of bounds");
    }

    current->next = new node<T>(value, current->next);
}

#endif // LINKED_LIST_HPP
