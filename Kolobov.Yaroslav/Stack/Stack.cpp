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
public:
    Stack() : st(nullptr) {}
    bool is_empty();
    void push(int _val);
    void print();
    void pop();
};

bool Stack::is_empty() {
    return st == nullptr;
}

void Stack::push(int _val) {
    Node* el = new Node(_val);
    if (is_empty()) {
        st = el;
    }
    else {
        el->next = st;
        st = el;
    }
}

void Stack::print() {
    if (is_empty()) {
        std::cout << "stack is empty" << std::endl;
    }
    else {
        Node* el = st;
        while (el) {
            std::cout << el->val << " ";
            el = el->next;
        }
        std::cout << std::endl;
    }
}

void Stack::pop() {
    if (is_empty()) return;
    Node* el = st;
    st = el->next;
    delete el;
}

int main() {
    Stack A;
    A.push(3);
    std::cout << "is empty? " << A.is_empty() << std::endl;
    A.print();
    A.push(2);
    A.print();
    A.pop();
    A.print();
    A.pop();
    A.print();

    return 0;
}