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
    for (int sorted = 0; sorted < array_size; sorted++)
    {
        for (int item = 0; item < array_size - 1; item++) 
        {
            if (array[item] > array[item + 1])
            {
                swap(array[item], array[item + 1]);
            }
        }
     }
    print_arr(array, array_size);
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
  print_arr(array, array_size);
}



int main()
{

    int arr_size = 5;
    int* arr = new int[5] { 8, 4, 1, -5, 3 };
    bubble_sort(arr, arr_size);
    delete[] arr;

    int* arr1 = new int[5] { 8, 4, 1, 11, 30};
    insertion_sort(arr1, arr_size);
    delete[] arr1;

    return 0;
}