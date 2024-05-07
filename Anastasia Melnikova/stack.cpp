#include <iostream>
#include <stdlib.h>
using namespace std;

class Stack {
private:
    int* data;
    int top;
    int size;

public:
    Stack(int n);
    ~Stack();
    void push(int value);  //  Метод для добавления элемента в стек
    void pop();  //  Метод для удаления элемента из вершины стека
    int peek();  //  Метод для получения элемента из вершины стека без его удаления
    int IsEmpty();  // Метод для проверки, не пустой ли стек
    int IsFull();  //  Метод для проверки, не заполнен ли стек
    void printStack();  // Метод вывода информации
};

Stack::Stack(int n) {
    size = n;
    data = new int[size];
    top = -1;
}

Stack::~Stack() {
    delete[] data;
}

int Stack::IsEmpty() {
    if (top == -1)
        return 1;
    else
        return 0;
}

int Stack::IsFull() {
    if (top == size - 1)
        return 1;
    else
        return 0;
}

void Stack::push(int value) {
    if (IsFull())
        cout << "Стек заполнен";
    else {
        top++;
        data[top] = value;
    }
    size++;
}

void Stack::pop() {
    if (IsEmpty())
        cout << "Стек пустой";
    else {
        cout << "Удален элемент: " << data[top];
        top--;
    }
    size--;
}

int Stack::peek() {
    if (IsEmpty())
        cout << "Стек пустой";
    else {
        return data[top];
    }    
}

void Stack::printStack() {
    while (!IsEmpty()) {
        for (int i; i < size; i++)
            cout << data[i] << " ";
    }
    cout << endl;
}


int main() {
    Stack s(5);
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    s.push(50);

    s.printStack();
    return 0;
}