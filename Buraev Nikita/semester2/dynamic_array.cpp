#include <iostream>

class DynamicArray {
private:
    int* data;
    int size;
    int buffer;

public:
    DynamicArray();
    explicit DynamicArray(int buffer);
    ~DynamicArray();

    int getElem(int index) const;
    void setElem(int index, int value);
    void add(int value);

    void resize(int new_size);
};

DynamicArray::DynamicArray() {
    buffer = 5;
    size = 0;
    data = new int[buffer];
}

DynamicArray::DynamicArray(int start_buffer) {
    buffer = start_buffer;
    size = 0;
    data = new int[buffer];
}

DynamicArray::~DynamicArray() {
    delete[] data;
}

int DynamicArray::getElem(int index) const {
    return data[index];
}

void DynamicArray::setElem(int index, int value) {
    data[index] = value;
}

void DynamicArray::add(int value) {
    if (size == buffer) {
        resize(buffer + 5);
    }
    data[size++] = value;
}

void DynamicArray::resize(int new_size) {
    int* new_data = new int[new_size];
    for (int i = 0; i < size; i++) {
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
