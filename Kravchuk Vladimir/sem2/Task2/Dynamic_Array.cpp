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
    void resize(size_t dop_size);
    void add(int element);
    void setElement(size_t idx, int element);
    void arrayPrint();
    int getElement(size_t idx);
    size_t getSize();
};


DynamicArray::DynamicArray(size_t length) : size{ 0 }, container { length } {
    if (length == 0) {
        exit(1);
    }
    array = new int[container];
}


DynamicArray::~DynamicArray() {
    delete[] array;
    array = nullptr;
}


void DynamicArray::resize(size_t dop_size) {
    if (size == container) {
        container += dop_size;
        int* newArray = new int[container];
        memcpy(newArray, array, size * sizeof(int));
        delete[] array;
        array = newArray;
    }
    size += 1;
}


void DynamicArray::add(int element) {
    resize(1);
    array[size - 1] = element;
}


void DynamicArray::setElement(size_t idx, int element) {
    if ((idx >= 0) && (idx < size)) {
        array[idx] = element;
    }
    else {
        cout << "The index of the element is invalid\n" << endl;
    }
}


void DynamicArray::arrayPrint() {
    for (size_t idx = 0; idx < size; idx++) {
        cout << array[idx] << "\t";
    }
    cout << "\n";
}


int DynamicArray::getElement(size_t idx) {
    if ((idx >= 0) && (idx < size)) {
        return array[idx];
    }
    else {
        cout << "The index of the element is invalid\n" << endl;
        return NAN;
    }
}


size_t DynamicArray::getSize() {
    return size;
}


int main()
{
    DynamicArray array(4);
    array.add(2);
    array.add(3);
    array.add(4);
    array.add(6);
    array.arrayPrint();
    array.getElement(-4);

    return 0;
}
