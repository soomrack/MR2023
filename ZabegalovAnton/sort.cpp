#include <iostream>
#include <string>
#include <bits/stdc++.h>

int Arr[] = {1, 3, 2, -5, 9, 100, -359};

int bubble_sort (int arr[], size_t size)
{
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = 0; j < size - 1; j++) {
            if (arr[j] > arr[j+1]) {
                std:: swap (arr[j], arr[j+1]);
            }
        }
    }

    return 0; 
}

int insertion_sort(int arr[], int size)
{
    for (int i = 1; i < size; i++){
        for (int j = 0; j < i; j++){
            if (arr[i - j] < arr[i - j - 1]){
                std:: swap(arr[i - j], arr[i - j -1]);
            } else {
                break;
            }
        }
    }
    return 0;
}

void heapify (int arr[], int size, int i)
{
    int largest = i;
    int left = i * 2 + 1;
    int right = i * 2 + 2;

    if (left < size && arr[largest] < arr[left]){
        largest = left;
    }
    
    if (right < size && arr[largest] < arr[right]){
        largest = right;
    }

    if (largest != i){
        std:: swap(arr[largest], arr[i]);
        heapify(arr, size, largest);
    }
}

void heap_sort (int arr[], int size)
{
    for (int i = size / 2 - 1; i >= 0; i--){
        heapify(arr, size, i);
    }

    for (int i = size - 1; i > 0; i--){
        std:: swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void merge (int arr[], int const left,
            int const mid, int const right)
{
    size_t const sub_arr_one = mid - left + 1;
    size_t const sub_arr_two = right - mid;

    auto *left_arr = new int[sub_arr_one];
    auto *right_arr = new int[sub_arr_two];

    for (int i = 0; i < sub_arr_one; i++){
        left_arr[i] = arr[left + i];
    }
    for (int j = 0; j < sub_arr_two; j++){
        right_arr[j] = arr[mid + 1 + j];
    }

    int idx_sub_arr_one  = 0;
    int idx_sub_arr_two  = 0;
    int idx_merge_arr = left;

    while (idx_sub_arr_one < sub_arr_one &&
            idx_sub_arr_two < sub_arr_two) {
        if (left_arr[idx_sub_arr_one] <=
            right_arr[idx_sub_arr_two]) {
            arr[idx_merge_arr] = left_arr[idx_sub_arr_one];
            idx_sub_arr_one++;
        } else {
            arr[idx_merge_arr] = right_arr[idx_sub_arr_two];
            idx_sub_arr_two++;
        }
        idx_merge_arr++;
    }    

    while (idx_sub_arr_one < sub_arr_one) {
        arr[idx_merge_arr] = left_arr[idx_sub_arr_one];
        idx_merge_arr++;
        idx_sub_arr_one++;
    }

    while (idx_sub_arr_two < sub_arr_two) {
        arr[idx_merge_arr] = right_arr[idx_sub_arr_two];
        idx_merge_arr++;
        idx_sub_arr_two++;
    }

    delete[] left_arr;
    delete[] right_arr;
}

void merge_sort (int arr[], int const begin, int const end)
{
    if (begin >= end){
        return;
    }

    size_t mid = begin + (end - begin) / 2;
    merge_sort (arr, begin, mid);
    merge_sort (arr, mid + 1, end);
    merge (arr, begin, mid, end);
}

void print_arr (int arr[], size_t size)
{
    std:: cout << "[";
    for(size_t i = 0; i < size - 1; i++) {
        std:: cout <<arr[i]<<", ";
    }
    std:: cout << arr[size-1] << "]" << std:: endl;
}

int main ()
{
    size_t size = sizeof(Arr) / sizeof(Arr[0]);
    print_arr(Arr, size);

    heap_sort(Arr, size);
    print_arr(Arr, size);
    return 0;
}
