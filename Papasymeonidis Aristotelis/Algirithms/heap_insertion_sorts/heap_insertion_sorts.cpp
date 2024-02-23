#include<iostream>

#define ARRAY_SIZE 10

typedef int arr_type;


arr_type sorted_part[ARRAY_SIZE];


void insert_sort(arr_type *arr, size_t number){
    arr_type buf_var;

    for(int sort_part_size = 0; sort_part_size <= number; sort_part_size++){
        buf_var = arr[sort_part_size + 1];
        for(int i = sort_part_size + 1; i > 0; i--)
        {
           if(arr[i - 1] > buf_var){
            arr[i] = arr[i - 1];
            arr[i - 1] = buf_var;
           } else {
            arr[i+1] = buf_var;
           }
        }   
    }
}


void print(int *arr, int number_out)
{
    for(int idx = 0; idx < number_out; idx++){
        std::cout << arr[idx] << " ";
    }

    std::cout<< std::endl;
}

int main(){

    arr_type arr[ARRAY_SIZE] = {1, 3, 4, 3, 2, 5, 7, 140, 2, 9};
    insert_sort(arr, ARRAY_SIZE);
    print(arr, ARRAY_SIZE);





    return 0;
}