#include <iostream>
#define LOW_PRIRITY 1
#define MID_PRIRITY 2
#define HIGH_PRIRITY 3

class LinkedListItem
{
public:
    int data;
    int priopity;
    LinkedListItem* next;
    LinkedListItem* prev;
};

class LinkedList {
private:
    LinkedListItem* head;
    LinkedListItem* tail;
public:
    LinkedList();
    void Push(int n, int prior);
    void Pop();
    void print();
};

LinkedList::LinkedList()
{
    head = NULL;
    tail = NULL;
}

void LinkedList::Push(int n, int prior)
{
    LinkedListItem* tmp = new LinkedListItem;
    LinkedListItem* tmp_idx = head;
    tmp->data = n;
    tmp->priopity = prior;
    tmp->next = tmp->prev = NULL;

    if (head == NULL) {
        head = tail = tmp;
        return;
    }

    while (prior > tmp_idx->priopity)
        tmp_idx = tmp_idx->prev;


    tmp->prev = tmp_idx;
    tmp->next = tmp_idx->next;
    if (tmp_idx->next != NULL)
        tmp_idx->next->prev = tmp;
    tmp_idx->next = tmp;
    if (head->next != NULL)
        head = head->next;
}

void LinkedList::Pop()
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
        std::cout << Tmp->data  << ",prior=" << Tmp->priopity << "\t";
        Tmp = Tmp->prev;
    }
    std::cout << "\n";
}

int main()
{
    LinkedList list;

    list.Push(1, 3);
    list.print();

    list.Push(2, 2);
    list.print();

    list.Push(3, 1);
    list.print();

    list.Push(4, 2);
    list.print();

    list.Pop();
    list.print();
    return 0;
}