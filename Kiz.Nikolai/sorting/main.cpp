#include <vector>
#include "BubbleSort.cpp"
#include "InsertionSort.cpp"
#include "MergeSort.cpp"
#include "HeapSort.cpp"

int main() {

    std::initializer_list<int> l = {1,4,-3,4,2,1,11,8,3,5,7,10};

    BubbleSort<int> bubble = l;
    InsertionSort<int> insert = l;
    MergeSort<int> merge = l;
    HeapSort<int> heap = l;

    std::vector<AbstractSort<int>*> sorts{&bubble, &insert, &merge, &heap};
    for (AbstractSort<int>* s_item: sorts) {
        s_item->sort();
        std::cout << *s_item;
    }
}
