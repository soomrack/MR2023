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

namespace structures
{

template <typename T>
struct stack : private linked_list<T>
{
    stack() = default;

    void push(const T &value_)
    {
        this->push_back(value_);
    }

    T pop()
    {
        return this->pop_back();
    }

    T &top()
    {
        return this->back();
    };

    bool empty()
    {
        return this->size() == 0;
    };

    size_t size()
    {
        return this->size();
    };
}; // class stack

}; // namespace structures

#endif // STACK_HPP_INCLUDED
