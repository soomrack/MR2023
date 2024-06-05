#include <stdio.h>

void insertionSort(int *array, size_t size) { //типы данных + переимеовать i j 
    for (size_t idx = 1; idx < size; idx++) {
        int temp = array[idx];
        int current_idx = idx - 1;

        while (current_idx >= 0 && array[current_idx] > temp) {
            array[current_idx + 1] = array[current_idx];
            current_idx--;
        }


        array[current_idx + 1] = temp;
    }
}

void print_arr(int *array, size_t size){
    for(size_t idx = 0; idx < size; idx++){
        printf("%d ", array[idx]);
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


