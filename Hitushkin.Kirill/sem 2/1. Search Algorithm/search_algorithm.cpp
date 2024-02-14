#include <iostream>


int Search(int* array, int first, int last, int target)
{
    if (first == last)  
    {
        if (array[first] == target) return array[first]; 
        
        return -1;
    }

    int middle = (last - first) / 2 + first;

    if (array[middle] < target) return Search(array, middle + 1, last, target); 
    
    if (array[middle] > target) return Search(array, first, middle, target);

    return middle;
}

int main()
{
    int array[10] = {0,2,12,15,32,35,50,70,80,90};

    std::cout << Search(array, 0, 10, 12) << std::endl;

    return 1;
}

