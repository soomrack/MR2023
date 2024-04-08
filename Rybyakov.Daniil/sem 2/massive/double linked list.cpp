#include <iostream>
using namespace std;

typedef int Data;

class Node {
public:
    Data data;
private:
    Node* next;
    Node* prev;
    friend class List;
public:
    Node() = delete;
    Node(const Data data, const Node* next = nullptr, const Node* prev = nullptr);
public:
    Node* get_next() { return next; }
    Node* get_prev() { return prev; }
    void add_next(Node* node, const Data value);
    void delete_next();
};


Node::Node(const Data data, const Node* next, const Node* prev) {
    this->data = data;
    this->next = const_cast<Node*>(next);
    this->prev = const_cast<Node*>(prev);
}


class List {

private:
    Node* head;
public:
    List() { head = nullptr; }
    ~List() { clear(); }
public:
    void add_head(const Data value);
    void delete_head();
    Node* get_head() { return head; };
    void clear();
};


void Node::add_next(Node* node, const Data value) {
    if (node == nullptr) {
        return;
    }
    Node* new_node = new Node(value, node->get_next(), node);
    node->next = new_node;
    if (new_node->next != nullptr) {
        new_node->next->prev = new_node;
    }
}


void Node::delete_next() {
    if (next == nullptr) {
        return;
    }
    Node* temp = next;
    if (temp->next != nullptr) {
        temp->next->prev = temp->prev;
    }
    next = temp->next;
    delete temp;
}


void List::add_head(const Data value) {
    Node* new_head = new Node(value, head, nullptr);
    if (head != nullptr) {
        head->prev = new_head;
    }
    head = new_head;
}


void List::delete_head() {
    if (head == nullptr) {
        return;
    }
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
    head = nullptr;
}


int main() {
    List list;
    list.add_head(5);
    list.add_head(22);
    list.add_head(8);
    list.delete_head();
    list.clear();
    return 0;
}