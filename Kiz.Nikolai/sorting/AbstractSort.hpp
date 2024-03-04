#include <iostream>
#include <cxxabi.h>
#pragma once

template <typename T>
class AbstractSort {

    friend std::ostream& operator<<(std::ostream& os, const AbstractSort<T>& obj) {
        os << obj.get_class_name() << ":\n";
        for (size_t id = 0; id < obj.sz; ++id) {
            os << obj.arr[id] << " ";
        }
        return os << "\n";
    } 

protected:
    T* arr = nullptr;
    size_t sz = 0;
    
    void swap(size_t id_1, size_t id_2) {
        T temp = arr[id_1];
        arr[id_1] = arr[id_2];
        arr[id_2] = temp;
    }

public:
    AbstractSort(std::initializer_list<T> l): arr{new T[l.size()]}, sz{l.size()}  {
        std::copy(l.begin(), l.end(), arr);
    }
    const char* get_class_name() const {
        return  abi::__cxa_demangle(typeid(*this).name(), nullptr, nullptr, nullptr);
    }
    AbstractSort() = delete;
    virtual ~AbstractSort() {delete[] arr;}
    const T& operator[](const size_t idx) const {return arr[idx];}
    virtual void sort() = 0;
    
};  //  class AbstractSort