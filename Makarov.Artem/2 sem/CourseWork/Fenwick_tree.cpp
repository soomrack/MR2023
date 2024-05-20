#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>


std::vector<int> source_array;
std::vector<int> fenwick_tree_sum;
std::vector<int> fenwick_tree_min;
std::vector<int> fenwick_tree_max;
int size;


int get_prefix_sum(int i)
{
    int result = 0;
    for (; i >= 0; i = (i & (i + 1)) - 1)
    {
        result += fenwick_tree_sum[i];
    }
    return result;
}


void update_value(int idx, int delta)
{
    source_array[idx] += delta;
    for (int i = idx; i < size; i |= i + 1)
    {
        fenwick_tree_sum[i] += delta;
    }

    for (int i = idx; i < size; i |= i + 1)
    {
        fenwick_tree_min[i] = std::min(fenwick_tree_min[i], source_array[idx]);
        fenwick_tree_max[i] = std::max(fenwick_tree_max[i], source_array[idx]);
    }
}


int get_sum_in_range(int left, int right)
{
    if (left)
    {
        return get_prefix_sum(right) - get_prefix_sum(left - 1);
    }
    else
    {
        return get_prefix_sum(right);
    }
}


int get_min_prefix(int i)
{
    int result = INT_MAX;
    for (; i >= 0; i = (i & (i + 1)) - 1)
    {
        result = std::min(result, fenwick_tree_min[i]);
    }
    return result;
}


int get_max_prefix(int i)
{
    int result = INT_MIN;
    for (; i >= 0; i = (i & (i + 1)) - 1)
    {
        result = std::max(result, fenwick_tree_max[i]);
    }
    return result;
}


int get_min_in_range(int left, int right)
{
    if (left == 0)
    {
        return get_min_prefix(right);
    }
    else
    {
        return std::min(get_min_prefix(right), get_min_prefix(left - 1));
    }
}


int get_max_in_range(int left, int right)
{
    if (left == 0)
    {
        return get_max_prefix(right);
    }
    else
    {
        return std::max(get_max_prefix(right), get_max_prefix(left - 1));
    }
}


void print_source_array()
{
    for (int i = 0; i < size; ++i)
    {
        std::cout << source_array[i] << " ";
    }
    std::cout << "\n";
}


void print_fenwick(std::vector<int>& fenwick_tree)
{
    for (int i = 0; i < size; ++i)
    {
        std::cout << fenwick_tree[i] << " ";
    }
    std::cout << "\n";
}


int main()
{
    std::cout << "Enter the number of elements in the array: ";
    std::cin >> size;

    source_array.resize(size);
    fenwick_tree_sum.resize(size, 0);
    fenwick_tree_min.resize(size, INT_MAX);
    fenwick_tree_max.resize(size, INT_MIN);

    for (int i = 0; i < size; i++) {
        int value;
        std::cout << "Enter an element in an array: ";
        std::cin >> value;
        update_value(i, value);
    }

    std::cout << "\nSource Array: ";
    print_source_array();

    std::cout << "\nFenwick Tree: ";
    print_fenwick(fenwick_tree_sum);

    std::cout << "\nSum from 1 to 3 elements: " << get_prefix_sum(2) << std::endl;
    std::cout << "\nSum from 3 to 5 elements: " << get_sum_in_range(2, 4) << std::endl;

    std::cout << "\nUpdate element 2 by the value delta = -3\n";
    update_value(1, -3);

    std::cout << "\nSource Array after update: ";
    print_source_array();

    std::cout << "\nFenwick Tree after update: ";
    print_fenwick(fenwick_tree_sum);

    std::cout << "\nSum from 1 to 3 elements: " << get_prefix_sum(2) << std::endl;
    std::cout << "\nSum from 3 to 5 elements: " << get_sum_in_range(2, 4) << std::endl;

    std::cout << "\nMinimum value from 1 to 3 elements: " << get_min_in_range(0, 2) << std::endl;
    std::cout << "\nMaximum value from 1 to 3 elements: " << get_max_in_range(0, 2) << std::endl;

    return 0;
}
