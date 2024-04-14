#include <iostream>


class Node {
public:
    int val;
    Node* next;
public:
    Node(int val) : val(val), next(nullptr) {}
};


class queue {
private:
    Node* head;
    Node* tail;
public:
    queue() : head(nullptr), tail(nullptr) {}

    bool is_empty();
    void push(int val);
    void print();
    int pop();
};


class Exception : public std::domain_error {
public:
    Exception(const char* const message) : std::domain_error(message) {}
};


Exception empty("queue is empty");


bool queue::is_empty() {
    return head == nullptr;
}


void queue::push(int val) {
    Node* el = new Node(val);
    if (is_empty() || val < head->val) {
        el->next = head;
        head = el;
    }
    else {
        Node* curr = head;
        while (curr->next != nullptr && val >= curr->next->val) {
            curr = curr->next;
        }
        el->next = curr->next;
        curr->next = el;
        if (el->next == nullptr) {
            tail = el;
        }
    }
}


void queue::print() {
    if (is_empty()) return;
    Node* el = head;
    while (el) {
        std::cout << el->val << " ";
        el = el->next;
    }
    std::cout << std::endl;
}


int queue::pop() {
    if (is_empty()) throw empty;
    Node* el = head;
    int head_val = el->val;
    head = el->next;
    delete el;
    return head_val;
}


int main() {
    queue A;
    A.push(3);
    A.push(1);
    A.push(5);
    A.push(2);

    A.print();

    while (!A.is_empty()) {
        std::cout << A.pop() << std::endl;
    }

    return 0;
}