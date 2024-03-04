#include "AbstractSort.hpp"


template <typename T>
class MergeSort: public AbstractSort<T> {
    using AbstractSort<T>::AbstractSort;

private:
    void merge(size_t low, size_t mid, size_t high) {
        size_t left_size = mid - low + 1;
        size_t right_size = high - mid;
        size_t left_idx = 0;
        size_t right_idx = 0;
        size_t sorted_idx = low;
        T left_part[left_size] {};
        T right_part[right_size] {};

        std::copy(&this->arr[low], &this->arr[mid+1], left_part);
        std::copy(&this->arr[mid+1], &this->arr[high+1], right_part);

        while (left_idx < left_size && right_idx < right_size) {
            if (left_part[left_idx] < right_part[right_idx]) {
                this->arr[sorted_idx] = left_part[left_idx];
                ++left_idx;
            }
            else {
                this->arr[sorted_idx] = right_part[right_idx];
                ++right_idx;
            }
            ++sorted_idx;
        }  //  one of the sorted arrays is over, need to copy other part

        if (left_idx < left_size)
            std::copy(&left_part[left_idx], &left_part[left_size], &this->arr[sorted_idx]);  // copy remaining left       
        if (right_idx < right_size) 
            std::copy(&right_part[right_idx], &right_part[right_size], &this->arr[sorted_idx]);  // copy remaining right
            
    }

    void merge_sort(size_t low, size_t high) {
        if (low >= high) {return;}
        size_t mid = (low + high) / 2;
        merge_sort(low, mid);
        merge_sort(mid+1, high);
        merge(low, mid, high);
    }

public:
    void sort() final {
        this->merge_sort(0, this->sz-1); 
    }

};  //  class MergeSort