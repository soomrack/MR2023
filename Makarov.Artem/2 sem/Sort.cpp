#include <iostream>
#include <vector>
#include <algorithm>


void BubbleSort(std::vector<int>& arr) 
{
    for (size_t idx_i = 0; idx_i + 1 < arr.size(); ++idx_i) {
        for (size_t idx_j = 0; idx_j + 1 < arr.size() - idx_i; ++idx_j) {
            if (arr[idx_j + 1] < arr[idx_j]) {
                std::swap(arr[idx_j], arr[idx_j + 1]);
            }
        }
    }
}


void MergeSortImpl(std::vector<int>& arr, int left, int right) 
{
    if (left < right) {
        int mid = (left + right) / 2;

        MergeSortImpl(arr, left, mid);
        MergeSortImpl(arr, mid + 1, right);

        int i = left;
        int j = mid + 1;

        while (i <= mid && j <= right) {
            if (arr[i] > arr[j]) {
                std::swap(arr[i], arr[j]);
                int k = j;
                while (k + 1 <= right && arr[k] > arr[k + 1]) {
                    std::swap(arr[k], arr[k + 1]);
                    ++k;
                }
            }
            ++i;
        }
    }
}


void MergeSort(std::vector<int>& arr) 
{
    if (!arr.empty()) {
        MergeSortImpl(arr, 0, arr.size() - 1);
    }
}


void InsertionSort(std::vector<int>& arr) 
{
    for (size_t idx_i = 1; idx_i < arr.size(); idx_i++) {
        for (size_t idx_j = idx_i; (idx_j > 0) && (arr[idx_j] < arr[idx_j - 1]); idx_j--) {
            std::swap(arr[idx_j], arr[idx_j - 1]);
        }
    }
}


void Heapify(std::vector<int>& arr, int n, int i) 
{
    int largest = i;

    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        Heapify(arr, n, largest);
    }
}


void HeapSort(std::vector<int>& arr) 
{
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        Heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        Heapify(arr, i, 0);
    }
}


void initBubbleSort() 
{
    std::vector<int> arr = { 11, 9, 28, 310, -2 };

    MergeSort(arr);

    std::cout << "Bubble Sort:\n";
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << "\n";
}


void initMergeSort() 
{
    std::vector<int> arr = { 3, 19, 8, 0, 48 };

    MergeSort(arr);

    std::cout << "Merge Sort:\n";
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << ' ';
    }
}


void initInsertionSort() 
{
    std::vector<int> arr = { 11, 9, 28, 310, -2 };

    InsertionSort(arr);

    std::cout << "Insertion Sort:\n";
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}


void initHeapSort() {
    std::vector<int> arr = { 11, 9, 28, 310, -2 };

    HeapSort(arr);

    std::cout << "Heap Sort:\n";
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
}


int main() {
    initBubbleSort();
    initMergeSort();
    initInsertionSort();
    initHeapSort();
}