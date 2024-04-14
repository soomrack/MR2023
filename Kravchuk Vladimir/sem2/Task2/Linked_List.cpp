#include <iostream>

using namespace std;

struct Element {
    int data;
    Element* pointer;
    Element(int value) : data(value), pointer(nullptr) {}
};


class LinkedList {
private:
    Element* topPointer;

public:
    LinkedList();
    ~LinkedList();
    void add(int element);
    void deleteElement();
    void doubling();
    void ListPrint();
};


LinkedList::LinkedList() : topPointer(nullptr) {}


LinkedList::~LinkedList() {
    Element* deleted = topPointer;
    while (deleted != nullptr) {
        Element* pointer = deleted->pointer;
        delete deleted;
        deleted = pointer;
    }
    topPointer = nullptr;
}


void LinkedList::add(int value) {
    Element* NewElement = new Element(value);
    NewElement->pointer = topPointer;
    topPointer = NewElement;
}


void LinkedList::deleteElement() {
    if (topPointer == nullptr) {
        return;
    }
    Element* buf = topPointer;
    topPointer = topPointer->pointer;
    delete[] buf;
}


void LinkedList::ListPrint() {
    Element* buf = topPointer;
    while (buf != nullptr) {
        cout << buf->data << "\t";
        cout << "\n";
        buf = buf->pointer;
    }
}


void LinkedList::doubling() {
    Element* buf = topPointer;
    while (buf != nullptr) {
        buf->data *= 2;
        buf = buf->pointer;
    }
}


int main()
{
    LinkedList List;
    List.add(3);
    List.add(3);
    List.add(4);
    List.add(3);
    List.deleteElement();
    List.ListPrint();
    List.doubling();
    List.ListPrint();

    return 0;
}
