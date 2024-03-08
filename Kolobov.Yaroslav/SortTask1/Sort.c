#include <stdio.h>
#include <stdlib.h>

void mass_print(int array[], const int number_of_elements)
{
    for (int printed_elements = 0; printed_elements < number_of_elements; printed_elements++) {
        printf("%i", array[printed_elements]);
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


void merge(int array[], int l_idx, int m_idx, int r_idx, int temp[])           
{                                                                               
                                                                            
    int l_arr_counter, r_arr_counter, full_arr_counter;

    for (l_arr_counter = l_idx; l_arr_counter < m_idx + 1; l_arr_counter++) {
       temp[l_arr_counter] = array[l_arr_counter];
    }

    for (r_arr_counter = m_idx + 1; r_arr_counter < r_idx + 1; r_arr_counter++) {
        temp[r_arr_counter] = array[r_arr_counter];
    }

    l_arr_counter = l_idx;
    r_arr_counter = m_idx + 1;
    full_arr_counter = l_idx;

    while (r_arr_counter < r_idx + 1 && l_arr_counter < m_idx + 1) {
        if (temp[r_arr_counter] < temp[l_arr_counter]) {
            array[full_arr_counter] = temp[r_arr_counter];
            ++r_arr_counter;
        } else {
            array[full_arr_counter] = temp[l_arr_counter];
            ++l_arr_counter;
        }
        ++full_arr_counter;
    }

    while (r_arr_counter < r_idx + 1) {
        array[full_arr_counter] = temp[r_arr_counter];
        ++r_arr_counter;
        ++full_arr_counter;
    }

    while (l_arr_counter < m_idx + 1) {
        array[full_arr_counter] = temp[l_arr_counter];
        ++l_arr_counter;
        ++full_arr_counter;
    }

}


void merge_sort_recursion(int array[], int l_idx, int r_idx, int temp[])
{
    if (l_idx < r_idx) {

    int m_idx = l_idx + (r_idx - l_idx) / 2;

    merge_sort_recursion(array, l_idx, m_idx, temp);
    merge_sort_recursion(array, m_idx + 1, r_idx, temp);

    merge(array, l_idx, m_idx, r_idx, temp);
    }
}

void merge_sort(int array[], int lenght)
{
    int* temp;
    temp = malloc(lenght * sizeof(int));
    if (temp == NULL) {
        printf("Allocation error\n");
        exit(1);
    }

    merge_sort_recursion(array, 0, lenght - 1, temp);

    temp = NULL;
}


void insertion_sort(int array[], const int lenght)
{
    int out_elements;
    int in_elements;
    int current_element;

    for(out_elements = 1; out_elements < lenght; out_elements++)
    {
        current_element = array[out_elements];

        in_elements = out_elements - 1;
        while(in_elements >= 0)
        {
            if(current_element < array[in_elements])
            {
                array[in_elements + 1] = array[in_elements]; // 9 2 3 4    9 9 3 4
            }
            else
            {
                break;
            }
            in_elements = in_elements - 1;
        }

        array[in_elements + 1] = current_element;
    }
}


void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void heapify(int array[], int lenght, int idx) {

  int largest_pos = idx;
  int left_pos = 2 * idx + 1;
  int right_pos = 2 * idx + 2;

  if (left_pos < lenght && array[left_pos] > array[largest_pos])
    largest_pos = left_pos;

  if (right_pos < lenght && array[right_pos] > array[largest_pos])
    largest_pos = right_pos;


  if (largest_pos != idx) {
    swap(&array[idx], &array[largest_pos]);
    heapify(array, lenght, largest_pos);
  }
}

void heap_sort(int array[], int lenght) {

  for (int idx = lenght / 2 - 1; idx >= 0; idx--) 
    heapify(array, lenght, idx);   

  for (int idx = lenght - 1; idx >= 0; idx--) {
    swap(&array[0], &array[idx]);

    heapify(array, idx, 0);
  }
}


int main()
{
    int mass[] = {9, 2, 6, 3, 5, 7};

    int size = sizeof(mass) / sizeof(int);

    heap_sort(mass, size);

    mass_print(mass, size);
}