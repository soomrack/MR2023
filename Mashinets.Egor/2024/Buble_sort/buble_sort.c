#include <stdio.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int *arr, size_t size){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(j < size-1 && arr[j]>arr[j+1]){
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

void print_arr(int *arr, size_t size){
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
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
