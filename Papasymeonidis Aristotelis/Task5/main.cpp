#include<iostream>
#include<cstring>
#include"din_arr.hpp"

typedef int Matrix_Item;


class Dynamic_array{
private:
    Matrix_Item* data;
    size_t size;

public:
    size_t get_size();
    void set_element(size_t index, Matrix_Item value);
    Matrix_Item* get_data();
    Matrix_Item get_element(size_t index);
    void resize(size_t new_size);
    Dynamic_array(size_t size);
    Dynamic_array(size_t size, Matrix_Item* data);

};

int main() {
    // Ваш код здесь
    return 0;
}