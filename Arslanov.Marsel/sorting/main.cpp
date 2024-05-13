#include <typeinfo>

#include "sorting.hpp"

int main() {
    int arr[10] = {5, -3, 7, 8, 10, 0, -1, 6, -9, 52};
    print<int>(arr, sizeof(arr) / sizeof(*arr));
    bubble_sort<int>(arr, sizeof(arr) / sizeof(*arr));
    insertion_sort<int>(arr, sizeof(arr) / sizeof(*arr));
    heapify<int>(arr, sizeof(arr) / sizeof(*arr), 0);
    heap_sort(arr, sizeof(arr) / sizeof(*arr));
    print<int>(arr, sizeof(arr) / sizeof(*arr));
    merge_sort(arr, sizeof(arr) / sizeof(*arr));
    print<int>(arr, sizeof(arr) / sizeof(*arr));

    return 0;
}