#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>

typedef int dtype;

class LinkedListException : public std::exception {
private:
    std::string exception_msg;
public:
    explicit LinkedListException(std::string msg) : exception_msg(std::move(msg)) {}

    [[nodiscard]] const char *what() const noexcept override { return exception_msg.c_str(); }
};

class LinkedListItem {
public:
    dtype data;
    LinkedListItem *next;

    LinkedListItem() = delete;

    LinkedListItem(const dtype &data_, LinkedListItem *next_) : data{data_}, next{next_} {};

    void push_back(const dtype &data_) { next = new LinkedListItem(data_, next); };

    void pop_back() { if (next != nullptr) next = next->next; };
};

class LinkedList {
protected:
    LinkedListItem head{0, nullptr};
    LinkedListItem *tail{&head};
    size_t size{0};
public:
    LinkedList() = default;

    LinkedList(const LinkedList &list);

    LinkedList(LinkedList &&list) noexcept;

    ~LinkedList() { while (size--) head.pop_back(); };

    [[nodiscard]] size_t get_size() const { return size; };

    [[nodiscard]] dtype get(size_t index) const;

    void push_back(const dtype &item);

    void pop_back();

    void insert(size_t index, const dtype &item);

    void remove(size_t index);

    void print() const;
};

#endif //LINKED_LIST_H