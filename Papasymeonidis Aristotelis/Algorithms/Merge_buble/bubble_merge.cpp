#include <iostream>
#include<cstring>
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


void merg(int* arr, int_arr* buf_arr, int begin, int end)
{
    int first_arr = begin;
    int mid = begin + (end - begin) / 2;
    int second_arr = mid + 1;
    int k = 0;
    memset(buf_arr, 0, ARRAY_SIZE);

    while (first_arr <= mid && second_arr <= end)
    {
        if(arr[first_arr] <= arr[second_arr]){
            buf_arr[k] = arr[first_arr];
            first_arr++;
        }else {
            buf_arr[k] = arr[second_arr];
            second_arr++;
        }
        k++;
    }
    

    /*
    memcpy()
    */
    while (first_arr <= mid)
    {
        buf_arr[k] = arr[first_arr];
        first_arr++;
        k++;
    }

    while (second_arr <= end)
    {
        buf_arr[k] = arr[second_arr];
        second_arr++;
        k++;
    }

    for(first_arr = 0; first_arr < k; first_arr++){
        arr[begin] = buf_arr[first_arr];
        begin++;
    }    

}

void merge_sort(int *arr, int_arr *buf_arr, int left, int right)
{
    if (left < right) { //array > 1
        if(right - left == 1){ //array is two-element
            if( arr[left] > arr[right]) {
                std :: swap(arr[left], arr[right]);
            }
        } else {
            merge_sort(arr, buf_arr, left, left + (right - left) / 2);
            merge_sort(arr, buf_arr, (left + (right - left) / 2) + 1, right);
            merg(arr, buf_arr, left, right);
        }
    }

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

    merge_sort(arr, buf_arr, 0, n - 1);

    //bubble_sort(arr, 10);
    std::cout << "Sorted array: " << std::endl;
    print(arr,n);

    return 0;



}