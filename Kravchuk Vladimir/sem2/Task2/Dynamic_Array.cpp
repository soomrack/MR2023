#include <iostream>

using namespace std;

class DynamicArray {
public:
    int* data;
    size_t size;
    size_t size_allocated;
private:
    size_t buf;
public:
    DynamicArray();
    DynamicArray(size_t size, size_t start_bufer);
    ~DynamicArray();
    void resize(size_t new_size);
    void add(int element);
    void set_element(size_t idx, int element);
    void array_print();
    int get_element(size_t idx);
    size_t get_size();
};


DynamicArray::DynamicArray() {
    buf = 5;
    size = 0;
    data = new int[buf];
}


DynamicArray::DynamicArray(size_t size, size_t start_bufer) : size{ size }, buf{ start_bufer } {
    data = new int[buf];
}


DynamicArray::~DynamicArray() {
    delete[] data;
}


void DynamicArray::resize(size_t new_size) {
    if (new_size > size_allocated) {
        size_allocated = new_size + buf;
        int* new_data = new int[size_allocated];
        memcpy(new_data, data, size * sizeof(int));
        delete[] data;
        data = new_data;
        size = new_size;
    }
    else {
        size = new_size;
    }
}


void DynamicArray::add(int element) {
    resize(size + 1);
    data[size] = element;
}


void DynamicArray::set_element(size_t idx, int element) {
    if (idx < size) {
        data[idx] = element;
    }
    else {
        cout << "The index of the element is invalid\n";
    }
}


void DynamicArray::array_print() {
    for (size_t idx = 0; idx < size; idx++) {
        cout << data[idx] << "\t";
    }
    cout << "\n";
}


int DynamicArray::get_element(size_t idx) {
    if (idx < size) {
        return data[idx];
    }
    else {
        cout << "The index of the element is invalid\n";
        return INT_MAX;
    }
}


size_t DynamicArray::get_size() {
    return size;
}


int main()
{
    DynamicArray array(3,3);
    array.set_element(2, 5);
    array.add(2);
    array.add(3);
    array.add(4);
    array.array_print();
    //array.get_element(-4);

    return 0;
}
