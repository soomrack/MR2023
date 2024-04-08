#include <iostream>
#include <stdexcept>

class QueueItem {
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
    ~Queue();
    void Push(int n, int prior);
    int Pop();
    void print();
};

Queue::Queue() {
    head = nullptr;
    tail = nullptr;
}

Queue::Queue(const Queue& L) {
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

Queue::Queue(Queue&& L) {
    head = L.head;
    tail = L.tail;
    L.head = L.tail = nullptr;
}

Queue::~Queue() {
    QueueItem* current = head;
    while (current != nullptr) {
        QueueItem* next = current->next;
        delete current;
        current = next;
    }
}

void Queue::Push(int n, int prior) {
    QueueItem* tmp = new QueueItem;
    tmp->data = n;
    tmp->priopity = prior;
    tmp->next = tmp->prev = nullptr;

    if (head == nullptr) {
        head = tail = tmp;
        return;
    }

    if (prior < head->priopity) {
        tmp->next = head;
        head->prev = tmp;
        head = tmp;
        return;
    }

    QueueItem* tmp_idx = head;
    while (tmp_idx->next != nullptr && prior >= tmp_idx->next->priopity) {
        tmp_idx = tmp_idx->next;
    }
    tmp->next = tmp_idx->next;
    tmp->prev = tmp_idx;
    if (tmp_idx->next != nullptr)
        tmp_idx->next->prev = tmp;
    tmp_idx->next = tmp;

    if (tmp_idx == tail)
        tail = tmp;
}

int Queue::Pop() {
    if (tail == nullptr) {
        throw std::runtime_error("Queue is empty");
    }

    int popped_data = tail->data;

    if (tail->next == nullptr) {
        delete tail;
        head = nullptr;
        tail = nullptr;
        return popped_data;
    }

    QueueItem* tmp = tail;
    tail = tail->next;
    tail->prev = nullptr;
    delete tmp;

    return popped_data;
}

void Queue::print() {
    QueueItem* Tmp = head;
    while (Tmp != nullptr) {
        std::cout << Tmp->data << ",prior=" << Tmp->priopity << "\t";
        Tmp = Tmp->prev;
    }
    std::cout << "\n";
}

int main() {
    Queue list;

    list.Push(1, 3);
    list.print();

    list.Push(2, 2);
    list.print();

    list.Push(3, 1);
    list.print();

    list.Push(4, 2);
    list.print();

    int popped_value = list.Pop();
    std::cout << "Popped value: " << popped_value << std::endl;
    list.print();

    return 0;
}
