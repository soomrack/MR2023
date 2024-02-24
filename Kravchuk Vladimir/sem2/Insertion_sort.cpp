#include <algorithm>
#include <iostream>
#include <vector>

void insertion(std::vector<int>& array, int size)
{
    for (size_t sorted = 1; sorted < size; sorted++) {
        for (size_t idx = sorted; idx > 0; idx--) {
            if (array[idx] < array[idx - 1]) std::swap(array[idx], array[idx - 1]);
        }
    }

}

void printArray(std::vector<int>& array, int size)
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

    insertion(array, size);

    printArray(array, size);
}

int main()
{
    initialization();

    return 0;
}
