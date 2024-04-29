/**
 * @file container_base.hpp
 * @author Semikozov Ian (semikozov.yal@yandex.ru)
 * @brief
 * @version 0.1
 * @date 29.04.2024
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef CONTAINER_BASE_HPP_INCLUDED
#define CONTAINER_BASE_HPP_INCLUDED

#include <cstddef>

namespace structures
{

template <typename T>
class container
{
public:
    container() = default;
    container(size_t size)
    {
        data = new T[size];
    }

    virtual ~container()
    {
        if (data) { delete[] data; }
    }

private:
    size_t size;
    T *data{ nullptr };

}; // class container

}; // namespace structures

#endif // CONTAINER_BASE_HPP_INCLUDED
