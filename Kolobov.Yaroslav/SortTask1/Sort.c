#include <stdio.h>
#include <stdlib.h>

void mass_print(int array[], const int number_of_elemnts)
{
    for (int printed_elements = 0; printed_elements < number_of_elemnts; printed_elements++) {
        printf("%d", array[printed_elements]);
    }
    printf("\n");
}

void bubble_sort(int array[], const int number_of_elements)
{

    for (int sorted_elemnts = 0; sorted_elemnts < number_of_elements - 1; ++sorted_elemnts) {
            for (int sorted_elements = 0; sorted_elements < number_of_elements; ++sorted_elements) {
                int buffer = array[sorted_elements];
                
                if (array[sorted_elements] > array[sorted_elements + 1]) {
                    array[sorted_elements] = array[sorted_elements + 1];
                    array[sorted_elements + 1] = buffer;
                }
            }
    }
}


void merge(int array[], int l_idx, int m_idx, int r_idx)
{
    int left_array_lenght = m_idx - l_idx + 1;
    int right_array_lenght = r_idx - m_idx;

    int* left_array;
    int* right_array;

    left_array = malloc(left_array_lenght * sizeof(int));
    right_array = malloc(right_array_lenght * sizeof(int));

    if (left_array == NULL || right_array == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }

    int l_arr_counter, r_arr_counter, full_arr_counter;

    for (l_arr_counter = 0; l_arr_counter < left_array_lenght; l_arr_counter++) {
        left_array[l_arr_counter] = array[l_idx + l_arr_counter];
    }

    for (r_arr_counter = 0; r_arr_counter < right_array_lenght; r_arr_counter++) {
        right_array[r_arr_counter] = array[m_idx + 1 + r_arr_counter];
    }

    l_arr_counter = 0;
    r_arr_counter = 0;
    full_arr_counter = l_idx;

    while (r_arr_counter < right_array_lenght && l_arr_counter < left_array_lenght) {
        if (right_array[r_arr_counter] < left_array[l_arr_counter]) {
            array[full_arr_counter] = right_array[r_arr_counter];
            ++r_arr_counter;
        } else {
            array[full_arr_counter] = left_array[l_arr_counter];
            ++l_arr_counter;
        }
        ++full_arr_counter;
    }

    while (r_arr_counter < right_array_lenght) {
        array[full_arr_counter] = right_array[r_arr_counter];
        ++r_arr_counter;
        ++full_arr_counter;
    }

    while (l_arr_counter < left_array_lenght) {
        array[full_arr_counter] = left_array[l_arr_counter];
        ++l_arr_counter;
        ++full_arr_counter;
    }

    left_array = NULL;
    right_array = NULL;
}


void merge_sort_recursion(int array[], int l_idx, int r_idx)
{
    if (l_idx < r_idx) {

    int m_idx = l_idx + (r_idx - l_idx) / 2;

    merge_sort_recursion(array, l_idx, m_idx);
    merge_sort_recursion(array, m_idx + 1, r_idx);

    merge(array, l_idx, m_idx, r_idx);
    }
}

void merge_sort(int array[], int lenght)
{
    merge_sort_recursion(array, 0, lenght - 1);
}


int main()
{
    int mass[] = {9, 2, 6, 3, 7, 5};

    int size = sizeof(mass) / sizeof(int);

    merge_sort(mass, size);

    mass_print(mass, size);
}