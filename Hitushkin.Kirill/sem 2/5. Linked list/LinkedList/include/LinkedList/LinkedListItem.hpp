#ifndef LINKED_LIST_ITEM_HPP
#define LINKED_LIST_ITEM_HPP

#include "LinkedListException.hpp"

namespace LinkList
{
    template <typename Type>
    class LinkedListItem
    {
    private:
        Type data_;
        LinkedListItem<Type>* next_;
        
    public:
        LinkedListItem() = delete;
        LinkedListItem(const Type& data, LinkedListItem<Type>* next);

        LinkedListItem<Type>* next();
        Type& data();
        void push_back(const Type& data);
        void pop_back();
    };


    template <typename Type>
    LinkedListItem<Type>::LinkedListItem(const Type& data, LinkedListItem<Type>* next)
    : data_{data}, next_{next} {}


    template <typename Type>
    LinkedListItem<Type>* LinkedListItem<Type>::next()
    {
        return next_;
    }


    template <typename Type>
    Type& LinkedListItem<Type>::data()
    {
        return data_;
    } 


    template <typename Type>
    void LinkedListItem<Type>::push_back(const Type& data)
    {
        next_ = new LinkedListItem<Type>(data, next_);
    }


    template <typename Type>
    void LinkedListItem<Type>::pop_back()
    {
        if (next_ == nullptr) return;
        
        LinkedListItem<Type>* new_next = next_->next_;
        delete next_;
        next_ = new_next;
    }
}

#endif
