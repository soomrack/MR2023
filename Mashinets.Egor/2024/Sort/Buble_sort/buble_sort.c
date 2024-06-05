#include <stdio.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int *arr, size_t size){ // одинаковые типы данных current
    for(size_t idx = 0; idx < size; idx++){
        for(size_t current_idx = 0; current_idx < size; current_idx++){
            if(current_idx < size-1 && arr[current_idx]>arr[current_idx+1]){
                swap(&arr[current_idx], &arr[current_idx+1]);
            }
        }
    }
}

void print_arr(int *arr, size_t size){
    for(size_t idx = 0; idx < size; idx++){
        printf("%d ", arr[idx]);
    }
    printf("\n");
}

int main(){
    int arr[] = {1, 40, 5, 15, 0};
    size_t size = sizeof(arr)/sizeof(arr[0]);

    bubble_sort(arr, size);
    print_arr(arr, size);

    return 0;
}
