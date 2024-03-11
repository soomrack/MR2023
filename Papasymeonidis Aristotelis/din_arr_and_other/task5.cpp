#include<iostream>
#include<cstring>

typedef int Matrix_Item;


class Dynamic_array{
    private: 
        Matrix_Item* data;
        size_t size;
    
    public:
        size_t get_size();
        int* get_data();
        int get_element(size_t index);
        void resize(size_t new_size);
        Dynamic_array(size_t size);
        Dynamic_array(size_t size, Matrix_Item* data);



};