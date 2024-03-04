#include "AbstractSort.hpp"

template <typename T>
class InsertionSort final: public AbstractSort<T> {
    using AbstractSort<T>::AbstractSort;

public:
    void sort() final {
        for (size_t sorted = 1; sorted < this->sz; ++sorted) { 
            size_t temp = sorted;
            for (int idx = static_cast<int>(sorted-1); idx >= 0; --idx) {
                if (this->arr[idx] > this->arr[sorted]) {
                    this->swap(idx, sorted); 
                    --sorted;
                    continue;
                    }
                break;
            }
            sorted = temp;
        }
    }
};  //  Class InsertionSort

