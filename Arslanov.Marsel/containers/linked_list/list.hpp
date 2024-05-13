#pragma once
#include <cstddef>
#include <iostream>
#include <list>

#include "node.hpp"

template <typename T>
class List
{
private:
    Node<T>* _head;
    Node<T>* _tail;
    size_t _sz;

public:
    List();

    List<T>& push_back(Node<T>* node);
    List<T>& push_back(const T& data);
    List<T>& push_back(T&& data);

    List<T>& push_front(Node<T>* node);
    List<T>& push_front(const T& data);
    List<T>& push_front(T&& data);

    bool is_empty();
    Node<T>& get_head();
    Node<T>& get_tail();

    // ! Works only with built-in types
    void print();

    void pop_back();
    void pop_front();
    void insert(size_t idx, const T& value);
    void erase(size_t idx);
};

template <typename T>
List<T>::List() : _head(nullptr), _tail(nullptr), _sz(0){};

template <typename T>
List<T>& List<T>::push_back(Node<T>* node) {
    if (is_empty()) {
        _tail = node;
        _head = _tail;
        ++_sz;
        return *this;
    }

    node->set_prev(_tail);
    node->set_next(nullptr);
    _tail->set_next(node);
    _tail = node;
    ++_sz;

    return *this;
}

template <typename T>
List<T>& List<T>::push_back(const T& data) {
    return push_back(new Node<T>(data));
}

template <typename T>
List<T>& List<T>::push_front(Node<T>* node) {
    if (is_empty()) {
        return push_back(node);
    }

    node->set_next(_head);
    node->set_prev(nullptr);
    _head->set_prev(node);
    _head = node;
    ++_sz;

    return *this;
}

template <typename T>
List<T>& List<T>::push_front(const T& data) {
    return push_front(new Node<T>(data));
}

template <typename T>
bool List<T>::is_empty() {
    return _sz;
}

template <typename T>
Node<T>& List<T>::get_head() {
    return _head;
}

// ! Works only with built-in types
template <typename T>
void List<T>::print() {
    Node<T>* item = _head;
    while (item) {
        std::cout << item;
        item = item->next();
    }
    std::cout << std::endl;
}