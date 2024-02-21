#include <iostream>
using namespace std;

void print_array(int* array, int array_size)
{
	for (int array_elem = 0; array_elem < array_size; ++array_elem) {
		cout << "  " << array[array_elem];
	}
	cout << "\n";
}


void swap_func(int *array, int index)
{
	int swap = array[index];
	array[index] = array[index + 1];
	array[index + 1] = swap;
}


void bubble_sort(int *array, int array_size) 
{
	for (int index_1 = 0; index_1 < array_size; ++index_1) {
		for (int index_2 = 0; index_2 < array_size - index_1 - 1; ++index_2) {
			if (array[index_2] > array[index_2 + 1]) {
				swap_func(array, index_2);
			}
		}
	}
	print_array(array, array_size);
}


int main() 
{
	int array_size = 10;
	int* array = new int[10] { 2, 4, 1, 11, 9, 7, 4, 9, 50, 20 };
	print_array(array, array_size);
	bubble_sort(array, array_size);
	delete[] array;
}