#include "abstractContainer.hpp"
#include "dynamicArray.hpp"


template<typename T>
class Stack: private DynamicArray<T> {

    using DynamicArray<T>::DynamicArray;
    friend std::ostream& operator<<(std::ostream& os, Stack<T>& obj) {
        return os << static_cast<DynamicArray<T>&>(obj);
    }

public:
    Stack(Stack<T>& copy);
    Stack(Stack<T>&& copy_rvalue);
    Stack<T>& operator=(Stack<T> other);
    void push(const T& value);
    void push_range(std::initializer_list<T> l);
    T pop();
    T& top();
    inline size_t size() {return this->DynamicArray<T>::size();}
    inline bool empty() {return size() == 0;}
};  //  class Stack


template<typename T>
Stack<T>::Stack(Stack<T>& copy): DynamicArray<T>::_sz{copy._sz}, DynamicArray<T>::_cap{copy._cap} { 
    std::copy(copy.begin(), copy.end(), this->_data);
}


template<typename T>
Stack<T>::Stack(Stack<T>&& copy_rvalue): DynamicArray<T>::_sz{copy_rvalue._sz},
                                         DynamicArray<T>::_cap{copy_rvalue._cap},
                                         DynamicArray<T>::_data{copy_rvalue._data} {
    copy_rvalue._data = nullptr;
    copy_rvalue._sz = 0;
    copy_rvalue._cap = 0;                                       
}


template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T> other) {
    swap(other);
    return *this;
}


template<typename T>
void Stack<T>::push(const T& value) {
    this->push_back(value);
}

template<typename T>
void Stack<T>::push_range(std::initializer_list<T> l) {
    this->insert(this->_sz, l);
}

template<typename T>
T Stack<T>::pop() {
    return this->pop_back(); 
}


template<typename T>
T& Stack<T>::top() {
    return this->back();
}

