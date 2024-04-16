#include <iostream>

using namespace std;

void print_array(int* array, int num_of_elements)
{
    for (int pr_elem = 0; pr_elem < num_of_elements; ++pr_elem) {
        cout << array[pr_elem] << " ";
    }
    cout << endl;
}

void insertion_sort(int* array, int num_of_elements)
{
    for (int i = 1; i < num_of_elements; i++) {
        int key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

int main()
{
    int num_of_elements = 7;
    int* array = new int[num_of_elements] {5, 4, 3, 2, 1, 6, 7};

    print_array(array, num_of_elements);

    insertion_sort(array, num_of_elements);

    print_array(array, num_of_elements);

    return 0;
}