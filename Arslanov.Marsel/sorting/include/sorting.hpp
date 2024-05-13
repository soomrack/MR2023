#pragma once

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>

template <typename T>
void swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

template <typename T>
void print(T* array, size_t size) {
    for (size_t idx = 0; idx < size; ++idx) {
        std::cout << array[idx] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void bubble_sort(T* array, size_t size) {
    for (size_t idx = 0; idx < size; ++idx) {
        for (size_t i = 0; i < size - 1; ++i) {
            if (array[i] > array[i + 1]) {
                swap<T>(array[i], array[i + 1]);
            }
        }
    }
}

template <typename T>
void insertion_sort(T* array, size_t size) {
    int32_t idx = 0;
    for (size_t inserted = 1; inserted < size; ++inserted) {
        T temp = array[inserted];
        idx = inserted - 1;
        while (idx >= 0 && temp < array[idx]) {
            array[idx + 1] = array[idx];
            --idx;
        }
        array[idx + 1] = temp;
    }
}

template <typename T>
void heapify(T* array, size_t size, size_t node) {
    size_t largest = node;
    size_t left_child = 2 * node + 1;
    size_t right_child = 2 * node + 2;
    if (left_child < size && array[left_child] > array[largest]) {
        largest = left_child;
    }
    if (right_child < size && array[right_child] > array[largest]) {
        largest = right_child;
    }
    if (node != largest) {
        swap<T>(array[node], array[largest]);
        heapify<T>(array, size, largest);
    }
}

template <typename T>
void heap_sort(T* array, size_t size) {
    for (int32_t idx = size / 2 - 1; idx >= 0; --idx) {
        heapify<T>(array, size, idx);
    }
    print<T>(array, size);
    for (int32_t idx = size - 1; idx > 0; --idx) {
        swap<T>(array[0], array[idx]);
        heapify<T>(array, idx, 0);
    }
}

template <typename T>
void merge(T* array, T* temp, size_t start, size_t middle, size_t end) {
    size_t left = start, right = middle + 1;
    size_t index = start;

    while (left <= middle && right <= end) {
        if (array[left] <= array[right]) {
            temp[index] = array[left];
            left++;
        } else {
            temp[index] = array[right];
            right++;
        }
        index++;
    }

    while (left <= middle) {
        temp[index] = array[left];
        index++;
        left++;
    }

    while (right <= end) {
        temp[index] = array[right];
        index++;
        right++;
    }
}

template <typename T>
void merge_sort_body(T* array, T* temp, size_t start, size_t end) {
    if (start < end) {
        size_t middle = start + (end - start) / 2;

        merge_sort_body(array, temp, start, middle);
        merge_sort_body(array, temp, middle + 1, end);

        merge(array, temp, start, middle, end);

        for (size_t idx = start; idx <= end; idx++) array[idx] = temp[idx];
    }
}

template <typename T>
void merge_sort(T* array, size_t size) {
    size_t start = 0;
    size_t end = size - 1;
    T* temp = new T[size];
    std::memcpy(temp, array, size);

    merge_sort_body(array, temp, start, end);

    delete[] temp;
}
