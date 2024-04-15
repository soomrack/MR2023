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
    Element* pop();
    int top();
    bool empty() const;
};


Stack::Stack() : topPointer(nullptr) {}


Stack::Stack(const Stack& copy) : topPointer(nullptr) {
    if (copy.empty()) {
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
    if (transfer.empty()) {
        return;
    }

    topPointer = transfer.topPointer;
    transfer.topPointer = nullptr;
}


Stack::~Stack() {
    while (!empty()) {
        pop();
    }
}


void Stack::push(int value) {
    Element* NewElement = new Element(value);
    NewElement->pointer = topPointer;
    topPointer = NewElement;
}


Element* Stack::pop() {
    if (empty()) {
        cout << "Stack is empty\n" << endl;
        return nullptr;
    }
    else {
        Element* deleted = topPointer;
        topPointer = topPointer->pointer;
        return  deleted;
    }
}


void Stack::print() {
    Element* buf = topPointer;
    while (buf != nullptr)
    {
        cout << buf->data << "\n" << endl;
        buf = buf->pointer;
    }
}


int Stack::top() {
    if (empty()) {
        cout << "Stack is empty\n" << endl;
        return 0;
    }
    return topPointer->data;
}


bool Stack::empty() const {
    return topPointer == nullptr;
}


int main()
{
    Stack Stack;
    Stack.push(1);
    Stack.push(2);
    Stack.push(3);
    Stack.print();
    return 0;
}
