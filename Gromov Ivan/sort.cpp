#include <iostream>
#include <cstring>
#include <string>


void bubble_sort(int arr[], int size)
{
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size - 1; ++j) {
			if (arr[j] > arr[j + 1]){
				std::swap(arr[j], arr[j + 1]);
			}
		}
	}
}

void insert_sort(int arr[], int size)
{
	 int i, key, j;
    for (i = 1; i < size; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) 
		{
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}


void merge(int arr[], int l, int m, int r)
{
	
    int n1 = m - l + 1;
    int n2 =  r - m;
	int i, j, k;
	
	int size = sizeof(&arr);
		
    int L[n1], M[n2];
 
    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
	}
    for (j = 0; j < n2; j++) {
        M[j] = arr[m + 1 + j];
	}
	
    i = 0; 
    j = 0; 
    k = l; 
 
    while (i < n1 && j < n2)
    {
        if (L[i] <= M[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = M[j];
            j++;
        }
        k++;
    }
 
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2)
    {
        arr[k] = M[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) 
{
  if (l < r) {
    int m = l + (r - l) / 2;

    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);

    merge(arr, l, m, r);
  }
}

void print(int arr[], int number_out)
{
    for(int idx = 0; idx < number_out; idx++) {
        std :: cout << arr[idx] << " ";
    }

    std :: cout<< std :: endl;
}


void heapify(int arr[], int n, int i)
{
    int largest = i;   

    int l = 2*i + 1;
    int r = 2*i + 2; 

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
	}

    for (int i=n-1; i>=0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main()
{

    int arr[10] = {1, 3, 43, 88, 33, 64, 2, 13, 7, 81};
    int n = sizeof(arr) / sizeof(arr[0]);
    std::cout << "Given array:" << std::endl;
    print(arr,10);

    //bubble_sort(arr, 10);
    mergeSort(arr, 0, n - 1);
    //insert_sort(arr, 10);
    //heapSort(arr, n);

    std::cout << "Sorted array: " << std::endl;
    print(arr, 10);

    return 0;
}