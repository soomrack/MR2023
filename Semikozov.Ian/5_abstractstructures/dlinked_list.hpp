/**
 * @file dlinked_other.hpp
 * @author Semikozov Ian (semikozov.yal@yandex.ru)
 * @brief
 * @version 0.1
 * @date 29.04.2024
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DLINKED_LIST_HPP_INCLUDED
#define DLINKED_LIST_HPP_INCLUDED

#include <cstddef>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <utility>

template <typename T>
struct doubly_linked_list
{
    doubly_linked_list() = default;
    doubly_linked_list(const doubly_linked_list &list);
    doubly_linked_list(doubly_linked_list &&list) noexcept;
    ~doubly_linked_list();

    T &operator[](const size_t index);
    friend std::ostream &operator<<(std::ostream &os, doubly_linked_list &list)
    {
        for (size_t idx = 0; idx < list.size_; idx++) { std::cout << list[idx] << "\t"; }
        std::cout << std::endl;
        return os;
    }

    template <typename U>
    friend void swap(doubly_linked_list<T> &lhs, doubly_linked_list<T> &rhs);

    size_t size() const;
    void push_back(const T &item);
    T pop_back();
    void push_head(const T &item);
    void pop_head();
    void insert(size_t index, const T &item);
    void remove(size_t index);

private:
    struct node
    {
        T data;
        node *next, *prev;
    };

private:
    node head{ 0, &tail, nullptr }, tail{ 0, nullptr, &head };
    size_t size_{ 0 };
}; // struct doubly_linked_list

template <typename U>
void swap(doubly_linked_list<U> &lhs, doubly_linked_list<U> &rhs)
{
    using std::swap;

    swap(lhs.head, rhs.head);
    swap(lhs.size_, rhs.size_);
    swap(lhs.tail, rhs.tail);
}

template <typename T>
doubly_linked_list<T>::doubly_linked_list(const doubly_linked_list &other)
{
    if (other.size == 0) { return; }

    for (size_t idx = 0; idx < other.size; idx++) { push_back(other.get(idx)); }
}

template <typename T>
doubly_linked_list<T>::doubly_linked_list(doubly_linked_list &&other) noexcept
{
    head = other.head;
    other.head.next = nullptr;
    other.head.prev = nullptr;

    tail = other.tail;
    other.tail.next = nullptr;
    other.tail.prev = nullptr;

    size_ = other.size;
    other.size = 0;
}

template <typename T>
doubly_linked_list<T>::~doubly_linked_list()
{
    while (size_--) { this->pop_back(); }
};
template <typename T>
T &doubly_linked_list<T>::operator[](const size_t index)
{
    if (index >= size_) { throw std::runtime_error("Memory bound of array"); }

    auto *item = head.next;

    size_t item_index = index + 1;
    while (--item_index) { item = item->next; }

    return item->data;
}

template <typename T>
size_t doubly_linked_list<T>::size() const
{
    return size_;
}

template <typename T>
void doubly_linked_list<T>::push_back(const T &value)
{
    auto *item_prev = tail.prev;

    tail.prev = new node{ value, &tail, item_prev };
    item_prev->next = tail.prev;

    size_++;
}

template <typename T>
T doubly_linked_list<T>::pop_back()
{
    if (size_ == 0) { throw std::runtime_error("Pop from empty list."); }

    auto *item_prev = tail.prev;

    item_prev->prev->next = &tail;
    tail.prev = item_prev->prev;
    node temp{ *item_prev };
    delete item_prev;

    size_--;
    return temp.data;
}

template <typename T>
void doubly_linked_list<T>::push_head(const T &value)
{
    auto *item_next = head.next;

    head.next = new node{ value, item_next, &head };
    item_next->prev = head.next;

    size_++;
}

template <typename T>
void doubly_linked_list<T>::pop_head()
{
    if (size_ == 0) { return; }

    auto *item_next = head.next;

    item_next->next->prev = &head;
    head.next = item_next->next;

    delete item_next;

    size_--;
}

template <typename T>
void doubly_linked_list<T>::insert(size_t index, const T &value)
{
    if (index >= size_) { throw std::runtime_error("Memory bound of array"); }

    auto *item = head.next;

    size_t item_index = index + 1;
    while (--item_index) { item = item->next; }

    auto *item_prev = item->prev;

    item_prev->next = new node{ value, item, item_prev };
    item->prev = item_prev->next;

    size_++;
}

template <typename T>
void doubly_linked_list<T>::remove(size_t index)
{
    if (index >= size_) { throw std::runtime_error("Memory bound of array"); }

    auto *item = head.next;

    size_t item_index = index + 1;
    while (--item_index) { item = item->next; }

    auto *item_prev = item->prev, *item_next = item->next;

    item_prev->next = item_next;
    item_next->prev = item_prev;
    delete item;

    size_--;
}

#endif // DLINKED_LIST_HPP_INCLUDED
