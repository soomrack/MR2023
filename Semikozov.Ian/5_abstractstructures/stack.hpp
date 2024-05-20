/**
 * @file stack.hpp
 * @author Semikozov Ian (semikozov.yal@yandex.ru)
 * @brief
 * @version 0.1
 * @date 29.04.2024
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef STACK_HPP_INCLUDED
#define STACK_HPP_INCLUDED

#include "linked_list.hpp"

template <typename T>
struct stack : private linked_list<T>
{
    stack() = default;

    void push(const T &value_)
    {
        linked_list<T>::push_back(value_);
    }

    T pop()
    {
        return linked_list<T>::pop_back();
    }

    T &top()
    {
        return linked_list<T>::back();
    };

    bool empty()
    {
        return linked_list<T>::empty();
    };

    size_t size()
    {
        return linked_list<T>::size();
    };
}; // struct stack

#endif // STACK_HPP_INCLUDED
