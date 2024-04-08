#include <iostream>

class LinkedListItem
{
public:
    int data;
    LinkedListItem* next;
};


class LinkedList {
    private:
        LinkedListItem* head;
        LinkedListItem* walk_head;
    public:
        LinkedList();
        LinkedList(const LinkedList& L);
        LinkedList(LinkedList&& L);
        void Push(int n);
        void Pop();
        void print();
        void walk_next();
        void return_to_first();
        void add_next(int n);
        void del_next();
};


LinkedList::LinkedList()
{
    head = nullptr;
    walk_head = nullptr;
}


LinkedList::LinkedList(const LinkedList& L)
{

    if (L.head == nullptr) {
        head = nullptr;
        walk_head = nullptr;
        return;
    }
    LinkedListItem* tmp_head = nullptr;
    for (LinkedListItem* tmp_idx = L.head; tmp_idx != nullptr; tmp_idx = tmp_idx->next) {
        LinkedListItem* tmp_item = new LinkedListItem;
        tmp_item->data = tmp_idx->data;
        tmp_item->next = nullptr;
        if (tmp_head == nullptr) {
            head = tmp_item;
            tmp_head = tmp_item;
        }
        else {
            tmp_head->next = tmp_item;
            tmp_head = tmp_item;
        }  
    }
    walk_head = head;
}


LinkedList::LinkedList(LinkedList&& L)
{
    head = L.head;
    walk_head = head;
    L.head = nullptr;
}


void LinkedList::Push(int n)
{
    LinkedListItem* tmp = new LinkedListItem;
    tmp->data = n;
    tmp->next = nullptr;

    if (head == nullptr) head = tmp;
    else
    {
        tmp->next = head;
        head = tmp;
    }
    walk_head = head;
}


void LinkedList::Pop()
{
    if (head != nullptr) {
        head->data = 0;
        head = head->next;
        walk_head = head;
    }
}


void LinkedList::print()
{
    LinkedListItem* Tmp = head;
    while (Tmp != nullptr)
    {
        std::cout << Tmp->data << "\t";
        Tmp = Tmp->next;
    }
    std::cout << "\n";
}


void LinkedList::walk_next()
{
    if (walk_head->next != nullptr) {
        std::cout << "before: " << walk_head->data << "\t";
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


void LinkedList::return_to_first() 
{
    walk_head = head;
}


void LinkedList::add_next(int n)
{
    LinkedListItem* tmp = new LinkedListItem;
    tmp->data = n;
    tmp->next = nullptr;

    if (head == nullptr) {
        head = tmp;
        walk_head = head;
    }
    else {
        tmp->next = walk_head->next;
        walk_head->next = tmp;
    }
}

void LinkedList::del_next()
{
    if (walk_head->next != nullptr) {
        walk_head->next->data = 0;
        walk_head->next = walk_head->next->next;
    }    
}


int main()
{
    LinkedList list;
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
            list.Pop();
            break;

        case 2:
            std::cout << "number: ";
            std::cin >> number;
            list.Push(number);
            break;

        case 3:
            list.print();
            break;

        case 4:
            list.walk_next();
            break;

        case 5:
            list.return_to_first();
            break;

        case 6:
            std::cout << "number: ";
            std::cin >> number;
            list.add_next(number);
            break;
        case 7:
            list.del_next();
            break;
        
        default:
            printf("wrong choise\n");
            break;
        }
        list.print();
    }
    return 0;
}