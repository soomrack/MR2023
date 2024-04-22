#include <iostream>
#include <stdexcept>

class Node {
private:
    int val;
    Node* next;

public:
    Node(int val) : val(val), next(nullptr) {}

public:
    Node* get_next() { return next; }
    int get_val() { return val; }
    void set_next(Node* next) { this->next = next; }
};

class Queue {
private:
    Node* head;
    Node* tail;
public:
    Queue() : head(nullptr), tail(nullptr) {}
    ~Queue();

public:
    bool is_empty() { return head == nullptr; }
    void push(int val);
    int pop();
    void print();
};

Queue::~Queue()
{
    while (!is_empty()) {
        pop();
    }
}


void Queue::push(int val)
{
    Node* el = new Node(val);
    if (is_empty()) {
        head = el;
        tail = el;
    }
    else {
        tail->set_next(el);
        tail = el;
    }
}


int Queue::pop()
{
    if (is_empty()) throw std::runtime_error("Queue is empty");
    int head_val = head->get_val();
    Node* temp = head;
    head = head->get_next();
    delete temp;
    return head_val;
}


void Queue::print()
{
    Node* el = head;
    while (el) {
        std::cout << el->get_val() << " ";
        el = el->get_next();
    }
    std::cout << std::endl;
}

int main() {
    Queue A;
    A.push(1);
    A.push(2);
    A.push(3);
    A.print();
    A.pop();
    A.print();
    return 0;
}