#include <iostream>
using namespace std;

typedef int Data;

class Node {
public:
    Data data;
private:
    Node* next;
    friend class Linked_List;
public:
    Node() = delete;
    Node(const Data data, const Node* next = nullptr);
public:
    Node* get_next() { return next; }
};


Node::Node(const Data data, const Node* next) {
    this->data = data;
    this->next = const_cast<Node*>(next);
}


class Linked_List {
private:
    Node* head;
public:
    Linked_List() : head{ nullptr } {}
    ~Linked_List() { clear(); }
public:
    void add_head(const Data value);
    void delete_head();
    Data get_head_data();
    void clear();
};


void Linked_List::add_head(const Data value) {
    head = new Node(value, head);
}


void Linked_List::delete_head() {
    if (head == nullptr) {
        return;
    }
    Node* temp = head;
    head = head->next;
    delete temp;
}


Data Linked_List::get_head_data() {
    if (head != nullptr) {
        return head->data;
    }
    else {
        return Data();
    }
}


void Linked_List::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}


int main() {
    Linked_List Linked_List;
    Linked_List.add_head(5);
    Linked_List.add_head(22);
    Linked_List.add_head(8);

    Data headData = Linked_List.get_head_data();
    cout <<  headData << endl;

    Linked_List.delete_head();
    Linked_List.clear();

    return 0;
}