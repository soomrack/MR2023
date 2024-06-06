#include "array.hpp"

#include <cstring>

Array::Array(size_t size)
        : size(size), capacity(size + 5), data(new data_type[capacity]{}){};

Array::Array(size_t size, data_type value)
        : size(size)
        , capacity(size + 5)
        , data(new data_type[capacity]{value}) {}

Array::Array(std::initializer_list<data_type> list)
        : size(list.size())
        , capacity(size + 1)
        , data(new data_type[list.size()]) {
    std::copy(list.begin(), list.end(), data);
}

Array::Array(const Array& other)
        : size(other.size)
        , capacity(other.capacity)
        , data(new data_type[capacity]) {
    memcpy(data, other.data, size);
}

// Array::Array(data_type&& array) {}

Array::~Array() { delete[] data; }

void Array::reserve(size_t new_capacity) {
    if (new_capacity < capacity) {
        return;
    }
    data_type* new_data = new data_type[new_capacity];
    memcpy(new_data, data, size * sizeof(data_type));
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

void Array::resize(size_t new_size, data_type value = 0) {
    if (new_size < size) {
        size = new_size;
        return;
    }
    if (new_size > capacity) {
        reserve(2 * new_size);
    }
    for (size_t idx = size; idx < new_size; ++idx) {
        data[idx] = value;
    }
    size = new_size;
}

void Array::set(size_t idx, data_type value) {
    if (idx >= size) {
        // throw
    }
    data[idx] = value;
}

Array::data_type Array::at(size_t idx) {
    if (idx >= size) {
        // throw
    }
    return data[idx];
}