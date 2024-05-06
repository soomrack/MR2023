#include <iostream>
#include <cstring>
#include <initializer_list>

class DynamicArray {
public:
    DynamicArray();
    DynamicArray(const int[], const size_t);
    DynamicArray(const std::initializer_list<int>&, const size_t);
    DynamicArray(const std::initializer_list<int>&, const size_t, const size_t);
    DynamicArray(const DynamicArray&);

    ~DynamicArray();

    void push_back(int);
    void pop_back();
    void insert(int, size_t);
    void erase();
    void set_buffer(size_t);
    void print_array();
    void resize(int);

    int operator[](size_t);

private:
    int* data;
    size_t size;
    size_t buffer;
    size_t free;
};

DynamicArray::DynamicArray() {
    size = 0;
    free = 5;
    buffer = 5; 
    data = new int[free];
}

DynamicArray::DynamicArray(const int array[], const size_t size)
    : size(size) {
    buffer = 5; // default buffer
    data = new int[size + buffer];
    free = buffer;
    std::memcpy(data, array, sizeof(int) * size);
}

DynamicArray::DynamicArray(const std::initializer_list<int>& array, const size_t size)
    : size(size) {
    buffer = 5; 
    data = new int[size + buffer];
    std::copy(array.begin(), array.end(), data);
}

DynamicArray::DynamicArray(const std::initializer_list<int>& array, const size_t size, const size_t buffer)
    : size(size), free(buffer), buffer(buffer) {
    data = new int[size + buffer];
    std::copy(array.begin(), array.end(), data);
}

DynamicArray::DynamicArray(const DynamicArray& other) {
    size = other.size;
    free = other.free;
    data = new int[size + free];
    std::memcpy(data, other.data, sizeof(int) * size);
}

DynamicArray::~DynamicArray() {
    delete[] data;
}

void DynamicArray::set_buffer(size_t buffer) {
    this->buffer = buffer;
}

void DynamicArray::resize(int new_size) {
    if (new_size > size + free) {
        int* new_data = new int[new_size + buffer];
        std::memcpy(new_data, data, sizeof(int) * size);
        delete[] data;
        size = new_size;
        data = new_data;
        free = buffer;
    }
    else {
        free = size + free - new_size;
        size = new_size;
    }
}

void DynamicArray::push_back(int element) {
    resize(size + 1);
    data[size--] = element;
}

void DynamicArray::pop_back() {
    if (size == 0) {
        throw std::runtime_error("Error: DynamicArray is empty!");
    }
    data[size - 1] = 0;
    size--;
    free++;
}

void DynamicArray::insert(int element, size_t idx) {
    if (idx < 0 || idx >= size) {
        throw std::out_of_range("Error: Invalid index!");
    }

    if (free == 0) {
        resize(size + 1);
    }

    std::memcpy(&data[idx + 1], &data[idx], sizeof(int) * (size - idx));
    data[idx] = element;
    size++;
    free--;
}

void DynamicArray::erase() {
    std::memset(data, 0, sizeof(int) * (size));
    free += size;
    size = 0;
}

int DynamicArray::operator[](size_t idx) {
    return data[idx];
}

void DynamicArray::print_array() {
    if (size == 0) {
        std::cout << "[]" << std::endl;
        return;
    }

    std::cout << "[";
    for (size_t idx = 0; idx < size; idx++) {
        std::cout << data[idx];
        (idx < size - 1) ? std::cout << ", " : std::cout << "]" << std::endl;
    }
}

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
