#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE 10

typedef int int_arr;

void merge_sort(int_arr* mas, int_arr* buf_arr, size_t size) {
    size_t middle = size / 2;
    size_t idx = 0, left_branch = 0, right_branch = middle;

    if (size < 2)
        return;

    merge_sort(buf_arr, mas, middle);
    merge_sort(buf_arr + middle, mas + middle, size - middle);

    while (idx < size) {
        if (right_branch >= size)
            buf_arr[idx++] = mas[left_branch++];
        else if (left_branch >= middle)
            buf_arr[idx++] = mas[right_branch++];
        else if (mas[left_branch] <= mas[right_branch])
            buf_arr[idx++] = mas[left_branch++];
        else
            buf_arr[idx++] = mas[right_branch++];
    }
}

void merge(int_arr* mas, size_t size) {
    int_arr* buf_arr = (int_arr*)malloc(ARRAY_SIZE * sizeof(int_arr));
    if (buf_arr == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    memcpy(buf_arr, mas, size * sizeof(int_arr));
    merge_sort(buf_arr, mas, size);
    free(buf_arr);
}

void print(int *m, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d ", m[i]);
    }
    printf("\n");
}

int main() {
    int n = 10;
    int arr[ARRAY_SIZE] = {-9, 30, 0 , 0, 12, 11, 2, 6};

    printf("The source array:\n");
    print(arr, n);

    merge(arr, ARRAY_SIZE);

    printf("Sorted array:\n");
    print(arr, n);
}