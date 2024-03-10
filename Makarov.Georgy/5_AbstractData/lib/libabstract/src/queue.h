#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

class QueueException : public std::exception {
private:
    std::string exception_msg;
public:
    explicit QueueException(std::string msg) : exception_msg(std::move(msg)) {}

    [[nodiscard]] const char *what() const noexcept override { return exception_msg.c_str(); }
};


class Queue {
};

#endif //QUEUE_H
