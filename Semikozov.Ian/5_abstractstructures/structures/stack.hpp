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

#include "container_base.hpp"

namespace structures
{

template <typename T>
struct stack : container<T>
{
    stack();
    ~stack() override;
}; // class stack

}; // namespace structures

#endif // STACK_HPP_INCLUDED
