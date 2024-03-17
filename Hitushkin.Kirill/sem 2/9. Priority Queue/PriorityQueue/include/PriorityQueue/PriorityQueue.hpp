#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include "PriorityQueueException.hpp"
#include <initializer_list>
#include <iostream>
#include <limits>


namespace priority_queue
{

template <typename Type>
class PriorityQueueItem {
public:
    Type data;
    PriorityQueueItem<Type>* next;    
};


template <typename Type>
class PriorityQueue
{
private:
    PriorityQueueItem<Type> head;
    size_t size;

public:
    PriorityQueue();
    ~PriorityQueue();

    size_t get_size() const;
    Type& top();
    void push(const Type& data);
    void pop();
};


template <typename Type>
PriorityQueue<Type>::PriorityQueue() : head{0, nullptr}, size{0} {}


template <typename Type>
PriorityQueue<Type>::~PriorityQueue()
{
    while (size) pop();
}


template <typename Type>
size_t PriorityQueue<Type>::get_size() const
{
    return size;
}


template <typename Type>
Type& PriorityQueue<Type>::top()
{
    if (!size) throw PriorityQueueException(__FILE__, __LINE__, "PriorityQueue empty!");

    return head.next->data;
}


template <typename Type>
void PriorityQueue<Type>::push(const Type& data)
{
    if (!size) {
        head.next = new PriorityQueueItem<Type>{data, nullptr};
        ++size;
        return;
    }
    
    PriorityQueueItem<Type>* item_ptr = &head;

    for (size_t idx = size; idx; --idx) {
        if (data > item_ptr->next->data) break;
        item_ptr = item_ptr->next;
    }

    item_ptr->next = new PriorityQueueItem<Type>{data, item_ptr->next};
    ++size;
}


template <typename Type>
void PriorityQueue<Type>::pop()
{
    if (!size) throw PriorityQueueException(__FILE__, __LINE__, "Priority Queue empty!");

    PriorityQueueItem<Type>* prev_head = head.next;
    head.next = head.next->next;
    delete prev_head;
    --size;
}


}


#endif
