#include <iostream>

#include <math.h>
#include <cstdlib>

using namespace std;

typedef int ArrayItem;


void print_array(const ArrayItem array[], size_t size)
{
    for (size_t idx = 0; idx < size; ++idx)
        std::cout << array[idx] << " ";

    std::cout << std::endl;
}


void swap_elements(ArrayItem& a, ArrayItem& b)
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
            if (array[idx] > array[idx + 1]) swap_elements(array[idx], array[idx + 1]);
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
        }
        else {
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


void heap_tree(ArrayItem array[], size_t size, int index) {
    int max = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && array[left] > array[max]) max = left;

    if (right < size && array[right] > array[max]) max = right;

    if (max != index) {
        swap_elements(array[index], array[max]);

        heap_tree(array, size, max);
    }
}


void sort_heap(ArrayItem array[], size_t size)
{
    for (int idx = size / 2 - 1; idx >= 0; idx--)
        heap_tree(array, size, idx);

    for (int idx = size - 1; idx > 0; idx--) {
        swap_elements(array[0], array[idx]);

        heap_tree(array, idx, 0);
    }
}


int main()
{
    size_t a_size = 10;
    ArrayItem* a;
    a = new ArrayItem[a_size];

    for (size_t i = 0; i < a_size; i++) {
        a[i] = std::rand();
    }

    print_array(a, a_size);
    std::cout << "______________" << std::endl;

    //sort_bubble(a, a_size);
    //sort_insertion(a, a_size);
    //sort_merge(a, a_size);

    sort_heap(a, a_size);

    std::cout << "______________" << std::endl;
    print_array(a, a_size);


    /*int A[] = {2, 4, 6, 8, 10, 1, 3, 5, 7, 9};

    for (int i = 0; i < 10; i++)
        cout << " " << A[i];*/
    return 0;
}