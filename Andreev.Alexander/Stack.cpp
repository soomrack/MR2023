#include <iostream>

class StackItem
{
public:
    int data;
    StackItem* next;
};


class Stack {
private:
    StackItem* head;
public:
    Stack();
    Stack(const Stack& L);
    Stack(Stack&& L);
    void Push(int n);
    void Pop();
    void print();
};


Stack::Stack()
{
    head = nullptr;
}


Stack::Stack(const Stack& L)
{

    if (L.head == nullptr) {
        head = nullptr;
        return;
    }
    StackItem* tmp_head = nullptr;
    for (StackItem* tmp_idx = L.head; tmp_idx != nullptr; tmp_idx = tmp_idx->next) {
        StackItem* tmp_item = new StackItem;
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
}


Stack::Stack(Stack&& L)
{
    head = L.head;
    L.head = nullptr;
}


void Stack::Push(int n)
{
    StackItem* tmp = new StackItem;
    tmp->data = n;
    tmp->next = nullptr;

    if (head == nullptr) head = tmp;
    else
    {
        tmp->next = head;
        head = tmp;
    }
}


void Stack::Pop()
{
    if (head != nullptr) {
        head->data = 0;
        head = head->next;
    }
}


void Stack::print()
{
    StackItem* Tmp = head;
    while (Tmp != nullptr)
    {
        std::cout << Tmp->data << "\t";
        Tmp = Tmp->next;
    }
    std::cout << "\n";
}


int main()
{
    Stack list;
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

        default:
            printf("wrong choise\n");
            break;
        }
        list.print();
    }
    return 0;
}