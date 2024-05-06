#include <utility>
#include <algorithm>
#include "queueNode.hpp"
#include "dynamicArray.hpp"


template<typename T>
class PriorityQueue: private DynamicArray<PQNode<T>> {

using initializer_node = std::pair<T, priority>;

    friend std::ostream& operator<<(std::ostream& os, const PriorityQueue<T>& obj) {
        return os << static_cast<const DynamicArray<PQNode<T>>&>(obj);
    }

public:
    PriorityQueue() = default;
    PriorityQueue(const T& value, priority pr);
    PriorityQueue(std::initializer_list<initializer_node> l);
    PriorityQueue(PriorityQueue<T>& copy);
    PriorityQueue(PriorityQueue<T>&& copy_rvalue);
    PriorityQueue<T>& operator=(PriorityQueue<T> other);

    ~PriorityQueue() = default;

    inline size_t size() {return this->DynamicArray<PQNode<T>>::size();}
    inline bool empty() {return this->DynamicArray<PQNode<T>>::size() == 0;}

    const T& top();
    void push(const T& value, const uint8_t pr);
    T pop();
    void push_range(std::initializer_list<initializer_node> range);
    void clear();

private:
    void sort_priority();
};  //  class PriorityQueue


template<typename T>
PriorityQueue<T>::PriorityQueue(const T& value, priority pr) {
    push(value, pr);
}


template<typename T>
void PriorityQueue<T>::push(const T& value, const uint8_t pr) {
    this->push_back(PQNode<T>(value, pr));
    sort_priority();
}


template<typename T>
PriorityQueue<T>::PriorityQueue(std::initializer_list<initializer_node> l) {
    for (initializer_node node: l) {
        this->push_back(PQNode<T>(node.first, node.second));
    }
    sort_priority();
}


template<typename T>
void PriorityQueue<T>::sort_priority() {
    std::sort(this->begin(), this->end(), 
    [](PQNode<T>& left, PQNode<T>& right) {
        return left._pr < right._pr;
    });
}


template<typename T>
void PriorityQueue<T>::push_range(std::initializer_list<initializer_node> l) {
    for (initializer_node node: l) {
        this->push_back(PQNode<T>(node.first, node.second));
    }
    sort_priority();
}


template<typename T>
const T& PriorityQueue<T>::top() {
    return this->front()._data;
}


template<typename T>
T PriorityQueue<T>::pop() {
    if (2 * this->_sz <= this->_cap)
    this->shrink_to_fit();
    T data = this->front()._data;
    this->erase(0);
    return data;
}


template<typename T>
void PriorityQueue<T>::clear() {
    this->DynamicArray<PQNode<T>>::clear();
}


template<typename T>
PriorityQueue<T>::PriorityQueue(PriorityQueue<T>& copy): DynamicArray<PQNode<T>>(copy) {}


template<typename T>
PriorityQueue<T>::PriorityQueue(PriorityQueue<T>&& copy_rvalue):    DynamicArray<PQNode<T>>::_data{copy_rvalue._data},
                                                                    DynamicArray<PQNode<T>>::_sz{copy_rvalue._sz},
                                                                    DynamicArray<PQNode<T>>::_cap{copy_rvalue._cap} 
                                                                {
    copy_rvalue._data = nullptr;
    copy_rvalue._sz = 0;
    copy_rvalue._cap = 0;
}

template<typename T>
PriorityQueue<T>& PriorityQueue<T>::operator=(PriorityQueue<T> other) {
    this->swap(other);
    return *this;
}