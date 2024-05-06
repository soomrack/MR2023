#include <iostream>

class Node 
{
public:
    int value;
    int priority;
    Node* next;

    Node(int val, int prior) : value(val), next(nullptr), priority(prior) {}
};


class Queue 
{
private:
    Node* head;
    Node* tail;
public:
    Queue() : head(nullptr), tail(nullptr) {}

    bool is_empty();
    void push(int val, int prior);
    void print();
    int pop();
    void clear();
};


class Exception : public std::domain_error 
{
public:
    Exception(const char* const message) : std::domain_error(message) {}
};


Exception empty("Queue is empty");


bool Queue::is_empty() 
{
    return head == nullptr;
}

void Queue::print() 
{
    if (is_empty()) return;
    Node* element = head;
    while (element) 
    {
        std::cout << element->value << " ";
        element = element->next;
    }
    std::cout << std::endl;
}

void Queue::push(int val, int prior) 
{
    Node* element = new Node(val, prior);
    if (is_empty() || prior < head->priority) 
    {
        element->next = head;
        head = element;
        if (tail == nullptr)
        {
            tail = element;
        }
    }
    else 
    {
        Node* current = head;
        while (current->next != nullptr && prior > current->next->priority) 
        {
            current = current->next;
        }
        element->next = current->next;
        current->next = element;
        if (element->next == nullptr) 
        {
            tail = element;
        }
    }
}

int Queue::pop() 
{
    if (is_empty()) throw empty;
    Node* element = head;
    int head_val = element->value;
    head = element->next;
    delete element;
    if (head == nullptr)
    {
        tail = nullptr;
    }
    return head_val;
}


void Queue::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
}

int main() 
{
    Queue A;
    A.push(4,1);
    A.push(5,2);
    A.push(1,2);
    A.print();

    return 0;
}