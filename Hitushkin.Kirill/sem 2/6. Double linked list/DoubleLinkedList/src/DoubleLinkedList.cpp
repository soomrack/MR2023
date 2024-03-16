#include "DoubleLinkedList/DoubleLinkedList.hpp"
#include <cmath>
#include <cstdint>

namespace DoubleLinkList
{

template <typename Type>
DoubleLinkedList<Type>::DoubleLinkedList() 
: head{0, &tail, nullptr}, tail{0, nullptr, &head}, size{0} {}


template <typename Type>
DoubleLinkedList<Type>::DoubleLinkedList(std::initializer_list<Type> lst)
: head{0, &tail, nullptr}, tail{0, nullptr, &head}, size{0}
{
    for (Type item: lst) push_back(item);
}


template <typename Type>
size_t DoubleLinkedList<Type>::get_size() const
{
    return size;
}


template <typename Type>
Type& DoubleLinkedList<Type>::operator[](const size_t idx)
{
    return get_element(idx)->data;
}


template <typename Type>
DoubleLinkedListItem<Type>* DoubleLinkedList<Type>::get_element(const size_t idx)
{
    if (idx >= size) throw DoubleLinkedListException(__FILE__, __LINE__, "Out of range");
    
    DoubleLinkedListItem<Type>* item_ptr = head.next;

    size_t idx_list = idx + 1;
    while (--idx_list) item_ptr = item_ptr->next;

    return item_ptr;
}


template <typename Type>
void DoubleLinkedList<Type>::push_back(const Type& data)
{
    DoubleLinkedListItem<Type>* prev_last = tail.prev;
    tail.prev = new DoubleLinkedListItem<Type>{data, &tail, prev_last};
    prev_last->next = tail.prev;
    ++size;
}


template <typename Type>
void DoubleLinkedList<Type>::insert_after(size_t idx, const Type& data)
{
    insert_after(get_element(idx), data);
}


template <typename Type>
void DoubleLinkedList<Type>::insert_after(DoubleLinkedListItem<Type>* item_ptr, const Type& data)
{
    DoubleLinkedListItem<Type>* prev_last = item_ptr->prev;

    prev_last->next = new DoubleLinkedListItem<Type>{data, item_ptr, prev_last};
    item_ptr->prev = prev_last->next;
    ++size;
}


template <typename Type>
void DoubleLinkedList<Type>::pop_back()
{
    if (!size) return;

    DoubleLinkedListItem<Type>* prev_last = tail.prev;
    prev_last->prev->next = &tail;
    tail.prev = prev_last->prev;

    delete prev_last;
    --size;
}


template <typename Type>
void DoubleLinkedList<Type>::erase_this(size_t idx)
{
    erase_this(get_element(idx));
}


template <typename Type>
void DoubleLinkedList<Type>::erase_this(DoubleLinkedListItem<Type>* item_ptr)
{
    DoubleLinkedListItem<Type>* prev_last = item_ptr->prev;
    DoubleLinkedListItem<Type>* next_last = item_ptr->next;
    prev_last->next = next_last;
    next_last->prev = prev_last;

    delete item_ptr;
    --size;
}


template <typename Type>
DoubleLinkedList<Type>::~DoubleLinkedList()
{
    while (size--) pop_back();
}

template class DoubleLinkedList<int>;
template class DoubleLinkedList<float>;
template class DoubleLinkedList<double>;
template class DoubleLinkedList<char>;

}