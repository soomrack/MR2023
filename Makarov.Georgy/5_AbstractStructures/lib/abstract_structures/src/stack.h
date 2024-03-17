#ifndef STACK_H
#define STACK_H

#include <linked_list.h>

class StackException : public std::exception {
private:
    std::string exception_msg;
public:
    explicit StackException(std::string msg) : exception_msg(std::move(msg)) {}

    [[nodiscard]] const char *what() const noexcept override { return exception_msg.c_str(); }
};


class Stack : LinkedList {
public:
    Stack() = default;

    Stack(const Stack &stack) = default;

    Stack(Stack &&stack) noexcept = default;

    ~Stack() = default;

    void push(dtype item) { push_back(item); };

    void pop() {
        if (empty())
            throw StackException("Cannot pop empty stack");

        pop_back();
    };

    dtype top() {
        if (empty())
            throw StackException("Cannot get top value from empty stack");

        return get(get_size() - 1);
    };

    bool empty() { return get_size() == 0; };

    size_t size() { return get_size(); };
};

#endif //STACK_H
