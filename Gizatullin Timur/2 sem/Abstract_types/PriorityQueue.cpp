#include <iostream>


class Node 
{
public:
    int value;
    Node* next;
public:
    Node(int val) : value(val), next(nullptr) {}
};


class queue 
{
private:
    Node* head;
    Node* tail;
public:
    queue() : head(nullptr), tail(nullptr) {}
    ~queue() {};

    bool is_empty();
    void push(int val);
    void print();
    int pop();
};


class Exception : public std::domain_error 
{
public:
    Exception(const char* const message) : std::domain_error(message) {}
};


Exception empty("Queue is empty");

queue::~queue() {
  while (head) {
    Node* temp = head;
    head = head->next;
    delete temp;
  }
  tail = nullptr;
}

bool queue::is_empty() 
{
    return head == nullptr;
}


void queue::push(int val) 
{
    Node* element = new Node(val);
    if (is_empty() || val < head->value) 
    {
        element->next = head;
        head = element;
    }
    else 
    {
        Node* current = head;
        while (current->next != nullptr && val > current->next->value)
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
    return head_val;
}


int main() 
{
    queue A;
    A.push(4);
    A.push(5);
    A.push(1);
    A.push(15);
    A.print();

    return 0;
}