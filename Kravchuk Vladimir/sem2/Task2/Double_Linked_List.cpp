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
    Element* top_pointer;
    Element* bottom_pointer;

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


DoubleLinkedList::DoubleLinkedList() : top_pointer(nullptr), bottom_pointer(nullptr){}


DoubleLinkedList::~DoubleLinkedList() {
    Element* deleted = top_pointer;
    while (deleted != nullptr) {
        Element* next = deleted->next;
        delete deleted;
        deleted = next;
    }
    bottom_pointer = nullptr;
}


void DoubleLinkedList::add_head(int value) {
    Element* New_Element = new Element(value);
    if (top_pointer == nullptr) {
        top_pointer = bottom_pointer = New_Element;
    }
    else {
        New_Element->next = top_pointer;
        top_pointer->previous = New_Element;
        top_pointer = New_Element;
    }
}


void DoubleLinkedList::add_tail(int value) {
    Element* New_Element = new Element(value);
    if (bottom_pointer == nullptr) {
        bottom_pointer = top_pointer = New_Element;
    }
    else {
        New_Element->previous = bottom_pointer;
        bottom_pointer->next = New_Element;
        bottom_pointer = New_Element;
    }
}


void DoubleLinkedList::list_print() {
    Element* buf = top_pointer;
    while (buf != nullptr) {
        cout << buf->data << "\t";
        cout << "\n";
        buf = buf->next;
    }
}


void DoubleLinkedList::list_print_reverse() {
    Element* buf = bottom_pointer;
    while (buf != nullptr) {
        cout << buf->data << "\t";
        cout << "\n";
        buf = buf->previous;
    }
}


void DoubleLinkedList::doubling() {
    Element* buf = top_pointer;
    while (buf != nullptr) {
        buf->data *= 2;
        buf = buf->next;
    }
}



int DoubleLinkedList::del_head() {
    if (top_pointer == nullptr) {
        return NAN;
    }
    else {
        Element* deleted = top_pointer;
        int deleted_data = deleted->data;
        top_pointer = top_pointer->next;
        top_pointer->previous = nullptr;
        delete[] deleted;
        return deleted_data;
    }
}


int DoubleLinkedList::del_tail() {
    if (bottom_pointer == nullptr) {
        return NAN;
    }
    else {
        Element* deleted = bottom_pointer;
        int deleted_data = deleted->data;
        bottom_pointer = bottom_pointer->previous;
        bottom_pointer->next = nullptr;
        delete[] deleted;
        return deleted_data;
    }
}


int DoubleLinkedList::get_head_element() {
    if (top_pointer != nullptr) {
        return top_pointer->data;
    }
    else {
        return NAN;
    }
}


int DoubleLinkedList::get_bottom_element() {
    if (bottom_pointer != nullptr) {
        return bottom_pointer->data;
    }
    else {
        return NAN;
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
