#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

using namespace std;

// Function to fill vector with random numbers
void fill_random_vector(vector<int>& vector, const int& min_num, const int& max_num){
    // First create an instance of an engine.
    random_device rnd_device;
    // Specify the engine and distribution.
    mt19937 mersenne_engine {rnd_device()};  // Generates random integers
    uniform_int_distribution<int> dist {min_num, max_num};
    
    auto gen = [&dist, &mersenne_engine](){
                   return dist(mersenne_engine);
               };

    generate(begin(vector), end(vector), gen);
}

//Print function
void vector_print(const string& info, const vector<int>& vector){
    cout << info << ": ";
    for(int item : vector){
        cout << item << " ";
    }
    cout << "\n";
}

//Bubble sort
void bubble_sort(vector<int>& vector){
    for (size_t sorted = 0; sorted < vector.size(); sorted++)
        for (size_t item = 0; item < vector.size() - 1; item++){
            if (vector[item] > vector[item+1])
                swap(vector[item], vector[item+1]);
        }
}

//Insertion sort
void insertion_sort(vector<int>& vector){
    for(size_t sorted = 1; sorted < vector.size(); sorted++){
        int idx = sorted;
        while((idx > 0) && (vector[idx] < vector[idx-1])){
            swap(vector[idx], vector[idx-1]);
            idx--;
        }
    }
}


void heapify(std::vector<int>& vector, int size, int idx) 
{
    int largest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < size && vector[left] > vector[largest]) {
        largest = left;
    }

    if (right < size && vector[right] > vector[largest]) {
        largest = right;
    }

    if (largest != idx) {
        swap(vector[idx], vector[largest]);
        heapify(vector, size, largest);
    }
}

//Heap sort
void heap_sort(vector<int>& vector)
{
    for (int idx = vector.size() / 2 - 1; idx >= 0; idx--) {
        heapify(vector, vector.size(), idx);
    }

    for (int idx = vector.size() - 1; idx > 0; idx--) {
        swap(vector[0], vector[idx]);
        heapify(vector, idx, 0);
    }
}

void merge(std::vector<int>& vector, std::vector<int>& temp, size_t start, size_t middle, size_t end)
{
    size_t left = start, right = middle + 1;
    size_t index = start;

    while (left <= middle && right <= end) {
        if (vector[left] <= vector[right]) {
            temp[index] = vector[left];
            left++;
        } else {
            temp[index] = vector[right];
            right++;
        }
        index++;
    }

    while (left <= middle) {
        temp[index] = vector[left];
        index++;
        left++;
    }

    while (right <= end) {
        temp[index] = vector[right];
        index++;
        right++;
    }
}

void merge_sort_body(std::vector<int>& vector, std::vector<int>& temp, size_t start, size_t end)
{
    if (start < end) {
        size_t middle = start + (end - start) / 2;

        merge_sort_body(vector, temp, start, middle);
        merge_sort_body(vector, temp, middle + 1, end);

        merge(vector, temp, start, middle, end);

        for (size_t idx = start; idx <= end; idx++)
            vector[idx] = temp[idx];
    }
}

//Merge sort
void merge_sort(std::vector<int>& vector)
{
    const size_t start = 0;
    const size_t end = vector.size() - 1;

    std::vector<int> temp = vector;

    merge_sort_body(vector, temp, start, end);
}

int main(){
    vector<int> unsorted(20);
    fill_random_vector(unsorted, -100, 100);
    vector<int> vector;

    vector_print("unsorted", unsorted);

    vector = unsorted;
    bubble_sort(vector);
    vector_print("bubble sort",vector);

    vector = unsorted;
    insertion_sort(vector);
    vector_print("insertion sort",vector);

    vector = unsorted;
    heap_sort(vector);
    vector_print("heap sort", vector);

    vector = unsorted;
    merge_sort(vector);
    vector_print("merge sort", vector);

    return 0;
}