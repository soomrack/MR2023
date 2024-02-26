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

void merge(int* arr, int* left_arr, int* right_arr, int begin, int mid, int end) {
    int first_arr = begin;
    int second_arr = mid + 1;
    int k = begin;

    while (first_arr <= mid && second_arr <= end) {
        if (left_arr[first_arr - begin] <= right_arr[second_arr - mid - 1]) {
            arr[k] = left_arr[first_arr - begin];
            first_arr++;
        } else {
            arr[k] = right_arr[second_arr - mid - 1];
            second_arr++;
        }
        k++;
    }

    while (first_arr <= mid) {
        arr[k] = left_arr[first_arr - begin];
        first_arr++;
        k++;
    }

    while (second_arr <= end) {
        arr[k] = right_arr[second_arr - mid - 1];
        second_arr++;
        k++;
    }
}

void merge_sort(int* arr, int* left_arr, int* right_arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort(arr, left_arr, right_arr, left, mid);
        merge_sort(arr, left_arr, right_arr, mid + 1, right);

        // Copy the left and right halves to separate arrays
        std::copy(arr + left, arr + mid + 1, left_arr);
        std::copy(arr + mid + 1, arr + right + 1, right_arr);

        // Merge the two halves directly into arr
        merge(arr, left_arr, right_arr, left, mid, right);
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

    int left_arr[ARRAY_SIZE / 2];
    int right_arr[ARRAY_SIZE - ARRAY_SIZE / 2];

    merge_sort(arr, left_arr, right_arr, 0, ARRAY_SIZE - 1);

    

    //bubble_sort(arr, 10);
    std::cout << "Sorted array: " << std::endl;
    print(arr,n);

    return 0;



}