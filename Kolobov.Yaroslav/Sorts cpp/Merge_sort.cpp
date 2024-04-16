#include <iostream>

using namespace std;

void print_array(int* array, int num_of_elements)
{
    for (int pr_elem = 0; pr_elem < num_of_elements; ++pr_elem) {
        cout << array[pr_elem] << " ";
    }
    cout << endl;
}


void merge(int* tmp_array, int* array, int num_of_elements)
{
    int m_idx = num_of_elements / 2;

    if (num_of_elements < 2) return;

    merge(array, tmp_array, m_idx);
    merge(array + m_idx, tmp_array + m_idx, num_of_elements - m_idx);

    for (int idx = 0, l_idx = 0, r_idx = m_idx; idx < num_of_elements; idx++) {
        if (r_idx >= num_of_elements) tmp_array[idx] = array[l_idx++];
        else if (l_idx >= m_idx) tmp_array[idx] = array[r_idx++];
        else if (array[l_idx] <= array[r_idx]) tmp_array[idx] = array[l_idx++];
        else tmp_array[idx] = array[r_idx++];
    }
}


void merge_sort(int* array, int num_of_elements)
{
    int* tmp_array = new int[num_of_elements];
    memcpy(tmp_array, array, sizeof(int) * num_of_elements);
    merge(tmp_array, array, num_of_elements);
    delete[] tmp_array;
}


int main()
{
    int num_of_elements = 7;
    int* array = new int[num_of_elements] {5, 4, 3, 2, 1, 6, 7};

    print_array(array, num_of_elements);

    merge_sort(array, num_of_elements);

    print_array(array, num_of_elements);

    return 0;
}