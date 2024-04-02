#include <iostream>
using namespace std;

class DynamicArray {
private:
    int* data;
    int size;
    int bufer;

public:

    DynamicArray();
    DynamicArray(int bufer);
    ~DynamicArray();

    int get_elem(int index);
    void set_elem(int index, int value);
    void add(int value);

    void resize(int new_size);

};


DynamicArray::DynamicArray() {
    bufer = 5;
    size = 0;
    data = new int[bufer];
}


DynamicArray::DynamicArray(int start_bufer) {
    bufer = start_bufer;
    size = 0;
    data = new int[bufer];
}


DynamicArray::~DynamicArray() {
    delete[] data;
}


int DynamicArray::get_elem(int index) {
    return data[index];
}


void DynamicArray::set_elem(int index, int value) {
    data[index] = value;
}


void DynamicArray::add(int value) {
    if (size == bufer) {
        resize(bufer + 5);
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
    bufer = new_size;
}


int main() {
    DynamicArray arr(3);
    arr.set_elem(2, 5);
    std::cout << arr.get_elem(2) << std::endl;

    arr.add(22);
    arr.add(3);
    arr.add(128);

    arr.resize(5);

    arr.add(33);
    arr.add(28);

    return 0;
}