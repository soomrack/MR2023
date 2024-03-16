//
// Created by simeonidi03 on 15.03.24.
//

#include"din_arr.hpp"



Dynamic_array::Dynamic_array(size_t size) {
    real_size = size;
    buf_size = size + BUFFER;
    data = new Array_Item[buf_size];
}


Dynamic_array::Dynamic_array(size_t real_size, size_t buffer) {
    this->real_size = real_size;
    buf_size = buffer;
    data = new Array_Item[buf_size];
}


Dynamic_array::Dynamic_array(const Dynamic_array& Arr){
    this->real_size = Arr.real_size;
    this->buf_size = Arr.buf_size;
    this->data = new Array_Item[buf_size];
    memcpy(data, Arr.data, sizeof(Arr.data));
}


Dynamic_array::Dynamic_array(Dynamic_array&& Arr){
    real_size = Arr.real_size;
    buf_size = Arr.buf_size;
    if(data != 0) {
        delete this->data;
    }
    data = Arr.data;

    Arr.real_size = 0;
    Arr.buf_size = 0;
    delete Arr.data;
}


Dynamic_array::Dynamic_array(size_t real_size, Array_Item* data) {
    this->real_size = real_size;
    buf_size = real_size + BUFFER;
    delete this->data;
    this->data = data;
}


Array_Item* Dynamic_array::get_data() const{
    return data;
}


Array_Item Dynamic_array::get_element(const size_t index) {
    if(index >= real_size) {
        return NAN;
    }
    return data[index];
}


size_t Dynamic_array::get_size() const{
    return real_size;
}

void Dynamic_array::resize(const size_t new_size) {
    real_size = new_size;
    buf_size = new_size + BUFFER;


}

