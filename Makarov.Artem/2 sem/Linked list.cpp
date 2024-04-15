#include <iostream>
#include <ctime>
#include <cstdlib>


struct Node
{
    int data;
    Node* next;
};


class List
{
private:
    Node* head;
    Node* tail;

public:
    List();

    void push_tail(int value);
    void display();
    void push_head(int value);
    void delete_head();
    void delete_tail();
    void delete_position(int pos);
    void fillWithRandom();
    void clearList();
};


List::List() 
{
    head = nullptr;
    tail = nullptr;
}


void List::push_tail(int value)  
{
    Node* temp = new Node;
    temp->data = value;
    temp->next = nullptr;

    if (head == nullptr)
    {
        head = temp;
        tail = temp;
        temp = nullptr;
    }
    else
    {
        tail->next = temp;
        tail = temp;
    }
}


void List::display() 
{  
    Node* temp = new Node;
    temp = head;
    while (temp != nullptr)
    {
        std::cout << temp->data << "\t";
        temp = temp->next;
    }
}


void List::push_head(int value) 
{
    Node* temp = new Node;
    temp->data = value;
    temp->next = head;
    head = temp;
}


void List::delete_head() 
{
    Node* temp = new Node;
    temp = head;
    head = head->next;
    delete temp;
}


void List::delete_tail()
{
    Node* current = new Node;
    Node* previous = new Node;
    current = head;

    while (current->next != nullptr)
    {
        previous = current;
        current = current->next;
    }

    tail = previous;
    previous->next = NULL;
    delete current;
}


void List::delete_position(int pos) 
{
    Node* current = new Node;
    Node* previous = new Node;
    current = head;

    for (int i = 1; i < pos; i++)
    {
        previous = current;
        current = current->next;
    }

    previous->next = current->next;
}


void List::fillWithRandom() 
{
    srand(time(0));

    for (int el = 0; el < 5; el++)
    {
        push_tail(rand() % 20);
    }
}


void List::clearList()
{
    head = nullptr;
    tail = nullptr;
}


int main()
{
    List list;

    list.fillWithRandom();
    list.display();

    std::cout << " \n";

    list.push_tail(55);
    list.display();

    std::cout << " \n";

    list.push_head(50);
    list.display();

    std::cout << " \n";

    list.delete_head();
    list.display();

    std::cout << " \n";

    list.delete_tail();
    list.display();

    std::cout << " \n";

    list.delete_position(4);
    list.display();
    list.clearList();

    return 0;
}