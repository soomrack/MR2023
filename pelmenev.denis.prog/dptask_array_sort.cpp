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
    for (size_t idx = 0; idx < sub_array_right.size(); ++idx) {
        if (sub_array_left.empty() && !sub_array_right.empty()) {
            array[idx] = sub_array_right[0];
            sub_array_right.erase(sub_array_right.begin());
        }
        
        if (!sub_array_left.empty() && sub_array_right.empty()) {
            array[idx] = sub_array_left[0];
            sub_array_left.erase(sub_array_left.begin());
        }

        if (sub_array_left[0] <= sub_array_right[0]) {
            array[idx] = sub_array_left[0];
            sub_array_left.erase(sub_array_left.begin());
        }
        else {
            array[idx] = sub_array_right[0];
            sub_array_right.erase(sub_array_right.begin());
        }
    }

    sub_array_left.clear();
    sub_array_right.clear();
}


void sort_merge(std::vector <int> &array)
{
    if (array.begin() != array.end()) {
        size_t ar_end_left = (size_t)(std::ceil(array.size() / 2));
        size_t ar_end_right = array.size();

        std::vector <int> sub_array_left;
        for (size_t idx = 0; idx < ar_end_left; ++idx)
            sub_array_left.push_back(array[idx]);

        std::vector <int> sub_array_right;
        for (size_t idx = ar_end_left; idx < ar_end_right; ++idx)
            sub_array_right.push_back(array[idx]);

        sort_merge(sub_array_left);
        sort_merge(sub_array_right);

        merge(array, sub_array_left, sub_array_right);
    }
}


int main()
{
    std::vector <int> a = {5, 4, 1, 3, 3, 8};
    print_array(a);
    std::cout << "--------------" << std::endl;
    sort_merge(a);
    print_array(a);
    
    return 0;
}