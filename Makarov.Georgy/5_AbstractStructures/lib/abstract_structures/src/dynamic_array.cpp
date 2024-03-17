#include "dynamic_array.h"


DynamicArray::DynamicArray(size_t size_, size_t buffer_size_) {
    if (size_ == 0 || buffer_size_ == 0)
        throw DynamicArrayException("Cannot create empty array");  // or return;

    size = size_;
    buffer_size = buffer_size_;

    data = new dtype[size + buffer_size];
}

DynamicArray::DynamicArray(const DynamicArray &array) {
    if (array.size == 0 || array.buffer_size == 0 || array.data == nullptr)
        throw DynamicArrayException("Cannot copy empty array");  // or return;

    size = array.size;
    buffer_size = array.buffer_size;

    data = new dtype[size + buffer_size];
    std::copy(array.data, array.data + size, data);
}

DynamicArray::DynamicArray(DynamicArray &&array) noexcept {
    size = array.size;
    buffer_size = array.buffer_size;
    array.size = 0;
    array.buffer_size = 0;

    data = array.data;
    array.data = nullptr;
}

DynamicArray::~DynamicArray() {
    size = 0;
    buffer_size = 0;

    delete[] data;
}

dtype DynamicArray::get(size_t index) {
    if (index >= size)
        throw DynamicArrayException("Index out of range");

    return data[index];
}

void DynamicArray::set(size_t index, dtype item) {
    if (index >= size + buffer_size)
        throw DynamicArrayException("Index out of buffer range");

    if (index >= size) {
        buffer_size += size - index - 1;
        size = index + 1;
    }

    data[index] = item;
}

void DynamicArray::resize(size_t new_size, size_t new_buffer_size) {
    if (new_size == 0 || new_buffer_size == 0)
        throw DynamicArrayException("Cannot resize to empty array");  // or return;

    if (new_size + new_buffer_size <= size + buffer_size) {
        if (new_size < size)
            for (size_t idx = new_size; idx < size; idx++)
                data[idx] = 0;
    } else {
        auto *new_data = new dtype[new_size + new_buffer_size];
        std::copy(data, data + size, new_data);

        delete[] data;
        data = new_data;
        for (size_t idx = size; idx < new_size - 1; idx++)
            data[idx] = 0;
    }

    size = new_size;
    buffer_size = new_buffer_size;
}

void DynamicArray::print() {
    for (size_t idx = 0; idx < size; idx++)
        std::cout << data[idx] << "\t";
    std::cout << "\n \n";
}