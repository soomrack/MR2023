#include <iostream>


void heapify(int* array, int index, int size)
{  
    int index_ = index;
    
    while ( true )
    {
        int left = 2 * index_ + 1;
        int right = 2 * index_ + 2;
        int largest = index_;

        if (left < size && array[left] > array[largest]) 
        {
            largest = left;
        }

        if (right < size && array[right] > array[largest])
        {
            largest = right;
        }

        if (largest == index_) 
        {
            break;
        }

        int temp = array[index_];
        array[index_] = array[largest];
        array[largest] = temp;
        index_ = largest;
    }
}


void build_heap(int* array, int size)
{
    for (int idx = size / 2; idx >= 0; idx--)
    {
        heapify(array, idx, size);
    }
}


void print_array(int* array, int size)
{
    for (int idx = 0; idx < size; idx++)
    {
        std::cout << array[idx] << ", ";
    }

    std::cout << std::endl;
}


int main() 
{
    int arrayOne[15] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    const int sizeOne = 15;
    int arrayTwo[10] = { 11, 23, 33, 12, 55, 113, 77, 7, 122, 200 };
    const int sizeTwo = 10;

    build_heap(arrayOne, sizeOne);
    build_heap(arrayTwo, sizeTwo);

    print_array(arrayOne, sizeOne);
    print_array(arrayTwo, sizeTwo);

    return 0;
}