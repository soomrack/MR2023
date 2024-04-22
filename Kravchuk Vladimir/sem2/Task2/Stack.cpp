#include <iostream>

using namespace std;

struct Element {
    int data;
    Element* pointer;
    Element(int value) : data(value), pointer(nullptr) {}
};


class Stack {
private:
    Element* topPointer;

public:
    Stack();
    Stack(const Stack& copy);
    Stack(Stack&& transfer);
    ~Stack();
    void push(int value);
    void print();
    int pop();
    int top();
    bool is_empty() const;
};


Stack::Stack() : topPointer(nullptr) {}


Stack::Stack(const Stack& copy) : topPointer(nullptr) {
    if (copy.is_empty()) {
        return;
    }


    Element* pointerOriginal = copy.topPointer;
    while (pointerOriginal != nullptr) {
        Element* newElement = new Element(pointerOriginal->data);
        newElement->pointer = topPointer;
        topPointer = newElement;
        pointerOriginal = pointerOriginal->pointer;
    }
}


Stack::Stack(Stack&& transfer) : topPointer(nullptr) {
    if (transfer.is_empty()) {
        return;
    }

    topPointer = transfer.topPointer;
    transfer.topPointer = nullptr;
}


Stack::~Stack() {
    while (!is_empty()) {
        pop();
    }
}


void Stack::push(int value) {
    Element* NewElement = new Element(value);
    NewElement->pointer = topPointer;
    topPointer = NewElement;
}


int Stack::pop() {
    if (is_empty()) {
        cout << "Stack is empty\n";
        return NAN;
    }
    else {
        Element* deleted = topPointer;
        int deleted_data = deleted->data;
        topPointer = topPointer->pointer;
        delete[] deleted;
        return  deleted_data;
    }
}


void Stack::print() {
    Element* buf = topPointer;
    while (buf != nullptr)
    {
        cout << buf->data << "\n";
        buf = buf->pointer;
    }
}


int Stack::top() {
    if (is_empty()) {
        cout << "Stack is empty\n";
        return 0;
    }
    return topPointer->data;
}


bool Stack::is_empty() const {
    return topPointer == nullptr;
}


int main()
{
    Stack Stack;
    Stack.push(1);
    Stack.push(2);
    Stack.push(3);
    Stack.pop();
    Stack.print();
    return 0;
}
