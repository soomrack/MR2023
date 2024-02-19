#include <iostream>
#include <vector>

void Merge(std::vector<int>& array, int initial, int middle, int last)
{
	int countinfirst = middle + 1 - initial;
	int countinsecond = last - middle;

	std::vector<int> firstpart(countinfirst);
	std::vector<int> secondpart(countinsecond);

	for (size_t i = 0; i < countinfirst; i++) {
		firstpart[i] = array[initial + i];
	}

	for (size_t i = 0; i < countinsecond; i++) {
		secondpart[i] = array[middle + 1 + i];
	}

	int i = 0;
	int j = 0;
	int k = initial;

	while (i < countinfirst && j < countinsecond) {
		if (firstpart[i] <= secondpart[j]) {
			array[k] = firstpart[i];
			i++;
		} else {
			array[k] = secondpart[j];
			j++;
		}
		k++;
	}

	while (i < countinfirst) {
		array[k] = firstpart[i];
		i++;
		k++;
	}
}

void Sort(std::vector<int>& array, int initial, int last) 
{
	if (initial < last) {
		int middle = initial + (last - initial) / 2;

		Sort(array, initial, middle);
		Sort(array, middle + 1, last);

		Merge(array, initial, middle, last);
	}
}


int main() {
	std::vector<int> array = { 1, 11, 7, 5, 9, 10, 14 };
	int size = array.size();

	Sort(array, 0, size - 1);

	std::cout << "\nSorted array: ";
	for (int i = 0; i < size; i++) {
		std::cout << array[i] << " ";
	}

	return 0;
}
