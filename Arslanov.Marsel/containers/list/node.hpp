#pragma once
#include <ostream>

template <typename T>
class Node
{
private:
    T data{0};
    Node<T>* next{nullptr};
    Node<T>* prev{nullptr};

public:
    Node() = default;
    Node(const T& data, Node<T>* next = nullptr, Node<T>* prev = nullptr)
            : data(data), next(next), prev(prev) {}
    Node(const Node& other)
            : data(other.data), next(other.next), prev(other.prev){};
    ~Node() = default;

    T get_data() { return data; }
    Node<T>* get_next() { return next; }
    Node<T>* get_prev() { return prev; }

    void set_data(const T& data) { this->data = data; }
    void set_next(Node<T>* next) { this->next = next; };
    void set_prev(Node<T>* prev) { this->prev = prev; };

    Node<T>& operator=(const Node<T>& rhs) {
        if (this == &rhs) {
            return *this;
        }
        data = rhs.data;
        next = rhs.next;
        prev = rhs.prev;

        return *this;
    };

    //! works only with built-in types
    friend std::ostream& operator<<(std::ostream& os, const Node<T>& node) {
        os << node.data << " ";
        return os;
    }
};