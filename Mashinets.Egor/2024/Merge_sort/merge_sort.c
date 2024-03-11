#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(int arr[], int temp[], int left, int mid, int right) {
    int k = 0, right_idx = mid + 1;

    while (left <= mid && right_idx <= right) {
        if (arr[left] <= arr[right_idx]) {
            temp[k++] = arr[left++];
        } else {
            temp[k++] = arr[right_idx++];
        }
    }

    if (left <= mid) {
        memcpy(&temp[k], &arr[left], (mid - left + 1) * sizeof(int));
        k += mid - left + 1;
    }

    if (right_idx <= right) {
        memcpy(&temp[k], &arr[right_idx], (right - right_idx + 1) * sizeof(int));
        k += right - right_idx + 1;
    }

    memcpy(&arr[0], temp, (right - left + 1) * sizeof(int));
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
        printf("Ошибка выделения\n");
        return 1;
    }

    mergeSort(arr, temp, 0, arr_size - 1);

    printArray(arr, arr_size);

    free(temp);
}