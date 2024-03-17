#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "QueueException.hpp"
#include <initializer_list>
#include <iostream>


namespace queue
{

template <typename Type>
class QueueItem {
public:
    Type data;
    QueueItem* next;    
};


template <typename Type>
class Queue
{
private:
    QueueItem<Type> head;
    QueueItem<Type> tail;
    size_t size;

public:
    Queue();
    ~Queue();

    size_t get_size() const;
    void push(const Type& data);
    Type pop();
};


template <typename Type>
Queue<Type>::Queue() : head{0, &tail}, tail{0, &head}, size{0} {}


template <typename Type>
Queue<Type>::~Queue()
{
    while (size) pop();
}


template <typename Type>
size_t Queue<Type>::get_size() const
{
    return size;
}


template <typename Type>
void Queue<Type>::push(const Type& data)
{
    tail.next->next = new QueueItem<Type>{data, &tail};
    tail.next = tail.next->next;
    ++size;
}


template <typename Type>
Type Queue<Type>::pop()
{
    if (!size) throw QueueException(__FILE__, __LINE__, "Queue empty!");

    Type data = head.next->data;

    QueueItem<Type>* prev_head = head.next;
    head.next = head.next->next;
    delete prev_head;
    --size;

    return data;
}


}


#endif
