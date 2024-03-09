#include <iostream>

class DLinkedListItem
{
public:
    int data;
    DLinkedListItem* next;
    DLinkedListItem* prev;
};

class DLinkedList {
private:
    DLinkedListItem* head;
    DLinkedListItem* tail;
public:
    DLinkedList();
    DLinkedList(const DLinkedList& L);
    DLinkedList(DLinkedList&& L);
    void Push(int n);
    void Pop();
    void print();
};


DLinkedList::DLinkedList()
{
    head = nullptr;
    tail = nullptr;
}


void DLinkedList::Push(int n)
{
    DLinkedListItem* tmp = new DLinkedListItem;
    tmp->data = n;
    tmp->next = tmp->prev = nullptr;

    if (head == nullptr) {
        head = tmp;
        tail = tmp;
    }
    else
    {
        tmp->prev = head;
        head->next = tmp;
        head = tmp;
    }
}


DLinkedList::DLinkedList(const DLinkedList& L)
{

    if (L.head == nullptr) {
        head = nullptr;
        tail = nullptr;
        return;
    }
    DLinkedListItem* tmp_head = nullptr;
    for (DLinkedListItem* tmp_idx = L.head; tmp_idx != nullptr; tmp_idx = tmp_idx->prev) {
        DLinkedListItem* tmp_list_item = new DLinkedListItem;
        tmp_list_item->data = tmp_idx->data;
        tmp_list_item->next = tmp_list_item->prev = nullptr;
        if (tmp_head == nullptr) {
            head = tmp_list_item;
            tmp_head = tmp_list_item;
        }
        else {
            tmp_head->prev = tmp_list_item;
            tmp_list_item->next = tmp_head;
            tmp_head = tmp_list_item;
        }
    }
    tail = tmp_head;
}


DLinkedList::DLinkedList(DLinkedList&& L)
{
    head = L.head;
    tail = L.tail;
    L.head = L.tail = nullptr;
}


void DLinkedList::Pop()
{
    if (tail == nullptr) return;

    tail->data = 0;

    if (tail->next == nullptr) {
        head = nullptr;
        tail = nullptr;
        return;
    }

    tail = tail->next;
    tail->prev = nullptr;
}


void DLinkedList::print()
{
    DLinkedListItem* Tmp = head;
    while (Tmp != nullptr)
    {
        std::cout << Tmp->data << "\t";
        Tmp = Tmp->prev;
    }
    std::cout << "\n";
}


int main()
{
    DLinkedList dlist;

    unsigned int choise, run = 1;
    int number;

    while (run)
    {
        std::cout << "choise: ";
        std::cin >> choise;

        switch (choise)
        {
        case 0:
            run = 0;
            break;

        case 1:
            std::cout << "number: ";
            std::cin >> number;
            dlist.Push(number);
            break;

        case 2:
            dlist.Pop();
            break;

        default:
            printf("wrong choise\n");
            break;
        }
        dlist.print();
    }

    return 0;
}