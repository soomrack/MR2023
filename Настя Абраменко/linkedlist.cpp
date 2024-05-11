#include <iostream>
using namespace std;

typedef int Data;

class Node {
public:
    Data data;
private:
    Node* next;
    friend class List;
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

class List {
private:
    Node* head;
public:
    List() : head{ nullptr } {}
    ~List() { clear(); }
public:
    void add_head(const Data value);
    void delete_head();
    Data get_head_data();
    void clear();
};

void List::add_head(const Data value) {
    head = new Node(value, head);
}

void List::delete_head() {
    if (head == nullptr) {
        return;
    }
    Node* temp = head;
    head = head->next;
    delete temp;
}

Data List::get_head_data() {
    if (head != nullptr) {
        return head->data;
    }
    else {
        return Data();
    }
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
    list.add_head(5);
    list.add_head(22);
    list.add_head(8);

    Data headData = list.get_head_data();
    cout << headData << endl;

    list.delete_head();
    list.clear();

    return 0;
}