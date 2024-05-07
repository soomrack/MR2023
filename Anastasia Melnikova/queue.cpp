#include <iostream>
using namespace std;

class Queue {
private:
    int* data;
    int front; // Индекс элемента, находящегося в начале очереди
    int rear; // Индекс элемента, находящегося в конце очереди
    int size;

public:
    Queue(int n);
    ~Queue();
    int get_front(); // Метод для получения первого элемента очереди
    int get_rear(); // Метод для получения последнего элемента очереди
    void enqueue(int value); // Метод для добавления элемента в конец очереди
    void printQueue(); // Метод для отображения элементов в очереди
    bool IsEmpty(); // Метод для проверки, пуста ли очередь
    bool IsFull(); // Метод для проверки, полна ли очередь
    void push(int value);  // Метод для добавления элемента в начало очереди
};

Queue::Queue(int n) {
    size = n;
    data = new int[size];
    front = -1;
    rear = -1;
}

Queue::~Queue() {
    delete[] data;
}

bool Queue::IsEmpty() {
    if (front == -1 && rear == -1)
        return 1;
    else
        return 0;
}

bool Queue::IsFull() {
    if (front = 0 && rear == size - 1)
        return 1;
    else
        return 0;
}

int Queue::get_front() {
    if (IsEmpty())
        cout << "Очередь пустая";
    else 
        return data[front];
}

int Queue::get_rear() {
    if (IsEmpty())
        cout << "Очередь пустая";
    else 
        return data[rear];
}

void Queue::enqueue(int value) {
    if (IsFull())
        cout << "Очередь заполнена";
    else {
        if (front == -1) front = 0;
        rear++;
        data[rear] = value;
    }
}

void Queue::push(int value) {
    if (IsFull())
        cout << "Очередь заполнена";
    else {
        if (front == -1) front = 0;
        rear++;
        data[rear] = value;
    }
}

void Queue::printQueue() {
    while (!IsEmpty()) {
        for (int i = front; i <= rear; i++)
            cout << data[i] << " ";
        cout << endl;
    }
}

int main() {
    Queue q(4);

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);

    q.printQueue();

    cout << "Front: " << q.get_front() << endl;
    cout << "Rear: " << q.get_rear() << endl;

    q.printQueue();

    return 0;
}