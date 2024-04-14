#include <iostream>
using namespace std;

class Dynamic_Array {
private:
    int* data;
    int size;
    int bufer;

public:
    Dynamic_Array();
    Dynamic_Array(size_t size, int start_bufer);
    ~Dynamic_Array();

    int get_element(int index);
    void set_element(int index, int value);
    void add (int value);
    void resize(int new_size);
};


Dynamic_Array::Dynamic_Array() {
    bufer = 5;
    size = 0;
    data = new int[bufer];
}


Dynamic_Array::Dynamic_Array(size_t size, int start_bufer) : size{ size }, bufer { start_bufer } {
    data = new int[bufer];
}


Dynamic_Array::~Dynamic_Array() {
    delete[] data;
}


int Dynamic_Array::get_element(int index) {
    if (index >= 0 && index < size) {
        return data[index];
    }
    else {
        std::cerr << "Error: Index out of bounds\n";
        return -1;
    }
}


void Dynamic_Array::set_element(int index, int value) {
    data[index] = value;
}


void Dynamic_Array::add(int value) {
    if (size == bufer) {
        resize(bufer + 1);
    }
    data[size++] = value;
}


void Dynamic_Array::resize(int new_size) {
    if (new_size > bufer + size) {
        int* new_data = new int[new_size];
        memcpy(new_data, data, size * sizeof(int));
        delete[] data;
        data = new_data;
        bufer = new_size;
    }
    else {
        size += 1;
        bufer -= 1;
    }
}


int main() {
    Dynamic_Array arr(3, 3);
    arr.set_element(2, 5);
    std::cout << arr.get_element(2) << std::endl;

    arr.add(22);
    arr.add(3);
    arr.add(128);

    arr.resize(5);

    arr.add(33);
    arr.add(28);

    return 0;
}