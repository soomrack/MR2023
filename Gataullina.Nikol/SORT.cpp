#include <iostream>
#include<cstring>
#include <string>
#define ARRAY_SIZE 10


typedef int arr_type;
enum type {less, greater};
arr_type sorted_part[ARRAY_SIZE];


template <typename Massive>
void bubble_sort(Massive *arr, size_t size) 
{
    for (size_t idx = 0; idx < size - 1; idx++) {
        for (size_t j = size - 1; idx < j; j--) {
            if (arr[j] < arr[j-1]) 
                std::swap(arr[j], arr[j-1]);
        }
    }
}


void merge_sort_insides(arr_type* mas, arr_type* buf_arr, size_t size)
{
    size_t middle = size / 2;

    if (size < 2){
        return;
    } 
    
    merge_sort_insides(buf_arr, mas, middle);
    merge_sort_insides(buf_arr + middle, mas + middle, size - middle);

    for (size_t idx = 0, left_branch = 0, right_branch = middle; idx < size; idx++) {
        if (right_branch >= size) buf_arr[idx] = mas[left_branch++];
        else if (left_branch >= middle) buf_arr[idx] = mas[right_branch++];
        else if (mas[left_branch] <= mas[right_branch]) buf_arr[idx] = mas[left_branch++];
        else buf_arr[idx] = mas[right_branch++];
    }

}


void merge_sort(arr_type* mas, size_t size)
{
    arr_type* buf_arr = new arr_type[ARRAY_SIZE];
    memcpy(buf_arr, mas, sizeof(arr_type) * size);
    merge_sort_insides(buf_arr, mas, size);
    delete[] buf_arr;
}


void input(int *arr, int &number_out)
{
    std :: cout << "Enter the number of array elements: ";
    std :: cin >> number_out;
    for(int idx = 0; idx < number_out; ++idx){
        std :: cout << "a[" << idx << "]= ";
        std :: cin >> arr[idx];
    }
}


bool predicate(arr_type left, arr_type right, type key)
{
    switch(key)
   {
    case less:
        return left < right ? true:false;
    break;

    case greater:
        return left > right ? true:false;
    break;

   } 
}


void insert_sort(arr_type *arr, type kind, size_t number)
{    
    for (size_t j = 1; j < number; j++)
    {
        arr_type buf_var = arr[j];
        int already_sorted = j - 1;

        while (already_sorted >= 0 && predicate(arr[already_sorted], buf_var, kind))
        {
            arr[already_sorted + 1] = arr[already_sorted];
            already_sorted--;
        }
        arr[++already_sorted] = buf_var;
        
    }
}


void heapify(arr_type arr[], int size_of_heap, int idx)
{  
    int largest = idx;
    
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if(left < size_of_heap && arr[left] > arr[largest]){
        largest = left;
    }

    if(right < size_of_heap && arr[right] > arr[largest]){
        largest = right;
    }

    if(largest != idx){
        std::swap(arr[idx], arr[largest]);
        heapify(arr, size_of_heap, largest);
    }
}


void heap_sort(arr_type arr[], int size_of_heap)
{
    for(int idx = size_of_heap / 2 - 1; idx >= 0; idx--){
        heapify(arr, size_of_heap, idx);
    }

    for(int idx = size_of_heap - 1; idx > 0; idx--){
        std::swap(arr[0], arr[idx]);
        heapify(arr, idx, 0);

    }

}


void print(int *arr, int number_out)
{
    for(int idx = 0; idx < number_out; idx++){
        std :: cout << arr[idx] << " ";
    }

    std :: cout<< std :: endl;
}


int main()
{
    int number_out;

    number_out = 10;
    arr_type arr[ARRAY_SIZE] = {1, 3, 4, 8, 13, 55, 7, 10, 9, 17};
    int n = sizeof(arr) / sizeof(arr[0]);
    std::cout << "The source array:" << std::endl;
    print(arr,number_out);

    bubble_sort(arr, 10);
    merge_sort(arr, ARRAY_SIZE);
    insert_sort(arr, less, ARRAY_SIZE);
    heap_sort(arr, n);

    std::cout << "Sorted array: " << std::endl;
    print(arr, ARRAY_SIZE);

    return 0;
}