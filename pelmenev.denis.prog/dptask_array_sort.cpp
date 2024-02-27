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
    ArrayItem buff = a;            // через xor
    a = b;
    b = buff;
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
        for (size_t idx = sorted; idx > 0; --idx)
            if (array[idx] < array[idx - 1]) swap_elements(array[idx], array[idx - 1]);
            else break;
}


/* void merge(size_t begin, size_t mid, size_t end, std::vector <ArrayItem> &array, std::vector <ArrayItem> &array_sort)
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


void split_array(size_t begin, size_t end, std::vector <ArrayItem> &array, std::vector <ArrayItem> &array_sort)
{
    size_t arr_size = end - begin;

    if (arr_size <= 1) return;

    size_t mid = arr_size - arr_size / 2;
    //std::cout << begin << " " << mid << " " << end << std::endl;                //DEBUG

    split_array(begin, mid, array_sort, array);
    split_array(mid, end, array_sort, array);

    merge(begin, mid, end, array, array_sort);
}


void sort_merge(std::vector <ArrayItem> &array, std::vector <ArrayItem> &array_sort)
{
    copy_array(array, array_sort);

    split_array(0, array.size(), array, array_sort);
} */


void rebuild_tree(ArrayItem array[], size_t sorted)
{
    for (size_t idx = 0; idx < sorted / 2; idx++) {
        while (2*idx + 2 <= sorted) {
            if (2*idx + 2 == sorted ) {
                if (array[idx] < array[2*idx + 1])
                    swap_elements(array[idx], array[2*idx + 1]);
                
                idx = 2*idx + 1;
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
}


void heap_tree(ArrayItem array[], size_t size)
{
    do {

    size_t length = size;

    if (length % 2 == 0) {
        if (array[length - 1] > array[(length - 2) / 2])
            swap_elements(array[length - 1], array[(length - 2) / 2]);

        length--;
    }

    size_t half = size / 2;
  
    for (size_t idx = length - 1; idx >= half; idx -= 2) {
        if ((array[idx] > array[(idx - 2) / 2]) || (array[idx - 1] > array[(idx - 2) / 2])) {
            if (array[idx] >= array[idx - 1])
                swap_elements(array[idx], array[(idx - 2) / 2]);
            else
                swap_elements(array[idx - 1], array[(idx - 2) / 2]);
        }
    }

    size = size / 2;

    } while (size > 2);
}


void sort_heap(ArrayItem array[], size_t size)
{
    heap_tree(array, size);

    rebuild_tree(array, size);

    swap_elements(array[0], array[size - 1]);
    
    for (size_t sorted = size - 1; sorted > 1; --sorted) {
        rebuild_tree(array, sorted);

        swap_elements(array[0], array[sorted - 1]);
    }
}


int main()
{
    ArrayItem a[] = {5, 4, 1, 3, 7, 3, 2, 0, 9, 6, 8};
    size_t a_size = 11;
    ArrayItem b[11];
    print_array(a, a_size);
    std::cout << "______________" << std::endl;
    //sort_bubble(a, a_size);
    //sort_insertion(a, a_size);
    //sort_merge(a, a_size, b);
    sort_heap(a, a_size);
    std::cout << "______________" << std::endl;
    print_array(a, a_size);

    return 0;
}
