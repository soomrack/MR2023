#include <iostream>
#include <string>
#include <bits/stdc++.h>

class Dynamic_array {
private: 
    int* data;
    size_t size;
    size_t container;

public:
    Dynamic_array(size_t your_container);
    Dynamic_array(Dynamic_array& arr);
    Dynamic_array(Dynamic_array&& arr);
    ~Dynamic_array();

public:
    int get_size();
    int get_container();
    int get_element(int idx);

    void print_arr();

    void set_arr();
    void set_element(int idx, int value);

    void resize(int new_size);
};


Dynamic_array:: Dynamic_array(size_t your_container)
{
    size = 0;
    container = your_container;
    data = new int[container];
} 


Dynamic_array:: Dynamic_array(Dynamic_array& arr)
{
    size = arr.size;
    container = arr.container;
    
    delete [] data;
    data = new int[container];
    memcpy(data, arr.data, sizeof(int) * size); 
} 



Dynamic_array:: Dynamic_array(Dynamic_array&& arr)
{
    size = arr.size;
    container = arr.container;
    
    delete [] data;
    data = arr.data;
    arr.data = nullptr;
} 


Dynamic_array:: ~Dynamic_array()
{
    size = 0;
    container = 0;
    delete [] data;
}


int Dynamic_array:: get_size()
{
    return size;
}


int Dynamic_array:: get_container()
{
    return container;
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

    resize(length);
    
    for(int i = 0; i < size; i++)
        data[i] = arr[i];
}


void Dynamic_array:: set_element(int idx, int value)
{
    if(idx > size - 1)
        resize(idx + 1);
    
    data[idx] = value;
}


void Dynamic_array:: resize(int new_size)
{
    if(new_size > container){
        int* new_data = new int[new_size];
        memcpy(new_data, data, size * sizeof(int));
        delete [] data;
        data = new_data;
        size = new_size;
        container = new_size;
    } else {
        size = new_size;
    }
}


int main()
{
    Dynamic_array Arr(10);

    Arr.set_arr();
    Arr.print_arr();

    std:: cout<<Arr.get_element(3)<<std::endl;

    Arr.resize(11);
    Arr.print_arr();

    return 0;
}
