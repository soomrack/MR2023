#include <iostream>
#include <stdexcept>
#include <vector>

class Node {
private:
    friend class PriorityQueue;
    int val;
    int priority;
public:
    Node(int _val, int _priority) : val(_val), priority(_priority) {}
};

class PriorityQueue {
private:
    std::vector<Node*> heap;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    PriorityQueue() {}

    bool isEmpty() const;
    void push(int _val, int _priority);
    void print() const;
    int pop();
};

class QueueException : public std::domain_error {
public:
    QueueException(const char* const message) : std::domain_error(message) {}
};

const QueueException emptyQueue("Queue is empty");

bool PriorityQueue::isEmpty() const {
    return heap.empty();
}

void PriorityQueue::push(int _val, int _priority) {
    Node* el = new Node(_val, _priority);
    heap.push_back(el);
    heapifyUp(heap.size() - 1);
}

void PriorityQueue::heapifyUp(int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && heap[parent]->priority > heap[index]->priority) {
        std::swap(heap[parent], heap[index]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

void PriorityQueue::print() const {
    if (isEmpty()) return;
    for (const auto& node : heap) {
        std::cout << node->val << "(" << node->priority << ") ";
    }
    std::cout << std::endl;
}

int PriorityQueue::pop() {
    if (isEmpty()) throw emptyQueue;
    Node* top = heap[0];
    int topVal = top->val;
    delete top;
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown(0);
    return topVal;
}

void PriorityQueue::heapifyDown(int index) {
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int smallest = index;

    if (leftChild < heap.size() && heap[leftChild]->priority < heap[smallest]->priority)
        smallest = leftChild;
    if (rightChild < heap.size() && heap[rightChild]->priority < heap[smallest]->priority)
        smallest = rightChild;

    if (smallest != index) {
        std::swap(heap[index], heap[smallest]);
        heapifyDown(smallest);
    }
}

int main() {
    PriorityQueue A;
    A.push(1, 2);
    std::cout << "Is empty? " << A.isEmpty() << std::endl;
    A.push(2, 1);
    A.print();
    A.push(3, 3);
    A.pop();
    A.print();
    return 0;
}
