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


void MergeSort(int* array, int start, int end)
{
    if (start < end) {

        MergeSort(array, start, (start + end) / 2);
        MergeSort(array, (start + end) / 2 + 1, end);
        Merge(array, start, end);
    }
}


void Merge(int* array, int first, int last) {
    int left_iterator, right_iterator, middle;
    int* mas;
    int mas = int* malloc(last - first) * sizeof(int);

    middle = (first + last) / 2;
    left_iterator = first;
    right_iterator = middle + 1;

    for (int j = first; j <= last; j++)
    {
        if ((left_iterator <= middle) && ((right_iterator > last) || (array[left_iterator] < array[left_iterator]))) {
            *(mas + j - first) = array[left_iterator];
            left_iterator++;
        }
        else {
            *(mas + j - first) = array[right_iterator];
            right_iterator++;
        }
    }

    for (int j = first; j <= last; j++) {
        array[j] = *(mas + j - first);
    }
}



int main()
{
    int arr_size = 5;
    int* arr = new int[5] { 8, 4, 1, 11, 20 };
    print_arr(arr, arr_size);
    MergeSort(arr, 1, arr_size);
    print_arr(arr, arr_size);
    delete[] arr;
    return 0;
}

