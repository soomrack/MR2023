/**
 * @file priority_queue.hpp
 * @author Semikozov Ian (semikozov.yal@yandex.ru)
 * @brief
 * @version 0.1
 * @date 19.05.2024
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef PRIORITY_QUEUE_HPP_INCLUDED
#define PRIORITY_QUEUE_HPP_INCLUDED

#include <cstddef>
#include <cstdint>

#include "dynamic_array.hpp"

namespace
{

using priority = uint8_t;

template <typename T>
struct pq_node
{
    pq_node(const T &value, const priority pr = -1);
    pq_node() = default;
    ~pq_node() = default;
    pq_node<T> &operator=(const T &value);

    T data{ 0 };
    priority _pr;
}; //  struct pq_node

template <typename T>
pq_node<T>::pq_node(const T &value, const priority pr) : _pr{ pr }
                                                       , data{ value }
{}

template <typename T>
pq_node<T> &pq_node<T>::operator=(const T &value)
{
    data = value;
}

}; // namespace

template <typename T>
struct priority_queue : private array<pq_node<T>>
{
    using initializer_pq_node = std::pair<T, priority>;

    friend std::ostream &operator<<(std::ostream &os, const priority_queue<T> &obj)
    {
        return os << static_cast<const array<T> &>(obj);
    }

public:
    priority_queue() = default;
    priority_queue(const T &value, priority pr);
    priority_queue(priority_queue<T> &copy);
    priority_queue(priority_queue<T> &&copy_rvalue);
    priority_queue<T> &operator=(priority_queue<T> &other);

    ~priority_queue() = default;

    inline size_t size()
    {
        return array<pq_node<T>>::size();
    }

    inline bool empty()
    {
        return array<pq_node<T>>::size() == 0;
    }

    const T &top();
    void push(const T &value, const priority pr);
    T pop();
    void clear();

private:
    void sort_priority();
}; //  struct priority_queue

template <typename T>
priority_queue<T>::priority_queue(const T &value, priority pr)
{
    push(value, pr);
}

template <typename T>
void priority_queue<T>::push(const T &value, const uint8_t pr)
{
    array<pq_node<T>>::append(pq_node<T>{ value, pr });
    sort_priority();
}

template <typename T>
void priority_queue<T>::sort_priority()
{
    auto end = array<pq_node<T>>::size_;
    std::sort(array<pq_node<T>>::data, &array<pq_node<T>>::data[end], [](pq_node<T> &lhs, pq_node<T> &rhs) { return lhs._pr < rhs._pr; });
}

template <typename T>
const T &priority_queue<T>::top()
{
    return array<pq_node<T>>::data[0].data;
}

template <typename T>
T priority_queue<T>::pop()
{
    if (2 * array<pq_node<T>>::size_ <= array<pq_node<T>>::capacity_) { array<pq_node<T>>::shrink_to_fit(); }
    pq_node<T> data = array<pq_node<T>>::data[0];
    array<pq_node<T>>::erase(0);

    return data.data;
}

template <typename T>
void priority_queue<T>::clear()
{
    array<pq_node<T>>::clear();
}

template <typename T>
priority_queue<T>::priority_queue(priority_queue<T> &other) : array<pq_node<T>>(other)
{}

template <typename T>
priority_queue<T>::priority_queue(priority_queue<T> &&other)
    : array<pq_node<T>>::data{ other.data }
    , array<pq_node<T>>::size_{ other.size_ }
    , array<pq_node<T>>::capacity_{ other.capacity_ }
{
    other.data = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

template <typename T>
priority_queue<T> &priority_queue<T>::operator=(priority_queue<T> &other)
{
    swap(*this, other);

    return *this;
}

#endif // PRIORITY_QUEUE_HPP_INCLUDED
