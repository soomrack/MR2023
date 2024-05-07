#include <iostream>

using namespace std;

void print_arr(int* m, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << m[i] << " ";
    }

    cout << endl;
}

void heapify(int* arr, int size, int idx)
{
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
        swap(arr[idx], arr[largest]);
        heapify(arr, size, idx);
    }
}

void heap_sort(int* arr, int size)
{
    for (int idx = size / 2 - 1; idx >= 0; idx--)
    {
        heapify(arr, size, idx);
    }
    for (int idx = size - 1; idx > 0; idx--)
    {
        swap(arr[0], arr[idx]);

        heapify(arr, idx, 0);
    }
}

int main()
{
    int size = 5;
    int* arr = new int[5] { 5, 8, 3, -33, 75 };
    print_arr(arr, size);
    heap_sort(arr, size);
    print_arr(arr, size);
    delete[] arr;
    return 0;
}