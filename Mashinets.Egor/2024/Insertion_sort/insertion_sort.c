#include <stdio.h>

void insertionSort(int *array, size_t size) {
    for (int i = 1; i < size; i++) {
        int key = array[i];
        int j = i - 1;

        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }


        array[j + 1] = key;
    }
}

void print_arr(int *array, size_t size){
    for(int i = 0; i < size; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int array[] = {7, 3, 11, 2, 23, -9};
    size_t size = sizeof(array) / sizeof(array[0]);

    insertionSort(array, size);

    print_arr(array, size);

    return 0;
}


