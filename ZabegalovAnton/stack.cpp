#include <iostream>


class Node {
public:
    int data;
    Node* next;
};


class Stack {
private:
    Node* head;

public:
    Stack(): head(nullptr) {};
    ~Stack();
    void push(int value);
    int pop();
    void print_stack();
};    


Stack::~Stack()
{
    while (head != nullptr){
        Node* temporary = head;
        head = head->next;
        delete temporary;
    }
}


void Stack::push(int value)
{
    Node* new_head = new Node();
    new_head->data = value;
    new_head->next = head;
    head = new_head;
}


int Stack::pop()
{
    if (head == nullptr) return int();

    Node* temporary = head;
    int buffer = head->data;
    head = head->next;
    delete temporary;
    return buffer;
}


void Stack::print_stack()
{
    if (head == nullptr) return;

    Node* temporary = head;
    while(head != nullptr){
        std::cout<<head->data<<"  ";
        head = head->next; 
    }
    std::cout<<std::endl;

    head = temporary;
}


int main()
{
    Stack stack;
    stack.push(3);
    stack.print_stack();

    stack.push(9);
    stack.push(12);
    stack.print_stack();

    stack.pop();
    stack.print_stack();
}
