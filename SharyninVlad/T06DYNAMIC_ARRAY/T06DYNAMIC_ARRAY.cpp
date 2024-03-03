#include <iostream>
#include <string>
#include <cstring>
#define MAX 10
#define BUF 5

typedef int ArrayItem;

class Dynamic_array {
public:
    Dynamic_array();
    Dynamic_array(size_t length);
    ~Dynamic_array();

private:
    ArrayItem* data;
    size_t size;
    size_t buffer_size;
    void set_zero(size_t left, size_t right);

public:
    size_t get_size();
    ArrayItem* get_data();
    void set_array();
    void set_element(size_t index, ArrayItem value);
    void print_array();
    ArrayItem get_element(size_t index);
    void resize(size_t new_size);
    void set_zero();
};

Dynamic_array::Dynamic_array() {
    size = MAX;
    buffer_size = (ArrayItem)(BUF);
    data = new ArrayItem[size + buffer_size];
}

Dynamic_array::Dynamic_array(size_t length) {
    size = length;
    buffer_size = (ArrayItem)(BUF);
    data = new ArrayItem[size + buffer_size];
}

Dynamic_array::~Dynamic_array() {
    size = 0;
    buffer_size = 0;
    delete[] data;
}

size_t Dynamic_array::get_size()
{
    return size;
}

ArrayItem* Dynamic_array::get_data()
{
    return data;
}

void Dynamic_array::set_array()
{
    for (size_t idx = 0; idx < size; idx++)
        data[idx] = (ArrayItem)(rand() % 100);
}

void Dynamic_array::set_zero()
{
    for (size_t idx = 0; idx < size; idx++)
        data[idx] = 0;
}

void Dynamic_array::set_zero(size_t left, size_t right)
{
    for (size_t index = left; index <= right; index++)
        data[index] = 0;
}

void Dynamic_array::set_element(size_t index, ArrayItem value)
{
    if (index >= size + buffer_size) {
        std::cout << "Wrong choise\n\n";
        return;
    }
    if (index >= size && index < size + buffer_size) {
        set_zero(size, index);
        buffer_size = size + buffer_size - index - 1;
        size = index + 1;        
    }        
    data[index] = value;
}

void Dynamic_array::print_array()
{
    for (size_t idx = 0; idx < size; idx++)
        std::cout << data[idx] << "\t";
    std::cout << "\n \n";
}

ArrayItem Dynamic_array::get_element(size_t index)
{
    if (index >= size) {
        std::cout << "Wrong choise\n\n";
        return NAN;
    }
    else
        return data[index];
}

void Dynamic_array::resize(size_t new_size) 
{
    if (new_size <= size + buffer_size) {
        size = new_size;
        set_zero(size, new_size);
        return;
    }
    
    ArrayItem* tmp = new ArrayItem[size];
    memcpy(tmp, data, size * sizeof(ArrayItem));
    size_t old_size = size;

    size = new_size;
    delete[] data;
    data = new ArrayItem[size + buffer_size];

    this->set_zero();
    memcpy(data, tmp, old_size * sizeof(ArrayItem));

    delete[] tmp;
}

int main(void)
{
    Dynamic_array Arr;
    
    Arr.set_array();
    Arr.print_array();

    Arr.set_element(15, 4);
    Arr.print_array();

    std::cout << Arr.get_element(12) << "\n";
    Arr.print_array();

    Arr.resize(20);
    Arr.print_array();

    return 1;
}