#include <iostream>
using namespace std;


void merge(int* array, int begin, int end, int* help_array)
{
	int idx_1 = begin;
	int middle = begin + (end - begin) / 2;
	int idx_2 = middle + 1;
	int idx_3 = 0;

	for (; idx_1 <= middle && idx_2 <= end; idx_3++) {
		if (array[idx_1] <= array[idx_2]) { help_array[idx_3] = array[idx_1]; idx_1++; }
		else { help_array[idx_3] = array[idx_2]; idx_2++; }
	}
	for (; idx_1 <= middle; idx_1++, idx_3++) {
		help_array[idx_3] = array[idx_1];
	}
	for (; idx_2 <= end; idx_2++, idx_3++) {
		help_array[idx_3] = array[idx_2];
	}
	for (idx_1 = 0; idx_1 < idx_3; idx_1++) {
		array[begin + idx_1] = help_array[idx_1];
	}
}


void swap_func(int* array, int index)
{
	int swap = array[index];
	array[index] = array[index + 1];
	array[index + 1] = swap;
}


void merge_sort(int* array, int left, int right, int* help_array)
{
	int swap = 0;
	if (left < right) {
		if (right - left == 1) {
			if (array[left] > array[right]) {
				swap_func(array, left);
			}
		}
		else {
			merge_sort(array, left, left + (right - left) / 2, help_array);
			merge_sort(array, left + (right - left) / 2 + 1, right, help_array);
			merge(array, left, right, help_array);
		}
	}
}


void array_print(int array_size, int *array)
{
	for (int elem = 0; elem < array_size; ++elem) {
		cout << array[elem] << " ";
	}
	cout << "\n";
}


void initialization()
{
	int array_size = 10;
	int* array = new int[10] { 2, 4, 1, 11, 9, 7, 4, 9, 50, 20 };

	int help_array_size = 10;
	int* help_array = new int[10];

	array_print(array_size, array);
	merge_sort(array, 0, array_size - 1, help_array);
	array_print(array_size, array);

	delete[] array;
	delete[] help_array;
}


int main()
{
	initialization();
}