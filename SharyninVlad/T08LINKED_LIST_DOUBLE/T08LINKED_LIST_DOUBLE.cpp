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
    DLinkedListItem* walk_head;
public:
    DLinkedList();
    DLinkedList(const DLinkedList& L);
    DLinkedList(DLinkedList&& L);
    void Push_Head(int n);
    void Pop_Head();
    void Push_Tail(int n);
    void Pop_Tail();
    void print();
    void walk_prev();
    void walk_next();
    void del_this();
    void add_next(int n);
};


DLinkedList::DLinkedList()
{
    head = nullptr; 
    tail = nullptr;
    walk_head = head;
}


void DLinkedList::Push_Head(int n)
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
    walk_head = head;
}


DLinkedList::DLinkedList(const DLinkedList& L)
{

    if (L.head == nullptr) {
        head = nullptr;
        tail = nullptr;
        walk_head = nullptr;
        return;
    }
    DLinkedListItem* tmp_head = nullptr;
    for (DLinkedListItem* tmp_idx = L.head; tmp_idx != nullptr; tmp_idx = tmp_idx->prev) {
        DLinkedListItem* tmp_list_item = new DLinkedListItem;
        tmp_list_item->data = tmp_idx->data;
        tmp_list_item->next = tmp_list_item->prev = nullptr;
        if (tmp_head == nullptr) {
            head = tmp_list_item;
            walk_head = head;
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
    walk_head = head;
    L.head = L.tail = nullptr;
}


void DLinkedList::Pop_Head()
{
    if (head == nullptr) return;
    head->data = 0;

    if (head->prev == nullptr) {
        head = nullptr;
        tail = nullptr;
        walk_head = head;
        return;
    }

    head = head->prev;
    head->next = nullptr;
    walk_head = head;
}


void DLinkedList::Push_Tail(int n)
{
    DLinkedListItem* tmp = new DLinkedListItem;
    tmp->data = n;
    tmp->next = tmp->prev = nullptr;

    if (tail == nullptr) {
        head = tmp;
        tail = tmp;
    }
    else
    {
        tmp->next = tail;
        tail->prev = tmp;
        tail = tmp;
    }
    walk_head = head;
}


void DLinkedList::Pop_Tail()
{
    if (tail == nullptr) return;

    tail->data = 0;

    if (tail->next == nullptr) {
        head = nullptr;
        tail = nullptr;
        walk_head = head;
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


void DLinkedList::walk_prev()
{
    if (walk_head->prev != nullptr) {
        std::cout << "next: " << walk_head->data << "\t";
        walk_head = walk_head->prev;
        std::cout << "now: " << walk_head->data << "\t";
        if (walk_head->prev == nullptr)
            std::cout << "prev: " << "nullptr" << "\t";
        else
            std::cout << "prev: " << walk_head->prev->data << "\t";
    }
    else
        std::cout << "end" << "\t";
    std::cout << "\n";
}
    

void DLinkedList::walk_next()
{
    if (walk_head->next != nullptr) {
        std::cout << "prev: " << walk_head->data << "\t";
        walk_head = walk_head->next;
        std::cout << "now: " << walk_head->data << "\t";
        if (walk_head->next == nullptr)
            std::cout << "next: " << "nullptr" << "\t";
        else
            std::cout << "next: " << walk_head->next->data << "\t";
    }
    else
        std::cout << "end" << "\t";
    std::cout << "\n";
}
    

void DLinkedList::del_this() 
{
    if (walk_head == nullptr) return;
    DLinkedListItem* tmp_next;
    DLinkedListItem* tmp_prev;

    tmp_next = walk_head->next;
    tmp_prev = walk_head->prev;

    walk_head->data = 0;

    if (tmp_next == nullptr && tmp_prev == nullptr) {
        head = nullptr;
        tail = nullptr;
        walk_head = nullptr;
        return;
    }
    else if (tmp_next == nullptr) {
        tmp_prev->next = nullptr;
        head = tmp_prev;
        walk_head = tmp_prev;
    }
    else if (tmp_prev == nullptr) {
        tmp_next->prev = nullptr;
        tail = tmp_prev;
        walk_head = tmp_next;
    }
    else {
        tmp_next->prev = tmp_prev;
        tmp_prev->next = tmp_next;
        walk_head = tmp_next;
    }
}


void DLinkedList::add_next(int n)
{
    DLinkedListItem* tmp = new DLinkedListItem;
    tmp->data = n;
    tmp->next = tmp->prev = nullptr;

    if (head == nullptr) {
        head = tmp;
        tail = tmp;
        walk_head = head;
    }
    else if (walk_head->next == nullptr) {
        tmp->prev = head;
        head->next = tmp;
        head = tmp;
        walk_head = head;
    }
    else
    {
        walk_head->next->prev = tmp;
        tmp->next = walk_head->next;
        tmp->prev = walk_head;
        walk_head->next = tmp;
    }
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
            dlist.Pop_Head();
            break;

        case 2:
            std::cout << "number: ";
            std::cin >> number;
            dlist.Push_Head(number);
            break;

        case 3:
            dlist.Pop_Tail();
            break;

        case 4:
            std::cout << "number: ";
            std::cin >> number;
            dlist.Push_Tail(number);
            break;

        case 5:
            dlist.walk_next();
            break;

        case 6:
            dlist.walk_prev();
            break;

        case 7:
            dlist.del_this();
            break;

        case 8:
            std::cout << "number: ";
            std::cin >> number;
            dlist.add_next(number);
            break;

        default:
            printf("wrong choise\n");
            break;
        }
        dlist.print();
    }
    DLinkedList dlist_2(dlist);
    dlist_2.print();

    return 0;
}