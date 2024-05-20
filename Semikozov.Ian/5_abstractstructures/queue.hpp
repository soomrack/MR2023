/**
 * @file queue.hpp
 * @author Semikozov Ian (semikozov.yal@yandex.ru)
 * @brief
 * @version 0.1
 * @date 29.04.2024
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef QUEUE_HPP_INCLUDED
#define QUEUE_HPP_INCLUDED

#include "linked_list.hpp"
#include <cstddef>

template <typename T>
struct queue : private linked_list<T>
{
public:
    queue() = default;
    ~queue();

    T &front();
    T &back();

    bool empty();
    size_t size();
    void push(const T &value_);
    void emplace();
    T pop();
}; // struct queue

template <typename T>
static void swap(queue<T> &lhs, queue<T> &rhs) noexcept
{
    queue<T> temp = lhs;
    lhs = rhs;
    rhs = temp;
}

template <typename T>
queue<T>::~queue()
{}

template <typename T>
T &queue<T>::front()
{
    return linked_list<T>::front();
}

template <typename T>
T &queue<T>::back()
{
    return linked_list<T>::back();
}

template <typename T>
bool queue<T>::empty()
{
    return linked_list<T>::empty();
}

template <typename T>
size_t queue<T>::size()
{
    return linked_list<T>::size();
}

template <typename T>
void queue<T>::push(const T &value_)
{
    return linked_list<T>::push_back(value_);
}

template <typename T>
T queue<T>::pop()
{
    return linked_list<T>::pop_back();
}

#endif // QUEUE_HPP_INCLUDED
