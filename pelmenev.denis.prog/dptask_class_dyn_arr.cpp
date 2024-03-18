#include <iostream>
#include <math.h>
#include <string.h>
#include <string>


typedef int ArrayItem;


class dynamic_array {
private:
    ArrayItem* data;
    size_t size;
    size_t real_size;
    size_t buf_size;
public:
    size_t buf_size_global = 5;
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


class dynamic_array_exception: public std::exception {
private:
    std::string msg;
public:
    dynamic_array_exception(std::string msg) : msg{msg} {}
    std::string get_message() const { return msg; }
};

dynamic_array_exception OUT_OF_RANGE("Index is out of range\n");
dynamic_array_exception ZERO_LENGTH("Array can't have zero length\n");
dynamic_array_exception NULL_ARRAY("Your array is not allocated");


dynamic_array::dynamic_array(size_t size_arr)
{
    if (size_arr == 0) {
        data = nullptr;
        size = 0;
        real_size = 0;
        buf_size = 0;
        throw ZERO_LENGTH;
    }

    size = size_arr;
    buf_size = buf_size_global;
    real_size = size + buf_size;
    data = new ArrayItem[real_size];
}


dynamic_array::dynamic_array(size_t size_arr, ArrayItem array[])
{
    if (size_arr == 0) {
        data = nullptr;
        size = 0;
        real_size = 0;
        buf_size = 0;
        throw ZERO_LENGTH;
    }

    size = size_arr;
    buf_size = buf_size_global;
    real_size = size + buf_size;
    data = new ArrayItem[real_size];

    for (size_t idx = 0; idx < size; ++idx)
        data[idx] = array[idx];

    for (size_t idx = size; idx < real_size; ++ idx)
        data[idx] = 0;
}


dynamic_array::dynamic_array(dynamic_array& array)
{
    if (array.data == nullptr) {
        data = nullptr;
        size = 0;
        real_size = 0;
        buf_size = 0;
        throw NULL_ARRAY;
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
    real_size = array.real_size;
    buf_size = array.buf_size;
    data = array.data;

    array.size = 0;
    array.buf_size = 0;
    array.real_size = 0;
    array.data = nullptr;
}


dynamic_array::~dynamic_array()
{
    size = 0;
    real_size = 0;
    buf_size = 0;
    delete[] data;
    data = nullptr;
}


void dynamic_array::print_array()
{
    if (data == nullptr) throw NULL_ARRAY;

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
    if ((index >= size) && (index < real_size)) {
        data[index] = value;
        buf_size = real_size - index - 1;

        for (size_t idx = size; idx < index; ++idx)
            data[idx] = 0;
        
        size = index + 1;

        return;
    }

    if ((index > size) && (index >= real_size)) {
        resize(index + 1);
    }

    data[index] = value;
}


void dynamic_array::resize(size_t new_size)
{
    if (new_size < real_size) {
        size = new_size;
        buf_size = real_size - size;
        return;
    }

    ArrayItem* new_data;
    
    real_size = new_size + buf_size_global;
    new_data = new ArrayItem[real_size];

    for (size_t idx = 0; idx < size; ++idx)
        new_data[idx] = data[idx];
    
    for (size_t idx = size; idx < real_size; ++ idx)
        new_data[idx] = 0;
    
    size = new_size;
    delete[] data;
    data = new_data;
}


ArrayItem dynamic_array::get_element(size_t index)
{
    if (index >= size) throw OUT_OF_RANGE;

    return this->data[index];
}


void dynamic_array::swap_elements(ArrayItem *a, ArrayItem *b)
{
    *b = *b ^ *a;
    *a = *b ^ *a;
    *b = *a ^ *b;
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
    if (data == nullptr) throw NULL_ARRAY;

    for (size_t sorted = size; sorted > 1; --sorted)
        for (size_t idx = 0; idx < sorted - 1; ++idx)
            if (data[idx] > data[idx + 1]) swap_elements(data + idx, data + idx + 1);
}


void dynamic_array::sort_insertion()
{
    if (data == nullptr) throw NULL_ARRAY;

    for (size_t sorted = 1; sorted < size; ++sorted)
        for (size_t idx = sorted; idx > 0; --idx) {
            if (data[idx] < data[idx - 1]) swap_elements(data + idx, data + idx - 1);
            else break;
        }
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
    if (data == nullptr) throw NULL_ARRAY;

    dynamic_array sorting = *this;

    split_array(0, size, sorting);
}


void dynamic_array::rebuild_tree(size_t sorted)
{
    size_t idx = 0;

    while (2*idx + 2 <= sorted) {
        if (2*idx + 2 == sorted ) {
            if (data[idx] < data[2*idx + 1])
                swap_elements(data + idx, data + 2*idx + 1);
            
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


void dynamic_array::heap_tree(size_t sorted)
{
    if (sorted == 1) return;

    size_t aber = 0;

    if (sorted % 2 == 0) {
        if (data[(size - 2) / 2] < data[size - 1])
            swap_elements(data + (size - 2) / 2, data + size - 1);
        
        aber++;
    }

    for (size_t idx = sorted / 2 - aber; idx > 0; idx--) {
        if ((data[idx - 1] < data[2 * idx - 1]) || (data[idx - 1] < data[2 * idx])) {
            if (data[2 * idx] >= data[2 * idx - 1]) {
                swap_elements(data + idx - 1, data + 2 * idx);
                continue;
            } else {
                swap_elements(data + idx - 1, data + 2 * idx - 1);
                continue;
            }
        }
    }

    rebuild_tree(sorted);
}


void dynamic_array::sort_heap()
{
    if (data == nullptr) throw NULL_ARRAY;

    heap_tree(size);
    
    for (size_t sorted = size; sorted > 1; --sorted) {
        swap_elements(data + 0, data + sorted - 1);

        rebuild_tree(sorted - 1);
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
    array.sort_heap();
    //array.sort_merge();

    array.print_array();

    return 0;
}
