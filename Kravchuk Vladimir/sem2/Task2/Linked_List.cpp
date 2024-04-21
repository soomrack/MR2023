#include <iostream>

using namespace std;

struct Element {
    int data;
    Element* pointer;
    Element(int value) : data(value), pointer(nullptr) {}
};


class LinkedList {
private:
    Element* top_pointer;

public:
    LinkedList();
    ~LinkedList();
    void add_head(int element);
    int del_head();
    void doubling();
    void List_print();
    int get_head_element();
};


LinkedList::LinkedList() : top_pointer(nullptr) {}


LinkedList::~LinkedList() {
    Element* deleted = top_pointer;
    while (deleted != nullptr) {
        Element* pointer = deleted->pointer;
        delete deleted;
        deleted = pointer;
    }
    top_pointer = nullptr;
}


void LinkedList::add_head(int value) {
    Element* New_Element = new Element(value);
    New_Element->pointer = top_pointer;
    top_pointer = New_Element;
}


int LinkedList::del_head() {
    if (top_pointer == nullptr) {
        return NAN;
    }
    Element* deleted = top_pointer;
    int deleted_data = deleted->data;
    top_pointer = top_pointer->pointer;
    delete[] deleted;
    return deleted_data;
}


void LinkedList::List_print() {
    Element* buf = top_pointer;
    while (buf != nullptr) {
        cout << buf->data << "\t";
        cout << "\n";
        buf = buf->pointer;
    }
}


void LinkedList::doubling() {
    Element* buf = top_pointer;
    while (buf != nullptr) {
        buf->data *= 2;
        buf = buf->pointer;
    }
}


int LinkedList::get_head_element() {
    if (top_pointer != nullptr) {
        return top_pointer->data;
    }
    else {
        return NAN;
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
    List.doubling();
    List.List_print();
    List.get_head_element();

    return 0;
}
