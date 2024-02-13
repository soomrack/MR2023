#include <iostream>
using namespace std;


int main() 
{
	int array[] = { 2, 4, 1, 11, 9, 7, 4, 9, 55, 23, 5 };

	int N = sizeof(array) / sizeof(array[0]);
	for(int k = 0; k < N; ++k) {
		for (int i = 0; i < N - k - 1; ++i) {
			if (array[i] > array[i + 1]) {
				int swap = array[i];
				array[i] = array[i + 1];
				array[i + 1] = swap;
			}
		}
	}

	for (int i = 0; i < N; ++i) {
		cout << "  " << array[i];
	}
	cout << "\n";
}