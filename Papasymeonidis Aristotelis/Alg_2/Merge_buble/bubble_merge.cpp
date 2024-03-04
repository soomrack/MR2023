#include <iostream>
#include<cstring>
#include <string>
#define ARRAY_SIZE 10



typedef int int_arr;


template <typename T>
void bubble_sort(T *arr, size_t size) 
{
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = size - 1; i < j; j--) {
            if (arr[j] < arr[j-1]) 
                std::swap(arr[j], arr[j-1]);
        }
    }
}


void merge_sort_insides(int_arr* mas, int_arr* buf_arr, size_t size)
{
    size_t middle = size / 2;

    if (size < 2) return;
    
    merge_sort_insides(buf_arr, mas, middle);
    merge_sort_insides(buf_arr + middle, mas + middle, size - middle);

    for (size_t idx = 0, left_branch = 0, right_branch = middle; idx < size; idx++) {
        if (right_branch >= size) buf_arr[idx] = mas[left_branch++];
        else if (left_branch >= middle) buf_arr[idx] = mas[right_branch++];
        else if (mas[left_branch] <= mas[right_branch]) buf_arr[idx] = mas[left_branch++];
        else buf_arr[idx] = mas[right_branch++];
    }

}


void merge_sort(int_arr* mas, size_t size)
{
    int_arr* buf_arr = new int_arr[ARRAY_SIZE];
    memcpy(buf_arr, mas, sizeof(int_arr) * size);
    merge_sort_insides(buf_arr, mas, size);
    delete[] buf_arr;
}


void input(int *m, int &n)
{
    std :: cout << "Enter the number of array elements: ";
    std :: cin >> n;
    for(int i = 0; i < n; ++i){
        std :: cout << "a[" << i << "]= ";
        std :: cin >> m[i];
    }
}


void print(int *m, int n)
{
    for(int i = 0; i < n; i++){
        std :: cout << m[i] << " ";
    }

    std :: cout<< std :: endl;
}



int main()
{
    int n;
    //int arr[ARRAY_SIZE];

    int_arr buf_arr[ARRAY_SIZE];

    //input(arr, n);
    n = 10;
    int arr[ARRAY_SIZE] = {1, 3, 4, 3, 2, 5, 7, 140, 2, 9};
    //int arr[3] = {1, 8, 6};
    std::cout << "The source array:" << std::endl;
    print(arr,n);



    merge_sort(arr, ARRAY_SIZE);

    

    //bubble_sort(arr, 10);
    std::cout << "Sorted array: " << std::endl;
    print(arr,n);

    return 0;



}