#include <iostream>
using namespace std;


void merge(int* array, int begin, int middle, int end) 
{
    int left = begin;
    int right = middle + 1;

    while (left <= middle && right <= end) {
        if (array[left] > array[right]) {
            int temp = array[right];
            for (int i = right; i > left; i--) {
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
    if (begin < end) {
        int middle = (begin + end) / 2;
        merge_sort(array, begin, middle);
        merge_sort(array, middle + 1, end);
        merge(array, begin, middle, end);
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

    array_print(array_size, array);
    merge_sort(array, 0, array_size - 1);
    array_print(array_size, array);

    delete[] array;
}


int main() 
{
    initialization();
}