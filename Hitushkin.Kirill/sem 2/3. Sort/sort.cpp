#include <iostream>


void swap(int* array, const int one, const int two)
{
    int tmp = array[one];
    array[one] = array[two];
    array[two] = tmp;
}


void bubble_sort(int* array, int size)
{
    for (int sorted_size = 0; sorted_size + 1 < size; sorted_size++)
    {
        for (int idx = 0; idx + 1 < size - sorted_size; idx++)
        {
            if (array[idx] > array[idx + 1])
            {
                swap(array, idx, idx + 1);
            }
        }
    }
}


void insertion_sort(int* array, const int size)
{
    for (int sort_idx = 1; sort_idx < size; sort_idx++) 
    {
        int key = array[sort_idx];
        int back_idx = sort_idx - 1;

        while (back_idx >= 0 && array[back_idx] > key) 
        {
            array[back_idx + 1] = array[back_idx];
            back_idx--;
        }

        array[back_idx + 1] = key;
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


void merge_sort(int* array, int size)
{
    int* temp_array = new int[size];
    
    int* sorted_array = temp_array;
    int* output_array = array;
    
    for (int block_size = 1; block_size < size; block_size *= 2)
    {
        for (int block_idx = 0; block_idx < size; block_idx += 2 * block_size)
        {
            int left_idx = 0;
            int right_idx = 0;

            int left_border = block_idx;
            int mid_border = block_idx + block_size;
            int right_border = block_idx + 2 * block_size;
            
            right_border = (right_border < size) ? right_border : size;

            while (left_border + left_idx < mid_border && mid_border + right_idx < right_border)
            {
                if (output_array[left_border + left_idx] < output_array[mid_border + right_idx])
                {
                    sorted_array[left_border + left_idx + right_idx] = output_array[left_border + left_idx];
                    left_idx++;
                }
                else
                {
                    sorted_array[left_border + left_idx + right_idx] = output_array[mid_border + right_idx];
                    right_idx++;
                }
            }

            while (left_border + left_idx < mid_border)
            {
                sorted_array[left_border + left_idx + right_idx] = output_array[left_border + left_idx];
                left_idx++;
            }

            while (mid_border + right_idx < right_border)
            {
                sorted_array[left_border + left_idx + right_idx] = output_array[mid_border + right_idx];
                right_idx++;
            }
        }

        std::swap(output_array, sorted_array);
    }

    if (output_array != array) 
    {
        std::swap(output_array, sorted_array);
        memcpy(output_array, sorted_array, size * sizeof(int));
    }

    delete[] temp_array;
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

    int arrayFour[11] = { -1, 3, 2, -11, 4, -5, 0, -3, 22, 7, -12 };
    int sizeFour = 11;

    merge_sort(arrayFour, sizeFour);
    print_array(arrayFour, sizeFour);

    return 0;
}