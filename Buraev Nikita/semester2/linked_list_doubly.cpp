#include <iostream>
#include <stdexcept>

class DoubleLinkedList {
private:
    class Node {
    public:
        int data;
        Node* next;
        Node* prev;

        Node(int value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t size;

public:
    DoubleLinkedList();
    ~DoubleLinkedList();

    void push_front(int);
    void push_back(int);
    int pop_front();
    int pop_back();
    void insert(int, size_t);
    size_t get_size();
    bool is_empty();
    void clear();
    void print_list();
};

DoubleLinkedList::DoubleLinkedList() : head(nullptr), tail(nullptr), size(0) {}

DoubleLinkedList::~DoubleLinkedList() {
    clear();
}

void DoubleLinkedList::push_front(int value) {
    Node* newNode = new Node(value);

    if (is_empty()) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    size++;
}

void DoubleLinkedList::push_back(int value) {
    Node* newNode = new Node(value);

    if (is_empty()) {
        head = tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }

    size++;
}

int DoubleLinkedList::pop_front() {
    if (is_empty()) {
        throw std::runtime_error("Error: DoubleLinkedList is empty!");
    }

    Node* temp = head;
    int poppedValue = temp->data;

    if (size == 1) {
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }

    delete temp;
    size--;

    return poppedValue;
}

int DoubleLinkedList::pop_back() {
    if (is_empty()) {
        throw std::runtime_error("Error: DoubleLinkedList is empty!");
    }

    Node* temp = tail;
    int poppedValue = temp->data;

    if (size == 1) {
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }

    delete temp;
    size--;

    return poppedValue;
}

void DoubleLinkedList::insert(int value, size_t index) {
    if (index < 0 || index > size) {
        throw std::out_of_range("Error: Invalid index!");
    }

    if (index == 0) {
        push_front(value);
        return;
    }

    if (index == size) {
        push_back(value);
        return;
    }

    Node* newNode = new Node(value);
    Node* current = head;

    for (size_t i = 0; i < index - 1; i++) {
        current = current->next;
    }

    newNode->prev = current;
    newNode->next = current->next;
    current->next = newNode;
    newNode->next->prev = newNode;

    size++;
}

size_t DoubleLinkedList::get_size() {
    return size;
}

bool DoubleLinkedList::is_empty() {
    return size == 0;
}

void DoubleLinkedList::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }

    head = tail = nullptr;
    size = 0;
}

void DoubleLinkedList::print_list() {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << "nullptr" << std::endl;
}

int main() {
    DoubleLinkedList doubleLinkedList;
    doubleLinkedList.push_back(5);
    doubleLinkedList.push_back(10);
    doubleLinkedList.push_back(15);

    std::cout << "DoubleLinkedList size: " << doubleLinkedList.get_size() << std::endl;
    std::cout << "List: ";
    doubleLinkedList.print_list();

    std::cout << "Popping back element: " << doubleLinkedList.pop_back() << std::endl;

    std::cout << "Inserting 20 at index 1." << std::endl;
    doubleLinkedList.insert(20, 1);
    std::cout << "List: ";
    doubleLinkedList.print_list();

    return 0;
}
