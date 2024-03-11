#include <iostream>
using namespace std;


void merge_sort(int* help_array, int* array, int array_size)
{
    int middle = array_size / 2;

    if (array_size < 2) return;

    merge_sort(help_array, array, middle);
    merge_sort(help_array + middle, array + middle, array_size - middle);

    for (int idx = 0, left = 0, right = middle; idx < array_size; idx++) {
        if (right >= array_size) help_array[idx] = array[left++];
        else if (left >= middle) help_array[idx] = array[right++];
        else if (array[left] <= array[right]) help_array[idx] = array[left++];
        else help_array[idx] = array[right++];
    }

    for (int i = 0; i < array_size; i++) {
        array[i] = help_array[i];
    }
}


void array_print(int array_size, int* array)
{
    for (int elem = 0; elem < array_size; ++elem) {
        cout << array[elem] << " ";
    }
    cout << "\n";
}


void initialization() 
{
    int array_size = 10;
    int* array = new int[10] { 2, 4, 1, 11, 9, 7, 4, 9, 50, 20 };
    int help_array_size = 10;
    int* help_array = new int[10];

    array_print(array_size, array);
  
    merge_sort(help_array, array, array_size);
    array_print(array_size, array);

    delete[] array;
    delete[] help_array;
}


int main() 
{
    initialization();
}