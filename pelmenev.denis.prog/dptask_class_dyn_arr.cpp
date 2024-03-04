#include <iostream>
#include <math.h>
#include <string.h>


typedef int ArrayItem;


class dynamic_array {
private:
    ArrayItem* data;
    size_t size;
    size_t real_size;
    size_t buf_size;
public:
    dynamic_array(size_t size_arr);
    dynamic_array(size_t size_arr, ArrayItem array[]);
    dynamic_array(dynamic_array& array);
    dynamic_array(dynamic_array&& array);
    ~dynamic_array();
public:
    dynamic_array& operator=(const dynamic_array& array);
    dynamic_array& operator=(dynamic_array&& array);
public:
    size_t get_size();
    ArrayItem* get_data();
    void set_element(size_t index, ArrayItem value);
    ArrayItem get_element(size_t index);
    void resize(size_t new_size);
    void print_array();
    void swap_elements(ArrayItem *a, ArrayItem *b);
public:
    void sort_bubble();
    void sort_insertion();
    void sort_merge();
    void sort_heap();
private:
    void split_array(size_t begin, size_t end, dynamic_array array_sort);
    void merge(size_t begin, size_t mid, size_t end, dynamic_array array_sort);
    void heap_tree(size_t sorted);
    void rebuild_tree(size_t sorted);
};


dynamic_array::dynamic_array(size_t size_arr)
{
    if (size_arr == 0) {
        data = nullptr;
        size = 0;
        real_size = 0;
        buf_size = 0;
        return;
    }

    size = size_arr;
    real_size = size + (size_t)(ceil((double)(size * 0.15)));
    buf_size = real_size - size;
    data = new ArrayItem[real_size];
}


dynamic_array::dynamic_array(size_t size_arr, ArrayItem array[])
{
    if (size_arr == 0) {
        data = nullptr;
        size = 0;
        real_size = 0;
        buf_size = 0;
        return;
    }

    size = size_arr;
    real_size = size + (size_t)(ceil((double)(size * 0.15)));
    buf_size = real_size - size;
    data = new ArrayItem[real_size];

    for (size_t idx = 0; idx < size; ++idx)
        data[idx] = array[idx];
}


dynamic_array::dynamic_array(dynamic_array& array)
{
    if (array.data == nullptr) {
        data = nullptr;
        size = 0;
        real_size = 0;
        buf_size = 0;
        return;
    }

    size = array.size;
    buf_size = array.buf_size;
    real_size = array.real_size;

    data = new ArrayItem[real_size];
    memcpy(data, array.data, array.size * sizeof(ArrayItem));
}


dynamic_array::dynamic_array(dynamic_array&& array)
{
    size = array.size;
    buf_size = array.buf_size;
    real_size = array.real_size;
    data = array.data;

    array.size = 0;
    array.buf_size = 0;
    array.real_size = 0;
    array.data = nullptr;
}


dynamic_array::~dynamic_array()
{
    size = 0;
    buf_size = 0;
    real_size = 0;
    delete[] data;
    data = nullptr;
}


void dynamic_array::print_array()
{
    if (data == nullptr) return;

    for(size_t idx = 0; idx < size; ++idx)
        std::cout << data[idx] << " ";
     
    std::cout << std::endl;
}


size_t dynamic_array::get_size()
{
    return size;
}


ArrayItem* dynamic_array::get_data()
{
    return data;
}


void dynamic_array::set_element(size_t index, ArrayItem value)
{

}


void dynamic_array::resize(size_t new_size)
{
    ArrayItem* new_data;
    
    real_size = new_size + (size_t)(ceil((double)(new_size * 0.15)));
    buf_size = real_size - new_size;
    new_data = new ArrayItem[real_size];

    for (size_t idx = 0; idx < size; ++idx)
        new_data[idx] = data[idx];
    
    data = new_data;
}


ArrayItem dynamic_array::get_element(size_t index)
{
    //if (index >= size) throw ;

    return this->data[index];
}


void dynamic_array::swap_elements(ArrayItem *a, ArrayItem *b)
{
    ArrayItem buff = *a;
    *a = *b;
    *b = buff;
}


dynamic_array& dynamic_array::operator=(const dynamic_array& array)
{
    if (this == &array) return *this;

    size = array.size;
    buf_size = array.buf_size;
    real_size = array.real_size;

    delete[] data;
    data = new ArrayItem[real_size];
    memcpy(data, array.data, array.size * sizeof(ArrayItem));
    return *this;
}


dynamic_array& dynamic_array::operator=(dynamic_array&& array)
{
    if (this == &array) return *this;
    
    size = array.size;
    buf_size = array.buf_size;
    real_size = array.real_size;
    delete[] data;
    data = array.data;

    array.size = 0;
    array.buf_size = 0;
    array.real_size = 0;
    array.data = nullptr;

    return *this;
}


void dynamic_array::sort_bubble()
{
    for (size_t sorted = size; sorted > 1; --sorted)
        for (size_t idx = 0; idx < sorted - 1; ++idx)
            if (data[idx] > data[idx + 1]) swap_elements(data + idx, data + idx + 1);
}


void dynamic_array::sort_insertion()
{
    for (size_t sorted = 1; sorted < size; ++sorted)
        for (size_t idx = sorted; idx > 0; --idx)
            if (data[idx] < data[idx - 1]) swap_elements(data + idx, data + idx - 1);
            else break;
}


void dynamic_array::merge(size_t begin, size_t mid, size_t end,  dynamic_array sorting)
{
    size_t l_count = begin;
    size_t r_count = mid;

    for (size_t idx = begin; idx < end; ++idx) {
        if ((l_count < mid) && (r_count >= end || sorting.data[l_count] <= sorting.data[r_count])) {
            data[idx] = sorting.data[l_count];
            l_count++;
        } else {
            data[idx] = sorting.data[r_count];
            r_count++;
        }
    }
}


void dynamic_array::split_array(size_t begin, size_t end, dynamic_array sorting)
{
    if (end - begin <= 1) return;

    sorting.split_array(begin, begin + (end - begin) / 2, *this);
    sorting.split_array(begin + (end - begin) / 2, end, *this);

    merge(begin, begin + (end - begin) / 2, end, sorting);
}


void dynamic_array::sort_merge()
{
    dynamic_array sorting = *this;

    split_array(0, size, sorting);
}


void dynamic_array::rebuild_tree(size_t sorted)
{
    for (size_t idx = 0; idx < sorted / 2; idx++) {
        while (2*idx + 2 <= sorted) {
            if (2*idx + 2 == sorted ) {
                if (data[idx] < data[2*idx + 1])
                    swap_elements(data + idx, data + 2*idx + 1);
                
                idx = 2*idx + 1;
                break;
            }

            if ((data[idx] >= data[2*idx + 1]) && (data[idx] >= data[2*idx + 2]))
                break;
        
            if (data[2*idx + 1] > data[2*idx + 2]) {
                swap_elements(data + idx, data + 2*idx + 1);
                idx = 2*idx + 1;
            } else {
                swap_elements(data + idx, data + 2*idx + 2);
                idx = 2*idx + 2;
            }
        }
    }
}


void dynamic_array::heap_tree(size_t sorted)
{
    do {

    size_t length = sorted;

    if (length % 2 == 0) {
        if (data[length - 1] > data[(length - 2) / 2])
            swap_elements(data + length - 1, data + (length - 2) / 2);

        length--;
    }

    size_t half = sorted / 2;
  
    for (size_t idx = length - 1; idx >= half; idx -= 2) {
        if ((data[idx] > data[(idx - 2) / 2]) || (data[idx - 1] > data[(idx - 2) / 2])) {
            if (data[idx] >= data[idx - 1])
                swap_elements(data + idx, data + (idx - 2) / 2);
            else
                swap_elements(data + idx - 1, data + (idx - 2) / 2);
        }
    }

    sorted = sorted / 2;

    } while (sorted> 2);
}


void dynamic_array::sort_heap()
{
    heap_tree(size);

    rebuild_tree(size);

    swap_elements(data + 0, data + size - 1);
    
    for (size_t sorted = size - 1; sorted > 1; --sorted) {
        rebuild_tree(sorted);

        swap_elements(data + 0, data + sorted - 1);
    }
}


int main()
{
    ArrayItem a[] = {5, 4, 1, 3, 7, 3, 9, 0};
    size_t a_size = 8;

    dynamic_array array(a_size, a);
    array.print_array();

    std::cout << "______________" << std::endl;

    //array.sort_bubble();
    //array.sort_insertion();
    //array.sort_heap();
    array.sort_merge();

    array.print_array();

    return 0;
}
