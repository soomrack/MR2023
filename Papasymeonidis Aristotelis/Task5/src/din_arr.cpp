//
// Created by simeonidi03 on 15.03.24.
//

#include "din_arr/din_arr.hpp"


Dynamic_array::Dynamic_array(): real_size{50}, buf_size{50 + buffer} {
    data = new Array_Item[buf_size];
}


Dynamic_array::Dynamic_array(size_t size): real_size{size}, buf_size{size + buffer} {
    data = new Array_Item[buf_size];
}


Dynamic_array::Dynamic_array(size_t real_size, size_t buffer): real_size{real_size}, buf_size{buffer}{
    data = new Array_Item[buf_size];
}


Dynamic_array::Dynamic_array(const Dynamic_array& Arr){
    this->real_size = Arr.real_size;
    this->buf_size = Arr.buf_size;
    if(buf_size == 0) throw DynamicArrayException("Cannot use dynamic array with size 0");
    this->data = new Array_Item[buf_size];
    std::memcpy(data, Arr.data, sizeof(Arr.data));
}


Dynamic_array::Dynamic_array(Dynamic_array&& Arr){
    real_size = Arr.real_size;
    buf_size = Arr.buf_size;
    data = Arr.data;

    Arr.real_size = 0;
    Arr.buf_size = 0;
    Arr.data = nullptr;
}


Dynamic_array::Dynamic_array(size_t real_size, Array_Item* user_data): real_size{real_size}, buf_size{real_size + buffer}{
    data = new Array_Item[buf_size];
    memcpy(data, user_data, real_size * sizeof(Array_Item));
}


Array_Item Dynamic_array::get_element(const size_t index) {
    if(index >= real_size) throw DynamicArrayException("array has not value with this index");
    return data[index];
}


size_t Dynamic_array::get_size() const{
    return real_size;
}


void Dynamic_array::resize(const size_t new_size){
    buf_size = new_size + buffer;
   
    if(real_size >= new_size + buffer) {
        real_size = new_size + buffer;
        return;
    } 
    Array_Item* new_data = new Array_Item[new_size + buffer];
    memcpy(new_data, data, real_size * sizeof(Array_Item));
    delete[] data;
    data = new_data;
    new_data = nullptr;
}


void Dynamic_array::set_element(size_t index, Array_Item value){
    if(index > buf_size - 1) throw DynamicArrayException("Cannot use dynamic array with size 0");

    if(index > real_size - 1) {
        data[real_size] = value;
        return;
    }

    for(size_t idx_ch = real_size; idx_ch >index; idx_ch--) {
        data[idx_ch] = data[idx_ch - 1];
    }

    data[index] = value;
}


void Dynamic_array::print_array() const {
    std::cout << "Array contents: ";
    for (size_t i = 0; i < real_size; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}


Dynamic_array::~Dynamic_array() {
    real_size = 0;
    buf_size = 0;
    delete[] data;
    data = nullptr;
}