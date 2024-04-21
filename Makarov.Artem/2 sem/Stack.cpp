#include <iostream>


class Node {
private:
    friend class Stack;
    int value;
    Node* next;

public:
    Node(int val) : value(val), next(nullptr) {}
};


class Stack {
private:
    Node* first_add;
    Node* last_add;
public:
    Stack() : first_add(nullptr), last_add(nullptr) {}
    bool isEmpty();
    void push(int val);
    void print();
    void pop();
};


bool Stack::isEmpty() 
{
    return first_add == nullptr;
}


void Stack::push(int val) 
{
    Node* element = new Node(val);
    if (isEmpty()) 
    {
        first_add = element;
        last_add = element;
    }
    else 
    {
        element->next = first_add;
        first_add = element;
    }
}


void Stack::print() 
{
    if (isEmpty()) 
    {
        std::cout << "stack is empty" << std::endl;
    }
    else 
    {
        std::cout << first_add->value << std::endl;
    }
}


void Stack::pop() 
{
    if (isEmpty()) return;
    Node* element = first_add;
    first_add = element->next;
    delete element;
}


int main() 
{
    Stack A;
    A.push(5);
    A.print();
    A.push(1);
    A.print();
    A.push(10);
    A.print();
    A.pop();
    A.print();
    A.pop();
    A.print();
    A.pop();
    A.print();

    return 0;
}