#include <stdio.h>
#include <stdlib.h>


struct array{
size_t number_of_elements;
int* array_data;
};

struct array array_create_fill(void){
    struct array A;
    size_t number_of_elements;

    printf("Enter number of elements\n");
    scanf("%d", &A.number_of_elements);

    A.array_data = (int*)malloc(A.number_of_elements * sizeof(int)); 

    if (A.array_data == NULL){
        printf("Allocation error\n"); //add errors and memory clear
    } 
 
    printf("Enter elements of array\n");
    for (int not_entered_elements = 0; not_entered_elements < A.number_of_elements; ++not_entered_elements){
        scanf("%d", A.array_data[not_entered_elements]);
    }

    for (int not_printed_elements = 0; not_printed_elements < A.number_of_elements; ++not_printed_elements){
        printf("%d ", A.array_data[not_printed_elements]);
    }
    
    return A;
}


struct array bubble_sort(const struct array A){
    for (int sorted_elements = 0; sorted_elements < A.number_of_elements - 1; ++sorted_elements)
        for (int i = 0; i < A.number_of_elements - 1; ++i){
            int buffer = 0;
            if (A.array_data[i] > A.array_data[i + 1]){
                buffer = A.array_data[i];
                A.array_data[i] = A.array_data[i + 1];
                A.array_data[i + 1] = buffer;
            }
        }

        return A;
}



void array_print(const struct array A){
    for (int not_printed_elements = 0; not_printed_elements < A.number_of_elements; ++not_printed_elements){
        printf("%d ", A.array_data[not_printed_elements]);
    }

}


int main(){
struct array A = array_create_fill();

// array_print(A);
}
