#include <iostream>
using namespace std;

void print_array(int* array, int array_size)
{
	for (int i = 0; i < array_size; ++i) {
		cout << "  " << array[i];
	}
	cout << "\n";
}


void bubble_sort(int *array, int array_size) 
{
	for (int k = 0; k < array_size; ++k) {
		for (int i = 0; i < array_size - k - 1; ++i) {
			if (array[i] > array[i + 1]) {
				int swap = array[i];
				array[i] = array[i + 1];
				array[i + 1] = swap;
			}
		}
	}
	print_array(array, array_size);
}


int main() 
{
	int array_size = 10;
	int* array = new int[10] { 2, 4, 1, 11, 9, 7, 4, 9, 55, 23 };
	print_array(array, array_size);
	bubble_sort(array, array_size);
	
}