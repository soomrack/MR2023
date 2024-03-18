#include "linked_list.h"

LinkedList::LinkedList(const LinkedList &list) {
    if (list.size == 0)
        return;

    for (size_t idx = 0; idx < list.size; idx++)
        push_back(list.get(idx));
}

LinkedList::LinkedList(LinkedList &&list) noexcept {
    head = list.head;
    list.head.next = nullptr;

    size = list.size;
    list.size = 0;
}

dtype LinkedList::get(const size_t index) const {
    if (index >= size)
        throw LinkedListException("Index out of range");

    LinkedListItem *item = head.next;

    size_t item_index = index + 1;
    while (--item_index) item = item->next;

    return item->data;
}

void LinkedList::push_back(const dtype &data) {
    tail->push_back(data);
    tail = tail->next;

    size++;
}

void LinkedList::push_back_priority(const dtype &data, size_t priority = 20) {
    LinkedListItem *new_item = new LinkedListItem(data, priority);

    if (head == nullptr) {
        head = new_item;
        tail = new_item;
    } else {
        tail->next = new_item;
        tail = new_item;
    }

    size++;
}

void LinkedList::pop_back() {
    if (size == 0)
        return;

    LinkedListItem *item = &head;

    size_t item_index = size - 1;
    while (item_index--) item = item->next;

    item->pop_back();

    size--;
}

void LinkedList::insert(size_t index, const dtype &data) {
    if (index >= size)
        throw LinkedListException("Index out of range");

    LinkedListItem *item = &head;

    size_t item_index = index;
    while (item_index--) item = item->next;

    item->push_back(data);

    size++;
}

void LinkedList::insert_priority(size_t index, const dtype &data, size_t priority = 20) {
    if (index > size)
        throw LinkedListException("Index out of range");

    LinkedListItem *new_item = new LinkedListItem(data, priority);

    if (index == 0) {
        new_item->next = head;
        head = new_item;
        if (tail == nullptr)
            tail = new_item;
    } else {
        LinkedListItem *current = head;
        for (size_t i = 0; i < index - 1; i++) {
            current = current->next;
        }

        new_item->next = current->next;
        current->next = new_item;

        if (current == tail)
            tail = new_item;
    }

    size++;
}

void LinkedList::remove(size_t index) {
    if (index >= size)
        throw LinkedListException("Index out of range");

    LinkedListItem *item = &head;

    size_t item_index = index;
    while (item_index--) item = item->next;

    item->pop_back();

    size--;
}

void LinkedList::print() const {
    for (size_t idx = 0; idx < size; idx++)
        std::cout << get(idx) << "\t";
    std::cout << std::endl;
}
