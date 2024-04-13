//
// Created by simeonidi03 on 15.03.24.
//
#include<iostream>
#include<cstring>
#include<cmath>


typedef int Array_Item;

#ifndef DIN_ARR_HPP
#define DIN_ARR_HPP

#include"container_exception/container_exception.hpp"

class Dynamic_array{
private:
    Array_Item* data;
    size_t real_size;
    size_t buf_size;


public:
    size_t buffer = 10;
    size_t bufer_per = 15;
    size_t standart_size = 50;

    [[nodiscard]] size_t get_size() const;
    void set_element(size_t index, Array_Item value);
    Array_Item get_element(size_t index);
    void resize(size_t new_size);
    void print_array() const;


public:
    Dynamic_array();
    Dynamic_array(size_t size);
    Dynamic_array(size_t real_size, size_t buffer);
    ~Dynamic_array();
    Dynamic_array(const Dynamic_array& Arr);
    Dynamic_array(Dynamic_array&& Arr);
    Dynamic_array(size_t real_size, Array_Item* data);
};

#endif //DIN_ARR_HPP
