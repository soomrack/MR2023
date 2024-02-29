#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "LinkedListException.hpp"
#include "LinkedListItem.hpp"
#include <initializer_list>
#include <iostream>
#include <memory>


namespace LinkList
{
    template <typename Type>
    class LinkedList
    {
    private:
        LinkedListItem<Type> items_;
        size_t size_;

    public:
        LinkedList();
        LinkedList(std::initializer_list<Type> lst);

        size_t get_size() const;

        Type& operator[](const size_t idx);
        
        void push_back(const Type& data);
        void insert(size_t idx, const Type& data);

        void pop_back();
        void erase(size_t idx);

        ~LinkedList();
    };


    template <typename Type>
    std::ostream& operator<<(std::ostream& os, LinkedList<Type>& A)
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
