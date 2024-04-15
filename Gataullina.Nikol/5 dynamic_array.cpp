#include <iostream>
using namespace std;

class Dynamic_Array {
private:
    int* data;
    size_t size;
    size_t size_allocated;

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


Dynamic_Array::Dynamic_Array(size_t size, size_t bufer) : size{ size }, bufer{ bufer }
  {
     size_allocated = size + bufer;
     if (size_allocated == 0) {
         data = nullptr;
     }
     else {
         data = new int[size_allocated];
        }
    }
}


Dynamic_Array::~Dynamic_Array() {
    delete[] data;
}


int Dynamic_Array::get_element(size_t index) {
    if (index < size) {
        return data[index];
    }
        std::cerr << "Error: Index out of bounds\n";
        return 0;
}


int Dynamic_Array::set_element(size_t index, int value) {
    if (index >= size) {
        return -1;
    }
    data[index] = value;
    return 0;
}



void Dynamic_Array::append(int value) {
    if (size == size_allocated) {
        resize(bufer + 1);
    }
    data[size - 1] = value;
}


void Dynamic_Array::resize(size_t new_size) {
    if (new_size > size_allocated) {
        int* new_data = new int[new_size];
        memcpy(new_data, data, size * sizeof(int));
        delete[] data;
        data = new_data;
        size_allocated = new_size + bufer;
    }
    else {
        size = new_size;
        bufer = size_allocated - size;
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