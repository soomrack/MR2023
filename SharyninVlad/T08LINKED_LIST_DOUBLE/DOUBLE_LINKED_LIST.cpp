#include <iostream>

class LinkedListItem
{
public:
    int data;
    LinkedListItem* next;
    LinkedListItem* prev;
};

class LinkedList {
private:
    LinkedListItem* head;
    LinkedListItem* tail;
public:
    LinkedList();
    void Push_Head(int n);
    void Pop_Head();
    void Push_Tail(int n);
    void Pop_Tail();
    void print();
};

LinkedList::LinkedList()
{
    head = NULL; 
    tail = NULL;
}

void LinkedList::Push_Head(int n)
{
    LinkedListItem* tmp = new LinkedListItem;
    tmp->data = n;
    tmp->next = tmp->prev = NULL;

    if (head == NULL) head = tail = tmp;
    else
    {
        tmp->prev = head;
        head->next = tmp;
        head = tmp;
    }
}

void LinkedList::Pop_Head()
{
    head->data = 0;

    head = head->prev;
    head->next = NULL;
}

void LinkedList::Push_Tail(int n)
{
    LinkedListItem* tmp = new LinkedListItem;
    tmp->data = n;
    tmp->next = tmp->prev = NULL;

    if (tail == NULL) head = tail = tmp;
    else
    {
        tmp->next = tail;
        tail->prev = tmp;
        tail = tmp;
    }
}

void LinkedList::Pop_Tail()
{
    tail->data = 0;

    tail = tail->next;
    tail->prev = NULL;
}

void LinkedList::print()
{
    LinkedListItem* Tmp = head;
    while (Tmp != NULL)
    {
        std::cout << Tmp->data << "\t";
        Tmp = Tmp->prev;
    }
    std::cout << "\n";
}

int main()
{
    LinkedList list;

    list.Push_Head(1);
    list.print();

    list.Push_Head(2);
    list.print();

    list.Push_Tail(3);
    list.print();

    list.Push_Tail(4);
    list.print();

    list.Pop_Head();
    list.print();
    return 0;
}