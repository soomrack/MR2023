#include <iostream>


class Node 
{
public:
    int value;
    int priority;
    Node* next;
public:
    Node(int val, int priority) : value(val), next(nullptr), priority(priority) {}
};


class queue 
{
private:
    Node* head;
    Node* tail;
public:
    queue() : head{nullptr}, tail{nullptr} {};

    bool is_empty();
    void push(int val, int priority);
    void print();
    int pop();
};


class Exception : public std::domain_error 
{
public:
    Exception(const char* const message) : std::domain_error(message) {}
};

Exception empty("Queue is empty");

bool queue::is_empty() 
{
    return head == nullptr;

}

void queue::push(int val, int priority) {
    Node* newNode = new Node(val, priority);
    if (is_empty() || priority < tail->priority)
    {
        newNode->next = tail;
        tail = newNode;
    }
    else
    {
        Node* current = tail;
        while (current->next != nullptr && current->next->priority < priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void queue::print() 
{
    if (is_empty()) return;
    Node* element = head;
    while (element) {
        std::cout << element->value << " ";
        element = element->next;
    }
    std::cout << std::endl;
}


int queue::pop() 
{
    if (is_empty()) throw empty;
    Node* element = head;
    int head_val = element->value;
    head = element->next;
    delete element;
    if (head == nullptr) {
    tail = nullptr;
    }
    return head_val;
}


int main() 
{
    queue A;

    return 0;
}