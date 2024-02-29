#include "DynamicArray/DynamicArray.hpp"
#include <cmath>
#include <cstdint>

namespace DynArr
{
    template <typename Type>
    size_t DynamicArray<Type>::capacity_calc(size_t capacity)
    {
        if (capacity <= 2) return capacity;
        
        return static_cast<size_t>(std::pow(2, std::ceil(std::log2(static_cast<double>(capacity)))));
    }
    

    template <typename Type>
    DynamicArray<Type>::DynamicArray() : size_{0}, capacity_{0}, data_{nullptr} {}


    template <typename Type>
    DynamicArray<Type>::DynamicArray(size_t size) : size_{size}
    {
        if (!size)
        {
            capacity_ = 0;
            data_ = nullptr;
            return;
        }
        
        capacity_ = capacity_calc(size);
        data_ = new Type[capacity_];
    }


    template <typename Type>
    DynamicArray<Type>& DynamicArray<Type>::operator=(std::initializer_list<Type> lst)
    {
        if (lst.size() != size_) resize(lst.size());

        std::copy(lst.begin(), lst.end(), data_);
        
        return *this;
    }

    template <typename Type>
    DynamicArray<Type>::DynamicArray(const DynamicArray<Type>& copy_array)
    : size_{copy_array.size_}, capacity_{copy_array.capacity_}
    {
        data_ = new Type[capacity_];
        memcpy(data_, copy_array.data_, size_ * sizeof(Type));
    }


    template <typename Type>
    DynamicArray<Type>::DynamicArray(DynamicArray<Type>&& copy_array)
    : size_{copy_array.size_}, capacity_{copy_array.capacity_}, data_{copy_array.data_}
    {}


    template <typename Type>
    DynamicArray<Type>& DynamicArray<Type>::operator=(const DynamicArray<Type>& copy_array)
    {
        resize(copy_array.size_);
        memcpy(data_, copy_array.data_, size_ * sizeof(Type));

        return *this;
    }


    template <typename Type>
    DynamicArray<Type>& DynamicArray<Type>::operator=(DynamicArray<Type>&& copy_array)
    {
        if (data_ != nullptr) delete[] data_;
        data_ = copy_array.data_;

        return *this;
    }


    template <typename Type>
    void DynamicArray<Type>::resize(size_t size)
    {
        if (size_ == size) return;
        
        size_t new_capacity = capacity_calc(size);

        if (new_capacity != capacity_) 
        {
            Type* new_data = new Type[new_capacity];
            memcpy(new_data, data_, sizeof(Type) * ((new_capacity > capacity_) ? size_ : size));
            delete[] data_;
            data_ = new_data;
            capacity_ = new_capacity;
        }  
        
        size_ = size;
    }


    template <typename Type>
    void DynamicArray<Type>::reserve(size_t size)
    {
        size_t new_capacity = capacity_calc(size);

        if (new_capacity <= capacity_) return;

        Type* new_data = new Type[new_capacity];
        memcpy(new_data, data_, sizeof(Type) * size_);
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }


    template <typename Type>
    size_t DynamicArray<Type>::get_size() const
    {
        return size_;
    }


    template <typename Type>
    size_t DynamicArray<Type>::get_capacity() const
    {
        return capacity_;
    }


    template <typename Type>
    Type& DynamicArray<Type>::operator[](const size_t idx)
    {
        if (idx >= size_) throw DynamicArrayException(__FILE__, __LINE__, "Out of range");

        return data_[idx];
    }


    template <typename Type>
    const Type& DynamicArray<Type>::operator[](const size_t idx) const
    {
        if (idx >= size_) throw DynamicArrayException(__FILE__, __LINE__, "Out of range");

        return data_[idx];
    }
    

    template <typename Type>
    void DynamicArray<Type>::push_back(const Type& item)
    {
        resize(size_ + 1);
        data_[size_ - 1] = item;
    }


    template <typename Type>
    void DynamicArray<Type>::insert(size_t idx, const Type& item)
    {
        if (idx >= size_) throw DynamicArrayException(__FILE__, __LINE__, "Out of range");
        
        resize(size_ + 1);

        for (size_t array_idx = size_ - 2; array_idx >= idx; --array_idx)
        {
            data_[array_idx + 1] = data_[array_idx];
        }

        data_[idx] = item;
    }


    template <typename Type>
    void DynamicArray<Type>::pop_back()
    {
        resize(size_ - 1);
    }


    template <typename Type>
    void DynamicArray<Type>::erase(size_t idx)
    {
        if (idx >= size_) throw DynamicArrayException(__FILE__, __LINE__, "Out of range");
        
        for (size_t array_idx = idx; array_idx < size_ - 1; ++array_idx)
        {
            data_[array_idx] = data_[array_idx + 1];
        }

        resize(size_ - 1);
    }


    template <typename Type>
    DynamicArray<Type>::~DynamicArray() 
    {
        if (data_ != nullptr) delete[] data_;
    }


    template class DynamicArray<int>;
    template class DynamicArray<double>;
    template class DynamicArray<float>;
    template class DynamicArray<char>;
    template class DynamicArray<uint8_t>;
    template class DynamicArray<uint16_t>;
    template class DynamicArray<uint32_t>;
    template class DynamicArray<uint64_t>;
}