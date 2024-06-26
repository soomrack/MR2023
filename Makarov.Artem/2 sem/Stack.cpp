﻿#include <iostream>


class Node 
{
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
    Stack S;
    S.push(5);
    S.print();
    
    S.push(1);
    S.print();
   
    S.push(10);
    S.print();
    
    S.pop();
    S.print();
    
    S.pop();
    S.print();
    
    S.pop();
    S.print();

    return 0;
}