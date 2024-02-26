#include <iostream>
#include <vector>
#include <math.h>


typedef int ArrayItem;


void print_array(const std::vector <ArrayItem> &array)
{
    for(size_t idx = 0; idx < array.size(); ++idx)
        std::cout << array[idx] << " ";
     
    std::cout << std::endl;
}


void swap_elements(ArrayItem &a, ArrayItem &b)
{
    ArrayItem buff = a;
    a = b;
    b = buff;
}


// copies data from array_one to array_two
void copy_array(std::vector <ArrayItem> &array_one, std::vector <ArrayItem> &array_two)
{
    if (!(array_two.empty()))
        array_two.clear();

    for (size_t idx = 0; idx < array_one.size(); ++idx)
        array_two.push_back(array_one[idx]);
}


void sort_bubble(std::vector <ArrayItem> &array)
{
    for (size_t sub_array = array.size(); sub_array > 1; --sub_array)
        for (size_t idx = 0; idx < sub_array - 1; ++idx)
            if (array[idx] > array[idx+1]) swap_elements(array[idx], array[idx+1]);
}


void sort_insertion(std::vector <ArrayItem> &array)
{
    for (size_t sorted = 1; sorted < array.size(); ++sorted)
        for (size_t idx = sorted; idx > 0; --idx)
            if (array[idx] < array[idx - 1]) swap_elements(array[idx], array[idx - 1]);
            else break;
}


void merge(size_t begin, size_t mid, size_t end, std::vector <ArrayItem> &array, std::vector <ArrayItem> &array_sort)
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
    if ((end - begin) <= 1) return;

    size_t mid = (size_t)(std::ceil((double)((end - begin) / 2.0)));
    std::cout << begin << " " << mid << " " << end << std::endl;

    split_array(begin, mid, array_sort, array);
    split_array(mid, end, array_sort, array);

    merge(begin, mid, end, array, array_sort);
}


void sort_merge(std::vector <ArrayItem> &array, std::vector <ArrayItem> &array_sort)
{
    copy_array(array, array_sort);

    split_array(0, array.size(), array, array_sort);
}


void heap_tree(std::vector <ArrayItem> &array, size_t sub_size)
{
    do {

    size_t length = sub_size;

    if (length % 2 == 0) {
        if (array[length - 1] > array[(length - 2) / 2])
            swap_elements(array[length - 1], array[(length - 2) / 2]);
        
        if (length == 2) return;

        length--;
    }

    size_t half = sub_size / 2;
  
    for (size_t idx = length - 1; idx >= half; idx -= 2) {
        if ((array[idx] > array[(idx - 2) / 2]) || (array[idx - 1] > array[(idx - 2) / 2])) {
            if (array[idx] >= array[idx - 1])
                swap_elements(array[idx], array[(idx - 2) / 2]);
            else
                swap_elements(array[idx - 1], array[(idx - 2) / 2]);
        }
    }

    sub_size = sub_size / 2;

    } while (sub_size > 2);
}


void sort_heap(std::vector <ArrayItem> &array)
{
    for (size_t sub_size = array.size(); sub_size > 1; --sub_size) {
        heap_tree(array, sub_size);

        swap_elements(array[0], array[sub_size - 1]);
    }
}


int main()
{
    std::vector <ArrayItem> a = {5, 4, 1, 3, 7, 3, 2, 0, 9, 6, 8};
    std::vector <ArrayItem> b;
    print_array(a);
    //sort_bubble(a);
    //sort_merge(a, b);
    sort_heap(a);
    std::cout << "______________" << std::endl;
    print_array(a);

    return 0;
}
