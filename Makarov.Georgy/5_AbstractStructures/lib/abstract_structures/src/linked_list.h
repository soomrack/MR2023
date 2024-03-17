#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>

class LinkedListException : public std::exception {
private:
    std::string exception_msg;
public:
    explicit LinkedListException(std::string msg) : exception_msg(std::move(msg)) {}

    const char *what() const noexcept override { return exception_msg.c_str(); }
};


class LinkedList {
};

#endif //LINKED_LIST_H