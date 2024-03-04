#include "AbstractSort.hpp"
#include "math.h"
/* 
    Heap sort with MaxHeap complete binary tree.
        -node at index i
        -left child at index 2 * i + 1
        -right child at index 2 * i + 2
        -parent at [i/2]    
*/


template<typename T>
class HeapSort final: public AbstractSort<T> {
    using AbstractSort<T>::AbstractSort;
private:
    void heapify(size_t heapsize, size_t parent) {
        size_t left_child = parent * 2 + 1;
        size_t right_child = left_child + 1;
        size_t max_child = this->arr[left_child] > this->arr[right_child] ? left_child : right_child;
        if (left_child >= heapsize) return;
        if (right_child >= heapsize) max_child = left_child;
        if (this->arr[max_child] > this->arr[parent]) {
            this->swap(max_child, parent);
            this->heapify(heapsize, max_child);
        }
    }

public:
    void sort() final {
        size_t first_parent = this->sz / 2 - 1;  //  first tree node with children (bottom-wise)
        for (int i = static_cast<int>(first_parent); i >= 0; --i)
            heapify(this->sz, i);
        for (int i = static_cast<int>(this->sz - 1); i >= 0; --i) {
            this->swap(0, i);
            heapify(i,0);
        }
    }

};  //  class HeapSort