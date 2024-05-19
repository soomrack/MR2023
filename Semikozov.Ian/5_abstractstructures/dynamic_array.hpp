/**
 * @file dynamic_array.hpp
 * @author Semikozov Ian (semikozov.yal@yandex.ru)
 * @brief
 * @version 0.1
 * @date 29.04.2024
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DYNAMIC_ARRAY_HPP_INCLUDED
#define DYNAMIC_ARRAY_HPP_INCLUDED

#include <cstddef>
namespace structures
{
template <typename T>
class array
{
    array(size_t size_);
    array(array &other);
    array(array &&other);

    void append(const T value_);
}; // class array
}; // namespace structures

#endif // DYNAMIC_ARRAY_HPP_INCLUDED
