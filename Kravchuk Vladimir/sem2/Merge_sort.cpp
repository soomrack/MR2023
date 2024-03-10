#include <iostream>
#include <vector>
#include <cstring>

void merge(int* array, int initial, int middle, int last)
{
	int i = initial;
	int j = middle + 1;

	while (i <= middle && j <= last) {
		if (array[i] <= array[j]) {
			i++;
		}
		else {
			int buff = array[j];
			for (int k = j; k > i; k--) {
				array[k] = array[k - 1];
			}
			array[i] = buff;

			j++;
			middle++;
		}
	}
}

void sort(int* array, int initial, int last)
{
	if (initial < last) 
	{
		int middle = initial + (last - initial) / 2;

		sort(array, initial, middle);
		sort(array, middle + 1, last);

		merge(array, initial, middle, last);
	}
}

void printArray(int size, int* array)
{
	std::cout << "\nSorted array: ";
	for (int idx = 0; idx < size; idx++) {
		std::cout << array[idx] << " ";
	}
}

void initialization()
{
	int array[] = { 1, 11, 7, 5, 9, 10, 14, 15, 3 };
	int size = std::end(array) - std::begin(array);

	sort(array, 0, size - 1);

	printArray(size, array);
}

int main() 
{
	initialization();

	return 0;
}
