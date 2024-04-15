#include <iostream>
#include <stdexcept>

class Node {
private:
    friend class Queue;
    size_t val;
    Node* next;

public:
    Node(int _val) : val(_val), next(nullptr) {}
};

class Queue {
private:
    Node* head;
    Node* tail;

public:
    Queue() : head(nullptr), tail(nullptr) {}

    bool isEmpty() const;
    void push(int _val);
    void print() const;
    int pop();
};

class QueueException : public std::domain_error {
public:
    QueueException(const char* const message) : std::domain_error(message) {}
};

const QueueException emptyQueue("Queue is empty");

void Queue::push(int _val) {
    Node* el = new Node(_val);
    if (head == nullptr) {
        head = tail = el;
        return;
    }
    tail->next = el;
    tail = el;
}

void Queue::print() const {
    if (head == nullptr) return;
    Node* el = head;
    while (el) {
        std::cout << el->val << " ";
        el = el->next;
    }
    std::cout << std::endl;
}

int Queue::pop() {
    if (head == nullptr) throw emptyQueue;
    Node* el = head;
    int headVal = el->val;
    head = el->next;
    delete el;
    return headVal;
}

int main() {
    Queue A;
    A.push(1);
    std::cout << "Is empty? " << A.isEmpty() << std::endl;
    A.push(2);
    A.print();
    A.push(3);
    A.pop();
    A.print();
    return 0;
}
