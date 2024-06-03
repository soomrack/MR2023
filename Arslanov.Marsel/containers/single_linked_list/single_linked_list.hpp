#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace single_linked_list {

using data_type = int32_t;

class Node
{
protected:
    data_type data{0};
    Node* next{nullptr};

public:
    Node() = default;
    Node(const data_type& data, Node* next = nullptr)
            : data(data), next(next){};
    Node(const Node& other) : data(other.data), next(other.next){};

    data_type get_data() { return data; };
    Node* get_next() { return next; };

    void set_data(const data_type& data) { this->data = data; }
    void set_next(Node* next) { this->next = next; }

    Node& operator=(const Node& rhs) {
        if (this == &rhs) {
            return *this;
        }
        data = rhs.data;
        next = rhs.next;

        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Node& node) {
        os << node.data << " ";
        return os;
    }
};

class Single_linked_list
{
protected:
    Node* head{nullptr};
    Node* tail{head};
    size_t size{0};

public:
    Single_linked_list() = default;
    Single_linked_list(std::initializer_list<data_type> list);
    Single_linked_list(const Single_linked_list& other);
    // Single_linked_list(Single_linked_list&& other);  // TODO
    ~Single_linked_list();

    Single_linked_list& push_back(Node& node);
    Single_linked_list& push_back(const data_type& value);
    // Single_linked_list& push_back(data_type&& value); //TODO
    Single_linked_list& push_front(Node& node);
    Single_linked_list& push_front(const data_type& value);
    // Single_linked_list& push_front(data_type&& value); //TODO
    Single_linked_list& pop_back();
    Single_linked_list& pop_front();
    void remove(size_t idx);
    void insertt(size_t idx, const data_type& value);
    size_t get_size() { return size; };

    friend std::ostream& operator<<(std::ostream& os,
                                    const Single_linked_list& list) {
        if (!list.size) {
            os << "Single linked list is empty." << std::endl;
            return os;
        }
        Node* temp = list.head;
        while (temp != nullptr) {
            os << *temp;
            temp = temp->get_next();
        }
        os << std::endl;
        return os;
    }
};
}  // namespace single_linked_list