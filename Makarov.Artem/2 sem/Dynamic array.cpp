#include <iostream>
#include <cstdlib>
#include <ctime>

class DynamicArray {
private:
    int* arr; 
    int size;

public:
    DynamicArray();

    ~DynamicArray();

    void add(int value, int index);

    void fillRandom(int n);

    void remove(int index);

    void print();

    void resize(int n);

    void clear();
};


DynamicArray::DynamicArray() {
    arr = nullptr;
    size = 0;
}


DynamicArray::~DynamicArray() {
    delete[] arr;
}


void DynamicArray::fillRandom(int n) {
    srand(time(nullptr));
    arr = new int[n];

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    size = n;
}


void DynamicArray::add(int value, int index) {
    int* temp = new int[size + 1]; 

    for (int i = 0; i < index; i++) {
        temp[i] = arr[i]; 
    }

    temp[index] = value;

    for (int i = index + 1; i < size + 1; i++) {
        temp[i] = arr[i - 1];
    }

    delete[] arr;
    arr = temp;
    size++;
}


void DynamicArray::remove(int index) {
    int* temp = new int[size - 1]; 

    for (int i = 0; i < index; i++) {
        temp[i] = arr[i];
    }

    for (int i = index + 1; i < size; i++) {
        temp[i - 1] = arr[i];
    }

    delete[] arr;
    arr = temp;
    size--;
}


void DynamicArray::print() {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;
}


void DynamicArray::resize(int n) {
    int* temp = new int[n];
    int minSize = (size < n) ? size : n;

    for (int i = 0; i < minSize; i++) {
        temp[i] = arr[i];
    }

    delete[] arr;
    arr = temp;
    size = n;
}


void DynamicArray::clear() {
    delete[] arr;
    arr = nullptr;
    size = 0;
}


int main() {
    DynamicArray arr;
    arr.fillRandom(10);
    arr.print();

    arr.add(42, 5);
    arr.print();

    arr.remove(3);
    arr.print();

    arr.resize(6);
    arr.print();

    arr.clear();

    return 0;
}

