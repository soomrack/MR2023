#pragma once
#include <iostream>
#include <stdint.h>

template<typename T>
class PriorityQueue;


using priority = uint8_t;


template<typename T>
class PQNode {


    friend class PriorityQueue<T>;

    friend std::ostream& operator<<(std::ostream& os, const PQNode<T>& obj) {
        return os << "{" << obj._data << ", " << static_cast<int>(obj._pr) << "} "; 
    }


private:
    T _data{0};
    priority _pr;  //  highest priority - 0, lowest_priority = 255
    
public:
    PQNode(const T& value, const priority pr = -1);
    PQNode() = default;
    ~PQNode() = default;
    PQNode<T>& operator=(const T& value);
};  //  class PQNode


template<typename T>
PQNode<T>::PQNode(const T& value, const priority pr): _pr{pr}, _data{value} {}


template<typename T>
PQNode<T>& PQNode<T>::operator=(const T& value) {_data = value;}





