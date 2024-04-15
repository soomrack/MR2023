#include <iostream>

class DynamicArray {
private:
    int* buffer; //memory space dynamically allocated
    int size; //number of elements currently in use
    int allocatedSize; //size of the memory space allocated (buffer)

public:
    DynamicArray();
    explicit DynamicArray(int initialAllocatedSize);
    ~DynamicArray();

    int getElem(int index) const;
    void setElem(int index, int value);
    void add(int value);

    void resize(int newSize);
};

DynamicArray::DynamicArray() {
    allocatedSize = 1;
    size = 0;
    buffer = new int[allocatedSize];
}

DynamicArray::DynamicArray(int initialAllocatedSize) {
    allocatedSize = initialAllocatedSize;
    size = 0;
    buffer = new int[allocatedSize];
}

DynamicArray::~DynamicArray() {
    delete[] buffer;
}

int DynamicArray::getElem(int index) const {
    return buffer[index];
}

void DynamicArray::setElem(int index, int value) {
    buffer[index] = value;
}

void DynamicArray::add(int value) {
    if (size == allocatedSize) {
        resize(allocatedSize + 5);
    }
    buffer[size++] = value;
}

void DynamicArray::resize(int newSize) {
    int* newBuffer = new int[newSize];
    for (int i = 0; i < size; i++) {
        newBuffer[i] = buffer[i];
    }
    delete[] buffer;
    buffer = newBuffer;
    allocatedSize = newSize;
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
