#include <iostream>
using namespace std;

class DynamicArray {
private:
    int* data; // Массив элементов
    int size;  // Текущий размер массива
    int capacity; // Максимальная вместимость массива

public:

    DynamicArray();
    DynamicArray(int capacity);
    ~DynamicArray();

    // Методы для доступа к элементам
    int get(int i);  // Получение элемента по индексу
    void set(int i, int value); // Изменение элемента по индексу 
    void add(int value);  // Добавление элемента в конец массива
    void resize(int new_capacity);  // Изменение размера массива
    int get_capacity();  // Возвращает максимальную вместимость массива
    int get_size();  // Возвращает текущий размер массива

    void print() {
        for (int i = 0; i <= size; i++)
            cout << data[i] << " ";
    }   
};

DynamicArray::DynamicArray() {
    capacity = 8;
    size = 0;
    data = new int[capacity];
}

DynamicArray::DynamicArray(int initial_capacity) {
    capacity = initial_capacity;
    size = 0;
    data = new int[capacity];
}

DynamicArray::~DynamicArray() {
    delete[] data;
}

int DynamicArray::get(int i) {
    if (i >= 0 && i <= size)
        return data[i];
    else {
        cout << "элемента с таким индексом не сущствует";
        return 0;
    }
}

void DynamicArray::set(int i, int value) {
    if (i >= 0 && i <= size)
       data[i] = value;
    else
        cout << "элемента с таким индексом не сущствует";
}


void DynamicArray::resize(int new_capacity) {
    int* new_data = new int[new_capacity];
    for (int i = 0; i < size; i++) {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

void DynamicArray::add(int value) {
    if (size == capacity) {
        resize(capacity * 2);
    }
    data[size++] = value;
}

int DynamicArray::get_size() {
    return size;
}

int DynamicArray::get_capacity() {
    return capacity;
}



int main() {
    DynamicArray arr(5);
    setlocale(LC_ALL, "RU");
    arr.add(1);
    arr.add(2);
    arr.add(3);
    arr.add(4);

    cout << "Размер: " << arr.get_size() << endl;
    cout << "Вместимость: " << arr.get_capacity() << endl;

    arr.set(1, 5);

    cout << "Элемент под индексом 1: " << arr.get(1) << endl;

    arr.resize(6);

    arr.add(6);
    arr.add(7);

    arr.print();

    return 0;
}