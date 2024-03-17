#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "DoubleLinkedListException.hpp"
#include <initializer_list>
#include <iostream>
#include <memory>


namespace DoubleLinkList
{

template <typename Type>
class DoubleLinkedListItem
{
public:
    Type data;
    DoubleLinkedListItem<Type>* next;
    DoubleLinkedListItem<Type>* prev;
};


template <typename Type>
class DoubleLinkedList
{
private:
    DoubleLinkedListItem<Type> head;
    DoubleLinkedListItem<Type> tail;
    size_t size;

public:
    DoubleLinkedList();
    DoubleLinkedList(std::initializer_list<Type> lst);
    ~DoubleLinkedList();

    size_t get_size() const;
    
    Type& operator[](const size_t idx);

    DoubleLinkedListItem<Type>* get_element(const size_t idx);

    void push_back(const Type& data);
    void insert_after(size_t idx, const Type& data);
    void insert_after(DoubleLinkedListItem<Type>* item_ptr, const Type& data);

    void pop_back();
    void erase_this(size_t idx);
    void erase_this(DoubleLinkedListItem<Type>* item_ptr);
};


template <typename Type>
std::ostream& operator<<(std::ostream& os, DoubleLinkedList<Type>& A)
{
    for (size_t idx = 0; idx < A.get_size(); ++idx)
    {
        std::cout << A[idx] << "; ";
    }

    std::cout << std::endl;

    return os;
}

}

#endif
