#include <algorithm>
#include <iostream>
#include <vector>

void bubble(std::vector<int>& array)
{
    int size = array.size();
    for (size_t numberElements = size; numberElements > 1; numberElements--) {
        for (size_t idx = 0; idx < size - 1; idx++) {
            if (array[idx] > array[idx + 1]) std::swap(array[idx], array[idx + 1]);
        }
    }

}

void printArray(int size, std::vector<int>& array)
{
    std::cout << "\nSorted array: ";
    for (int idx = 0; idx < size; idx++) {
        std::cout << array[idx] << " ";
    }
}

void initialization()
{
    std::vector<int> array = { 20, 8, 7, 15, 10, 6 };
    int size = array.size();

    bubble(array);

    printArray(size, array);
}

int main()
{
    initialization();

    return 0;
}
