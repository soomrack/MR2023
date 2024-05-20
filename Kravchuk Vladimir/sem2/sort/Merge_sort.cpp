#include <iostream>
#include <vector>
#include <cstring>

void merge(int* array, int initial, int middle, int last, int* buff)
{
    int i = initial;
    int j = middle + 1;
    int k = initial;

    while (i <= middle && j <= last) {
        if (array[i] <= array[j]) {
            buff[k] = array[i];
            i++;
        }
        else {
            buff[k] = array[j];
            j++;
        }
        k++;
    }

    while (i <= middle) {
        buff[k] = array[i];
        i++;
        k++;
    }

    while (j <= last) {
        buff[k] = array[j];
        j++;
        k++;
    }
}

void sort(int* array, int initial, int last, int* buff)
{
    if (initial < last) {
        int middle = initial + (last - initial) / 2;

        sort(buff, initial, middle, array);
        sort(buff, middle + 1, last, array);

        merge(array, initial, middle, last, buff);
    }
}

void printArray(int size, int* array)
{
    std::cout << "\nSorted array: ";
    for (int idx = 0; idx < size; idx++) {
        std::cout << array[idx] << " ";
    }
}

void initialization()
{
    int array[] = { 1, 11, 7, 5, 9, 10, 14, 15 };
    int size = std::end(array) - std::begin(array);

    int* buff = new int[size];

    sort(array, 0, size - 1, buff);

    delete[] buff;

    printArray(size, array);
}

int main()
{
    initialization();

    return 0;
}
