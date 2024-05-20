#ifndef SORT_HPP_INCLUDED
#define SORT_HPP_INCLUDED

#include <vector>

using sorting_t = std::vector<int>;

void bubble_sort(sorting_t &vector);
void merge_sort(sorting_t &vector);
void heap_sort(sorting_t &vector);
void insertion_sort(sorting_t &vector);

#endif // SORT_HPP_INCLUDED
