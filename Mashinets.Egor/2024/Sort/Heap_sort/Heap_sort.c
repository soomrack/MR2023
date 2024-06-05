#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void print_arr(int *arr, int size) {
  for (int idx = 0; idx < size; idx++) {
    printf("%d ", arr[idx]);
  }
  printf("\n");
}

void heap_sort(int *arr, int size) {
  // Строим бинарное дерево
  for (int idx = size / 2 - 1; idx >= 0; idx--) {
    heapify(arr, size, idx);
  }

  // Извлекаем элементы из дерева в порядке убывания по индексу
  for (int idx = size - 1; idx > 0; idx--) {
    swap(&arr[0], &arr[idx]);

    heapify(arr, idx, 0);
  }
}

void heapify(int *arr, int size, int idx) {
  int largest = idx;
  int left = 2 * idx + 1;
  int right = 2 * idx + 2;

  if (left < size && arr[left] > arr[largest]) {
    largest = left;
  }

  if (right < size && arr[right] > arr[largest]) {
    largest = right;
  }

  if (largest != idx) {
    swap(&arr[idx], &arr[largest]);
    heapify(arr, size, idx);
  }
}

int main() {
  int arr[] = {100, 7, 8, -9, 1, 5};
  int size = sizeof(arr) / sizeof(arr[0]);

  heap_sort(arr, size);

  print_arr(arr, size);

  return 0;
}










