#include <iostream>
using namespace std;

class Dynamic_Array {
private:
    int* data;
    size_t size;
    size_t size_allocated

public:
    size_t bufer = 10;

public:
    Dynamic_Array();
    Dynamic_Array(size_t size, size_t bufer);
    ~Dynamic_Array();

    int get_element(size_t index);
    void set_element(size_t index, int value);
    void add (int value);
    void resize(size_t new_size);
};


Dynamic_Array::Dynamic_Array() : size{ 0 }, size_allocated{ 0 }, bufer{ 0 } 
{
    data = nullptr;
}


Dynamic_Array::Dynamic_Array(size_t size, size_t bufer) : size{ size }, bufer { bufer } 
{
    size_allocated = size + bufer;
    data = new size_t[size_allocated];
}


Dynamic_Array::~Dynamic_Array() {
    delete[] data;
}


int Dynamic_Array::get_element(size_t index) {
    if (index >= 0 && index < size) {
        return data[index];
    }
        std::cerr << "Error: Index out of bounds\n";
        return 0;
}


void Dynamic_Array::set_element(size_t index, int value) {
    data[index] = value;
    if (size < index) {
        return 0;
    }
}


void Dynamic_Array::append(int value) {
    if (size == bufer) {
        resize(bufer + 1);
    }
    data[size - 1] = value;
}


void Dynamic_Array::resize(size_t new_size) {
    if (new_size > bufer + size) {
        int* new_data = new size_t[new_size];
        memcpy(new_data, data, size * sizeof(size_t));
        delete[] data;
        data = new_data;
        bufer = new_size;
        return 0;
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