#include <algorithm>
#include <iostream>
#include <vector>

void heapify(std::vector<int>& array, int size, int idx)
{
    int maxInHeap = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < size && array[left] > array[maxInHeap])
        maxInHeap = left;

    if (right < size && array[right] > array[maxInHeap])
        maxInHeap = right;

    if (maxInHeap != idx) {
        std::swap(array[idx], array[maxInHeap]);
        heapify(array, size, maxInHeap);
    }
}

void heapSort(std::vector<int>& array) 
{
    int size = array.size();

    for (int idx = size / 2 - 1; idx >= 0; idx--) {
        heapify(array, size, idx);
    }

    for (int idx = size - 1; idx > 0; idx--) {
        std::swap(array[0], array[idx]);
        heapify(array, idx, 0);
    }
}

void printArray(std::vector<int>& array, int size)
{
    std::cout << "\nSorted array: ";
    for (int idx = 0; idx < size; idx++) {
        std::cout << array[idx] << " ";
    }
}

void initialization()
{
    std::vector<int> array = { 20, 8, 7, 15, 10, 6 };
    int size = array.size();

    heapSort(array);

    printArray(array, size);
}

int main()
{
    initialization();

    return 0;
}
