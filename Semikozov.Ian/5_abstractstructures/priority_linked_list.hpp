/**
 * @file priority_linked_other.hpp
 * @author Semikozov Ian (semikozov.yal@yandex.ru)
 * @brief
 * @version 0.1
 * @date 20.05.2024
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef PRIORITY_LINKED_LIST_HPP_INCLUDED
#define PRIORITY_LINKED_LIST_HPP_INCLUDED

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <stdexcept>

namespace
{

using priority = uint8_t;

template <typename T>
struct node
{
    T data;
    priority priority_;
    node *next;

    node() = delete;

    node(const T &data_, priority priority_, node *next_) : data{ data_ }, priority_{ priority_ }, next{ next_ } {};
    void push_back(const T &data_, priority priority_)
    {
        next = new node{ data_, priority_, next };
    };

    void pop_back()
    {
        if (next != nullptr) { next = next->next; }
    };
}; // struct node

}; // namespace

template <typename T>
struct priority_linked_list
{
protected:
    node<T> head{ 0, 20, nullptr }, *tail{ &head };
    size_t size_{ 0 };

public:
    priority_linked_list() = default;
    priority_linked_list(const priority_linked_list &other);
    priority_linked_list(priority_linked_list &&other) noexcept;
    ~priority_linked_list();

    T &operator[](size_t index) const;
    friend std::ostream &operator<<(std::ostream &os, priority_linked_list &list)
    {
        for (size_t idx = 0; idx < list.size_; idx++) { os << list[idx] << " "; }
        os << std::endl;
    }

    size_t size() const;
    priority get_priority(size_t index) const;
    void push_back(const T &item, uint8_t priority = 20);
    void push_priority(const T &item, uint8_t priority = 20);
    void pop_back();
    void insert(size_t index, const T &item, priority priority);
    void remove(size_t index);
};

template <typename T>
priority_linked_list<T>::priority_linked_list(const priority_linked_list<T> &other)
{
    if (other.size_ == 0) { return; }

    for (size_t idx = 0; idx < other.size_; idx++) { push_back(other[idx], other.get_priority(idx)); }
}

template <typename T>
priority_linked_list<T>::priority_linked_list(priority_linked_list<T> &&other) noexcept
{
    head = other.head;
    other.head.next = nullptr;

    size_ = other.size_;
    other.size_ = 0;
}

template <typename T>
T &priority_linked_list<T>::operator[](size_t index) const
{
    if (index > size_ - 1) { throw std::runtime_error("Array index out of bounds"); }

    auto *item = head.next;

    size_t item_index = index + 1;
    while (--item_index) { item = item->next; }

    return item->data;
}

template <typename T>
priority priority_linked_list<T>::get_priority(size_t index) const
{
    if (index >= size_) { throw std::runtime_error("Array index out of bounds"); }

    auto *item = head.next;

    size_t item_index = index + 1;
    while (--item_index) { item = item->next; }

    return item->priority;
}

template <typename T>
void priority_linked_list<T>::push_back(const T &data, priority priority)
{
    tail->push_back(data, priority);
    tail = tail->next;

    size_++;
}

template <typename T>
void priority_linked_list<T>::push_priority(const T &data, priority priority)
{
    auto *current = &head, *next_item = head.next;

    while (next_item != nullptr && next_item->priority <= priority)
    {
        current = next_item;
        next_item = next_item->next;
    }

    current->push_back(data, priority);
    size_++;
}

template <typename T>
void priority_linked_list<T>::pop_back()
{
    if (size_ == 0) { return; }

    auto *item = &head;

    size_t item_index = size_ - 1;
    while (item_index--) { item = item->next; }

    item->pop_back();

    size_--;
}

template <typename T>
void priority_linked_list<T>::insert(size_t index, const T &data, priority priority)
{
    if (index >= size_) { throw std::runtime_error("Array index out of bounds"); }

    auto *item = &head;

    size_t item_index = index;
    while (item_index--) { item = item->next; }

    item->push_back(data, priority);

    size_++;
}

template <typename T>
void priority_linked_list<T>::remove(size_t index)
{
    if (index >= size_) { throw std::runtime_error("Array index out of bounds"); }

    auto *item = &head;

    size_t item_index = index;
    while (item_index--) { item = item->next; }

    item->pop_back();

    size_--;
}

#endif // PRIORITY_LINKED_LIST_HPP_INCLUDED
