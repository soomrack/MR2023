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

    A.data = malloc(A.quantity * sizeof(MassData));

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

    return Mass;
}


void mass_print(const struct Array Mass) 
{
    int printed_elements;
    
    for (printed_elements = 0; printed_elements < Mass.quantity; ++printed_elements) {
        printf("%i\t", Mass.data[printed_elements]);
        fflush(stdout);
        
    }
}


struct Array bubble_sort(const struct Array mass) 
{
    int sorted_elements;
    int m;
    struct Array sorted_mass;

    sorted_mass = mass;

    for (sorted_elements = 0; sorted_elements < sorted_mass.quantity - 1; ++sorted_elements) {
        for (m = 0; m < sorted_mass.quantity - 1; ++m) {
            int buf = sorted_mass.data[m];
            if (sorted_mass.data[m] > sorted_mass.data[m + 1]) {
                sorted_mass.data[m] = sorted_mass.data[m + 1];
                sorted_mass.data[m + 1] = buf; 
            } 

        }
    }

    return sorted_mass;
}


struct Array merge_sort(const struct Array mass)
{

}


void merge_sort(const struct Array mass)
{
    int l_idx = 0;
    int r_idx = mass.quantity - 1;
    int m_idx = l_idx + (r_idx - l_idx) / 2;

    struct Array tmp_left = array_create(l_idx + m_idx);
    struct Array tmp_right = array_create(r_idx - m_idx + 1);

    for (int i = 0; i <= m_idx; ++i){
        tmp_left.data[i] = mass.data[i];
    }

    for (int i = m_idx + 1; i <= r_idx; ++i){
        int k = 0;
        tmp_right.data[k] = mass.data[i];
        ++k;
    }
}


// 1 5 4 8 7 2
// 1 5 4
// 8 7 2

struct Array insertion_sort()
{

}


struct Array heap_sort()
{

}


int main(){
    struct Array mass;
    struct Array sorted_mass;
    
    mass = array_fill(5, (int[]){4, 2, 3, 1, 8});
    sorted_mass = bubble_sort(mass);
    mass_print(sorted_mass);

    return 0;
}