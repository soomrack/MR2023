#include <iostream>


class Node
{
    friend class queue;
private:
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

    bool isEmpty();
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


bool queue::isEmpty()
{
    return head == nullptr;
}


void queue::push(int val)
{
    Node* element = new Node(val);
    if (isEmpty())
    {
        head = element;
        tail = element;
        return;
    }
    tail->next = element;
    tail = element;
}


void queue::print()
{
    if (isEmpty())
    {
        std::cout << "Queue is empty" << std::endl;
        return;
    }
    Node* element = head;
    while (element)
    {
        std::cout << element->value << " ";
        element = element->next;
    }
    std::cout << std::endl;
}


int queue::pop()
{
    if (isEmpty())
    {
        throw empty;
    }
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


int main()
{
    queue Q;
    Q.push(4);
    Q.push(8);
    Q.push(12);
    Q.print();
    Q.push(15);
    Q.pop();
    Q.pop();
    Q.print();

    return 0;
}
