#include <iostream>

using namespace std;

struct Element {
    int data;
    Element* pointer;
    Element(int value) : data(value), pointer(nullptr) {}
};


class LinkedList {
private:
    Element* head;

public:
    LinkedList();
    ~LinkedList();
    void add_head(int element);
    int del_head();
    void List_print();
    int get_head_element();
};


LinkedList::LinkedList() : head(nullptr) {}


LinkedList::~LinkedList() {
    Element* deleted = head;
    while (deleted != nullptr) {
        Element* pointer = deleted->pointer;
        delete deleted;
        deleted = pointer;
    }
    head = nullptr;
}


void LinkedList::add_head(int value) {
    Element* New_Element = new Element(value);
    New_Element->pointer = head;
    head = New_Element;
}


int LinkedList::del_head() {
    if (head == nullptr) {
        return INT_MAX;
    }
    Element* deleted = head;
    int deleted_data = deleted->data;
    head = head->pointer;
    delete[] deleted;
    return deleted_data;
}


void LinkedList::List_print() {
    Element* buf = head;
    while (buf != nullptr) {
        cout << buf->data << "\t";
        cout << "\n";
        buf = buf->pointer;
    }
}


int LinkedList::get_head_element() {
    if (head != nullptr) {
        return head->data;
    }
    else {
        return INT_MAX;
    }
}


int main()
{
    LinkedList List;
    List.add_head(3);
    List.add_head(3);
    List.add_head(4);
    List.add_head(3);
    List.del_head();
    List.List_print();
    List.List_print();
    List.get_head_element();

    return 0;
}
