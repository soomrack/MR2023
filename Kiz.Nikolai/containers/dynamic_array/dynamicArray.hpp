#pragma once
#include <iostream>
#include <utility>
#include <cstring>
#include "abstractContainer.hpp"

template<typename T>
class DynamicArray: public AbstractContainer<T> {

    friend std::ostream& operator<<(std::ostream& os, const DynamicArray<T>& obj) {
        os << "[ ";
        if (obj._sz == 0) {return os << "empty\n";}
        for (size_t idx = 0; idx < obj._sz; ++idx) {
            os << obj[idx] << " ";
        } 
        return os << "]\n";
    }

protected:
    size_t _sz{0};
    size_t _cap{0};
    T* _data{nullptr};

    void swap(AbstractContainer<T>& other) override;
    inline T* begin() {return _data;}
    inline T* end() {return _data + _sz;}


public:
    DynamicArray() = default;
    DynamicArray(std::initializer_list<T> l); 
    DynamicArray(DynamicArray<T>& other); 
    DynamicArray(DynamicArray<T>&& rvalue_other); 
    DynamicArray(size_t sz);
    DynamicArray<T>& operator=(DynamicArray<T> other); 


    ~DynamicArray(); 


    T& operator[](const size_t idx); 
    const T& operator[](const size_t idx) const; 

    inline size_t size() {return _sz;}
    inline size_t capacity() {return _cap;}


    void push_back(const T& value) override;
    void push_back(T&& rvalue); 
    T pop_back() override; 
    void insert(const size_t idx, const T& value) override; 
    void clear() override;


    void reserve(const size_t newcap); 
    void insert(const size_t idx, std::initializer_list<T> l); 
    void shrink_to_fit();  
    void resize(const size_t count);  //  for new size less or equal to present
    void resize(const size_t count, const T& value);  //  for new size more than present. filling value is required.
    void erase(const size_t idx); 
    void erase(const size_t first, size_t last); 
    inline T& front() {return *begin();}
    inline T& back() {return *(end() - 1);}

};  //  class DynamicArray


template<typename T>
DynamicArray<T>::DynamicArray(std::initializer_list<T> l): _sz{l.size()}, _cap{_sz*2}, _data{new T[_cap]} {
        std::copy(l.begin(), l.end(), _data);
    }


template<typename T>
DynamicArray<T>::DynamicArray(size_t sz): _sz{sz} {
    reserve(sz);
}


template<typename T>
DynamicArray<T>::DynamicArray(DynamicArray<T>& copy): _sz{copy._sz}, _cap{copy._cap}, _data{new T[_cap]} {
    std::copy(copy.begin(), copy.end(), _data);
}


template<typename T>
DynamicArray<T>::DynamicArray(DynamicArray<T>&& rvalue_copy): _sz{rvalue_copy._sz}, _cap{rvalue_copy._cap}, _data{rvalue_copy._data} {
    rvalue_copy._data = nullptr;
    rvalue_copy._sz = 0;
    rvalue_copy._cap = 0;
}


template<typename T>
DynamicArray<T>::~DynamicArray() {
        delete[] _data;
}


template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray<T> other) {
    swap(other);
    return *this;
}


template<typename T>
void DynamicArray<T>::swap(AbstractContainer<T>& other) {
    std::swap(_data, dynamic_cast<DynamicArray<T>&>(other)._data);
    std::swap(_cap, dynamic_cast<DynamicArray<T>&>(other)._cap);
    std::swap(_sz, dynamic_cast<DynamicArray<T>&>(other)._sz);
}

template<typename T>
const T& DynamicArray<T>::operator[](const size_t idx) const {
    return _data[idx];
}


template<typename T>
T& DynamicArray<T>::operator[](const size_t idx) {
    return const_cast<T&>(std::as_const(*this)[idx]);
}


template<typename T>
void DynamicArray<T>::reserve(const size_t newcap) {
    if (newcap == 0) reserve(1);
    if (newcap <= _cap) return;
    T* new_data = new T[newcap];
    std::copy(begin(), end(), new_data);
    _cap = newcap;
    delete[] _data;
    _data = new_data;
}   


template<typename T>
void DynamicArray<T>::push_back(const T& value) {
    if (_sz == _cap) reserve(2*_cap);
    T* new_last = end();
    *new_last = value;
    ++_sz;
}


template<typename T>
void DynamicArray<T>::push_back(T&& rvalue) {
    if (_sz == _cap) reserve(2*_cap);
    T* new_last = end();
    *new_last = std::move(rvalue);
    ++_sz;
}


template<typename T>
void DynamicArray<T>::insert(const size_t idx, const T& value) {
    if (idx >= _sz) return push_back(value);
    if (_sz == _cap) reserve(2*_cap);
    T* current_element = begin() + idx;
    std::copy(current_element, end(), current_element+1);
    *current_element = value;
    ++_sz;
}


template<typename T>
void DynamicArray<T>::insert(const size_t idx, std::initializer_list<T> l) {
    if (idx > _sz) return insert(_sz, l);
    if (_cap < _sz + l.size())
    reserve(_sz + l.size());
    T* current_element = begin() + idx;
    std::copy(current_element, end(), current_element+l.size());
    std::copy(l.begin(), l.end(), current_element);
    _sz += l.size();
} 


template<typename T>
T DynamicArray<T>::pop_back() {
    if (_sz == 0) throw std::runtime_error("Pop from empty container.");

    T last = back();
    --_sz;
    return last;
} 


template<typename T>
void DynamicArray<T>::shrink_to_fit() {
    T* new_arr = new T[_sz];
    std::copy(begin(), end(), new_arr);
    delete[] _data;
    _data = new_arr;
    _cap = _sz;
}


template<typename T>
void DynamicArray<T>::resize(const size_t count) {
    if (count > _sz) throw std::runtime_error("Bad resize overload.");
    if (count == _sz) return;
    
    T* new_arr = new T[count];
    std::copy(begin(), begin() + count, new_arr);
    delete [] _data;
    _data = new_arr;
    _sz = count;
    _cap = count;
}

template<typename T>
void DynamicArray<T>::resize(const size_t count, const T& value) {
    if (count <= _sz) throw std::runtime_error("Bad resize overload.");
    if (_sz + count > _cap) reserve((_sz+count));

    for(size_t idx = 0; idx < count; ++idx) {
        push_back(value);
    }
}


template<typename T>
void DynamicArray<T>::erase(const size_t idx) {
    if (idx >= _sz) throw std::runtime_error("Bad erase index.");

    std::copy(begin() + idx + 1, end(), begin() + idx);
    --_sz;
}


template<typename T>
void DynamicArray<T>::erase(const size_t first, const size_t last) {
    if (first >= _sz || last >= _sz) throw std::runtime_error("Bad erase indexes."); 
    if (first == last) return erase(last);
    
    std::copy(begin() + last + 1, end(), begin() + first);
    _sz -= (last - first + 1);
}


template<typename T>
void DynamicArray<T>::clear() {
    _sz = 0;
}