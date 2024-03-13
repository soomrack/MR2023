#include <iostream>
#include <math.h>


typedef int ArrayItem;


void print_array(const ArrayItem array[], size_t size)
{
    for(size_t idx = 0; idx < size; ++idx)
        std::cout << array[idx] << " ";
     
    std::cout << std::endl;
}


void swap_elements(ArrayItem &a, ArrayItem &b)
{
    b = b ^ a;
    a = b ^ a;
    b = a ^ b;
}


// copies data from array_one to array_two
void copy_array(ArrayItem array_one[], ArrayItem array_two[], size_t size)
{
    for (size_t idx = 0; idx < size; ++idx)
        array_two[idx] = array_one[idx];
}


void sort_bubble(ArrayItem array[], size_t size)
{
    for (size_t sorted = size; sorted > 1; --sorted)
        for (size_t idx = 0; idx < sorted - 1; ++idx)
            if (array[idx] > array[idx+1]) swap_elements(array[idx], array[idx+1]);
}


void sort_insertion(ArrayItem array[], size_t size)
{
    for (size_t sorted = 1; sorted < size; ++sorted)
        for (size_t idx = sorted; idx > 0; --idx) {
            if (array[idx] < array[idx - 1]) swap_elements(array[idx], array[idx - 1]);
            else break;
        }
}


void merge(size_t begin, size_t mid, size_t end, ArrayItem array[], ArrayItem array_sort[])
{
    size_t l_count = begin;
    size_t r_count = mid;

    for (size_t idx = begin; idx < end; ++idx) {
        if ((l_count < mid) && (r_count >= end || array_sort[l_count] <= array_sort[r_count])) {
            array[idx] = array_sort[l_count];
            l_count++;
        } else {
            array[idx] = array_sort[r_count];
            r_count++;
        }
    }
}


void split_array(size_t begin, size_t end, ArrayItem array[], ArrayItem array_sort[])
{
    if (end - begin <= 1) return;

    split_array(begin, begin + (end - begin) / 2, array_sort, array);
    split_array(begin + (end - begin) / 2, end, array_sort, array);

    merge(begin, begin + (end - begin) / 2, end, array, array_sort);
}


void sort_merge(ArrayItem array[], size_t size)
{
    ArrayItem* array_sort;
    array_sort = new ArrayItem[size];
    copy_array(array, array_sort, size);

    split_array(0, size, array, array_sort);

    delete[] array_sort;
}


void rebuild_tree(ArrayItem array[], size_t sorted)
{
    size_t idx = 0;

    while (2*idx + 2 <= sorted) {
        if (2*idx + 2 == sorted ) {
            if (array[idx] < array[2*idx + 1])
                swap_elements(array[idx], array[2*idx + 1]);
            
            break;
        }

        if ((array[idx] >= array[2*idx + 1]) && (array[idx] >= array[2*idx + 2]))
            break;
        
        if (array[2*idx + 1] > array[2*idx + 2]) {
            swap_elements(array[idx], array[2*idx + 1]);
            idx = 2*idx + 1;
        } else {
            swap_elements(array[idx], array[2*idx + 2]);
            idx = 2*idx + 2;
        }
    }
}


void heap_tree(ArrayItem array[], size_t size)
{
    if (size == 1) 
        return;
    
    for (size_t idx = size / 2; idx > 0; idx--) {
        if ((idx == size / 2) && (size % 2 == 0))
            if (array[idx - 1] < array[2 * idx + 1]) {
                swap_elements(array[idx], array[2 * idx - 1]);
                continue;
            } else continue;

        if ((array[idx - 1] < array[2 * idx - 1]) || (array[idx - 1] < array[2 * idx])) {
            if (array[2 * idx] >= array[2 * idx - 1]) {
                swap_elements(array[idx - 1], array[2 * idx]);
                continue;
            } else {
                swap_elements(array[idx - 1], array[2 * idx - 1]);
                continue;
            }
        }
    }
}


void sort_heap(ArrayItem array[], size_t size)
{
    heap_tree(array, size);
    
    for (size_t sorted = size; sorted > 1; --sorted) {
        swap_elements(array[0], array[sorted - 1]);

        rebuild_tree(array, sorted - 1);
    }
}


int main()
{
    ArrayItem a[] = {5, 4, 1, 3, 7, 3, 9, 0, 8};
    size_t a_size = 9;
    print_array(a, a_size);
    std::cout << "______________" << std::endl;
    //sort_bubble(a, a_size);
    //sort_insertion(a, a_size);
    //sort_merge(a, a_size);
    sort_heap(a, a_size);
    std::cout << "______________" << std::endl;
    print_array(a, a_size);

    return 0;
}
