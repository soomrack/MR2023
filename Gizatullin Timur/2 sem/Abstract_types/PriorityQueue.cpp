#include <iostream>
#include <stdexcept>

class PriorityQueue {
    class Node {
    public:
        int data;
        size_t priority;
        Node* next;

        Node(int value, size_t prior) : data(value), priority(prior), next(nullptr) {}
    };

    Node* front;
    size_t size;

public:
    PriorityQueue() : front(nullptr), size(0) {}
    ~PriorityQueue() { clear(); }

    void enqueue(int value, size_t priority);
    int dequeue();
    int front_element();
    size_t get_size();
    bool is_empty();
    void clear();
};

void PriorityQueue::enqueue(int value, size_t priority) {
    Node* newNode = new Node(value, priority);

    if (front == nullptr || priority < front->priority) {
        newNode->next = front;
        front = newNode;
    } else {
        Node* current = front;
        while (current->next != nullptr && current->next->priority < priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    size++;
}

int PriorityQueue::dequeue() {
    if (is_empty()) {
        throw std::runtime_error("Error: Queue is empty!");
    }

    Node* temp = front;
    int dequeuedValue = temp->data;
    front = front->next;
    delete temp;
    size--;

    return dequeuedValue;
}

int PriorityQueue::front_element() {
    if (is_empty()) {
        throw std::runtime_error("Error: Queue is empty!");
    }
    return front->data;
}

size_t PriorityQueue::get_size() {
    return size;
}

bool PriorityQueue::is_empty() {
    return size == 0;
}

void PriorityQueue::clear() {
    Node* current = front;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    front = nullptr;
    size = 0;
}

int main() {
    PriorityQueue PrOue;
    PrOue.enqueue(2,2);
    PrOue.enqueue(2,0);
    PrOue.get_size();
    PrOue.front_element();
    PrOue.dequeue();
    return 0;
}
