#include<iostream>

#define ARRAY_SIZE 10

typedef int arr_type;

enum type {less, greater};


arr_type sorted_part[ARRAY_SIZE];


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


bool predicate(arr_type left, arr_type right, type key){
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

void insert_sort(arr_type *arr, type kind, size_t number){    
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


void print(int *arr, int number_out)
{
    for(int idx = 0; idx < number_out; idx++){
        std::cout << arr[idx] << " ";
    }

    std::cout<< std::endl;
}

int main(){

    arr_type arr[ARRAY_SIZE] = {1, 3, 4, 3, 2, 5, 7, 140, 2, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    insert_sort(arr, less, ARRAY_SIZE);
    //heap_sort(arr, n);
    print(arr, ARRAY_SIZE);

    return 0;
}