#pragma once

#include <cstddef>
#include <cstdint>
#include <iostream>

namespace priority_queue {

using data_type = int32_t;
using priority = uint8_t;

class Node
{
protected:
    data_type data{0};
    Node* next{nullptr};
    priority pri;

public:
    Node() = default;
    Node(const data_type& data, Node* next, priority pri)
            : data(data), next(next), pri(pri){};
    Node(const Node& other)
            : data(other.data), next(other.next), pri(other.pri){};
    ~Node() = default;

    data_type get_data() { return data; };
    Node* get_next() { return next; };
    priority get_priority() { return pri; }

    void set_data(const data_type& data) { this->data = data; }
    void set_next(Node* next) { this->next = next; }
    void set_priority(priority pri) { this->pri = pri; }

    Node& operator=(const Node& rhs) {
        if (this == &rhs) {
            return *this;
        }
        data = rhs.data;
        next = rhs.next;
        pri = rhs.pri;

        return *this;
    }
};

class Priority_queue
{
protected:
    Node* head{nullptr};
    Node* tail{head};
    size_t size{0};

public:
    Priority_queue() = default;
    ~Priority_queue();

    size_t get_size() { return size; };

    Priority_queue& push(const data_type& data, priority pri);
    data_type top() { return head->get_data(); }
    Priority_queue& pop();
};

inline Priority_queue::~Priority_queue() {
    if (size == 0) {
        return;
    }
    Node* temp = head;
    while (temp != nullptr) {
        temp = head->get_next();
        delete head;
        head = temp;
    }
}

inline Priority_queue& Priority_queue::push(const data_type& data,
                                            priority pri) {
    Node* node = new Node(data, nullptr, pri);
    if (!get_size()) {
        tail = node;
        head = tail;
        ++size;

        return *this;
    }

    Node* temp = head;
    while (temp->get_priority() != node->get_priority() &&
           temp->get_next()->get_priority() != pri) {
        temp = temp->get_next();
    }
    node->set_next(temp->get_next());
    temp->set_next(node);
    ++size;

    return *this;
}

inline Priority_queue& Priority_queue::pop() {
    if (!get_size()) {
        return *this;
    }

    Node* temp = head->get_next();
    delete head;
    head = temp;
    --size;

    return *this;
}

}  // namespace priority_queue