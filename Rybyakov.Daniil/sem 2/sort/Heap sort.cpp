#include <iostream>
using namespace std;

void print_array(int* array, int array_size)
{
	for (int array_elem = 0; array_elem < array_size; ++array_elem) {
		cout << "  " << array[array_elem];
	}
	cout << "\n";
}


void heap(int* array, int array_size, int idx) {
	int max = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2; 

	if (left < array_size && array[left] > array[max]){ max = left; }	
	if (right < array_size && array[right] > array[max]){ max = right; }	
	if (max != idx) {
		swap(array[idx], array[max]);
		heap(array, array_size, max);
	}
}


void heap_sort(int* array, int array_size)
{
	for (int idx = array_size / 2 - 1; idx >= 0; idx--)
		heap(array, array_size, idx);

	for (int idx = array_size - 1; idx > 0; idx--) {
		swap(array[0], array[idx]);
		heap(array, idx, 0);
	}
	print_array(array, array_size);
}


void initialization()
{
	int array_size = 10;
	int* array = new int[10] { 2, 4, 1, 11, 9, 7, 4, 9, 50, 20 };
	print_array(array, array_size);
	heap_sort(array, array_size);
	delete[] array;
}


int main()
{
	initialization();
}