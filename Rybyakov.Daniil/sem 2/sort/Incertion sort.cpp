#include <iostream>
using namespace std;

void print_array(int* array, int array_size)
{
	for (int array_elem = 0; array_elem < array_size; ++array_elem) {
		cout << "  " << array[array_elem];
	}
	cout << "\n";
}


void incertion_sort(int* array, int array_size)
{
	for (int idx = 1; idx < array_size; ++idx) {
		int sort_idx = idx;
		int arr_elem = array[sort_idx];
		for (; sort_idx > 0 && array[sort_idx - 1] > arr_elem; --sort_idx) {
			array[sort_idx] = array[sort_idx - 1];
		}
		array[sort_idx] = arr_elem;
	}
	print_array(array, array_size);
}


int main()
{
	int array_size = 10;
	int* array = new int[10] { 2, 4, 1, 11, 9, 7, 4, 9, 50, 20 };
	print_array(array, array_size);
	incertion_sort(array, array_size);
	delete[] array;
}