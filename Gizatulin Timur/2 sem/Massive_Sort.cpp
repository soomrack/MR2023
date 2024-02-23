#include <iostream>
#include <vector>
#include <math.h>
 
using namespace std;

void Swap(int* A, int* B)
{
    int interim = *A;
    *A = *B;
    *B = interim;
}

void print_arr(int* m, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << m[i] << " ";
    }

    cout << endl;
}

void bubble_sort(int* Arr, int Size) {
    for (int i = 0; i < Size - 1; i++)
    {
        for (int j = 0; j < Size - 1 - i; j++)
        {
            if (Arr[j] > Arr[j + 1])
                Swap(&Arr[j], &Arr[j + 1]);
        }
    }
}

void insertion_sort(int* Arr, int Size)
{
    for (int i = 1; i < Size; i++)
    {
        for (int j = i;
            (j > 0) && (Arr[j] < Arr[j - 1]); j--)
        {
            Swap(&Arr[j], &Arr[j - 1]);
        }
    }
}



int main()
{

    int size = 5;
    int* arr = new int[5] { 8, 4, 1, 11, 20 };
    print_arr(arr,  size);
    bubble_sort(arr, size);
    print_arr(arr, size);
    delete[] arr;
 
    size = 7;
    int* arr1 = new int[7] { 2, 4, 1, 11, 20, 76, 65};
    print_arr(arr1, size);
    insertion_sort(arr1, size);
    print_arr(arr1, size);
    delete[] arr1;




    return 0;
 }