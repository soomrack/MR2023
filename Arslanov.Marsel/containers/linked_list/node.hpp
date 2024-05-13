#pragma once
#include <ostream>

template <typename T>
class Node
{
private:
    T _data;
    Node<T>* _next;
    Node<T>* _prev;

public:
    Node<T>* next();
    Node<T>* prev();

    void set_next(const Node<T>& next);
    void set_prev(const Node<T>& prev);

    Node(const T& data, Node<T>* prev = nullptr, Node<T>* next = nullptr);
    // todo to find out with T&& lvalue rvalue
    // Node<T>(T&& data);

    //! works only with built-in types
    friend std::ostream& operator<<(std::ostream& os, const Node<T>& node) {
        os << node._data << " ";
        return os;
    }

    Node<T>& operator=(const Node<T>& node);
};

template <typename T>
Node<T>::Node(const T& data, Node<T>* prev, Node<T>* next)
    : _data(data), _next(next), _prev(prev) {}

template <typename T>
Node<T>* Node<T>::next() {
    return _next;
}

template <typename T>
Node<T>* Node<T>::prev() {
    return _prev;
}

template <typename T>
void Node<T>::set_next(const Node<T>& next) {
    _next = &next;
}

template <typename T>
void Node<T>::set_prev(const Node<T>& prev) {
    _prev = &prev;
}

template <typename T>
Node<T>& Node<T>::operator=(const Node<T>& node) {
    if (&node == this) {
        return *this;
    }
    if (&node == nullptr) {
        throw "Assigment is bad";
    }
    _next = node._next;
    _prev = node._prev;
    _data = node._data;

    return *this;
}