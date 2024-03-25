#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>

typedef int dtype;

class DoublyLinkedListException : public std::exception {
private:
    std::string exception_msg;
public:
    explicit DoublyLinkedListException(std::string msg) : exception_msg(std::move(msg)) {}

    [[nodiscard]] const char *what() const noexcept override { return exception_msg.c_str(); }
};

struct DoublyLinkedListItem {
    dtype data;
    DoublyLinkedListItem *next;
    DoublyLinkedListItem *prev;
};

class DoublyLinkedList {
private:
    DoublyLinkedListItem head{0, &tail, nullptr};
    DoublyLinkedListItem tail{0, nullptr, &head};
    size_t size{0};

public:
    DoublyLinkedList() = default;

    DoublyLinkedList(const DoublyLinkedList &list);

    DoublyLinkedList(DoublyLinkedList &&list) noexcept;

    ~DoublyLinkedList() { while (size--) pop_back(); };

    [[nodiscard]] size_t get_size() const { return size; };

    [[nodiscard]] dtype get(size_t index) const;

    void push_back(const dtype &item);

    void pop_back();

    void push_head(const dtype &item);

    void pop_head();

    void insert(size_t index, const dtype &item);

    void remove(size_t index);

    void print() const;
};

#endif //DOUBLY_LINKED_LIST_H
