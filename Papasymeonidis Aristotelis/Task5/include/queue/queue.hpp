#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream> // Ensure to include for std::cout, std::endl

template <typename T>
class queue_node {
public:
    int priority;
    T data;
    queue_node<T>* next;
    queue_node(const T& data, int priority = 0, queue_node<T>* next = nullptr)
        : data(data), priority(priority), next(next) {}
};

template <typename T>
class queue {
private:
    queue_node<T>* head;

public:
    queue() : head(nullptr) {}
    ~queue();

    void push(const T& value, int priority);
    T pop();
    void print() const;
};

template <typename T>
queue<T>::~queue() {
    while (head) {
        queue_node<T>* temp = head;
        head = head->next;
        delete temp;
    }
}

template <typename T>
void queue<T>::push(const T& value, int priority) {
    queue_node<T>* new_node = new queue_node<T>(value, priority);
    if (!head || head->priority < priority) { 
        new_node->next = head;
        head = new_node;
    } else {
        queue_node<T>* current = head;
        while (current->next && current->next->priority >= priority) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}


template <typename T>
T queue<T>::pop() {
    if (!head) throw std::runtime_error("Queue is empty");
    queue_node<T>* temp = head;
    T result = head->data;
    head = head->next;
    delete temp;
    return result;
}

template <typename T>
void queue<T>::print() const {
    queue_node<T>* current = head;
    while (current) {
        std::cout << current->data << " (Priority: " << current->priority << ") ";
        current = current->next;
    }
    std::cout << std::endl;
}

#endif // QUEUE_HPP
