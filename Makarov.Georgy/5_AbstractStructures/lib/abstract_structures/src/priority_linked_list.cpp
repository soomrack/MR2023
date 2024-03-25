#include "priority_linked_list.h"

PriorityLinkedList::PriorityLinkedList(const PriorityLinkedList &list) {
    if (list.size == 0)
        return;

    for (size_t idx = 0; idx < list.size; idx++)
        push_back(list.get_item(idx), list.get_priority(idx));
}

PriorityLinkedList::PriorityLinkedList(PriorityLinkedList &&list) noexcept {
    head = list.head;
    list.head.next = nullptr;

    size = list.size;
    list.size = 0;
}

dtype PriorityLinkedList::get_item(size_t index) const {
    if (index >= size)
        throw PriorityLinkedListException("Index out of range");

    PriorityLinkedListItem *item = head.next;

    size_t item_index = index + 1;
    while (--item_index) item = item->next;

    return item->data;
}

uint8_t PriorityLinkedList::get_priority(size_t index) const {
    if (index >= size)
        throw PriorityLinkedListException("Index out of range");

    PriorityLinkedListItem *item = head.next;

    size_t item_index = index + 1;
    while (--item_index) item = item->next;

    return item->priority;
}

void PriorityLinkedList::push_back(const dtype &data, uint8_t priority) {
    tail->push_back(data, priority);
    tail = tail->next;

    size++;
}

void PriorityLinkedList::push_priority(const dtype &data, uint8_t priority) {
    PriorityLinkedListItem *current = &head;
    PriorityLinkedListItem *next_item = head.next;

    while (next_item != nullptr && next_item->priority <= priority) {
        current = next_item;
        next_item = next_item->next;
    }

    current->push_back(data, priority);
    size++;
}

void PriorityLinkedList::pop_back() {
    if (size == 0)
        return;

    PriorityLinkedListItem *item = &head;

    size_t item_index = size - 1;
    while (item_index--) item = item->next;

    item->pop_back();

    size--;
}

void PriorityLinkedList::insert(size_t index, const dtype &data, uint8_t priority) {
    if (index >= size)
        throw PriorityLinkedListException("Index out of range");

    PriorityLinkedListItem *item = &head;

    size_t item_index = index;
    while (item_index--) item = item->next;

    item->push_back(data, priority);

    size++;
}

void PriorityLinkedList::remove(size_t index) {
    if (index >= size)
        throw PriorityLinkedListException("Index out of range");

    PriorityLinkedListItem *item = &head;

    size_t item_index = index;
    while (item_index--) item = item->next;

    item->pop_back();

    size--;
}

void PriorityLinkedList::print() const {
    for (size_t idx = 0; idx < size; idx++)
        std::cout << get_item(idx) << "\t";
    std::cout << std::endl;
}