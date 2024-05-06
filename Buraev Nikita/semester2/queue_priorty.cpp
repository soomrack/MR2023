#include <iostream>
#include <stdexcept>

class PriorityQueue {
private:
    class Node {
    public:
        int data;
        size_t priority;
        Node* next;

        Node(int value) : data(value), priority(0), next(nullptr) {}
        Node(int value, size_t prio) : data(value), priority(prio), next(nullptr) {}
    };

    Node* front;
    Node* end;
    size_t size;

public:
    PriorityQueue();
    ~PriorityQueue();

    void enqueue(int, size_t);
    int dequeue();
    int front_element();
    size_t get_size();
    bool is_empty();
    void clear();
};

PriorityQueue::PriorityQueue() : front(nullptr), end(nullptr), size(0) {}

PriorityQueue::~PriorityQueue() {
    clear();
}

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
    PriorityQueue priorityQueue;
    priorityQueue.enqueue(5, 2);
    priorityQueue.enqueue(10, 1);
    priorityQueue.enqueue(15, 3);

    std::cout << "PriorityQueue size: " << priorityQueue.get_size() << std::endl;
    std::cout << "Front element: " << priorityQueue.front_element() << std::endl;

    std::cout << "Dequeueing elements: ";
    while (!priorityQueue.is_empty()) {
        std::cout << priorityQueue.dequeue() << " ";
    }
    std::cout << std::endl;

    return 0;
}
