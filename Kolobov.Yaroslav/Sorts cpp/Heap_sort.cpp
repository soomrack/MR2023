#include <iostream>

using namespace std;

void print_array(int* array, int num_of_elements)
{
    for (int pr_elem = 0; pr_elem < num_of_elements; ++pr_elem) {
        cout << array[pr_elem] << " ";
    }
    cout << endl;
}

void heapify(int* array, int num_of_elements, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < num_of_elements && array[left] > array[largest]) {
        largest = left;
    }

    if (right < num_of_elements && array[right] > array[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(array[i], array[largest]);
        heapify(array, num_of_elements, largest);
    }
}

void build_heap(int* array, int num_of_elements)
{
    for (int i = num_of_elements / 2 - 1; i >= 0; i--) {
        heapify(array, num_of_elements, i);
    }
}

void heap_sort(int* array, int num_of_elements)
{
    build_heap(array, num_of_elements);

    for (int i = num_of_elements - 1; i >= 0; i--) {
        swap(array[0], array[i]);
        heapify(array, i, 0);
    }
}

int main()
{
    int num_of_elements = 7;
    int* array = new int[num_of_elements] {5, 4, 3, 2, 1, 6, 7};

    print_array(array, num_of_elements);

    heap_sort(array, num_of_elements);

    print_array(array, num_of_elements);

    return 0;
}