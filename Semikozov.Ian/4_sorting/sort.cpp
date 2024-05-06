#include "sort.hpp"

#include <cstddef>
#include <vector>

void bubble_sort(std::vector<int> &v)
{
    if (v.size() <= 1) { return; }

    for (size_t i = 0; i < v.size(); i++)
    {
        for (size_t j = 0; j < v.size() - 1; j++)
        {
            if (v[j] > v[j + 1]) { std::swap(v[j], v[j + 1]); }
        }
    }
}

void merge_sort_body(std::vector<int> &v, std::vector<int> &&temp, size_t start, size_t end)
{
    if (start < end)
    {
        auto merge = [](std::vector<int> &vector, std::vector<int> &temp, size_t start, size_t middle, size_t end)
        {
            size_t left = start, right = middle + 1;
            size_t index = start;

            while (left <= middle && right <= end)
            {
                if (vector[left] <= vector[right])
                {
                    temp[index] = vector[left];
                    left++;
                }
                else
                {
                    temp[index] = vector[right];
                    right++;
                }
                index++;
            }

            while (left <= middle)
            {
                temp[index] = vector[left];
                index++;
                left++;
            }

            while (right <= end)
            {
                temp[index] = vector[right];
                index++;
                right++;
            }
        };
        size_t middle = start + (end - start) / 2;

        merge_sort_body(v, std::move(temp), start, middle);
        merge_sort_body(v, std::move(temp), middle + 1, end);

        merge(v, temp, start, middle, end);

        for (size_t idx = start; idx <= end; idx++) { v[idx] = temp[idx]; }
    }
}

void merge_sort(std::vector<int> &v)
{
    if (v.size() <= 1) { return; }

    merge_sort_body(v, std::vector<int>{ v }, 0, v.size() - 1);
}

void heapify(std::vector<int> &vector, size_t size, size_t idx)
{
    const size_t left = 2 * idx + 1, right = 2 * idx + 2;
    size_t idx_max_heap = idx;

    if (left < size && vector[left] > vector[idx_max_heap]) { idx_max_heap = left; }

    if (right < size && vector[right] > vector[idx_max_heap]) { idx_max_heap = right; }

    if (idx_max_heap != idx)
    {
        std::swap(vector[idx], vector[idx_max_heap]);
        heapify(vector, size, idx_max_heap);
    }
}

void heap_sort(std::vector<int> &vector)
{
    for (size_t idx = vector.size() / 2 - 1; true; idx--)
    {
        if (idx + 1 == 0) break;

        heapify(vector, vector.size(), idx);
    }

    for (size_t idx = vector.size() - 1; true; idx--)
    {
        if (idx + 1 == 0) break;

        std::swap(vector[0], vector[idx]);
        heapify(vector, idx, 0);
    }
}

void insertion_sort(std::vector<int> &vector)
{
    for (size_t sorted = 1; sorted < vector.size(); sorted++)
    {
        int item = vector[sorted];

        size_t idx = sorted - 1;
        while ((idx + 1 != 0) && (vector[idx] > item))
        {
            vector[idx + 1] = vector[idx];
            idx--;
        }

        vector[idx + 1] = item;
    }
}
