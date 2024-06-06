#pragma once
#include <cstddef>
#include <iostream>
#include <list>

#include "node.hpp"

template <typename T>
class List
{
protected:
    Node<T>* head{nullptr};
    Node<T>* tail{head};
    size_t size{0};

public:
    List() = default;
    List(std::initializer_list<T> list);
    List(const List<T>& other);
    // List<T>(List<T>&& other);  // TODO
    ~List();

    List<T>& push_back(Node<T>& node);
    List<T>& push_back(const T& data);
    // List<T>& push_back(T&& data);  // TODO
    List<T>& push_front(Node<T>& node);
    List<T>& push_front(const T& data);
    // List<T>& push_front(T&& data);  // TODO
    List<T>& pop_back();
    List<T>& pop_front();
    void remove(size_t idx);
    void insert(size_t idx, const T& data);
    size_t get_size() { return size; }

    friend std::ostream& operator<<(std::ostream& os, const List<T>& list) {
        if (!list.size) {
            os << "List is empty." << std::endl;
            return os;
        }
        Node<T>* temp = list.head;
        while (temp != nullptr) {
            os << *temp;
            temp = temp->get_next();
        }
        os << std::endl;
        return os;
    };
};

template <typename T>
List<T>::List(std::initializer_list<T> list) {
    for (auto it = list.begin(); it != list.end(); ++it) {
        List<T>::push_back(*it);
    }
}

template <typename T>
List<T>::List(const List<T>& other) {
    if (other.size == 0) {
        return;
    }
    Node<T>* temp_other = other.head;
    while (temp_other != nullptr) {
        this->push_back(temp_other->get_data());
        temp_other = temp_other->get_next();
        ++this->size;
    }
}

template <typename T>
List<T>::~List() {
    if (size == 0) {
        return;
    }
    Node<T>* temp = head;
    while (temp != nullptr) {
        temp = head->get_next();
        delete head;
        head = temp;
    }
}

template <typename T>
List<T>& List<T>::push_back(Node<T>& node) {
    if (!get_size()) {
        node.set_next(nullptr);
        node.set_prev(nullptr);
        tail = &node;
        head = tail;
        ++size;

        return *this;
    }

    tail->set_next(&node);
    node.set_next(nullptr);
    node.set_prev(tail);
    tail = &node;
    ++size;

    return *this;
}

template <typename T>
List<T>& List<T>::push_back(const T& value) {
    Node<T>* node = new Node(value);
    List<T>::push_back(*node);
    return *this;
}

template <typename T>
List<T>& List<T>::push_front(Node<T>& node) {
    if (!get_size()) {
        push_back(node);

        return *this;
    }

    node.set_next(head);
    node.set_prev(nullptr);
    head = &node;
    ++size;

    return *this;
}

template <typename T>
List<T>& List<T>::push_front(const T& value) {
    Node<T>* node = new Node(value);
    List<T>::push_front(*node);
    return *this;
}

template <typename T>
List<T>& List<T>::pop_front() {
    if (!get_size()) {
        return *this;
    }

    Node<T>* temp = head->get_next();
    delete head;
    head = temp;
    head->set_prev(nullptr);
    --size;

    return *this;
}

template <typename T>
List<T>& List<T>::pop_back() {
    if (!get_size()) {
        return *this;
    }

    Node<T>* temp = tail->get_prev();
    delete tail;
    tail = temp;
    tail->set_next(nullptr);
    --size;

    return *this;
}

template <typename T>
void List<T>::remove(size_t idx) {
    if (idx >= size) {
        // throw exeption
    }
    if (idx == 0) {
        pop_front();
        return;
    }
    if (idx == size - 1) {
        pop_back();
        return;
    }
    Node<T>* temp = head;
    for (size_t index = 0; index < idx - 1; ++index) {
        temp = temp->get_next();
    }
    Node<T>* node_to_delete = temp->get_next();
    temp->set_next(temp->get_next()->get_next());
    temp = temp->get_next()->get_next();
    temp->set_prev(temp->get_prev()->get_prev());
    delete node_to_delete;
    --size;
}

template <typename T>
void List<T>::insert(size_t idx, const T& value) {
    if (idx > size) {
        // throw exeption
    }
    if (idx == size) {
        push_back(value);
        return;
    }
    if (idx == 0) {
        push_front(value);
        return;
    }
    Node<T>* new_node = new Node<T>(value);
    Node<T>* temp = head;
    for (size_t index = 0; index < idx - 1; ++index) {
        temp = temp->get_next();
    }
    new_node->set_next(temp->get_next());
    new_node->set_prev(temp);
    temp->set_next(new_node);
    temp = temp->get_next()->get_next();
    temp->set_prev(new_node);
    ++size;
}
