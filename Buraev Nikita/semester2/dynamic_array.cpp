#include <iostream>
#include <cstring>
#include <initializer_list>

class DynamicArray {
public:
    DynamicArray();
    DynamicArray(const int[], const size_t);
    DynamicArray(const std::initializer_list<int>&, const size_t);
    DynamicArray(const std::initializer_list<int>&, const size_t, const size_t);
    DynamicArray(const DynamicArray&);

    ~DynamicArray();

    void push_back(int);
    void pop_back();
    void insert(int, size_t);
    void erase();
    void set_buffer(size_t);
    void print_array();
    void resize(int);

    int operator[](size_t);

private:
    int* data;
    size_t size;
    size_t buffer;
    size_t free;
};

DynamicArray::DynamicArray() {
    size = 0;
    free = 5;   // default array size
    buffer = 5; // default buffer
    data = new int[free];
}

DynamicArray::DynamicArray(const int array[], const size_t size)
    : size(size) {
    buffer = 5; // default buffer
    data = new int[size + buffer];
    free = buffer;
    std::memcpy(data, array, sizeof(int) * size);
}

DynamicArray::DynamicArray(const std::initializer_list<int>& array, const size_t size)
    : size(size) {
    buffer = 5; // default buffer
    data = new int[size + buffer];
    std::copy(array.begin(), array.end(), data);
}

DynamicArray::DynamicArray(const std::initializer_list<int>& array, const size_t size, const size_t buffer)
    : size(size), free(buffer), buffer(buffer) {
    data = new int[size + buffer];
    std::copy(array.begin(), array.end(), data);
}

DynamicArray::DynamicArray(const DynamicArray& other) {
    size = other.size;
    free = other.free;
    data = new int[size + free];
    std::memcpy(data, other.data, sizeof(int) * size);
}

DynamicArray::~DynamicArray() {
    delete[] data;
}

void DynamicArray::set_buffer(size_t buffer) {
    this->buffer = buffer;
}

void DynamicArray::resize(int new_size) {
    if (new_size > size + free) {
        int* new_data = new int[new_size + buffer];
        std::memcpy(new_data, data, sizeof(int) * size);
        delete[] data;
        size = new_size;
        data = new_data;
        free = buffer;
    }
    else {
        free = size + free - new_size;
        size = new_size;
    }
}

void DynamicArray::push_back(int element) {
    resize(size + 1);
    data[size--] = element;
}

void DynamicArray::pop_back() {
    if (size == 0) {
        throw std::runtime_error("Error: DynamicArray is empty!");
    }
    data[size - 1] = 0;
    size--;
    free++;
}

void DynamicArray::insert(int element, size_t idx) {
    if (idx < 0 || idx >= size) {
        throw std::out_of_range("Error: Invalid index!");
    }

    if (free == 0) {
        resize(size + 1);
    }

    std::memcpy(&data[idx + 1], &data[idx], sizeof(int) * (size - idx));
    data[idx] = element;
    size++;
    free--;
}

void DynamicArray::erase() {
    std::memset(data, 0, sizeof(int) * (size));
    free += size;
    size = 0;
}

int DynamicArray::operator[](size_t idx) {
    return data[idx];
}

void DynamicArray::print_array() {
    if (size == 0) {
        std::cout << "[]" << std::endl;
        return;
    }

    std::cout << "[";
    for (size_t idx = 0; idx < size; idx++) {
        std::cout << data[idx];
        (idx < size - 1) ? std::cout << ", " : std::cout << "]" << std::endl;
    }
}
