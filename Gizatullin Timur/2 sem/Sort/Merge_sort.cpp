#include <iostream>

using namespace std;

void print_arr(int* m, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << m[i] << " ";
    }

    cout << endl;
}


void merge_Sort(int* arr, int size)
{
    int mid = size / 2; // находим середину сортируемой последовательности
    if (size % 2 == 1)
        mid++;
    int h = 1;// шаг
    int* arr1 = new int[size]; // выделяем память
    int step;
    while (h < size)
    {
        step = h;
        int index_firstway = 0;
        int index_secondway = mid;
        int index_resultway = 0;
        while (step <= mid)
        {
            while ((index_firstway < step) && (index_secondway < size) && (index_secondway < (mid + step))) 
              // пока не дошли до конца пути заполняем следующий элемент формируемой последовательности меньшим из двух просматриваемых
            {
                if (arr[index_firstway] < arr[index_secondway])
                {
                    arr1[index_resultway] = arr[index_firstway];
                    index_firstway++; index_resultway++;
                }
                else {
                    arr1[index_resultway] = arr[index_secondway];
                    index_secondway++; index_resultway++;
                }
            }
            while (index_firstway < step)
            { //если второй путь кончился раньше, то переписываем оставшиеся элементы первого пути)
                arr1[index_resultway] = arr[index_firstway];
                index_firstway++; index_resultway++;
            }
            while ((index_secondway < (mid + step)) && (index_secondway < size))
            {
                arr1[index_resultway] = arr[index_secondway];
                index_secondway++; index_resultway++;
            }
            step = step + h;
        }
        h = h * 2;

        // Переносим упорядоченную последовательность(промежуточный вариант) в исходный массив
        for (int i = 0; i < size; i++)
            arr[i] = arr1[i];

    }

    delete[] arr1;

}

int main() {
    int* arr = new int[8] { -9, -3, 4, -10, -1, -6, 8, 8 };
    int arr_size = 8;

    print_arr(arr, arr_size);
    merge_Sort(arr, arr_size);
    print_arr(arr, arr_size);
    delete[] arr;
    return 0;
}
