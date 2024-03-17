#include "doubly_linked_list.h"

DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList &list) {
    if (list.size == 0)
        return;

    for (size_t idx = 0; idx < list.size; idx++)
        push_back(list.get(idx));
}

DoublyLinkedList::DoublyLinkedList(DoublyLinkedList &&list) noexcept {
    head = list.head;
    list.head.next = nullptr;
    list.head.prev = nullptr;

    tail = list.tail;
    list.tail.next = nullptr;
    list.tail.prev = nullptr;

    size = list.size;
    list.size = 0;
}

dtype DoublyLinkedList::get(const size_t index) const {
    if (index >= size)
        throw DoublyLinkedListException("Index out of range");

    DoublyLinkedListItem *item = head.next;

    size_t item_index = index + 1;
    while (--item_index) item = item->next;

    return item->data;
}

void DoublyLinkedList::push_back(const dtype &data) {
    DoublyLinkedListItem *item_prev = tail.prev;

    tail.prev = new DoublyLinkedListItem{data, &tail, item_prev};
    item_prev->next = tail.prev;

    size++;
}

void DoublyLinkedList::pop_back() {
    if (size == 0) return;

    DoublyLinkedListItem *item_prev = tail.prev;

    item_prev->prev->next = &tail;
    tail.prev = item_prev->prev;
    delete item_prev;

    size--;
}


void DoublyLinkedList::insert(size_t index, const dtype &data) {
    if (index >= size)
        throw DoublyLinkedListException("Index out of range");

    DoublyLinkedListItem *item = head.next;

    size_t item_index = index + 1;
    while (--item_index) item = item->next;

    DoublyLinkedListItem *item_prev = item->prev;

    item_prev->next = new DoublyLinkedListItem{data, item, item_prev};
    item->prev = item_prev->next;

    size++;
}

void DoublyLinkedList::remove(size_t index) {
    if (index >= size)
        throw DoublyLinkedListException("Index out of range");

    DoublyLinkedListItem *item = head.next;

    size_t item_index = index + 1;
    while (--item_index) item = item->next;

    DoublyLinkedListItem *item_prev = item->prev;
    DoublyLinkedListItem *item_next = item->next;

    item_prev->next = item_next;
    item_next->prev = item_prev;
    delete item;

    size--;
}

void DoublyLinkedList::print() const {
    for (size_t idx = 0; idx < size; idx++)
        std::cout << get(idx) << "\t";
    std::cout << std::endl;
}