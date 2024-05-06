#include "sort.hpp"
#include <iostream>

std::ostream &operator<<(std::ostream &os, std::vector<int> &v)
{
    for (auto it : v) { os << it << " "; }
    os << std::endl;

    return os;
}

int main()
{
    std::vector<int> unsorted_vector = { 84, 52, -79, -45, 4, -63, 25, 37, -3, 0 };
    std::vector<int> vector;

    std::cout << "Unsorted: " << unsorted_vector;

    // Bubble sort
    vector = unsorted_vector;
    bubble_sort(vector);
    std::cout << "Bubble sort: " << vector;

    // Merge sort
    vector = unsorted_vector;
    merge_sort(vector);
    std::cout << "Merge sort: " << vector;

    // Heap sort
    vector = unsorted_vector;
    heap_sort(vector);
    std::cout << "Heap sort: " << vector;

    // Insertion sort
    vector = unsorted_vector;
    insertion_sort(vector);
    std::cout << "Insertion sort: " << vector;

    return 0;
}
