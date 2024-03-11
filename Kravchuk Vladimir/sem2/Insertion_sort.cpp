#include <algorithm>
#include <iostream>
#include <vector>

void insertion(int* array, int size)
{
    for (int idx = 1; idx < size; ++idx) {
        int sortedIdx = idx;
        int buff = array[idx];
        for (; sortedIdx > 0 && array[sortedIdx - 1] > buff; --sortedIdx) {
            array[sortedIdx] = array[sortedIdx - 1];
        }
        array[sortedIdx] = buff;
    }

}

void printArray(int* array, int size)
{
    std::cout << "\nSorted array: ";
    for (int idx = 0; idx < size; idx++) {
        std::cout << array[idx] << " ";
    }
}

void initialization()
{
    int array[] = {20, 8, 7, 15, 10, 6};
    int size = std::end(array) - std::begin(array);

    insertion(array, size);

    printArray(array, size);
}

int main()
{
    initialization();

    return 0;
}
