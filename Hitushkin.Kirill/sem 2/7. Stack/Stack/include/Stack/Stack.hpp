#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include "StackException.hpp"
#include <initializer_list>
#include <iostream>


namespace stack
{

template <typename Type>
class StackItem {
public:
    Type data;
    StackItem* next;    
};


template <typename Type>
class Stack
{
private:
    StackItem<Type>* head;
    size_t size;

public:
    Stack();
    ~Stack();

    size_t get_size() const;
    Type& top();
    void push(const Type& data);
    void pop();
};


template <typename Type>
Stack<Type>::Stack() : head{nullptr}, size{0} {}


template <typename Type>
Stack<Type>::~Stack()
{
    while (size) pop();
}


template <typename Type>
size_t Stack<Type>::get_size() const
{
    return size;
}


template <typename Type>
Type& Stack<Type>::top()
{
    if (!size) throw StackException(__FILE__, __LINE__, "Stack empty!");

    return head->data;
}


template <typename Type>
void Stack<Type>::push(const Type& data)
{
    head = new StackItem<Type>{data, head};
    ++size;
}


template <typename Type>
void Stack<Type>::pop()
{
    if (!size) throw StackException(__FILE__, __LINE__, "Stack empty!");

    StackItem<Type>* prev_head = head;
    head = head->next;
    delete prev_head;
    --size;
}


}


#endif
