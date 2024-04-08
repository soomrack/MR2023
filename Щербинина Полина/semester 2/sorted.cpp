#include <iostream>
using namespace std;

void swap(int* array, const int one, const int two)
{
    int tmp = array[one];
    array[one] = array[two];
    array[two] = tmp;
}

void bubble_sort(int array[], int size)
{
    for (int sorted_size = 0; sorted_size + 1 < size; sorted_size++)
    {
        for (int idx = 0; idx + 1 < size - sorted_size; idx++)
        {
            if (array[idx] > array[idx + 1])
            {
                swap(array, idx, idx + 1);
            }
        }
    }
}


void insertion_sort(int* array, const int size)
{
    for (int sort_idx = 1; sort_idx < size; sort_idx++) 
    {
        int key = array[sort_idx];
        int back_idx = sort_idx - 1;

        while (back_idx >= 0 && array[back_idx] > key) 
        {
            array[back_idx + 1] = array[back_idx];
            back_idx--;
        }

        array[back_idx + 1] = key;
    }
}


void heapify(int arr[], int n, int i) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < n && arr[left] > arr[largest])
    largest = left;
  
  if (right < n && arr[right] > arr[largest])
    largest = right;

  if (largest != i) {
    swap(arr[i], arr[largest]);
    heapify(arr, n, largest);
  }
}

void heapSort(int arr[], int n) {
  for (int i = n / 2 - 1; i >= 0; i--)
    heapify(arr, n, i);

  for (int i = n - 1; i >= 0; i--) {
    swap(arr[0], arr[i]);
    
  heapify(arr, i, 0);
  }
}

void heap_sort(int* array, int size)
{
    for (int idx = size / 2; idx >= 0; idx--)
    {
        heapify(array, idx, size);
    }

    for (int i = size - 1; i > 0; i--)
    {
        swap(array, 0, i);
        heapify(array, 0, i);
    }
}

void merge_Sort(int* arr, int size)
{
    int mid = size / 2;
    if (size % 2 == 1)
        mid++;
    int s = 1;
    int* arr1 = new int[size];
    int step;
    while (s < size)
    {
        step = s;
        int path1_i = 0;
        int path2_i = mid;
        int res_i = 0;
        while (step <= mid)
        {
            while ((path1_i < step) && (path2_i < size) && (path2_i < (mid + step))) 
            {
                if (arr[path1_i] < arr[path2_i])
                {
                    arr1[res_i] = arr[path1_i];
                    path1_i++; res_i++;
                }
                else {
                    arr1[res_i] = arr[path2_i];
                    path2_i++; res_i++;
                }
            }
            while (path1_i < step)
            {
                arr1[res_i] = arr[path1_i];
                path1_i++; res_i++;
            }
            while ((path2_i < (mid + step)) && (path2_i < size))
            {
                arr1[res_i] = arr[path2_i];
                path2_i++; res_i++;
            }
            step = step + s;
        }
      
        s = s * 2;

        for (int i = 0; i < size; i++)
            arr[i] = arr1[i];
    }

    delete[] arr1;
}

    delete[] temp_array;
}
