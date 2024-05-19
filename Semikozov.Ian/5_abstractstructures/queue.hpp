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

namespace structures
{
template <typename T>
struct queue : private linked_list<T>
{
    queue() = default;
    ~queue(){};

    T &front() {}
    T &back() {}

    bool empty() {}
    size_t size() {}
    void push(const T &value_) {}
    void emplace() {}
    T pop() {}

}; // struct queue

template <typename T>
static void swap(queue<T> &lhs, queue<T> &rhs) noexcept
{
    queue<T> temp = lhs;
    lhs = rhs;
    rhs = temp;
}

}; // namespace structures

#endif // QUEUE_HPP_INCLUDED
