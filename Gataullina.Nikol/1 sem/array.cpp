#include <cstddef>
#include <iostream>
#include <conio.h>
#include <utility>

using std::swap;

template <typename T>
class Sorter {
    public:
        void bubbleSort(T *arr, size_t size);
        void mergeSort(T *arr, size_t left, size_t right);
    private:
        void merge(T *arr, size_t left, size_t middle, size_t right);
};

template <typename T>
void Sorter<T>::bubbleSort(T *arr, size_t size) { // Алгоритмическая сложность O(n^2)
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = size - 1; i < j; j--) {
            if (arr[j] < arr[j-1]) 
                swap(arr[j], arr[j-1]);
        }
    }
}

template <typename T>
void Sorter<T>::merge(T *arr, size_t left, size_t middle, size_t right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    T L[n1], R[n2];

    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[middle + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

template <typename T>
void Sorter<T>::mergeSort(T *arr, size_t left, size_t right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        merge(arr, left, middle, right);
    }
}

int main() {
    double a[5] = {1,4,3,6,5};
    Sorter<double> doubleSorter;
    doubleSorter.bubbleSort(a, 5);
    doubleSorter.mergeSort(a, 5);
    for (unsigned int i = 0; i < 5; i++) {
        std::cout << a[i] << "\t";
    }
}