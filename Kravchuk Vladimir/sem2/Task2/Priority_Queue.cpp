#include <iostream>

using namespace std;

struct Element
{
    int data;
    Element* next;
    Element* previous;
    Element(int value) : data(value), next(nullptr), previous(nullptr) {}
};


class Queue {
private:
    Element* top_pointer;
    Element* bottom_pointer;
public:
    Queue();
    ~Queue();
    void push(int value);
    int pop();
    void queue_print();
    bool is_empty();

};


Queue::Queue() : top_pointer(nullptr), bottom_pointer(nullptr) {};


Queue::~Queue() {
    while (!is_empty()) {
        pop();
    }
}


void Queue::push(int value) {
    Element* New_Element = new Element(value);
    if (is_empty() || value < top_pointer->data) {
        New_Element->previous = top_pointer;
        New_Element->next = nullptr;
        top_pointer = New_Element;
    }
    else {
        Element* buf = top_pointer;
        while (buf->previous != nullptr && value >= buf->previous->data) {
            buf = buf->previous;
        }
        New_Element->previous = buf->previous;
        buf->previous = New_Element;
        if (New_Element->previous == nullptr) {
            bottom_pointer = New_Element;
        }
    }
}


int Queue::pop() {
    if (is_empty()) {
        return NAN;
    }
    else {
        Element* deleted = top_pointer;
        top_pointer = top_pointer->previous;
        //top_pointer->next = nullptr;
        if (top_pointer != nullptr) {
            top_pointer->next = nullptr;
        }
        return deleted->data;
    }
}


void Queue::queue_print() {
    Element* buf = top_pointer;
    while (buf != nullptr) {
        cout << buf->data << "\t";
        cout << "\n";
        buf = buf->previous;
    }
}


bool Queue::is_empty() {
    return top_pointer == nullptr;
}


int main()
{
    Queue queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.push(4);
    queue.pop();
    queue.queue_print();

    return 0;
}
