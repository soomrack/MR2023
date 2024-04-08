#include <iostream>

typedef int Data;

class Node {
public:
    Data data;
    Node* next;
    Node* prev;

    Node(Data _data, Node* _next = nullptr, Node* _prev = nullptr) : data(_data), next(_next), prev(_prev) {}
};

class List {
private:
    Node* head;

public:
    List() : head(nullptr) {}
    ~List() { clear(); }

    void addHead(Data value);
    void deleteHead();
    Node* getHead() const { return head; }
    void clear();
};

void List::addHead(Data value) {
    Node* newHead = new Node(value, head, nullptr);
    if (head != nullptr) {
        head->prev = newHead;
    }
    head = newHead;
}

void List::deleteHead() {
    if (head == nullptr) return;
    Node* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    }
    delete temp;
}

void List::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    List list;
    list.addHead(5);
    list.addHead(22);
    list.addHead(8);
    list.deleteHead();
    list.clear();
    return 0;
}
