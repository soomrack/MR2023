#include <iostream>
#include <string>
#include <cstring>

typedef int ArrayItem;

class Dynamic_array {
private:
    ArrayItem* data;
    size_t size;
    size_t buffer_size;

public:
    Dynamic_array(size_t length, size_t buffer);
    ~Dynamic_array();
    Dynamic_array(const Dynamic_array& Arr);
    Dynamic_array(Dynamic_array&& Arr);

public:
    size_t get_size();
    ArrayItem* get_data();
    void set_array();
    void set_element(size_t index, ArrayItem value);
    void print_array();
    ArrayItem get_element(size_t index);
    void resize(size_t new_size, size_t buffer);
    void set_zero();
    void set_zero(size_t left, size_t right);
};


Dynamic_array::Dynamic_array(const Dynamic_array& Arr)
{
    size = Arr.size;
    buffer_size = Arr.buffer_size;

    delete[] data;
    data = new ArrayItem[size + buffer_size];
    memcpy(data, Arr.data, sizeof(ArrayItem) * size);
}


Dynamic_array::Dynamic_array(Dynamic_array&& Arr)
{
    size = Arr.size;
    buffer_size = Arr.buffer_size;
    Arr.size = 0;
    Arr.buffer_size = 0;

    delete[] data;
    data = Arr.data;
    Arr.data = nullptr;
}


Dynamic_array::Dynamic_array(size_t length, size_t buffer) {
    size = length;
    buffer_size = buffer;
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


void Dynamic_array::resize(size_t new_size, size_t new_buffer)
{
    if (new_size + new_buffer <= size + buffer_size) {
        if (new_size < size)
            set_zero(new_size, new_buffer);
        size = new_size;
        buffer_size = new_buffer;
        return;
    }

    ArrayItem* tmp = new ArrayItem[new_size + new_buffer];
    memcpy(tmp, data, size * sizeof(ArrayItem));

    delete[] data;
    data = tmp;
    set_zero(size, new_size - 1);
    size = new_size;
    buffer_size = new_buffer;
}


int main(void)
{
    Dynamic_array Arr(10, 5);
    
    Arr.set_array();
    Arr.print_array();

    Arr.set_element(8, 4);
    Arr.print_array();

    std::cout << Arr.get_element(6) << "\n";
    Arr.print_array();

    Arr.resize(20, 6);
    Arr.print_array();

    return 1;
}