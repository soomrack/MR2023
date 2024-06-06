#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <ostream>

class Array
{
    using data_type = uint32_t;

private:
    size_t size{0};
    size_t capacity{0};
    data_type* data{nullptr};

public:
    Array() = default;
    Array(size_t size);
    Array(size_t size, data_type value);
    Array(std::initializer_list<data_type> list);
    Array(const Array& other);
    Array(data_type&& array);  // TODO
    ~Array();

    void reserve(size_t new_capacity);
    void resize(size_t new_size, data_type value);
    void set(size_t idx, data_type value);
    data_type at(size_t idx);

    size_t get_size() const { return size; }
    size_t get_capacity() const { return capacity; }

    friend std::ostream& operator<<(std::ostream& os, const Array& array) {
        for (size_t idx = 0; idx < array.size; ++idx) {
            os << array.data[idx] << " ";
        }
        os << std::endl;
        return os;
    }
};