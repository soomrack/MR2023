#include <stdio.h>

void merge(int arr[], int left, int mid, int right, int temp[]);

void merge_sort(int *arr, int right, int left, int temp[]){
    while(left <= right){
        int mid = (left + right) / 2;

        merge_sort(arr, left, mid, temp );
        merge_sort(arr, mid + 1, right, temp);

        merge(arr, left, mid, right, temp);
    }
}

void merge(int arr[], int left, int mid, int right, int temp[]) {
    int k = 0, right_idx = mid + 1; 

    while (left <= mid && right_idx <= right) {
        if (arr[left] <= arr[right_idx]) {
            temp[k] = arr[left];
            left++;
        } else {
            temp[k] = arr[right_idx];
            right_idx++;
        }
        k++;
    }

    while (left <= mid) {
        temp[k] = arr[left];
        left++;
        k++;
    }

    while (right_idx <= right) {
        temp[k] = arr[right_idx];
        right_idx++;
        k++;
    }

    for (int i = left; i <= right; i++) {
        arr[left] = temp[i - left];
    }
}
void print_arr(int *arr, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(){
    int arr[] = {};
    int size = sizeof(arr) / sizeof(arr[0]);
    int temp[size];

    merge_sort(arr, size - 1, 0, temp);
    print_arr(arr, size);
}