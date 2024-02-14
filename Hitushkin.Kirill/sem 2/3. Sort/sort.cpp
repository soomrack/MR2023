#include <iostream>


void swap(int* array, const int one, const int two)
{
	int tmp = array[one];
	array[one] = array[two];
	array[two] = tmp;
}


void bubble_sort(int* array, int size)
{
	for (int i = 0; i + 1 < size; i++)
	{
		for (int j = 0; j + 1 < size - i; j++)
		{
			if (array[j] > array[j + 1])
			{
				swap(array, j, j + 1);
			}
		}
	}
}


void insertion_sort(int* array, const int size)
{
    for (int i = 1; i < size; i++) 
    {
        int key = array[i];
        int j = i - 1;

        while (j >= 0 && array[j] > key) 
        {
            array[j + 1] = array[j];
            j--;
        }

        array[j + 1] = key;
    }
}


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


void heap_sort(int* array, int size)
{
	build_heap(array, size);

	for (int i = size - 1; i > 0; i--)
	{
		swap(array, 0, i);
		heapify(array, 0, i);
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
	int arrayOne[6] = { 4, 3, 6, 1, 2, 5 };
	int sizeOne = 6;

	bubble_sort(arrayOne, sizeOne);
	print_array(arrayOne, sizeOne);

	int arrayTwo[10] = { -1, 4, 3, -7, 6, 11, 13, -75, 100, 66 };
	int sizeTwo = 10;

	insertion_sort(arrayTwo, sizeTwo);
	print_array(arrayTwo, sizeTwo);

	int arrayThree[11] = { 5, 33, 7, 11, 66, -87, 0, -3, 32, 10, 99 };
	int sizeThree = 11;

	heap_sort(arrayThree, sizeThree);
	print_array(arrayThree, sizeThree);

	return 0;
}