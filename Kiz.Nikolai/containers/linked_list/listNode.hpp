#pragma once
#include <iostream>


template<typename T>
class SingleLinkedList;

template<typename T>
class DoublyLinkedList;

template<typename T>
class LLNodeBase {
    friend std::ostream& operator<<(std::ostream& os, const LLNodeBase<T>& node){ 
        return os << node._data << " ";
    }

protected:
    T _data{0};

public:
    LLNodeBase() = delete;
    ~LLNodeBase() = default;

protected:
    explicit LLNodeBase(const T& value);
    LLNodeBase<T>& operator=(const T& value);
    
};  //  class LLNodeBase


template<typename T>
LLNodeBase<T>::LLNodeBase(const T& value): _data{value} {}


template<typename T>
LLNodeBase<T>& LLNodeBase<T>::operator=(const T& value) {
    if (this == nullptr) throw std::runtime_error("Can't assign to empty node.");
    _data = value;
    return *this;
}



template<typename T>
class SLLNode: public LLNodeBase<T> {
    friend class SingleLinkedList<T>;
    using LLNodeBase<T>::LLNodeBase;

private:
    SLLNode<T>* _next{nullptr};
    
public:
    SLLNode<T>& next();

private:
    SLLNode(const T& value, SLLNode<T>* next);
    ~SLLNode() = default;
};


template<typename T>
SLLNode<T>::SLLNode(const T& value, SLLNode<T>* next): LLNodeBase<T>(value) {
    _next = next;
}


template<typename T>
SLLNode<T>& SLLNode<T>::next() {return *_next;}


template<typename T>
class DLLNode: public LLNodeBase<T> {

    friend class DoublyLinkedList<T>;
    using LLNodeBase<T>::LLNodeBase;

private:
    DLLNode<T>* _prev{nullptr};
    DLLNode<T>* _next{nullptr};

public:
    DLLNode<T>& prev();
    DLLNode<T>& next();
    ~DLLNode() = default;

private:
    DLLNode(const T& value, DLLNode<T>* prev, DLLNode<T>* next);

};  //  class DLLNode



template<typename T>
DLLNode<T>::DLLNode(const T& value, DLLNode<T>* prev, DLLNode<T>* next): LLNodeBase<T>(value) {
    _prev = prev;
    _next = next;
}

template<typename T>
DLLNode<T>& DLLNode<T>::prev() {return *_prev;}


template<typename T>
DLLNode<T>& DLLNode<T>::next() {return *_next;}