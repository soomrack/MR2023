#include <iostream>
using namespace std;


void merge(int* help_array, int* array, int array_size)
{
    int middle = array_size / 2;

    if (array_size < 2) return;

    merge(array, help_array, middle);
    merge(array + middle, help_array + middle, array_size - middle);

    for (int idx = 0, left = 0, right = middle; idx < array_size; idx++) {
        if (right >= array_size) help_array[idx] = array[left++];
        else if (left >= middle) help_array[idx] = array[right++];
        else if (array[left] <= array[right]) help_array[idx] = array[left++];
        else help_array[idx] = array[right++];
    }
}

void merge_sort(int* array, int array_size)
{
    int* help_array = new int[array_size];
    memcpy(help_array, array, sizeof(int) * array_size);
    merge(help_array, array, array_size);
    delete[] help_array;
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

    array_print(array_size, array);
    merge_sort(array, array_size);
    array_print(array_size, array);

    delete[] array;
}


int main() 
{
    initialization();
}