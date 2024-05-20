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

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <utility>

template <typename T>
struct array
{
public:
    array() = default;
    array(array &other);
    array(array &&other);
    array(size_t size_);
    array &operator=(array other);

    ~array();

    T &operator[](const size_t idx);
    const T &operator[](const size_t idx) const;

    template <typename U>
    friend void swap(array &lhs, array &rhs);

    size_t size();
    size_t capacity();

    void append(const T &value);
    void append(T &&value);
    void insert(const size_t idx, const T &value);
    void clear();
    T pop_back();
    void reserve(const size_t capacity_);
    void shrink_to_fit();
    void resize(const size_t count);
    void resize(const size_t count, const T &value);
    void erase(const size_t idx);
    void erase(const size_t first, size_t last);
    T &front();
    T &back();

protected:
    size_t size_{ 0 }, capacity_{ 0 };
    T *data{ nullptr };
}; // class array

template <typename u>
void swap(array<u> &rhs, array<u> &lhs)
{
    using std::swap;

    swap(lhs.data, rhs.data);
    swap(lhs.capacity_, rhs.capacity_);
    swap(lhs.size_, rhs.capacity_);
}

template <typename T>
array<T>::array(size_t size_) : size_{ size_ }
{
    this->reserve(size_);
}

template <typename T>
array<T>::array(array<T> &other) : size_{ other.size_ }
                                 , capacity_{ other.capacity_ }
                                 , data{ new T[capacity_] }
{
    std::memcpy(data, other.data, size_ * sizeof(T));
}

template <typename T>
array<T>::array(array<T> &&other) : size_{ other.size_ }
                                  , capacity_{ other.capacity_ }
                                  , data{ other.data }
{
    other.data = nullptr;
    other.size_ = 0;
    other.size = 0;
}

template <typename T>
array<T>::~array()
{
    delete[] data;
}

template <typename T>
array<T> &array<T>::operator=(array<T> other)
{
    swap(*this, other);
    return *this;
}

template <typename T>
const T &array<T>::operator[](const size_t idx) const
{
    return data[idx];
}

template <typename T>
void array<T>::reserve(const size_t capacity)
{
    if (capacity == 0) { reserve(1); }
    if (capacity <= capacity_) { return; }

    T *new_data = new T[capacity];
    std::memcpy(new_data, data, size_ * sizeof(T));
    capacity_ = capacity;

    delete[] data;
    data = new_data;
}

template <typename T>
void array<T>::append(const T &value)
{
    if (size_ == capacity_) { reserve(2 * capacity_); }

    T *new_last = &data[size_];
    *new_last = value;
    size_++;
}

template <typename T>
void array<T>::append(T &&value)
{
    if (size_ == capacity_) { reserve(2 * capacity_); }
    T *new_last = &data[size_];
    *new_last = std::move(value);
    size_++;
}

template <typename T>
void array<T>::insert(const size_t idx, const T &value)
{
    if (idx >= size_) { return push_back(value); }
    if (size_ == capacity_) { reserve(2 * capacity_); }
    T *current_element = data[0] + idx;
    std::copy(current_element, &data[size_], current_element + 1);
    *current_element = value;
    size_++;
}

template <typename T>
T array<T>::pop_back()
{
    if (size_ == 0) { throw std::runtime_error("Pop from empty container."); }

    T last = back();
    size_--;
    return last;
}

template <typename T>
void array<T>::shrink_to_fit()
{
    T *new_arr = new T[size_];
    std::copy(data, &data[size_], new_arr);
    delete[] data;
    data = new_arr;
    capacity_ = size_;
}

template <typename T>
void array<T>::resize(const size_t count)
{
    if (count > size_) { throw std::runtime_error("Bad resize overload."); }
    if (count == size_) { return; }

    T *new_arr = new T[count];
    std::copy(data, data + count, new_arr);
    delete[] data;
    data = new_arr;
    size_ = count;
    capacity_ = count;
}

template <typename T>
void array<T>::resize(const size_t count, const T &value)
{
    if (count <= size_) { throw std::runtime_error("Bad resize overload."); }
    if (size_ + count > capacity_) { reserve((size_ + count)); }

    for (size_t idx = 0; idx < count; ++idx) { push_back(value); }
}

template <typename T>
void array<T>::erase(const size_t idx)
{
    if (idx >= size_) { throw std::runtime_error("Bad erase index."); }

    std::copy(data + idx + 1, &data[size_], data + idx);
    size_--;
}

template <typename T>
void array<T>::erase(const size_t first, const size_t last)
{
    if (first >= size_ || last >= size_) { throw std::runtime_error("Bad erase indexes."); }
    if (first == last) { return erase(last); }

    std::copy(data + last + 1, &data[size_], data + first);
    size_ -= (last - first + 1);
}

template <typename T>
void array<T>::clear()
{
    size_ = 0;
}

template <typename T>
T &array<T>::front()
{
    return data[0];
}

template <typename T>
T &array<T>::back()
{
    return data[size_ - 1];
}

#endif // DYNAMIC_ARRAY_HPP_INCLUDED
