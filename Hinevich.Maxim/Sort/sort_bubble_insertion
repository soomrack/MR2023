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

void bubble_sort(int* array, int array_size)
{
    for (int unsorted = 0; unsorted < array_size; unsorted++)
    {
        for (int item = 0; item < array_size - unsorted - 1; item++) 
        {
            if (array[item] > array[item + 1])
            {
                swap(array[item], array[item + 1]);
            }
        }
     }
}


void insertion_sort(int* array, int array_size)
{
    for (int sort_idx = 1; sort_idx < array_size; sort_idx++)
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



int main()
{

    int arr_size = 5;
    int* arr = new int[5] { 5, 3, 8, -7, 10 };
    print_arr(arr, arr_size);
    bubble_sort(arr, arr_size);
    print_arr(arr, arr_size);
    delete[] arr;

    int* arr1 = new int[5] { 11, 5, 4, 6, 20};
    print_arr(arr, arr_size);
    insertion_sort(arr1, arr_size);
    print_arr(arr, arr_size);
    delete[] arr1;

    return 0;
}
