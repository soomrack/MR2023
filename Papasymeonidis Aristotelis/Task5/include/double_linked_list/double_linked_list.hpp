//
// Created by simeonidi03 on 3/25/24.
//


#ifndef DOUBLE_LINKED_LIST_HPP
#define DOUBLE_LINKED_LIST_HPP

#include"container_exception/container_exception.hpp"

template<typename T>
class node {
public:
    node<T>* preview;
    T data;
    node<T>* next;
    node(const T& data) : preview(nullptr), data(data), next(nullptr) {}
    node(const T& data, node<T>* next) : preview(nullptr), data(data), next(next) {}
    node(const node<T>* preview, const T& data, const node<T>* next) : preview(preview), data(data), next(nullptr) {}
};


template<typename T>
class double_linked_list {
private:
    node<T>* head;
    node<T>* tail;
    //node<T>* current_ptr;
public:
    double_linked_list() : head(nullptr) tail(nullptr){}
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
        node<T>* del_node_ptr = head;
        head = head->next;
        delete del_node_ptr;
    }
}


template<typename T>
void double_linked_list<T>::push_head(const T& value) {
    node<T>* new_node = new node<T>(value);
    if(head == nullptr && tail == nullptr) {
        tail = new_node;
    }
    head = new_node;
    new_node->next = head;
    head->preview = new_node;
}


template<typename T>
void double_linked_list<T>::print() const {
    node<T> *current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}


template<typename T>
T double_linked_list<T>::pop_first() {
    if(tail == nullptr){ throw container_exception("Empty list!");}
    node<T>*next_ptr = tail->preview;
    T pop_data = head->data;

    if(tail->preview == nullptr){
        head = nullptr;
        tail = nullptr;
        return pop_data;
    }

    next_ptr->next = nullptr;
    delete[] head;
    head = next_ptr;
    return pop_data;
}


template<typename T>
T double_linked_list<T>::pop_head(){
    if(head == nullptr){ throw container_exception("Empty list!"); }
    node<T>*next_ptr = head->next;
    next_ptr->preview = nullptr;
    T pop_data = head->data;

    if(head->next == nullptr){
        head = nullptr;
        tail = nullptr;
        return pop_data;
    }

    delete[] head;
    head = next_ptr;
    return pop_data;
}


template<typename T>
void double_linked_list<T>::pop_element(size_t index){
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
        current_ptr->next->preview = current_ptr;
        delete[] next_ptr;
    }else {
        std::cout<<"Error! This element is the last one"<<std::endl;
     }
}


template<typename T>
void double_linked_list<T>::push_element(size_t index, const T& value) {
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
        node<T>* next_ptr = new node<T>{current_ptr, value, current_ptr->next};
        current_ptr->next = next_ptr;
    } else {
        std::cout << "Unknown error" << std::endl;
    }
}









#endif //DOUBLE_LINKED_LIST_HPP
