#include <stdio.h>

void merge_sort(int *arr, size_t size){

}

void print_arr(int *arr, size_t size){
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(){
    int arr[] = {};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    merge_sort(arr, size);
    print_arr(arr, size);
}