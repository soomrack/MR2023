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
    void resize();
    void add(int element);
    void setElement(size_t idx, int element);
    void arrayPrint();
    int getElement(size_t idx);
    size_t getSize();
};


DynamicArray::DynamicArray(size_t length) : size{ 0 }, container { length } {
    array = new int[container];
}


DynamicArray::~DynamicArray() {
    delete[] array;
    array = nullptr;
}


void DynamicArray::resize() {
    if (size == container) {
        container *= 2;
        int* newArray = new int[container];
        memcpy(newArray, array, size * sizeof(int));
        delete[] array;
        array = newArray;
    }
}


void DynamicArray::add(int element) {
    resize();
    array[size] = element;
    size += 1;
}


void DynamicArray::setElement(size_t idx, int element) {
    array[idx] = element;
}


void DynamicArray::arrayPrint() {
    for (size_t idx = 0; idx < size; idx++) {
        cout << array[idx] << "\t";
    }
    cout << "\n";
}


int DynamicArray::getElement(size_t idx) {
    if ((idx > 0) && (idx < size)) {
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
