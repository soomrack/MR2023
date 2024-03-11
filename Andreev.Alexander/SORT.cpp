#include <iostream>
#include <string>
#include <cstring>

#define MAX 50
typedef int MassItem;

class Massive {
public:
    Massive();
    Massive(const size_t n);
    ~Massive();

private:
    MassItem* Mas;
    size_t length;
private:
    void Merge_sort_insides(MassItem* mas, MassItem* tmp, size_t size);

public:
    void print();
    void set();
    size_t getsize();
    MassItem* getdata();
    void print_array(MassItem* mas, size_t size);

public:
    void Swap(MassItem* a, MassItem* b);
    void Bubble_sort();
    void Merge_sort(MassItem* mas, size_t size);
    void Insertion_sort(MassItem* mas, size_t size);
    void Heap_sort(MassItem* mas, size_t size);
    void Heap_correction(MassItem* mas, size_t size, size_t idx);
};

Massive::Massive() {
    length = MAX;
    Mas = new MassItem[length];
}

Massive::Massive(const size_t n) {
    length = n;
    if (length == 0)
        Mas = nullptr;
    else
        Mas = new MassItem[length];
}

Massive::~Massive() {
    length = 0;
    delete[] Mas;
}

void Massive::set()
{
    for (size_t idx = 0; idx < length; idx++)
        Mas[idx] = (MassItem)(rand() % 100);
}

void Massive::print()
{
    for (size_t idx = 0; idx < length; idx++)
        std::cout << Mas[idx] << "\t";
    std::cout << "\n \n \n";
}

size_t Massive::getsize()
{
    return length;
}

MassItem* Massive::getdata()
{
    return Mas;
}

void Massive::print_array(MassItem* mas, size_t size)
{
    for (size_t idx = 0; idx < size; idx++)
        std::cout << mas[idx] << "\t";
    std::cout << "\n \n \n";
}

void Massive::Swap(MassItem* a, MassItem* b)
{
    MassItem tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

void Massive::Bubble_sort()
{
    for (size_t unsorted_idx = length; unsorted_idx > 1; unsorted_idx--)
        for (size_t current_idx = 0; current_idx < unsorted_idx - 1; current_idx++)
            if (Mas[current_idx] > Mas[current_idx + 1]) Swap(&Mas[current_idx], &Mas[current_idx + 1]);
}

void Massive::Merge_sort(MassItem* mas, size_t size)
{
    MassItem* tmp = new MassItem[getsize()];
    memcpy(tmp, mas, sizeof(MassItem) * size);
    Merge_sort_insides(tmp, mas, size);
    delete[] tmp;
}

void Massive::Merge_sort_insides(MassItem* mas, MassItem* tmp, size_t size)
{
    size_t middle = size / 2;

    if (size < 2) return;

    Merge_sort_insides(tmp, mas, middle);
    Merge_sort_insides(tmp + middle, mas + middle, size - middle);

    for (size_t idx = 0, left_idx = 0, right_idx = middle; idx < size; idx++) {
        if (right_idx >= size) tmp[idx] = mas[left_idx++];
        else if (left_idx >= middle) tmp[idx] = mas[right_idx++];
        else if (mas[left_idx] <= mas[right_idx]) tmp[idx] = mas[left_idx++];
        else tmp[idx] = mas[right_idx++];
    }
}

void Massive::Insertion_sort(MassItem* mas, size_t size)
{
    MassItem key;

    for (size_t sorted_idx = 1, current_idx; sorted_idx < size; sorted_idx++) {
        key = mas[sorted_idx];
        for (current_idx = sorted_idx - 1; current_idx >= 0 && mas[current_idx] > key; current_idx--)
            mas[current_idx + 1] = mas[current_idx];
        mas[current_idx + 1] = key;
    }
}

void Massive::Heap_correction(MassItem* mas, size_t size, size_t idx)
{
    size_t largest = idx,
        left = 2 * idx + 1,
        right = 2 * idx + 2;

    if (left < size && mas[left] > mas[largest]) largest = left;
    if (right < size && mas[right] > mas[largest]) largest = right;
    if (largest != idx) {
        Swap(&mas[idx], &mas[largest]);
        Heap_correction(mas, size, largest);
    }
}

void Massive::Heap_sort(MassItem* mas, size_t size)
{
    for (int idx = size / 2 - 1; idx >= 0; idx--)
        Heap_correction(mas, size, idx);
    for (int idx = size - 1; idx >= 0; idx--) {
        Swap(&mas[0], &mas[idx]);
        Heap_correction(mas, idx, 0);
    }
}

int main(void)
{
    Massive M;

    M.set();
    std::cout << "Unsorted Array: ";
    M.print();
    M.Bubble_sort();
    std::cout << "Bubble Sorted Array: ";
    M.print();

    M.set();
    std::cout << "Unsorted Array: ";
    M.print();
    M.Merge_sort(M.getdata(), M.getsize());
    std::cout << "Merge Sorted Array: ";
    M.print();

    M.set();
    std::cout << "Unsorted Array: ";
    M.print();
    M.Insertion_sort(M.getdata(), M.getsize());
    std::cout << "Insertion Sorted Array: ";
    M.print();

    M.set();
    std::cout << "Unsorted Array: ";
    M.print();
    M.Heap_sort(M.getdata(), M.getsize());
    std::cout << "Heap Sorted Array: ";
    M.print();

    return 1;
}
