#include <iostream>


const int nmax = 10;


template <typename T>
void bubbleSort(T *arr, size_t size) 
{
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = size - 1; i < j; j--) {
            if (arr[j] < arr[j-1]) 
                std::swap(arr[j], arr[j-1]);
        }
    }
}


void Merg(int* arr, int begin, int end)
{
    int i = begin;
    int mid = begin + (end - begin) / 2;
    int j = mid + 1;
    int k = 0;
    int d[nmax];

    while (i <= mid && j <= end)
    {
        if(arr[i] <= arr[j]){
            d[k] = arr[i];
            i++;
        }else {
            d[k] = arr[j];
            j++;
        }
        k++;
    }
    
    while (i <= mid)
    {
        d[k] = arr[i];
        i++;
        k++;
    }

    while (j <= end)
    {
        d[k] = arr[j];
        j++;
        k++;
    }

    for(i = 0; i < k; i++){
        arr[begin + 1] = d[i];
    }    

}

void MergeSort(int *arr, int left, int right)
{
    int temp = 0;
    if(left < right){ //is the array single-element?
        if(right - left == 1){ //is the array two-element?
            if(arr[left] > arr[right]){
                temp = arr[left];
                arr[left] = arr[right];
                arr[right] = temp;
            }
        } else {
            MergeSort(arr, left, left + (right - left) / 2);
            MergeSort(arr, (left + (right - left) / 2) + 1, right);
            Merg(arr, left, right);
        }
    }

}


void input(int *m, int &n)
{
    std :: cout<< "Enter the number of array elements: ";
    std :: cin >> n;
    for(int i = 0; i < n; ++i){
        std::cout << "a[" << i << "]= ";
        std::cin >> m[i];
    }
}


void print(int *m, int n)
{
    for(int i = 0; i < n; i++){
        std::cout << m[i] << " ";
    }

    std::cout<< std::endl;
}



int main()
{
    int n;
    //int arr[nmax];

    //input(arr, n);
    n = 10;
    int arr[10] = {1, 3, 4, 3, 2, 5, 7, 2, 2, 9};
    //int arr[3] = {1, 8, 6};
    std::cout << "The source array:" << std::endl;
    print(arr,n);

    MergeSort(arr, 0, n - 1);

    std::cout << "Sorted array" << std::endl;
    print(arr,n);

    return 0;



}