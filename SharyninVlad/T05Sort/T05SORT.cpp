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
    size_t lenth;

public:
    void print();
    void set();
    size_t getsize();
    MassItem* getdata();

public:
    void Swap(MassItem* a, MassItem* b);
    void BubbleSort();
    void MergeSort(MassItem* mas, MassItem* tmp, size_t size);
    void InsertionSort(MassItem* mas, size_t size);
    void QuickSort(MassItem* mas, size_t size);
};

Massive::Massive() {
    lenth = MAX;
    Mas = new MassItem[lenth];
}

Massive::Massive(const size_t n) {
    lenth = n;
    if (lenth == 0)
        Mas = nullptr;
    else
        Mas = new MassItem[lenth];
}

Massive::~Massive() {
    lenth = 0;
    delete[] Mas;
}

void Massive::set()
{
    for (size_t idx = 0; idx < lenth; idx++)
        Mas[idx] = (MassItem)(rand() % 100);
}

void Massive::print()
{
    for (size_t idx = 0; idx < lenth; idx++)
        std::cout << Mas[idx] << "\t";
    std::cout << "\n \n \n";
}

size_t Massive::getsize()
{
    return lenth;
}

MassItem* Massive::getdata()
{
    return Mas;
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
    for (size_t m = lenth; m > 1; m--)
        for (size_t k = 0; k < m - 1; k++)
            if (Mas[k] > Mas[k + 1]) Swap(&Mas[k], &Mas[k + 1]);
}

void Massive::MergeSort(MassItem* mas, MassItem* tmp, size_t size)
{
    size_t middle = size / 2;

    if (size < 2)
        return;
    else {
        MergeSort(mas, tmp, middle);
        MergeSort(mas + middle, tmp, size - middle);
    }
    for (size_t idx = 0, i = 0, j = middle; idx < size; idx++) {
        if (j >= size || i < middle && mas[i] <= mas[j])
            tmp[idx] = mas[i++];
        else
            tmp[idx] = mas[j++];
    }
    for (size_t idx = 0; idx < size; idx++)
        mas[idx] = tmp[idx];
}

void Massive::InsertionSort(MassItem* mas, size_t size)
{
    MassItem key;

    for (size_t i = 1, j; i < size; i++) {
        key = mas[i];
        j = i - 1;

        while (j >= 0 && mas[j] > key) {
            mas[j + 1] = mas[j];
            j--;
        }
        mas[j + 1] = key;
    }
}

void Massive::QuickSort(MassItem* mas, size_t size)
{
    size_t b = 0, e = size - 1;
    MassItem x = mas[size / 2];

    if (size < 2)
        return;
    else
    {
        while (b <= e)
        {
            while (b < size && mas[b] < x)
                b++;
            while (e >= 0 && mas[e] > x)
                e--;
            if (b <= e)
            {
                if (b != e)
                    Swap(&mas[b], &mas[e]);
                b++;
                e--;
            }
        }
        QuickSort(mas, e + 1);
        QuickSort(mas + b, size - b);
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
    MassItem* tmp = new MassItem[M.getsize()];
    M.MergeSort(M.getdata(), tmp, M.getsize());
    delete[] tmp;
    M.print();

    M.set();
    M.print();
    M.InsertionSort(M.getdata(), M.getsize());
    M.print();
    
    M.set();
    M.print();
    M.QuickSort(M.getdata(), M.getsize());
    M.print();

    return 1;
}
