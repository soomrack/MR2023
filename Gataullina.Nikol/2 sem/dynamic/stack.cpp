#include <iostream>

class Node {
private:
    friend class Stack;
    int value;
    Node* next;
public:
    Node(int val) : value(val), next(nullptr) {}
};

class Stack {
private:
    Node* first_add;
    Node* last_add;
public:
    Stack() : first_add(nullptr), last_add(nullptr) {}
    bool is_empty();
    void push(int val);
    void print();
    void pop();
};

bool Stack::is_empty() {
    return first_add == nullptr;
}

void Stack::push(int val) {
    Node* element = new Node(val);
    if (is_empty()) {
        first_add = element;
        last_add = element;
    }
    else {
        element->next = first_add;
        first_add = element;
    }
}

void Stack::print() {
    if (is_empty()) {
        std::cout << "stack is empty" << std::endl;
    }
    else {
        std::cout << first_add->value << std::endl;
    }
}

void Stack::pop() {
    if (is_empty()) return;
    Node* element = first_add;
    first_add = element->next;
    delete element;
}

int main() {
    Stack A;
    A.push(3);
    std::cout << "is empty?\n" << A.is_empty() << std::endl;
    A.print();
    A.push(2);
    A.print();
    A.pop();
    A.print();
    A.pop();
    A.print();

    return 0;
}