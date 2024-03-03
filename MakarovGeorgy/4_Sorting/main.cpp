#include <iostream>
#include <vector>


void print(const std::string &info, const std::vector<int> &vector) {
    std::cout << info;
    for (int item: vector) std::cout << item << ", ";
    std::cout << "\b\b" << std::endl;
}


// Bubble sort

void bubble_sort(std::vector<int> &vector) {
    for (size_t sorted = 0; sorted < vector.size(); sorted++)
        for (size_t item = 0; item < vector.size() - 1; item++)
            if (vector[item] > vector[item + 1]) std::swap(vector[item], vector[item + 1]);
}


// Merge sort

void merge(std::vector<int> &vector, std::vector<int> &left, std::vector<int> &right) {
    size_t left_idx = 0;
    size_t right_idx = 0;

    while (left_idx < left.size() && right_idx < right.size()) {
        if (left.at(left_idx) < right.at(right_idx)) vector.push_back(left.at(left_idx++));
        else vector.push_back(right.at(right_idx++));
    }

    while (left_idx < left.size()) vector.push_back(left.at(left_idx++));
    while (right_idx < right.size()) vector.push_back(right.at(right_idx++));
}

void merge_sort(std::vector<int> &vector) {
    if (vector.size() <= 1) return;

    const auto middle = vector.begin() + vector.size() / 2;

    std::vector<int> left(vector.begin(), middle);
    std::vector<int> right(middle, vector.end());

    merge_sort(left);
    merge_sort(right);

    vector.clear();
    merge(vector, left, right);
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
    for (int idx = (int) vector.size() / 2 - 1; idx >= 0; idx--) {
        heapify(vector, vector.size(), idx);
    }

    for (int idx = (int) vector.size() - 1; idx > 0; idx--) {
        std::swap(vector[0], vector[idx]);
        heapify(vector, idx, 0);
    }
}


// Insertion sort

void insertion_sort(std::vector<int> &vector) {
    for (int sorted = 1; sorted < vector.size(); sorted++) {
        int item = vector[sorted];

        int idx = sorted - 1;  // integer as it can be negative
        while ((idx >= 0) && (vector[idx] > item)) {
            vector[idx + 1] = vector[idx];
            idx--;
        }

        vector[idx + 1] = item;
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