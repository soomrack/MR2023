#include <iostream>
#include <stdexcept>

class Stack {
private:
    class Node {
    public:
        int data;
        Node* next;

        Node(int value) : data(value), next(nullptr) {}
    };

    Node* head;
    size_t size;

public:
    Stack();
    ~Stack();

    void push(int);
    int pop();
    int top();
    size_t get_size();
    bool is_empty();
    void clear();
};

Stack::Stack() {
    head = nullptr;
    size = 0;
}

Stack::~Stack() {
    clear();
}

void Stack::push(int value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
    size++;
}

int Stack::pop() {
    if (is_empty()) {
        throw std::runtime_error("Error: Stack is empty!");
    }

    Node* temp = head;
    int poppedValue = temp->data;
    head = head->next;
    delete temp;
    size--;

    return poppedValue;
}

int Stack::top() {
    if (is_empty()) {
        throw std::runtime_error("Error: Stack is empty!");
    }
    return head->data;
}

size_t Stack::get_size() {
    return size;
}

bool Stack::is_empty() {
    return size == 0;
}

void Stack::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
    size = 0;
}

int main() {
    // Testing Stack
    Stack stack;
    stack.push(5);
    stack.push(10);
    stack.push(15);

    std::cout << "Stack size: " << stack.get_size() << std::endl;
    std::cout << "Top element: " << stack.top() << std::endl;

    std::cout << "Popping elements: ";
    while (!stack.is_empty()) {
        std::cout << stack.pop() << " ";
    }
    std::cout << std::endl;

    return 0;
}
