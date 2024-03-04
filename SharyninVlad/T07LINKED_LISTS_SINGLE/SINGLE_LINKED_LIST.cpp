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
    public:
        LinkedList();
        void Push(int n);
        void Pop();
        void print();
};

LinkedList::LinkedList()
{
    head = NULL;
}

void LinkedList::Push(int n)
{
    LinkedListItem* tmp = new LinkedListItem;
    tmp->data = n;
    tmp->next = NULL;

    if (head == NULL) head = tmp;
    else
    {
        tmp->next = head;
        head = tmp;
    }
}

void LinkedList::Pop()
{
    head->data = 0;
    head = head->next;
}

void LinkedList::print()
{
    LinkedListItem* Tmp = head;
    while (Tmp != NULL)
    {
        std::cout << Tmp->data << "\t";
        Tmp = Tmp->next;
    }
    std::cout << "\n";
}

int main()
{
    LinkedList list;

    list.Push(1);
    list.Push(2);
    list.Push(3);

    list.Pop();


    list.print();
    return 0;
}