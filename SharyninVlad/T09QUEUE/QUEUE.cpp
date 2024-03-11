#include <iostream>

class QueueItem
{
public:
    int data;
    int priopity;
    QueueItem* next;
    QueueItem* prev;
};

class Queue {
private:
    QueueItem* head;
    QueueItem* tail;
public:
    Queue();
    Queue(const Queue& L);
    Queue(Queue&& L);
    void Push(int n, int prior);
    void Pop();
    void print();
};

Queue::Queue()
{
    head = NULL;
    tail = NULL;
}

Queue::Queue(const Queue& L)
{

    if (L.head == nullptr) {
        head = nullptr;
        tail = nullptr;
        return;
    }
    QueueItem* tmp_head = nullptr;
    for (QueueItem* tmp_idx = L.head; tmp_idx != nullptr; tmp_idx = tmp_idx->prev) {
        QueueItem* tmp_list_item = new QueueItem;
        tmp_list_item->data = tmp_idx->data;
        tmp_list_item->priopity = tmp_idx->priopity;
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


Queue::Queue(Queue&& L)
{
    head = L.head;
    tail = L.tail;
    L.head = L.tail = nullptr;
}


void Queue::Push(int n, int prior)
{
    QueueItem* tmp = new QueueItem;
    QueueItem* tmp_idx = head;
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

void Queue::Pop()
{

    if (tail == nullptr) return;

    tail->data = 0;
    tail->priopity = 0;

    if (tail->next == nullptr) {
        head = nullptr;
        tail = nullptr;
        return;
    }

    tail = tail->next;
    tail->prev = nullptr;
}

void Queue::print()
{
    QueueItem* Tmp = head;
    while (Tmp != NULL)
    {
        std::cout << Tmp->data  << ",prior=" << Tmp->priopity << "\t";
        Tmp = Tmp->prev;
    }
    std::cout << "\n";
}

int main()
{
    Queue list;

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