#include <stdio.h>

void merge_sort(int *arr, int right, int left){
    while(left <= right){
        int mid = (left + right) / 2;

        merge_sort(arr, left, mid );
        merge_sort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void merge(int arr[], int left, int mid, int right) {
    int temp[right - left + 1];
    int k = 0, j = mid + 1; 

    while (left <= mid && j <= right) {
        if (arr[left] <= arr[j]) {
            temp[k] = arr[left];
            left++;
        } else {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }

    while (left <= mid) {
        temp[k] = arr[left];
        left++;
        k++;
    }

    while (j <= right) {
        temp[k] = arr[j];
        j++;
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

    merge_sort(arr, size - 1, 0);
    print_arr(arr, size);
}