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
    Node* tail;

public:
    List() : head(nullptr), tail(nullptr) {}
    ~List() { clear(); }

    void addHead(Data value);
    void addTail(Data value);
    void deleteHead();
    void deleteTail();
    Node* getHead() const { return head; }
    Node* getTail() const { return tail; }
    void clear();
};

void List::addHead(Data value) {
    Node* newHead = new Node(value, head, nullptr);
    if (head != nullptr) {
        head->prev = newHead;
    }
    head = newHead;
    if (tail == nullptr) {
        tail = newHead;
    }
}

void List::addTail(Data value) {
    Node* newTail = new Node(value, nullptr, tail);
    if (tail != nullptr) {
        tail->next = newTail;
    }
    tail = newTail;
    if (head == nullptr) {
        head = newTail;
    }
}

void List::deleteHead() {
    if (head == nullptr) return;
    Node* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    delete temp;
}

void List::deleteTail() {
    if (tail == nullptr) return;
    Node* temp = tail;
    tail = tail->prev;
    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }
    delete temp;
}

void List::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}

int main() {
    List list;
    list.addHead(5);
    list.addHead(22);
    list.addHead(8);
    list.addTail(10);
    list.deleteHead();
    list.deleteTail();
    list.clear();
    return 0;
}
