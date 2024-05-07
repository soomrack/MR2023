#include <iostream>
using namespace std;

class PriorityQueue {
private:
    int* data; // Массив элементов очереди
    int capacity; // Максимальная вместимость очереди
    int size; // Текущий размер очереди

public:
    PriorityQueue(int n); // Конструктор, инициализирующий массив и устанавливающий размер на 0
    ~PriorityQueue(); // Деструктор, освобождающий память, выделенную под массив

    void push(int value); // Добавление элемента в очередь
    void pop(); // Удаление элемента из очереди
    int head(); // Возвращает значение первого элемента в очереди (с наибольшим приоритетом)
    int tail(); // Возвращает значение последнего элемента в очереди (с наименьшим приоритетом)
    int IsEmpty(); // Проверка, является ли очередь пустой
    int IsFull(); // Проверка, является ли очередь полной
};

PriorityQueue::PriorityQueue(int n) {
    capacity = n;
    data = new int[capacity];
    size = 0;
}

PriorityQueue::~PriorityQueue() {
    delete[] data;
}

int PriorityQueue::IsEmpty() {
    if (size == 0)
        return 1;
    else
        return 0;
}

int PriorityQueue::IsFull() {
    if (size == capacity)
        return 1;
    else
        return 0;
}

void PriorityQueue::push(int value) {  // реализуем очередь с приоритетом включения
    if (IsFull())
        cout << "Очередь заполнена";
    else {
        int i = 0;
        while (i < size && data[i] > value) {
            i++;
        }
        for (int j = size; j > i; j--) {
            data[j] = data[j - 1];
        }
        data[i] = value;
        size++;
    }
}

void PriorityQueue::pop() {
    if (IsEmpty())
        cout << "Очередь пустая";
    else {
        for (int i = 0; i < size; i++) {
            data[i] = data[i + 1];
        }
        size--;
    }
}

int PriorityQueue::head() {
    if (IsEmpty())
        cout << "Очередь пустая";
    else {
        return data[0];
    }
}

int PriorityQueue::tail() {
    if (IsEmpty())
        cout << "Очередь пустая";
    else {
        return data[size - 1];
    }
}

int main() {
    setlocale(LC_ALL, "Ru");

    PriorityQueue pq(5);

    pq.push(3);
    pq.push(5);
    pq.push(1);
    pq.push(4);

    cout << "Элемент с наивысшим приоритетом: " << pq.head() << endl;
    cout << "Элемент с наинизшем приоритетом: " << pq.tail() << endl;

    pq.pop();

    std::cout << "Элемент с наивысшим приоритетом после удаление одного элемента: " << pq.head() << endl;
    std::cout << "Элемент с наинизшим приоритетом после удаление одного элемента: " << pq.tail() << endl;

    return 0;
}