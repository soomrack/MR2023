#include <iostream>
#include <vector>

using namespace std;


/**
 * Prints the elements of a vector.
 *
 * @param vector The vector containing the elements to be printed.
 */
void print_ar(const auto& vector) {
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
void bubble_sort(auto& array) {
    auto temp = array[0];
    size_t unsorted = array.size();
    for (size_t iteration = 0; iteration < unsorted; iteration++, unsorted--) {
        for (size_t element = 0; element < unsorted - 1; element++) {
            if (array[element] > array[element+1]) {
                temp = array[element];
                array[element] = array[element + 1];
                array[element + 1] = temp; 
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
 * @param array_length The length of the array.
 */
void merge(auto& array, size_t start_index, size_t end_index, size_t middle_index, size_t array_length)
{
    int left, right, temp_index, temp[array_length];
    left = start_index;
    temp_index = start_index;
    right = middle_index + 1;
    int t = 0;
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
 * Sorts a vector in ascending order using the merge sort algorithm.
 *
 * @param a The array to be sorted.
 * @param start_index The starting index of the vector to be sorted.
 * @param end_index The ending index of the vector to be sorted.
 */
void merge_sort(auto& a, size_t start_index, size_t end_index) {
    if (start_index < end_index) {
        size_t middle_index = (start_index + end_index) / 2;
        merge_sort(a, start_index, middle_index);
        merge_sort(a, middle_index+1, end_index);

        merge(a, start_index, end_index, middle_index, a.size());
    }
    return;
}


int main() {
    vector<int> a = {4, 8, 1, 5, 9, 0, 2, 7, 3, 6};

    bubble_sort(a);
    print_ar(a);

    a = {4, 8, 1, 5, 9, 0, 2, 7, 3, 6};
    size_t start_index = 0;
    size_t end_index = a.size() - 1;

    merge_sort(a, start_index, end_index);
    print_ar(a);

    return 0;
}