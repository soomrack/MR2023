#include <iostream>
#include <string>
#include <bits/stdc++.h>

class Dynamic_array {
private: 
    int* data;
    size_t size;
    size_t buffer;

public:
    Dynamic_array(size_t your_size, size_t your_buffer);
    Dynamic_array(Dynamic_array& arr);
    Dynamic_array(Dynamic_array&& arr);
    ~Dynamic_array();

public:
    int get_size();
    int get_buffer();
    int get_element(int idx);

    void print_arr();

    void set_arr();
    void set_element(int idx, int value);

    void resize(int new_size);
};


Dynamic_array:: Dynamic_array(size_t your_size, size_t your_buffer)
{
    size = your_size;
    buffer = your_buffer;
    data = new int[size + buffer];
} 


Dynamic_array:: Dynamic_array(Dynamic_array& arr)
{
    size = arr.size;
    buffer = arr.buffer;
    
    delete [] data;
    data = new int[size + buffer];
    memcpy(data, arr.data, sizeof(int) * size); 
} 



Dynamic_array:: Dynamic_array(Dynamic_array&& arr)
{
    size = arr.size;
    buffer = arr.buffer;
    
    delete [] data;
    data = arr.data;
    arr.data = nullptr;
} 


Dynamic_array:: ~Dynamic_array()
{
    size = 0;
    buffer = 0;
    delete [] data;
}


int Dynamic_array:: get_size()
{
    return size;
}


int Dynamic_array:: get_buffer()
{
    return buffer;
}


int Dynamic_array:: get_element(int idx)
{
    if(idx > size - 1)
        return NAN;

    return data[idx];
}


void Dynamic_array:: print_arr()
{
    std:: cout<<"[";
    for(int i = 0; i < size - 1; i++){
        std:: cout<<data[i]<<", ";
    }
    std:: cout<<data[size - 1]<<"]"<<std::endl;
}


void Dynamic_array:: set_arr()
{
    int arr[] = {1, 2, 3, 4, 150};
    int length = sizeof(arr) / sizeof(arr[0]);

    if(length != size)
        return;
    
    for(int i = 0; i < size; i++)
        data[i] = arr[i];
}


void Dynamic_array:: set_element(int idx, int value)
{
    if(idx > size - 1)
        return;
    
    data[idx] = value;
}


void Dynamic_array:: resize(int new_size)
{
    if(new_size > size + buffer){
        int* new_data = new int[new_size];
        memcpy(new_data, data, size * sizeof(int));
        delete [] data;
        data = new_data;
        size = new_size;
    } else {
        buffer = size + buffer - new_size;
        size = new_size;
    }
}


int main()
{
    Dynamic_array Arr(5, 5);

    Arr.set_arr();
    Arr.print_arr();

    std:: cout<<Arr.get_element(3)<<std::endl;

    Arr.resize(11);
    Arr.print_arr();

    return 0;
}
