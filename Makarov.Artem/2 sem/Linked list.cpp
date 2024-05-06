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
public:
    List();

    void push_head(int value);
    void pop_head();
    void delete_position(int pos);
    void fillWithRandom();
    void clearList();
    void display();
};


List::List() 
{
    head = nullptr;
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


void List::pop_head() 
{
    Node* temp = new Node;
    temp = head;
    head = head->next;
    delete temp;
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
        push_head(rand() % 20);
    }
}


void List::clearList()
{
    head = nullptr;
}


int main()
{
    List list;

    list.fillWithRandom();
    list.display();

    std::cout << " \n";

    list.push_head(50);
    list.display();

    std::cout << " \n";

    list.pop_head();
    list.display();

    std::cout << " \n";

    list.delete_position(4);
    list.display();
    list.clearList();

    return 0;
}