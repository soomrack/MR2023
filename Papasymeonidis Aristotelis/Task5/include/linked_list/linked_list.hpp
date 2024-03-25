//
// Created by simeonidi03 on 17.03.24.
//

#include <iostream>


#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

template<typename T>
class node {
public:
    T data;
    node<T>* next;
    node(const T& data) : data(data), next(nullptr) {}
    node(const T& data, node<T>* next) : data(data), next(next) {}
};


template<typename T>
class linked_list {
private:
    node<T>* head;
    //node<T>* current_ptr;
public:
    linked_list() : head(nullptr) {}
    ~linked_list();

    void push_head(const T& value);
    void pop_first();
    void pop_head();
    void pop_element(size_t index);
    void print() const;
    void push_element(size_t index, const T& value);
};

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

template<typename T>
void linked_list<T>::pop_first() {
    node<T>*next_ptr = head->next;
    delete[] head;
    head = next_ptr;
}


template<typename T>
void linked_list<T>::pop_head(){
    node<T>*next_ptr = head->next;
    delete[] head;
    head = next_ptr;
}

template<typename T>
void linked_list<T>::pop_element(size_t index){
    if(index == 0) {
        pop_head();
        return;
    }
    node<T>* current_ptr = head;
    for(size_t current_idx = 1; current_idx < index; ++current_idx) {
        current_ptr = current_ptr->next;
     }
    if(current_ptr->next->next != nullptr) {
        node<T>*next_ptr = current_ptr->next;
        current_ptr->next = current_ptr->next->next;
        delete[] next_ptr;
    }else {
        std::cout<<"Error! This element is the last one"<<std::endl;
     }
}

template<typename T>
void linked_list<T>::push_element(size_t index, const T& value) {
    if(index == 0) {
        push_head(value);
        return;
    }

    node<T>* current_ptr = head;
    for(size_t current_idx = 1; current_idx < index - 1; ++current_idx) {
        if(current_ptr == nullptr) {
            std::cerr << "Index out of bounds" << std::endl;
            return;
        }
        current_ptr = current_ptr->next;
    }

    if(current_ptr != nullptr) {
        node<T>* next_ptr = new node<T>{value, current_ptr->next};
        current_ptr->next = next_ptr;
    } else {
        std::cout << "Unknown error" << std::endl;
    }
}




#endif //LINKED_LIST_HPP
