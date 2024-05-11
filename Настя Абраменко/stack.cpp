#include <iostream>

class Node {
private:
    friend class Stack;
    int val;
    Node* next;
public:
    Node(int _val) : val(_val), next(nullptr) {}
};

class Stack {
private:
    Node* st;
    Node* last;
public:
    Stack() : st(nullptr), last(nullptr) {}
    bool empty();
    void push(int _val);
    void print();
    void pop();
};

bool Stack::empty() {
    return st == nullptr;
}

void Stack::push(int _val) {
    Node* el = new Node(_val);
    if (empty()) {
        st = el;
        last = el;
    }
    else {
        el->next = st;
        st = el;
    }
}

void Stack::print() {
    if (empty()) {
        std::cout << "stack is empty" << std::endl;
    }
    else {
        std::cout << st->val << std::endl;
    }
}

void Stack::pop() {
    if (empty()) return;
    Node* el = st;
    st = el->next;
    delete el;
}

int main() {
    Stack A;
    A.push(3);
    std::cout << "is empty? " << A.empty() << std::endl;
    A.print();
    A.push(2);
    A.print();
    A.pop();
    A.print();
    A.pop();
    A.print();

    return 0;
}