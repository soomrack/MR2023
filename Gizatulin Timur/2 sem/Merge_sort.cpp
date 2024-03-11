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

void merge(int* array, int begin, int middle, int end)
{
    int left = begin;
    int right = middle + 1;

    while (left <= middle && right <= end)
    {
        if (array[left] > array[right])
        {
            int temp = array[right];
            for (int i = right; i > left; i--)
            {
                array[i] = array[i - 1];
            }
            array[left] = temp;
            middle++;
            right++;
        }
        left++;
    }
}

void merge_sort(int* array, int begin, int end)
{
    if (begin < end)
    {
        int middle = (begin + end) / 2;
        merge_sort(array, begin, middle);
        merge_sort(array, middle + 1, end);
        merge(array, begin, middle, end);
    }
}


int main()
{

    int arr_size = 5;
    int* arr = new int[5] { 8, 4, 1, 11, 20 };

    print_arr(arr, arr_size);
    merge_sort(arr, 0, arr_size - 1);
    print_arr(arr, arr_size);
 

    delete[] arr;



    return 0;
}

