#include <iostream>

using namespace std;

class DynamicArray {
private:
    int* array;
    size_t size;
    size_t container;

public:
    DynamicArray(size_t length);
    ~DynamicArray();
    void resize(size_t new_size);
    void add(int element);
    void set_element(size_t idx, int element);
    void array_print();
    int get_element(size_t idx);
    size_t get_size();
};


DynamicArray::DynamicArray(size_t length) : size{ 0 }, container { length } {
    if (length == 0) {
        array = nullptr;
    }
    array = new int[container];
}


DynamicArray::~DynamicArray() {
    delete[] array;
    array = nullptr;
}


void DynamicArray::resize(size_t new_size) {
    if (new_size > container) {
        container = new_size;
        int* new_array = new int[container];
        memcpy(new_array, array, size * sizeof(int));
        delete[] array;
        array = new_array;
    }
}


void DynamicArray::add(int element) {
    resize(size + 1);
    array[size] = element;
    size += 1;
}


void DynamicArray::set_element(size_t idx, int element) {
    if (idx < size) {
        array[idx] = element;
    }
    else {
        cout << "The index of the element is invalid\n";
    }
}


void DynamicArray::array_print() {
    for (size_t idx = 0; idx < size; idx++) {
        cout << array[idx] << "\t";
    }
    cout << "\n";
}


int DynamicArray::get_element(size_t idx) {
    if (idx < size) {
        return array[idx];
    }
    else {
        cout << "The index of the element is invalid\n";
        return NAN;
    }
}


size_t DynamicArray::get_size() {
    return size;
}


int main()
{
    DynamicArray array(4);
    array.add(2);
    array.add(3);
    array.add(4);
    array.add(6);
    array.array_print();
    array.get_element(-4);

    return 0;
}
