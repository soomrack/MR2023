#include <iostream>

using namespace std;

void bubble_sort(int* arr, int lenght) {
	for (size_t i = 0; i < lenght; i++) {
		for (size_t j = 0; j < lenght - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
		}
	}
}

void insortion_sort(int* arr, int lenght) {
	for (size_t i = 1; i < lenght; i++) {
		for (size_t j = i; j > 0; j--) {
			if (arr[j] < arr[j - 1]) {
				swap(arr[j], arr[j - 1]);
			}
			else {
				break;
			}
		}
	}
}

void heap(int* arr, int lenght, int i) {
	int largest = i;
	int left = i * 2 + 1;
	int right = i * 2 + 2;

	if (left < lenght && arr[largest] < arr[left]) {
		largest = left;
	}

	if (right < lenght && arr[largest] < arr[right]) {
		largest = right;
	}

	if (largest != i) {
		swap(arr[largest], arr[i]);
		heap(arr, lenght, largest);
	}
}

void heap_sort(int* arr, int lenght) {
	// построение кучи
	for (int i = lenght / 2 - 1; i >= 0; i--) {
		heap(arr, lenght, i);
	}

	// сортируем
	for (int i = lenght - 1; i > 0; i--) {
		swap(arr[0], arr[i]);
		heap(arr, i, 0);
	}
}

void merge_sort_recursion(int* arr, int left, int right) {
	if (left < right) {
		int m = left + (right - 1) / 2;

		merge_sort_recursion(arr, left, m);
		merge_sort_recursion(arr, m + 1, right);

		merge_sorted_arr(arr, left, m, right);
	}
}

void merge_sorted_arr(int* arr, int left, int right, int m) {
	int left_lenght = m - left + 1;
	int right_lenght = m - right;

	int temp_left[left_lenght];
	int temp_right[right_lenght];

	int i, j, k;

	for (int i = 0; i < left_lenght; i++)
		temp_left[i] = arr[left + i];
	
	for (int i = 0; i < right_lenght; i++)
		temp_right[i] = arr[m + 1 + i];

	for (i = 0, j = 0, k = left, k <= right, k++){
		if ((i < left_lenght) && ((j >= right_lenght) 
			|| temp_left[i] <= temp_right[j])){

			arr[k] = temp_left[i];
			i++;
			}
		else{
			arr[k] = temp_right[j];
			j++;
		}
	}
}

void merge_sort(int* arr, int lenght) {
	merge_sort_recursion(arr, 0, lenght - 1);
}

void print_arr(int* arr, int lenght) {
	for (size_t i = 0; i < lenght; ++i)
		cout << arr[i] << " ";
	cout << endl;
}

int main() {
	int arr[] = {1, 4, 7, 3, 8, 2 };
	int lenght = 6;

	bubble_sort(arr, lenght);
	print_arr(arr, lenght);

	insortion_sort(arr, lenght);
	print_arr(arr, lenght);

	heap_sort(arr, lenght);
	print_arr(arr, lenght);

	merge_sort(arr, lenght);
	print_arr(arr, lenght);
	return 0;
}

