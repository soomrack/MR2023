#include <iostream>


class Node {
public:
    int data;
    Node* next;
};


class Linked_list {
private:
    Node* head;

public:
    Linked_list(): head(nullptr) {};
    ~Linked_list();
    void add_head(int value);
    void delete_head();
    void print_head();
    int get_head();
};    


Linked_list::~Linked_list()
{
    while (head != nullptr){
        Node* temporary = head;
        head = head->next;
        delete temporary;
    }
}


void Linked_list::add_head(int value)
{
    Node* new_head = new Node();
    new_head->data = value;
    new_head->next = head;
    head = new_head;
}


void Linked_list::delete_head()
{
    if (head = nullptr) return;

    Node* temporary = head;
    head = head->next;
    delete temporary;
}


void Linked_list::print_head()
{
    if (head = nullptr) return;

    std::cout<<head->data<<std::endl;
}


int Linked_list::get_head()
{
    if (head = nullptr) return 1;

    return head->data;
}


int main()
{
    Linked_list list;
    list.add_head(33);
    list.add_head(22);
    list.add_head(11);

    list.print_head();

    list.delete_head();
    list.print_head();
}
