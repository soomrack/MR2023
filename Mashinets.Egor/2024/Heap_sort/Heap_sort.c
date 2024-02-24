#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void print_arr(int *arr, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void heap_sort(int *arr, int size) {
  // Строим бинарное дерево
  for (int i = size / 2 - 1; i >= 0; i--) {
    heapify(arr, size, i);
  }

  // Извлекаем элементы из дерева в порядке убывания по индексу
  for (int i = size - 1; i > 0; i--) {
    swap(&arr[0], &arr[i]);

    heapify(arr, i, 0);
  }
}

void heapify(int *arr, int size, int i) {
  int largest = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;

  if (l < size && arr[l] > arr[largest]) {
    largest = l;
  }

  if (r < size && arr[r] > arr[largest]) {
    largest = r;
  }

  if (largest != i) {
    swap(&arr[i], &arr[largest]);
    heapify(arr, size, i);
  }
}

int main() {
  int arr[] = {100, 7, 8, -9, 1, 5};
  size_t size = sizeof(arr) / sizeof(arr[0]);

  heap_sort(arr, size);

  print_arr(arr, size);

  return 0;
}
