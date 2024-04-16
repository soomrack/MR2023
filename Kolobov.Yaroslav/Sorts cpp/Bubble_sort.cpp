#include <iostream>

using namespace std;

void print_array(int* array, int num_of_elements)
{
	for (int pr_elem = 0; pr_elem < num_of_elements; ++pr_elem) {
		cout << array[pr_elem];
	}
	cout << endl;
}


void swap(int* array, int el1_idx, int el2_idx)
{
	int buf = array[el1_idx];

	array[el1_idx] = array[el2_idx];

	array[el2_idx] = buf;
}


void bubble_sort(int* array, int num_of_elements)
{
	for (int sorted_elements = 0; sorted_elements < num_of_elements; ++sorted_elements) {
		for (int not_sorted_elements = sorted_elements + 1; not_sorted_elements < num_of_elements; ++not_sorted_elements) {
			if (array[sorted_elements] > array[not_sorted_elements]) {
				swap(array, sorted_elements, not_sorted_elements);
			}
		}
	}
}


int main()
{
	int num_of_elements = 5;
	int* array = new int[num_of_elements] {5, 4, 3, 2, 1};

	print_array(array, num_of_elements);

	bubble_sort(array, num_of_elements);

	print_array(array, num_of_elements);

	delete[] array;

	return 0;
}