#include <iostream>
#include <vector>


void print(const std::string &info, const std::vector<int> &vector) {
    std::cout << info;
    for (int item: vector) std::cout << item << ", ";
    std::cout << "\b\b" << std::endl;
}


// Bubble sort

void bubble_sort(std::vector<int> &vector) {
    const size_t size = vector.size();

    for (size_t idx = 0; idx < size; idx++)
        for (size_t item = 0; item < size - 1; item++)
            if (vector[item] > vector[item + 1]) std::swap(vector[item], vector[item + 1]);
}


// Merge sort

void merge(std::vector<int> &vector, size_t start, size_t middle, size_t end) {
    const size_t size_first = middle + 1 - start;
    const size_t size_second = end - middle;

    std::vector<int> vector_first(size_first);
    std::vector<int> vector_second(size_second);

    for (size_t i = 0; i < size_first; i++) vector_first[i] = vector[start + i];
    for (size_t i = 0; i < size_second; i++) vector_second[i] = vector[middle + 1 + i];

    int idx = 0;
    int jdx = 0;
    int kdx = (int) start;

    while (idx < size_first && jdx < size_second) {
        if (vector_first[idx] <= vector_second[jdx]) {
            vector[kdx] = vector_first[idx];
            idx++;
        } else {
            vector[kdx] = vector_second[jdx];
            jdx++;
        }
        kdx++;
    }

    while (idx < size_first) {
        vector[kdx] = vector_first[idx];
        idx++;
        kdx++;
    }
}

void merge_sort_body(std::vector<int> &vector, size_t start, size_t end) {
    if (start < end) {
        size_t middle = start + (end - start) / 2;

        merge_sort_body(vector, start, middle);
        merge_sort_body(vector, middle + 1, end);

        merge(vector, start, middle, end);
    }
}

void merge_sort(std::vector<int> &vector) {
    const size_t start = 0;
    const size_t end = vector.size() - 1;

    merge_sort_body(vector, start, end);
}


// Heap sort

void heapify(std::vector<int> &vector, size_t size, int idx) {
    const int left = 2 * idx + 1;
    const int right = 2 * idx + 2;

    int idx_max_heap = idx;

    if (left < size && vector[left] > vector[idx_max_heap])
        idx_max_heap = left;

    if (right < size && vector[right] > vector[idx_max_heap])
        idx_max_heap = right;

    if (idx_max_heap != idx) {
        std::swap(vector[idx], vector[idx_max_heap]);
        heapify(vector, size, idx_max_heap);
    }
}

void heap_sort(std::vector<int> &vector) {
    const size_t size = vector.size();

    for (int idx = (int) size / 2 - 1; idx >= 0; idx--) {
        heapify(vector, size, idx);
    }

    for (int idx = (int) size - 1; idx > 0; idx--) {
        std::swap(vector[0], vector[idx]);
        heapify(vector, idx, 0);
    }
}


// Insertion sort

void insertion_sort(std::vector<int> &vector) {
    const size_t size = vector.size();

    int idx_old;
    int temp;

    for (int idx = 1; idx < size; idx++) {
        temp = vector[idx];
        idx_old = idx - 1;

        while ((idx_old >= 0) && (vector[idx_old] > temp)) {
            vector[idx_old + 1] = vector[idx_old];
            idx_old--;
        }

        vector[idx_old + 1] = temp;
    }
}


int main() {
    std::vector<int> unsorted_vector = {84, 52, -79, -45, 4, -63, 25, 37, -3, 0};
    std::vector<int> vector;

    print("Unsorted: ", unsorted_vector);

    // Bubble sort
    vector = unsorted_vector;
    bubble_sort(vector);
    print("Bubble sort: ", vector);

    // Merge sort
    vector = unsorted_vector;
    merge_sort(vector);
    print("Merge sort: ", vector);

    // Heap sort
    vector = unsorted_vector;
    heap_sort(vector);
    print("Heap sort: ", vector);

    // Insertion sort
    vector = unsorted_vector;
    insertion_sort(vector);
    print("Insertion sort: ", vector);

    return 0;
}