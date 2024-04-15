#include <iostream>

class DynamicArray {
private:
    int* data;
    size_t size;
    size_t buffer;

public:
    DynamicArray();
    explicit DynamicArray(size_t buffer);
    ~DynamicArray();

    int getElem(size_t index) const;
    void setElem(size_t index, int value);
    void add(int value);

    void resize(size_t new_size);
};

DynamicArray::DynamicArray() {
    buffer = 1;
    size = 0;
    data = new int[buffer];
}

DynamicArray::DynamicArray(size_t start_buffer) {
    buffer = start_buffer;
    size = 0;
    data = new int[buffer];
}

DynamicArray::~DynamicArray() {
    delete[] data;
}

int DynamicArray::getElem(size_t index) const {
    return data[index];
}

void DynamicArray::setElem(size_t index, int value) {
    data[index] = value;
}

void DynamicArray::add(int value) {
    if (size == buffer) {
        resize(buffer + 1);
    }
    data[size++] = value;
}

void DynamicArray::resize(size_t new_size) {
    if (new_size <= buffer) {
        buffer = new_size;
        return;
    }
    int* new_data = new int[new_size];
    for (size_t i = 0; i < size; i++) {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    buffer = new_size;
}

int main() {
    DynamicArray arr(3);
    arr.setElem(2, 5);
    std::cout << arr.getElem(2) << std::endl;

    arr.add(22);
    arr.add(3);
    arr.add(128);

    arr.resize(5);

    arr.add(33);
    arr.add(28);

    return 0;
}
