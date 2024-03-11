#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int temp[], int left, int mid, int right) {
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
}

void mergeSort(int arr[], int temp[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, temp, left, mid);
        mergeSort(arr, temp, mid + 1, right);

        merge(arr, temp, left, mid, right);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {1, 11, -13, 5, 6, 7};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    int *temp = (int *)malloc(arr_size * sizeof(int));
    if (temp == NULL) {
        printf("Ошибка выделенияя\n");
        return 1;
    }

    mergeSort(arr, temp, 0, arr_size - 1);

    printArray(arr, arr_size);

    free(temp);
}