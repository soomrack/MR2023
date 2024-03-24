#ifndef QUEUE_H
#define QUEUE_H

#include <priority_linked_list.h>

class QueueException : public std::exception {
private:
    std::string exception_msg;
public:
    explicit QueueException(std::string msg) : exception_msg(std::move(msg)) {}

    [[nodiscard]] const char *what() const noexcept override { return exception_msg.c_str(); }
};


class Queue : PriorityLinkedList {
public:
    Queue() = default;

    Queue(const Queue &queue) = default;

    Queue(Queue &&queue) noexcept = default;

    ~Queue() = default;

    void enqueue(dtype item, size_t priority = 20) {
        if (priority >= 20) push_back(item);

        push_priority(item, priority);
    };

    void dequeue() {
        if (empty())
            throw QueueException("Cannot dequeue from empty queue");

        remove(0);
    };

    dtype front() {
        if (empty())
            throw QueueException("Cannot get front item from empty queue");

        return get_item(0);
    };

    dtype back() {
        if (empty())
            throw QueueException("Cannot get back item from empty queue");

        return get_item(get_size() - 1);
    };

    bool empty() { return get_size() == 0; };

    size_t size() { return get_size(); };

    void print_queue() { print(); }
};

#endif //QUEUE_H
