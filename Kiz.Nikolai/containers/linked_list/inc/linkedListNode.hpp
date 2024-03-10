#pragma once
#include <initializer_list>
#include <iostream>


template<typename T>
class LinkedList;

template<typename T>
class LinkedListNode {

    friend class LinkedList<T>;
    friend std::ostream& operator<<(std::ostream& os, const LinkedListNode<T>& node) {return os << node._data << " ";}

protected:

    T _data;
    LinkedListNode<T>* _next{nullptr};

public:
    LinkedListNode() = delete;
    explicit LinkedListNode(const T& value);
    LinkedListNode(const T& value, LinkedListNode<T>* next_item);
    void operator=(const T& value);
    LinkedListNode<T>* next();
    ~LinkedListNode() = default;
};  //  class LinkedListNode


template<typename T>
LinkedListNode<T>::LinkedListNode(const T& value): _data{value} {}


template<typename T>
LinkedListNode<T>::LinkedListNode(const T& value, LinkedListNode<T>* next_item): LinkedListNode(value) {_next = next_item;}


template<typename T>
void LinkedListNode<T>::operator=(const T& value) {
    if (this == nullptr) throw std::runtime_error("Writing in empty node.");
    _data=value;
}


template<typename T>
LinkedListNode<T>* LinkedListNode<T>::next() {return _next;}

