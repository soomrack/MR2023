/**
 * @file linked_list.hpp
 * @author Semikozov Ian (semikozov.yal@yandex.ru)
 * @brief
 * @version 0.1
 * @date 29.04.2024
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef LINKED_LIST_HPP_INCLUDED
#define LINKED_LIST_HPP_INCLUDED

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

namespace structures
{

template <typename T>
struct node
{
    static constexpr T null_node{ 0 };

    T value;
    node *next;
    node() = delete;
    node(const T value_, node *next_ = nullptr) : value{ value_ }, next{ next_ } {};

    node(const node &other)
    {
        *this = other;
    }

    node &operator=(const node &rhs)
    {
        if (this == &rhs) { return *this; }

        value = rhs.value;
        next = rhs.next;

        return *this;
    };

    node &operator=(const node &&rhs)
    {
        if (this == &rhs) { return *this; }

        value = rhs.value;
        next = rhs.next;

        rhs.next = nullptr;
        rhs = 0;

        return *this;
    };
};

template <typename T>
static void swap(node<T> &lhs, node<T> &rhs) noexcept
{
    node<T> temp = lhs;
    lhs = rhs;
    rhs = temp;
}

template <typename T>
struct linked_list
{
public:
    linked_list() = default;

    linked_list(const linked_list &other)
    {
        if (other.size == 0) { return; }

        for (size_t i = 0; i < other.size; i++) { push_back(other[i]); }
    }

    linked_list(linked_list &&other) noexcept
    {
        head = other.head;
        other.head->next = nullptr;

        size_ = other.size_;
        other.size_ = 0;
    }

    ~linked_list()
    {
        node<T> *temp;

        while (--size_)
        {
            temp = head->next;
            delete head;
            head = temp;
        }
    }

    bool empty()
    {
        return head == nullptr;
    }

    size_t size() const
    {
        return size_;
    }

    T &at(const size_t index) const
    {
        if (this->empty() || index > size_ - 1) { throw std::runtime_error("Array index out of bounds"); }

        int temp = index;
        auto p = head;

        while (temp--) { p = p->next; }
    }

    int find(T value_)
    {
        if (this->empty()) { throw std::runtime_error("Array index out of bounds"); }

        auto p = head;
        size_t index{ 0 };
        while (p && p->value != value_)
        {
            p = p->next;
            index++;
        }

        return (p && p->value == value_) ? index : -1;
    }

    void push_back(const T &item)
    {
        size_++;
        auto new_ = new node(item);
        if (this->empty())
        {
            head = tail = new_;
            return;
        }
        tail->next = new_;
        tail = new_;
    }

    T pop_back()
    {
        if (this->empty()) { throw std::runtime_error("Array index out of bounds"); }

        if (head == tail) { return this->pop_front(); }

        T temp;
        auto p = head;
        while (p->next != tail) { p = p->next; }

        p->next = nullptr;

        temp = tail->value;
        delete tail;
        tail = p;
        size_--;

        return temp;
    }

    T pop_front()
    {
        if (this->empty()) { throw std::runtime_error("Array index out of bounds"); }

        auto p = head;
        head = p->next;

        T temp{ p->value };
        delete p;

        return temp;
    }

    T &front()
    {
        if (this->empty()) { throw std::runtime_error("Array index out of bounds"); }
        return head->value;
    }

    T &back()
    {
        if (this->empty()) { throw std::runtime_error("Array index out of bounds"); }
        return tail->value;
    }

    void insert(const size_t index, const T &item) {}

    void remove(const T value_)
    {
        if (this->empty()) { throw std::runtime_error("Array index out of bounds"); }

        if (head->value == value_)
        {
            this->pop_front();
            return;
        }
        else if (tail->value == value_)
        {
            this->pop_back();
            return;
        }

        auto slow = head;
        auto fast = head->next;

        while (fast && fast->value != value_)
        {
            fast = fast->next;
            slow = slow->next;
        }

        if (!fast) { return; }

        slow->next = fast->next;
        delete fast;
    }

    void remove(const size_t index)
    {
        if (this->empty() || index > size_ - 1) { throw std::runtime_error("Array index out of bounds"); }
        if (index == 0)
        {
            this->pop_front();
            return;
        }

        auto slow = head;
        auto fast = head->next;

        size_t temp{ index - 1 };

        while (temp--)
        {
            slow = slow->next;
            fast = fast->next;
        }
        slow->next = fast->next;

        delete fast;

        size_--;
    }

    T &operator[](const size_t index)
    {
        if (this->empty() || index > size_ - 1) { throw std::runtime_error("Array index out of bounds"); }
        auto p = head;

        size_t temp{ index };
        while (temp--) { p = p->next; }

        return p->value;
    }

protected:
    node<T> *head{ nullptr }, *tail{ nullptr };
    size_t size_{ 0 };
};
}; // namespace structures

#endif // LINKED_LIST_HPP_INCLUDED
