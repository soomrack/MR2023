//
// Created by simeonidi03 on 17.03.24.
//
#include"linked_list.hpp"

template<typename T>
linked_list<T>::~linked_list() {
        while (head != nullptr) {
            node<T>* del_node_ptr = head;
            head = head->next;
            delete del_node_ptr;
        }
}

template<typename T>
void linked_list<T>::push_head(const T& value) {
    node<T>* new_node = new node<T>(value);
    new_node->next = head;
    head = new_node;
}


template<typename T>
void linked_list<T>::print() const {
    node<T> *current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}
