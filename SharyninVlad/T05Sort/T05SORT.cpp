#include <iostream>
#include <string>
#include <cstring>

#define MAX 100
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
    void MergeSort_insides(MassItem* mas, MassItem* tmp, size_t size);

public:
    void print();
    void set();
    size_t getsize();
    MassItem* getdata();
    void print_array(MassItem* mas, size_t size);

public:
    void Swap(MassItem* a, MassItem* b);
    void BubbleSort();
    void MergeSort(MassItem* mas, size_t size);
    void InsertionSort(MassItem* mas, size_t size);
    void HeapSort(MassItem* mas, size_t size);
    void HeapCorrection(MassItem* mas, size_t size, size_t i);
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

void Massive::BubbleSort()
{
    for (size_t m = length; m > 1; m--)
        for (size_t k = 0; k < m - 1; k++)
            if (Mas[k] > Mas[k + 1]) Swap(&Mas[k], &Mas[k + 1]);
}

void Massive::MergeSort(MassItem* mas, size_t size)
{
    MassItem* tmp = new MassItem[getsize()];
    MergeSort_insides(mas, tmp, size);
    delete[] tmp;
}

void Massive::MergeSort_insides(MassItem* mas, MassItem* tmp, size_t size)
{
    size_t middle = size / 2;

    if (size < 2) return;

    MergeSort_insides(mas, tmp, middle);
    MergeSort_insides(mas + middle, tmp, size - middle);

    for (size_t idx_tmp = 0, left_branch = 0, right_branch = middle; idx_tmp < size; idx_tmp++) {
        if (right_branch >= size) tmp[idx_tmp] = mas[left_branch++];
        else if (left_branch >= middle) tmp[idx_tmp] = mas[right_branch++];
        else if (mas[left_branch] <= mas[right_branch]) tmp[idx_tmp] = mas[left_branch++];
        else tmp[idx_tmp] = mas[right_branch++];
    }
    memcpy(mas, tmp, sizeof(MassItem) * size);
}

void Massive::InsertionSort(MassItem* mas, size_t size)
{
    MassItem key;

    for (size_t idx = 1, idx_sorted_part; idx < size; idx++) {
        key = mas[idx];        
        for (idx_sorted_part = idx - 1; idx_sorted_part >= 0 && mas[idx_sorted_part] > key; idx_sorted_part--)
            mas[idx_sorted_part + 1] = mas[idx_sorted_part];
        mas[idx_sorted_part + 1] = key;
    }
}

void Massive::HeapSort(MassItem* mas, size_t size)
{
    for (int idx = size / 2 - 1; idx >= 0; idx--) {
        HeapCorrection(mas, size, idx);
        //print_array(mas, size);
    }
    for (int idx = size - 1; idx >= 0; idx--) {
        Swap(&mas[0], &mas[idx]);
        HeapCorrection(mas, idx, 0);
        //print_array(mas, size);
    }
}

void Massive::HeapCorrection(MassItem* mas, size_t size, size_t idx)
{
    while (1){
        size_t left = 2 * idx + 1, right = 2 * idx + 2, big = idx;

        if (left < size && mas[left] > mas[idx]) big = left;
        if (right < size && mas[right] > mas[big]) big = right;
        if (idx == big) return;
        Swap(&mas[idx], &mas[big]);
        idx = big;
    }
}

int main(void)
{
    Massive M;
    
    M.set();
    M.print();
    M.BubbleSort();
    M.print();
    
    M.set();
    M.print();
    M.MergeSort(M.getdata(), M.getsize());
    M.print();
    
    M.set();
    M.print();
    M.InsertionSort(M.getdata(), M.getsize());
    M.print();
    
    M.set();
    M.print();
    M.HeapSort(M.getdata(), M.getsize());
    M.print();
    
    return 1;
}
