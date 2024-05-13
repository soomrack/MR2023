#include <iostream>
using namespace std;

typedef int Data;

class Node {
public:
    Data data;
    Node* previous;
    Node* next;

    Node(const Data data, Node* previous = nullptr, Node* next = nullptr) : data(data), previous(previous), next(next) {}
};


class Double_Linked_List {
private:
    Node* head;
    Node* tail;

public:
    Double_Linked_List() : head(nullptr), tail(nullptr) {}
    ~Double_Linked_List() { clear(); }

    void add_head(const Data value);
    void add_tail(const Data value);
    void delete_head();
    void delete_tail();

    Data get_head_data();
    Data get_tail_data();
    void clear();
};


void Double_Linked_List::add_head(const Data value) {
    if (head == nullptr) {
        head = tail = new Node(value);
    }
    else {
        Node* newNode = new Node(value, nullptr, head);
        head->previous = newNode;
        head = newNode;
    }
}


void Double_Linked_List::add_tail(const Data value) {
    if (tail == nullptr) {
        head = tail = new Node(value);
    }
    else {
        Node* newNode = new Node(value, tail, nullptr);
        tail->next = newNode;
        tail = newNode;
    }
}


void Double_Linked_List::delete_head() {
    if (head == nullptr) {
        return;
    }
    Node* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->previous = nullptr;
    }
    else {
        tail = nullptr;
    }
    delete temp;
}


void Double_Linked_List::delete_tail() {
    if (tail == nullptr) {
        return;
    }
    Node* temp = tail;
    tail = tail->previous;
    if (tail != nullptr) {
        tail->next = nullptr;
    }
    else {
        head = nullptr;
    }
    delete temp;
}


Data Double_Linked_List::get_head_data() {
    if (head != nullptr) {
        return head->data;
    }
    else {
        return Data();
    }
}


Data Double_Linked_List::get_tail_data() {
    if (tail != nullptr) {
        return tail->data;
    }
    else {
        return Data();
    }
}


void Double_Linked_List::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}


int main() {
    Double_Linked_List Double_Linked_List;
    Double_Linked_List.add_head(5);
    Double_Linked_List.add_head(22);
    Double_Linked_List.add_head(8);
    Double_Linked_List.add_tail(42);

    Data headData = Double_Linked_List.get_head_data();
    Data tailData = Double_Linked_List.get_tail_data();
    cout << "Value in the head node: " << headData << endl;
    cout << "Value in the tail node: " << tailData << endl;

    Double_Linked_List.delete_head();
    Double_Linked_List.delete_tail();
    Double_Linked_List.clear();

    return 0;
}