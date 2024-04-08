#ifndef PRIORITY_LINKED_LIST_H
#define PRIORITY_LINKED_LIST_H

#include <iostream>

typedef int dtype;

class PriorityLinkedListException : public std::exception {
private:
    std::string exception_msg;
public:
    explicit PriorityLinkedListException(std::string msg) : exception_msg(std::move(msg)) {}

    [[nodiscard]] const char *what() const noexcept override { return exception_msg.c_str(); }
};

class PriorityLinkedListItem {
public:
    dtype data;
    uint8_t priority;
    PriorityLinkedListItem *next;

    PriorityLinkedListItem() = delete;

    PriorityLinkedListItem(const dtype &data_, uint8_t priority_, PriorityLinkedListItem *next_) : data{data_},
                                                                                                   priority{priority_},
                                                                                                   next{next_} {};

    void push_back(const dtype &data_, uint8_t priority_) {
        next = new PriorityLinkedListItem(data_, priority_, next);
    };

    void pop_back() { if (next != nullptr) next = next->next; };
};

class PriorityLinkedList {
protected:
    PriorityLinkedListItem head{0, 20, nullptr};
    PriorityLinkedListItem *tail{&head};
    size_t size{0};
public:
    PriorityLinkedList() = default;

    PriorityLinkedList(const PriorityLinkedList &list);

    PriorityLinkedList(PriorityLinkedList &&list) noexcept;

    ~PriorityLinkedList() { while (size--) head.pop_back(); };

    [[nodiscard]] size_t get_size() const { return size; };

    [[nodiscard]] dtype get_item(size_t index) const;

    [[nodiscard]] uint8_t get_priority(size_t index) const;

    void push_back(const dtype &item, uint8_t priority = 20);

    void push_priority(const dtype &item, uint8_t priority = 20);

    void pop_back();

    void insert(size_t index, const dtype &item, uint8_t priority);

    void remove(size_t index);

    void print() const;
};

#endif //PRIORITY_LINKED_LIST_H