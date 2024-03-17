#include "linked_list.h"

LinkedList::LinkedList(const LinkedList &list) {
    if (list.size == 0)
        throw LinkedListException("Cannot copy empty list"); // or return;

    LinkedListItem *current = list.items.next;
    LinkedListItem *previous = &items;

    while (current != nullptr) {
        previous->push_back(current->data);

        current = current->next;
        previous = previous->next;

        size++;
    }
}

LinkedList::LinkedList(LinkedList &&list) noexcept {
    items = list.items;
    list.items.next = nullptr;

    size = list.size;
    list.size = 0;
}


dtype LinkedList::get(const size_t index) const {
    if (index >= size)
        throw LinkedListException("Index out of range");

    LinkedListItem *item = items.next;

    size_t item_index = index + 1;
    while (--item_index) item = item->next;

    return item->data;
}


void LinkedList::push_back(const dtype &data) {
    LinkedListItem *item = &items;

    size_t item_index = size;
    while (item_index--) item = item->next;

    item->push_back(data);

    size++;
}


void LinkedList::pop_back() {
    if (size == 0)
        throw LinkedListException("Cannot pop back empty list");  // or return;

    LinkedListItem *item = &items;

    size_t item_index = size - 1;
    while (item_index--) item = item->next;

    item->pop_back();

    size--;
}


void LinkedList::insert(size_t index, const dtype &data) {
    if (index >= size)
        throw LinkedListException("Index out of range");

    LinkedListItem *item = &items;

    size_t item_index = index;
    while (item_index--) item = item->next;

    item->push_back(data);

    size++;
}

void LinkedList::remove(size_t index) {
    if (index >= size)
        throw LinkedListException("Index out of range");

    LinkedListItem *item = &items;

    size_t item_index = index;
    while (item_index--) item = item->next;

    item->pop_back();

    size--;
}

void LinkedList::print() const {
    for (size_t idx = 0; idx < size; ++idx)
        std::cout << get(idx) << "\t";
    std::cout << std::endl;
}