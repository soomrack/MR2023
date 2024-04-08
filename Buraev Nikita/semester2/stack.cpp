#include <iostream>
#include <stdexcept>

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
    Node* top;
public:
    Stack() : top(nullptr) {}
    bool isEmpty() const;
    void push(int _val);
    void print() const;
    void pop();
};

class StackException : public std::domain_error {
public:
    StackException(const char* const message) : std::domain_error(message) {}
};

const StackException emptyStack("Stack is empty");

bool Stack::isEmpty() const {
    return top == nullptr;
}

void Stack::push(int _val) {
    Node* el = new Node(_val);
    if (isEmpty()) {
        top = el;
    }
    else {
        el->next = top;
        top = el;
    }
}

void Stack::print() const {
    if (isEmpty()) {
        std::cout << "Stack is empty" << std::endl;
    }
    else {
        std::cout << top->val << std::endl;
    }
}

void Stack::pop() {
    if (isEmpty()) throw emptyStack;
    Node* el = top;
    top = el->next;
    delete el;
}

int main() {
    Stack A;
    A.push(3);
    std::cout << "Is empty? " << A.isEmpty() << std::endl;
    A.print();
    A.push(2);
    A.print();
    A.pop();
    A.print();
    A.pop();
    A.print();

    return 0;
}
