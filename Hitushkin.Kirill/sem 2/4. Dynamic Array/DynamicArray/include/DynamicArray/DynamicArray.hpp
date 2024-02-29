#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include "DynamicArrayException.hpp"
#include <initializer_list>
#include <iostream>

namespace DynArr
{
    template <typename Type>
    class DynamicArray
    {
    private:
        Type* data_;
        size_t size_;
        size_t capacity_;

    private:
        size_t capacity_calc(size_t capacity);

    public:
        DynamicArray();
        explicit DynamicArray(size_t size);
        DynamicArray& operator=(std::initializer_list<Type> lst);
        DynamicArray(const DynamicArray& copy_array);
        DynamicArray(DynamicArray&& copy_array);

        DynamicArray& operator=(const DynamicArray& copy_array);
        DynamicArray& operator=(DynamicArray&& copy_array);

        void resize(size_t size);
        void reserve(size_t size);

        size_t get_size() const;
        size_t get_capacity() const;

        Type& operator[](const size_t idx);
        const Type& operator[](const size_t idx) const;
        
        void push_back(const Type& item);
        void insert(size_t idx, const Type& item);

        void pop_back();
        void erase(size_t idx);

        ~DynamicArray();
    };


    template <typename Type>
    std::ostream& operator<<(std::ostream& os, const DynamicArray<Type>& A)
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
