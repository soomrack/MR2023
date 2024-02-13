#include <iostream>
using namespace std;


void merge(int* array, int begin, int end)
{
	int i = begin;
	int middle = begin + (end - begin) / 2;
	int j = middle + 1;
	int k = 0;
	int help_array[1000];

	for (; i <= middle && j <= end; k++) {
		if (array[i] <= array[j]) { help_array[k] = array[i]; i++; }
		else { help_array[k] = array[j]; j++; }
	}
	for (; i <= middle;) {
		help_array[k] = array[i]; i++; k++;
	}
	for (; j <= end;) {
		help_array[k] = array[j]; j++; k++;
	}
	for (i = 0; i < k; i++) {
		array[begin + i] = help_array[i];
	}
}


void merge_sort(int* array, int left, int right)
{
	int swap = 0;
	if (left < right) {
		if (right - left == 1) {
			if (array[left] > array[right]) {
				swap = array[left];
				array[left] = array[right];
				array[right] = swap;
			}
		}
		else {
			merge_sort(array, left, left + (right - left) / 2);
			merge_sort(array, left + (right - left) / 2 + 1, right);
			merge(array, left, right);
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


int main()
{
	int array_size = 10;
	int *array = new int[10]{ 2, 4, 1, 11, 9, 7, 4, 9, 55, 23 };
	array_print(array_size, array);
	merge_sort(array, 0, array_size - 1);
	array_print(array_size, array);
	delete[] array;
}