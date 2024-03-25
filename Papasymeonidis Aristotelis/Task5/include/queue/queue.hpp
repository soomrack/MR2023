//
// Created by simeonidi03 on 25/3/24.
//

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <stdexcept>

struct Task {
    std::string name;
    int priority;

    Task(const std::string& n, int p) : name(n), priority(p) {}
};

class PriorityQueue {
private:
    Task* heap;
    int capacity;
    int size;

    // Helper function to maintain heap property while pushing an element
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[parent].priority > heap[index].priority)
                break;
            std::swap(heap[parent], heap[index]);
            index = parent;
        }
    }

    // Helper function to maintain heap property while popping an element
    void heapifyDown(int index) {
        int leftChild, rightChild, largestChild;
        while (true) {
            leftChild = 2 * index + 1;
            rightChild = 2 * index + 2;
            largestChild = index;

            if (leftChild < size && heap[leftChild].priority > heap[largestChild].priority)
                largestChild = leftChild;

            if (rightChild < size && heap[rightChild].priority > heap[largestChild].priority)
                largestChild = rightChild;

            if (largestChild == index)
                break;

            std::swap(heap[index], heap[largestChild]);
            index = largestChild;
        }
    }

    // Helper function to resize the heap when needed
    void resize() {
        if (size == capacity) {
            Task* newHeap = new Task[capacity * 2];
            for (int i = 0; i < size; ++i) {
                newHeap[i] = heap[i];
            }
            delete[] heap;
            heap = newHeap;
            capacity *= 2;
        }
    }

public:
    // Constructor
    PriorityQueue() : capacity(10), size(0) {
        heap = new Task[capacity];
    }

    // Destructor
    ~PriorityQueue() {
        delete[] heap;
    }

    // Method to push a task into the priority queue
    void push(const Task& task) {
        resize();
        heap[size++] = task;
        heapifyUp(size - 1);
    }

    // Method to pop the highest priority task from the priority queue
    Task pop() {
        if (isEmpty()) {
            throw std::out_of_range("Priority queue is empty!");
        }

        Task topTask = heap[0];
        heap[0] = heap[--size];
        heapifyDown(0);
        return topTask;
    }

    // Method to check if the priority queue is empty
    bool isEmpty() const {
        return size == 0;
    }
};

#endif //QUEUE_HPP
