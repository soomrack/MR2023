#include <iostream>
#include <cstring>
#include <initializer_list>

class LinkedList {
private:
    class Node {
    public:
        int data;
        Node* next;

        Node(int value) {
            data = value;
            next = nullptr;
        }
    };

    Node* head;
    size_t size;

public:
    LinkedList();
    ~LinkedList();

    size_t get_size();
    bool is_empty();
    void push_front(int);
    void insert(int, size_t);
    void push_back(int);
    int pop_front();
    int pop_back();
    void print_list();
    void clear();
};

LinkedList::LinkedList() {
    head = nullptr;
    size = 0;
}

LinkedList::~LinkedList() {
    clear();
}

size_t LinkedList::get_size() {
    return size;
}

bool LinkedList::is_empty() {
    return size == 0;
}

void LinkedList::push_front(int value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
    size++;
}

void LinkedList::insert(int value, size_t index) {
    if (index < 0 || index > size) {
        throw std::out_of_range("Invalid index!");
    }

    if (index == 0) {
        push_front(value);
    }

    if (index == size) {
        push_back(value);
    }

    Node* newNode = new Node(value);
    Node* current = head;

    for (size_t i = 0; i < index - 1; i++) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
    size++;
}

void LinkedList::push_back(int value) {
    Node* newNode = new Node(value);

    if (is_empty()) {
        head = newNode;
    }
    else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }

    size++;
}

int LinkedList::pop_front() {
    if (is_empty()) {
        throw std::runtime_error("Error: LinkedList is empty!");
    }

    Node* temp = head;
    int poppedValue = temp->data;
    head = head->next;
    delete temp;
    size--;

    return poppedValue;
}

int LinkedList::pop_back() {
    if (is_empty()) {
        throw std::runtime_error("Error: LinkedList is empty!");
    }

    if (size == 1) {
        return pop_front();
    }

    Node* current = head;
    while (current->next->next != nullptr) {
        current = current->next;
    }

    Node* temp = current->next;
    int poppedValue = temp->data;
    current->next = nullptr;
    delete temp;
    size--;

    return poppedValue;
}

void LinkedList::print_list() {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << "nullptr" << std::endl;
}

void LinkedList::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
    size = 0;
}
