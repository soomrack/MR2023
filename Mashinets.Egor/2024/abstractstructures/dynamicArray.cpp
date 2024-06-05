#include <iostream>


class DynamicArray {
private:
    int* data;
    size_t size;
    size_t size_allocated;
public:
    size_t bufer;

    DynamicArray();
    ~DynamicArray();

    explicit DynamicArray(size_t size, size_t buffer);

    int get_elem(size_t index) const;
    void set_elem(size_t index, int value);
    void add(int value);
    void resize(size_t new_size);
};


DynamicArray::DynamicArray() : size{0}, bufer{1}, data{nullptr} {}


DynamicArray::DynamicArray(size_t size, size_t bufer) : size{ size }, bufer{ bufer }, size_allocated{ size + bufer } 
{
    if (size_allocated == 0) 
    {
        data = nullptr;
    }
    else 
    {
        data = new int[size_allocated];
    }
}


DynamicArray::~DynamicArray() 
{
    delete[] data;
}


int DynamicArray::get_elem(size_t index) const
{
    if (index >= size) 
    {
        return data[index];
    }
    return 0;
}


void DynamicArray::set_elem(size_t index, int value) 
{
    if (size < index) return;
    data[index] = value;
}


void DynamicArray::add(int value)
{
    resize(size++);
    data[size--] = value;
}


void DynamicArray::resize(size_t new_size) 
{
    if (new_size > size_allocated)
    {
        size_allocated = new_size + bufer;
        int* new_data = new int[size_allocated];
        for (size_t i = 0; i < size; i++) 
        {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
    }
    size = new_size;
}


int main()
{
    DynamicArray arr(0, 3);
   
    arr.add(22);
    arr.add(3);

    arr.set_elem(2, 5);
   
    arr.add(72);

    arr.resize(5);

    arr.add(42);
    arr.add(25);

    return 0;
}