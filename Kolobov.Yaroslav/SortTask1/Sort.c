#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int MassData;

struct Array {
    size_t quantity;
    MassData *data;
};

struct Array array_create(const size_t number_of_elements) 
{
    struct Array A = {.quantity = number_of_elements, .data = NULL};

    A.data = (int*)malloc(A.quantity * sizeof(int));

    if (A.data == NULL) {
        printf("Allocation error\n");
    }

    return A;
}


struct Array array_fill(const size_t number_of_elements, const MassData *data) 
{
    struct Array Mass;
    
    Mass = array_create(number_of_elements);
    if (Mass.data == NULL) {
        printf("Allocation error\n");
    }
    memcpy(Mass.data, data, number_of_elements * sizeof(MassData));
}


void mass_print(const struct Array Mass) 
{
    int printed_elements;
    
    for (printed_elements = 0; printed_elements < Mass.quantity - 1; ++printed_elements) {
        printf("%d ", Mass.data[printed_elements]);
        printf("\n");
    }
}

int main(){
    struct Array Mass;
    Mass = array_fill(4, (int[]){1, 2, 3, 4});
    mass_print(Mass);

    return 0;
}