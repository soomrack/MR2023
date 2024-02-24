#include <iostream>
#include <vector>

void merge(std::vector<int>& array, int initial, int middle, int last,  int* firstPart, int* secondPart)
{
	int countInFirst = middle + 1 - initial;
	int countInSecond = last - middle;

	memcpy(&firstPart[0], &array[initial], countInFirst * sizeof(int));
	memcpy(&secondPart[0], &array[middle + 1], countInSecond * sizeof(int));

	int i = 0; // The element of the firstPart array
	int j = 0; // The element of the secondPart array
	int k = initial; // The element of the sorted array

	while (i < countInFirst && j < countInSecond) {
		if (firstPart[i] <= secondPart[j]) {
			array[k] = firstPart[i];
			i++;
		} else {
			array[k] = secondPart[j];
			j++;
		}
		k++;
	}

	if (i < countInFirst) {
		memcpy(&array[k], &firstPart[i], (countInFirst - i) * sizeof(int));
		k += countInFirst - i;
	}

	if (j < countInSecond) {
		memcpy(&array[k], &secondPart[j], (countInSecond - j) * sizeof(int));
		k += countInSecond - j;
	}
}

void sort(std::vector<int>& array, int initial, int last) 
{
	if (initial < last) {
		int middle = initial + (last - initial) / 2;

		sort(array, initial, middle);
		sort(array, middle + 1, last);

		int* firstPart = new int[middle + 1 - initial];
		int* secondPart = new int[last - middle];

		merge(array, initial, middle, last,  firstPart, secondPart);
	}
}

void print_array(int size, std::vector<int>& array)
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

	sort(array, 0, size - 1);

	print_array(size, array);
}

int main() 
{
	initialization();

	return 0;
}
