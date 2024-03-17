#ifndef QUEUE_H
#define QUEUE_H

#include <linked_list.h>

class QueueException : public std::exception {
private:
    std::string exception_msg;
public:
    explicit QueueException(std::string msg) : exception_msg(std::move(msg)) {}

    [[nodiscard]] const char *what() const noexcept override { return exception_msg.c_str(); }
};


class Queue : LinkedList {
public:
    Queue() = default;

    Queue(const Queue &queue) = default;

    Queue(Queue &&queue) noexcept = default;

    ~Queue() = default;

    void enqueue(dtype item, size_t priority = 0) {
        if (priority >= get_size() || priority == 0) push_back(item);
        else insert(priority - 1, item);
    };

    void dequeue() {
        if (empty())
            throw QueueException("Cannot dequeue from empty queue");

        remove(0);
    };

    dtype front() {
        if (empty())
            throw QueueException("Cannot get front item from empty queue");

        return get(0);
    };

    dtype back() {
        if (empty())
            throw QueueException("Cannot get back item from empty queue");

        return get(get_size() - 1);
    };

    bool empty() { return get_size() == 0; };

    size_t size() { return get_size(); };

    void print_queue() { print(); }
};

#endif //QUEUE_H
