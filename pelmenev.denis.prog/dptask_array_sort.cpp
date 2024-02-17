#include <iostream>
#include <vector>
#include <math.h>


void print_array(const std::vector <int> &array)
{
    for(size_t idx = 0; idx < array.size(); ++idx)
        std::cout << array[idx] << " ";
     
    std::cout << std::endl;
}


void swap_elements(std::vector <int> &array, size_t idx_1, size_t idx_2)
{
    if (idx_1 >= array.size() || idx_2 >= array.size()) return;

    int buff = array[idx_1];
    array[idx_1] = array[idx_2];
    array[idx_2] = buff;
}


void sort_bubble(std::vector <int> &array)
{
    for (size_t sub_array = array.size(); sub_array > 1; --sub_array)
        for (size_t idx = 0; idx < sub_array - 1; ++idx)
            if (array[idx] > array[idx+1]) swap_elements(array, idx, idx+1);
}


void merge(std::vector <int> &array, std::vector <int> &sub_array_left, std::vector <int> &sub_array_right)
{
    for (size_t idx = 0; idx < array.size(); ++idx) {
        if (sub_array_left.empty() && sub_array_right.empty()) break;

        if (sub_array_left.empty() && !sub_array_right.empty()) {
            array[idx] = sub_array_right[0];
            sub_array_right.erase(sub_array_right.begin());
            break;
        }
        
        if (!sub_array_left.empty() && sub_array_right.empty()) {
            array[idx] = sub_array_left[0];
            sub_array_left.erase(sub_array_left.begin());
            break;
        }

        if (sub_array_left[0] < sub_array_right[0]) {
            array[idx] = sub_array_left[0];
            sub_array_left.erase(sub_array_left.begin());
        }
        else {
            array[idx] = sub_array_right[0];
            sub_array_right.erase(sub_array_right.begin());
        }
    }
}


void sort_merge(std::vector <int> &array)
{
    if (array.size() > 1) {
        size_t ar_end_left = (size_t)(std::round(array.size() / 2));
        size_t ar_end_right = array.size();

        //std::cout << "Length: " << ar_end_left << " " << ar_end_right << std::endl;     //DEBUG

        std::vector <int> sub_array_left;
        for (size_t idx = 0; idx < ar_end_left; ++idx)
            sub_array_left.push_back(array[idx]);
        
        //std::cout << "sub_array_left:  ";
        //print_array(sub_array_left);

        std::vector <int> sub_array_right;
        for (size_t idx = ar_end_left; idx < ar_end_right; ++idx)
            sub_array_right.push_back(array[idx]);
        
        //std::cout << "sub_array_right:  ";
        //print_array(sub_array_right);

        sort_merge(sub_array_left);
        sort_merge(sub_array_right);

        merge(array, sub_array_left, sub_array_right);

        //std::cout << "Merged array:  ";
        //print_array(array);
    }
}


int main()
{
    std::vector <int> a = {5, 4, 1, 3, 7, 3};
    print_array(a);
    std::cout << "--------------" << std::endl;
    //sort_bubble(a);
    sort_merge(a);
    print_array(a);
    
    return 0;
}
