#include <iostream>
#include <stdexcept>

class Queue {
private:
    class Node {
    public:
        int data;
        Node* next;

        Node(int value) : data(value), next(nullptr) {}
    };

    Node* front;
    Node* end;
    size_t size;

public:
    Queue();
    ~Queue();

    void enqueue(int);
    int dequeue();
    int front_element();
    size_t get_size();
    bool is_empty();
    void clear();
};

Queue::Queue() : front(nullptr), end(nullptr), size(0) {}

Queue::~Queue() {
    clear();
}

void Queue::enqueue(int value) {
    Node* newNode = new Node(value);
    if (end == nullptr) {
        front = end = newNode;
    } else {
        end->next = newNode;
        end = newNode;
    }
    size++;
}

int Queue::dequeue() {
    if (is_empty()) {
        throw std::runtime_error("Error: Queue is empty!");
    }

    Node* temp = front;
    int dequeuedValue = temp->data;
    front = front->next;
    if (front == nullptr) {
        end = nullptr;
    }
    delete temp;
    size--;

    return dequeuedValue;
}

int Queue::front_element() {
    if (is_empty()) {
        throw std::runtime_error("Error: Queue is empty!");
    }
    return front->data;
}

size_t Queue::get_size() {
    return size;
}

bool Queue::is_empty() {
    return size == 0;
}

void Queue::clear() {
    Node* current = front;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    front = end = nullptr;
    size = 0;
}

int main() {
    Queue queue;
    queue.enqueue(5);
    queue.enqueue(10);
    queue.enqueue(15);

    std::cout << "Queue size: " << queue.get_size() << std::endl;
    std::cout << "Front element: " << queue.front_element() << std::endl;

    std::cout << "Dequeueing elements: ";
    while (!queue.is_empty()) {
        std::cout << queue.dequeue() << " ";
    }
    std::cout << std::endl;

    return 0;
}
