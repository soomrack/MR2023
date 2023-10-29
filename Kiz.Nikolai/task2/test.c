#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>


void print_array(int * array, uint8_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("value : %d\n", array[i]);
    }
}


int main() {
    int  arr[4] = {1, 2, 3, 4};
    print_array(arr, 4);
    return 0;
}