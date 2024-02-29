#include "AbstractSort.hpp"

template <typename T>
class BubbleSort final: public AbstractSort<T> {
    using AbstractSort<T>::AbstractSort;

public:
    void sort() final {
        for (size_t still = 0; still < this->sz; ++still) {
            for (size_t move = still + 1; move < this->sz; ++move) {
                if (this->arr[move] < this->arr[still]) this->swap(move, still);
            }
        }
    }   
};  //  class BubbleSort

