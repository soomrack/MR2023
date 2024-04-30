#pragma once
#include <stddef.h>


template<typename T>
class AbstractContainer {
protected:
    virtual void push_back(const T& value) = 0;
    virtual T pop_back() = 0;
    virtual void insert(size_t index, const T& value) = 0;
    virtual void clear() = 0;
    virtual ~AbstractContainer() = default;
    virtual void swap(AbstractContainer<T>& other) = 0;
};  //  AbstractContainer interface
