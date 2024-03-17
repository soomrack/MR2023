//
// Created by simeonidi03 on 17.03.24.
//

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP
#include <iostream>

template<typename T>
class node {
public:
    T data;
    node<T>* next;
    node(const T& data) : data(data), next(nullptr) {}
};

template<typename T>
class linked_list {
private:
    node<T>* head;
public:
    linked_list() : head(nullptr) {}
    ~linked_list();

    void push_head(const T& value);

    // Метод для вывода содержимого списка
    void print() const {
        node<T>* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    linked_list<int> list;

    // Добавляем элементы в начало списка
    list.push_front(3);
    list.push_front(5);
    list.push_front(7);

    // Выводим содержимое списка
    list.print();

    return 0;
}

#endif //LINKED_LIST_HPP
