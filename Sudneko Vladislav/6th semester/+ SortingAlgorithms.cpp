#include <bits/stdc++.h>

#include <iostream>

template <typename T>
void printar(T& array) {
  std::cout << "{ ";
  for (const auto& element : array) {
    std::cout << element << " ";
  }
  std::cout << "}" << std::endl;
}

template <typename T>
void bubble_sort(T& array, size_t array_size) {
  for (int iteration = 0; iteration < array_size; iteration++) {
    for (int element = 0; element < array_size - 1 - iteration; element++) {
      if (array[element] > array[element + 1]) {
        std::swap(array[element], array[element + 1]);
      }
    }
  }
}

template <typename T>
void merge(T* array, T* temp, size_t size) {
  size_t middle = size / 2;

  if (size < 2) {
    return;
  }

  merge(temp, array, middle);
  merge(temp + middle, array + middle, size - middle);

  for (size_t idx = 0, left = 0, right = middle; idx < size; idx++) {
    if (right >= size) {
      temp[idx] = array[left++];
    } else if (left >= middle) {
      temp[idx] = array[right++];
    } else if (array[left] <= array[right]) {
      temp[idx] = array[left++];
    } else {
      temp[idx] = array[right++];
    }
  }
}

template <typename T>
void merge_sort(T* array, size_t size) {
  T* temp = new T[size];
  memcpy(temp, array, sizeof(T) * size);
  merge(temp, array, size);
  delete[] temp;
}

template <typename T>
void heapify(T& array, size_t array_size, size_t non_leaf_node) {
  size_t largest = non_leaf_node;
  size_t left = 2 * non_leaf_node + 1;
  size_t right = 2 * non_leaf_node + 2;
  if (left < array_size && array[left] > array[largest]) {
    largest = left;
  }
  if (right < array_size && array[right] > array[largest]) {
    largest = right;
  }
  if (largest != non_leaf_node) {
    std::swap(array[largest], array[non_leaf_node]);
    heapify(array, array_size, largest);
  }
}

template <typename T>
void heap_sort(T& array, size_t array_size) {
  for (size_t non_leaf_node = array_size / 2; non_leaf_node > 0;
       --non_leaf_node) {
    heapify(array, array_size, non_leaf_node - 1);
  }
  for (size_t non_leaf_node = array_size; non_leaf_node > 0; --non_leaf_node) {
    std::swap(array[0], array[non_leaf_node - 1]);
    heapify(array, non_leaf_node - 1, 0);
  }
}

template <typename T>
void insertion_sort(T& array, size_t array_size) {
  for (size_t index_of_current_element = 1;
       index_of_current_element < array_size; ++index_of_current_element) {
    for (size_t index_of_element_before = index_of_current_element;
         index_of_element_before > 0; --index_of_element_before) {
      if (array[index_of_element_before - 1] > array[index_of_element_before]) {
        std::swap(array[index_of_element_before - 1],
                  array[index_of_element_before]);
      } else {
        break;
      }
    }
  }
}

int main() {
  int array[] = {4, 8, 1, 5, 9, 0, 2, 7, 3, 6};
  int temp[] = {4, 8, 1, 5, 9, 0, 2, 7, 3, 6};
  size_t array_size = 10;

  // Bubble sort
  // *******
  memcpy(array, temp, sizeof(int) * array_size);
  bubble_sort(array, array_size);
  std::cout << "Bubble sort:" << std::endl;
  printar(array);
  // *******
  // Merge sort
  // *******
  merge_sort(array, array_size);
  std::cout << "Merge sort:" << std::endl;
  printar(array);
  // *******
  // Heap sort
  // *******
  memcpy(array, temp, sizeof(int) * array_size);
  heap_sort(array, array_size);
  std::cout << "Heap sort:" << std::endl;
  printar(array);
  // *******
  // Insertion sort
  // *******
  memcpy(array, temp, sizeof(int) * array_size);
  std::cout << "Insertion sort:" << std::endl;
  insertion_sort(array, array_size);
  printar(array);
  // *******

  return 0;
}
