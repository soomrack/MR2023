#include <iostream>
using namespace std;

class DynamicArray {
private:
    int* data;
    int size;
    int bufer;

public:

    DynamicArray();
    DynamicArray(size_t size, int start_bufer);
    ~DynamicArray();

    int get_elem(int index);
    void set_elem(int index, int value);
    void append(int value);

    void resize(int new_size);

};


DynamicArray::DynamicArray() {
    bufer = 5;
    size = 0;
    data = new int[bufer];
}


DynamicArray::DynamicArray(size_t size, int start_bufer) : size{ size }, bufer { start_bufer } {
    data = new int[bufer];
}


DynamicArray::~DynamicArray() {
    delete[] data;
}


int DynamicArray::get_elem(int index) {
    if (index >= 0 && index < size) {
        return data[index];
    }
    else {
        std::cerr << "Error: Index out of bounds\n";
        return -1;
    }
}


void DynamicArray::set_elem(int index, int value) {
    data[index] = value;
}


void DynamicArray::append(int value) {
    if (size == bufer) {
        resize(bufer + 1);
    }
    data[size++] = value;
}


void DynamicArray::resize(int new_size) {
    if (new_size > bufer + size) {
        int* new_data = new int[new_size];
        memcpy(new_data, data, size * sizeof(int));
        delete[] data;
        data = new_data;
        bufer = new_size;
    }
}


int main() {
    DynamicArray arr(3, 3);
    arr.set_elem(2, 5);
    std::cout << arr.get_elem(2) << std::endl;

    arr.append(22);
    arr.append(3);
    arr.append(128);

    arr.resize(5);

    arr.append(33);
    arr.append(28);

    return 0;
}