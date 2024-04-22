#include <iostream>

using namespace std;

struct Element {
    int data;
    Element* next;
    Element* previous;
    Element(int value) : data(value), next(nullptr), previous(nullptr){}
};


class DoubleLinkedList {
private:
    Element* head;
    Element* tail;

public:
    DoubleLinkedList();
    ~DoubleLinkedList();
    void add_head(int element);
    void add_tail(int element);
    void doubling();
    void list_print();
    void list_print_reverse();
    int del_head();
    int del_tail();
    int get_head_element();
    int get_bottom_element();
};


DoubleLinkedList::DoubleLinkedList() : head(nullptr), tail(nullptr){}


DoubleLinkedList::~DoubleLinkedList() {
    Element* deleted = head;
    while (deleted != nullptr) {
        Element* next = deleted->next;
        delete deleted;
        deleted = next;
    }
    tail = nullptr;
}


void DoubleLinkedList::add_head(int value) {
    Element* New_Element = new Element(value);
    if (head == nullptr) {
        head = tail = New_Element;
    }
    else {
        New_Element->next = head;
        head->previous = New_Element;
        head = New_Element;
    }
}


void DoubleLinkedList::add_tail(int value) {
    Element* New_Element = new Element(value);
    if (tail == nullptr) {
        tail = head = New_Element;
    }
    else {
        New_Element->previous = tail;
        tail->next = New_Element;
        tail = New_Element;
    }
}


void DoubleLinkedList::list_print() {
    Element* buf = head;
    while (buf != nullptr) {
        cout << buf->data << "\t";
        cout << "\n";
        buf = buf->next;
    }
}


void DoubleLinkedList::list_print_reverse() {
    Element* buf = tail;
    while (buf != nullptr) {
        cout << buf->data << "\t";
        cout << "\n";
        buf = buf->previous;
    }
}


void DoubleLinkedList::doubling() {
    Element* buf = head;
    while (buf != nullptr) {
        buf->data *= 2;
        buf = buf->next;
    }
}



int DoubleLinkedList::del_head() {
    if (head == nullptr) {
        return INT_MAX;
    }
    
    Element* deleted = head;
    int deleted_data = deleted->data;
    head = head->next;
    head->previous = nullptr;
    delete[] deleted;
    return deleted_data;
}


int DoubleLinkedList::del_tail() {
    if (tail == nullptr) {
        return INT_MAX;
    }
    Element* deleted = tail;
    int deleted_data = deleted->data;
    tail = tail->previous;
    tail->next = nullptr;
    delete[] deleted;
    return deleted_data;
}


int DoubleLinkedList::get_head_element() {
    if (head != nullptr) {
        return head->data;
    }
    else {
        return INT_MAX;
    }
}


int DoubleLinkedList::get_bottom_element() {
    if (tail != nullptr) {
        return tail->data;
    }
    else {
        return INT_MAX;
    }
}


int main()
{
    DoubleLinkedList List;
    List.add_head(3);
    List.add_head(3);
    List.add_head(4);
    List.add_head(3);
    List.add_tail(5);
    List.del_head();
    List.del_tail();
    List.list_print();
    List.doubling();
    List.list_print_reverse();
    List.get_head_element();

    return 0;
}
