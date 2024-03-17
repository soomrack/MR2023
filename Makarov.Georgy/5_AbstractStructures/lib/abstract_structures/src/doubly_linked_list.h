#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>

class DoublyLinkedListException : public std::exception {
private:
    std::string exception_msg;
public:
    explicit DoublyLinkedListException(std::string msg) : exception_msg(std::move(msg)) {}

    [[nodiscard]] const char *what() const noexcept override { return exception_msg.c_str(); }
};


class DoublyLinkedList {
};

#endif //DOUBLY_LINKED_LIST_H
