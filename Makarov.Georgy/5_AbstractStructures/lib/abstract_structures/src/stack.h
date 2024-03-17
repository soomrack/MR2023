#ifndef STACK_H
#define STACK_H

#include <iostream>

class StackException : public std::exception {
private:
    std::string exception_msg;
public:
    explicit StackException(std::string msg) : exception_msg(std::move(msg)) {}

    [[nodiscard]] const char *what() const noexcept override { return exception_msg.c_str(); }
};


class Stack {
};

#endif //STACK_H
