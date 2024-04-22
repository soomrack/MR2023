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
    Element* head;
    Element* tail;
public:
    Queue();
    ~Queue();
    void push(int value);
    int pop();
    void queue_print();
    bool is_empty();

};


Queue::Queue() : head(nullptr), tail(nullptr) {};


Queue::~Queue() {
    while (!is_empty()) {
        pop();
    }
}


void Queue::push(int value) {
    Element* New_Element = new Element(value);
    if (is_empty()) {
        head = tail = New_Element;
    }
    else {
        tail->previous = New_Element;
        New_Element->next = tail;
        tail = New_Element;
    }
}


int Queue::pop() {
    if (is_empty()) {
        return INT_MAX;
    }
    else {
        Element* deleted = head;
        int deleted_data = deleted->data;
        head = head->previous;
        if (head != nullptr) {
            head->next = nullptr;
        }
        delete[] deleted;
        return deleted_data;
    }
}


void Queue::queue_print() {
    Element* buf = head;
    while (buf != nullptr) {
        cout << buf->data << "\t";
        cout << "\n";
        buf = buf->previous;
    }
}


bool Queue::is_empty() {
    return head == nullptr;
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
