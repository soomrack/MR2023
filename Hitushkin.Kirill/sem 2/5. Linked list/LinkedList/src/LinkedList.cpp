#include "LinkedList/LinkedList.hpp"
#include <cmath>
#include <cstdint>

namespace LinkList
{
    template <typename Type>
    LinkedList<Type>::LinkedList() : items_{0, nullptr}, size_{0} {}


    template <typename Type>
    LinkedList<Type>::LinkedList(std::initializer_list<Type> lst)
    : items_{0, nullptr}, size_{0}
    {
        for (Type item: lst) push_back(item);
    }

    template <typename Type>
    size_t LinkedList<Type>::get_size() const
    {
        return size_;
    }


    template <typename Type>
    Type& LinkedList<Type>::operator[](const size_t idx)
    {
        if (idx >= size_) throw LinkedListException(__FILE__, __LINE__, "Out of range");
        
        LinkedListItem<Type>* item_ptr = items_.next();

        size_t idx_list = idx + 1;
        while (--idx_list) item_ptr = item_ptr->next();

        return item_ptr->data();
    }


    template <typename Type>
    void LinkedList<Type>::push_back(const Type& data)
    {
        size_t idx_list = size_;
        LinkedListItem<Type>* item_ptr = &items_;

        while (idx_list--) item_ptr = item_ptr->next();

        item_ptr->push_back(data);
        ++size_;
    }


    template <typename Type>
    void LinkedList<Type>::insert(size_t idx, const Type& data)
    {
        if (idx >= size_) throw LinkedListException(__FILE__, __LINE__, "Out of range");
        
        size_t idx_list = idx;
        LinkedListItem<Type>* item_ptr = &items_;

        while (idx_list--) item_ptr = item_ptr->next();

        item_ptr->push_back(data);
        ++size_;
    }


    template <typename Type>
    void LinkedList<Type>::pop_back()
    {
        if (!size_) return;

        size_t idx_list = size_ - 1;
        LinkedListItem<Type>* item_ptr = &items_;

        while (idx_list--) item_ptr = item_ptr->next();

        item_ptr->pop_back();
        --size_;
    }


    template <typename Type>
    void LinkedList<Type>::erase(size_t idx)
    {
        if (idx >= size_) throw LinkedListException(__FILE__, __LINE__, "Out of range");
        
        size_t idx_list = idx;
        LinkedListItem<Type>* item_ptr = &items_;

        while (idx_list--) item_ptr = item_ptr->next();

        item_ptr->pop_back();
        --size_;
    }


    template <typename Type>
    LinkedList<Type>::~LinkedList()
    {
        while (size_--) items_.pop_back();
    }

    template class LinkedList<int>;
    template class LinkedList<float>;
    template class LinkedList<double>;
    template class LinkedList<char>;
}