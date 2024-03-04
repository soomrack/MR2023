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

void merge(std::vector<int> &vector, std::vector<int> &temp, size_t start, size_t middle, size_t end) {
    size_t left = start, right = middle + 1;
    size_t index = start;

    while (left <= middle && right <= end) {
        if (vector[left] <= vector[right]) {
            temp[index] = vector[left];
            left++;
        } else {
            temp[index] = vector[right];
            right++;
        }
        index++;
    }

    while (left <= middle) {
        temp[index] = vector[left];
        index++;
        left++;
    }

    while (right <= end) {
        temp[index] = vector[right];
        index++;
        right++;
    }

    for (size_t idx = start; idx <= end; idx++) {
        vector[idx] = temp[idx];
    }
}

void merge_sort_body(std::vector<int> &vector, std::vector<int> &temp, size_t start, size_t end){
    if(start < end){
        size_t middle = start + (end - start) / 2;

        merge_sort_body(vector, temp, start, middle);
        merge_sort_body(vector, temp, middle + 1, end);

        merge(temp, vector, start, middle, end);
    }
}

void merge_sort(std::vector<int> &vector) {
    const size_t start = 0;
    const size_t end = vector.size() - 1;

    std::vector<int> temp = vector;
    
    merge_sort_body(vector, temp, start, end);
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
    for (size_t idx = vector.size() / 2 - 1; idx >= 0; idx--) {
        if (idx + 1 == 0) break;

        heapify(vector, vector.size(), idx);
    }

    for (size_t idx = vector.size() - 1; idx > 0; idx--) {
        if (idx + 1 == 0) break;

        std::swap(vector[0], vector[idx]);
        heapify(vector, idx, 0);
    }
}


// Insertion sort

void insertion_sort(std::vector<int> &vector) {
    for (size_t sorted = 1; sorted < vector.size(); sorted++) {
        int item = vector[sorted];

        size_t idx = sorted - 1; 
        while ((idx + 1 != 0) && (vector[idx] > item)) {
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
