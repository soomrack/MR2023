#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

/**
 * Prints the elements of a vector.
 *
 * @param vector The vector containing the elements to be printed.
 */
void print_array(const auto& vector) {
    cout << "{ ";
    for (auto element : vector) {
        cout << element << " ";
    }
    cout << "}" << endl;
}


/**
 * Sorts a given array in ascending order using the bubble sort algorithm.
 *
 * @param array The array to be sorted.
 */
void bubble_sort(auto& array, int array_size) {
    auto temp = array[0];
    size_t unsorted = array_size;
    for (size_t iteration = 0; iteration < unsorted; iteration++, unsorted--) {
        for (size_t element = 0; element < unsorted - 1; element++) {
            if (array[element] > array[element+1]) {
                swap(array[element], array[element+1]);
            }
        }
    }
}


/**
 * Merges and sorts two sorted halves of an array in ascending order.
 *
 * @param array The array to be sorted.
 * @param start_index The starting index of the portion to be sorted.
 * @param end_index The ending index of the portion to be sorted.
 * @param middle_index The middle index dividing the two sorted halves.
 * @param array_size The length of the array.
 */
void merge(auto& array, auto& temp, size_t start_index, size_t end_index, size_t middle_index, size_t array_size)
{
    size_t left, right, temp_index;
    left = start_index;
    temp_index = start_index;
    right = middle_index + 1;
    while (left <= middle_index && right <= end_index)
    {
        if (array[left] < array[right])
        {
            temp[temp_index] = array[left];
            temp_index++;
            left++;
        }
        else
        {
            temp[temp_index] = array[right];
            temp_index++;
            right++;
        }
    }
    while (left <= middle_index)
    {
        temp[temp_index] = array[left];
        temp_index++;
        left++;
    }
    while (right <= end_index)
    {
        temp[temp_index] = array[right];
        temp_index++;
        right++;
    }
    for (left = start_index; left < temp_index; left++)
    {
        array[left] = temp[left];
    }
}


/**
 * The main function for merge sort, contains the main stages of the algorithm.
 *
 * @param array         The array to be sorted.
 * @param temp          Temporary array to store values
 * @param start_index   The starting index of the vector to be sorted.
 * @param end_index     The ending index of the vector to be sorted.
 */
void merge_sort_main(auto& array, auto temp, size_t start_index, size_t end_index) {
    if (start_index < end_index) {
        size_t middle_index = (start_index + end_index) / 2;
        merge_sort_main(array, temp, start_index, middle_index);
        merge_sort_main(array, temp, middle_index+1, end_index);

        merge(array, temp, start_index, end_index, middle_index, end_index+1);
    }
    return;
}


/**
 * The function creates a temporary array to store elements and calls 
 * the main merge sort function.
 *
 * @param array         The array to be sorted.
 * @param start_index   The starting index of the vector to be sorted.
 * @param end_index     The ending index of the vector to be sorted.
 */
void merge_sort(auto& array, size_t start_index, size_t end_index) {
    using temp_type = remove_reference<decltype( array[0] )>::type;
    size_t temp_size = end_index+1; 
    temp_type temp[temp_size];
    merge_sort_main(array, temp, start_index, end_index);
}


/**
 * A function that sorts a graph.
 * 
 * @param array             The array to be heapified.
 * @param array_size        The size of the array.
 * @param non_leaf_node     The index to start heapifying from.
 */
void heapify(auto& array, size_t array_size, size_t non_leaf_node) { 
    size_t largest = non_leaf_node; 
    size_t left = 2*non_leaf_node + 1; 
    size_t right = 2*non_leaf_node + 2; 
    if (left < array_size && array[left] > array[largest]) { 
        largest = left; 
    } 
    if (right < array_size && array[right] > array[largest]) { 
        largest = right; 
    } 
    if (largest != non_leaf_node) { 
        swap(array[largest], array[non_leaf_node]); 
        heapify(array, array_size, largest); 
    } 
} 


/**
 * Function to perform heap sort on the given array.
 * 
 * @param array          The array to be sorted.
 * @param array_size     The size of the array.
 */
void heap_sort(auto& array, int array_size) { 
    for (size_t non_leaf_node = floor(array_size/2) - 1; non_leaf_node >= 0; non_leaf_node--) { 
        heapify(array, array_size, non_leaf_node); 
    } 
    for (size_t non_leaf_node = array_size - 1; non_leaf_node >= 0; non_leaf_node--) {
        swap(array[0], array[non_leaf_node]);
        heapify(array, non_leaf_node, 0); 
    } 
}


/**
 * Function to perform insertion sort on the given array.
 * 
 * @param array          The array to be sorted.
 * @param array_size     The size of the array.
 */
void insertion_sort(auto& array, size_t array_size) {
    using temp_type = remove_reference<decltype( array[0] )>::type;
    temp_type temp;
    size_t index_of_element_before;
    for (size_t index_of_current_element = 1; index_of_current_element < array_size; index_of_current_element++) {

        temp =  array[index_of_current_element];
        index_of_element_before = index_of_current_element - 1;

        while ((index_of_element_before >= 0) && (array[index_of_element_before] > temp)) {
            array[index_of_element_before + 1] = array[index_of_element_before];
            index_of_element_before--;
        }
        array[index_of_element_before+1] = temp;
    }
}


int main() {
    vector<int> array = {4, 8, 1, 5, 9, 0, 2, 7, 3, 6};

    // Bubble sort
    // ***********************************
    bubble_sort(array, array.size());
    cout << "Bubble sort:" << endl;
    print_array(array);
    // ***********************************

    // Merge sort
    // ***********************************
    array = {4, 8, 1, 5, 9, 0, 2, 7, 3, 6};
    int start_index = 0;
    int end_index = array.size() - 1;
    merge_sort(array, start_index, end_index);
    cout << "Merge sort:" << endl;
    print_array(array);
    // ***********************************

    // Heap sort
    // ***********************************
    array = {4, 8, 1, 5, 9, 0, 2, 7, 3, 6};
    heap_sort(array, array.size());
    cout << "Heap sort:" << endl;
    print_array(array);
    // ***********************************

    // Insertion sort
    // ***********************************
    array = {4, 8, 1, 5, 9, 0, 2, 7, 3, 6};
    cout << "Insertion sort:" << endl;
    insertion_sort(array, array.size());
    print_array(array);
    // ***********************************

    return 0;
}