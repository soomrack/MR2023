#include <iostream>
#include <vector>
#include <cstring>

void merge(std::vector<int>& array, int initial, int middle, int last,  int* buff)
{
	int countInFirst = middle + 1 - initial;
	int countInSecond = last - middle;

	memcpy(buff, &array[initial], countInFirst * sizeof(int));

	int i = 0; // The element of the buff array
	int j = middle + 1; // The element of the unsorted array
	int k = initial; // The element of the sorted array

	while (i < countInFirst && j <= last) {
		if (buff[i] <= array[j]) {
			array[k] = buff[i];
			i++;
		} else 
		{
			array[k] = array[j];
			j++;
		}
		k++;
	}

	memcpy(&array[k], &buff[i], (countInFirst - i) * sizeof(int));
}

void sort(std::vector<int>& array, int initial, int last, int* buff) 
{
	if (initial < last) {
		int middle = initial + (last - initial) / 2;

		sort(array, initial, middle, buff);
		sort(array, middle + 1, last, buff);

		merge(array, initial, middle, last,  buff);
	}
}

void printArray(int size, std::vector<int>& array)
{
	std::cout << "\nSorted array: ";
	for (int idx = 0; idx < size; idx++) {
		std::cout << array[idx] << " ";
	}
}

void initialization()
{
	std::vector<int> array = { 1, 11, 7, 5, 9, 10, 14 };
	int size = array.size();

	int* buff = new int[size];

	sort(array, 0, size - 1, buff);

	printArray(size, array);

	delete[] buff;
}

int main() 
{
	initialization();

	return 0;
}
