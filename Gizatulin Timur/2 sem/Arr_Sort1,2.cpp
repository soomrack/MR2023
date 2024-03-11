#include <iostream>

using namespace std;

void Swap(int* A, int* B)
{
    int tmp = *A;
    *A = *B;
    *B = tmp;
}

void swap_func(int* array, int index)
{
    int swap = array[index];
    array[index] = array[index + 1];
    array[index + 1] = swap;
}

void print_arr(int* m, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << m[i] << " ";
    }

    cout << endl;
}

void bubble_sort(int* array, int array_size)
{
    for (int index_1 = 0; index_1 < array_size; ++index_1) {
        for (int index_2 = 0; index_2 < array_size - index_1 - 1; ++index_2) {
            if (array[index_2] > array[index_2 + 1]) {
                swap_func(array, index_2);
            }
        }
    }
    print_arr(array, array_size);
}



void insertion_sort(int* Arr, int array_size)
{
    for (int index_1 = 1; index_1 < array_size; index_1++)
    {
        for (int index_2 = index_1;
            (index_2 > 0) && (Arr[index_2] < Arr[index_2 - 1]); index_2--)
        {
            Swap(&Arr[index_2], &Arr[index_2 - 1]);
        }
    }
    print_arr(Arr, array_size);
}


int main()
{

    int arr_size = 5;
    int* arr = new int[5] { 8, 4, 1, 11, 20 };

    print_arr(arr, arr_size);

    bubble_sort(arr, arr_size);

    delete[] arr;

    int* arr1 = new int[5] { 8, 4, 1, 11, 30};
    print_arr(arr1, arr_size);

    insertion_sort(arr1, arr_size);

    delete[] arr1;

    return 0;
}