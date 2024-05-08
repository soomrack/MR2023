#include <iostream>
#include <string>
using namespace std;

typedef double MyData;

class Node {
public:
    MyData data;
    Node* prev, * next;

public:
    Node(MyData data) {
        this->data = data;
        this->prev = this->next = NULL;
    }
};

class List {
public:
    Node* head, * tail;

public:
    List() {
        this->head = this->tail = NULL;
    }
    ~List() {
        while (head != NULL)
            pop_front();
    }

    Node* push_front(MyData data);  // добавления элементов в начало двусвязного списка
    Node* push_back(MyData data);  // добавления элементов в конец двусвязного списка
    void pop_front();  // удаление элементов в начале двусвязного списка:
    void pop_back();   // удаление элементов в конце двусвязного списка:
    Node* getAt(int index);  // метод для доступа к произвольному элементу двусвязного списка
    Node* operator [] (int index);  // оператор для доступа к произвольному элементу двусвязного списка
    Node* insert(int index, MyData data);  // метод для вставки нового элемента в связный список с индексом index
    void erase(int index);  // удаление произвольного элемента с индексом index из связного списка
};

Node* List::push_front(MyData data) {
    Node* ptr = new Node(data);

    ptr->next = head;
    if (head != NULL)
        head->prev = ptr;
    if (tail == NULL)
        tail = ptr;
    head = ptr;

    return ptr;
}


Node* List::push_back(MyData data) {
    Node* ptr = new Node(data);

    ptr->prev = tail;
    if (tail != NULL)
        tail->next = ptr;
    if (head == NULL)
        head = ptr;
    tail = ptr;

    return ptr;
}

void List::pop_front() {
    if (head == NULL) return;

    Node* ptr = head->next;
    if (ptr != NULL)
        ptr->prev = NULL;
    else
        tail = NULL;

    delete head;
    head = ptr;
}


void List::pop_back() {
    if (tail == NULL) return;

    Node* ptr = tail->prev;
    if (ptr != NULL)
        ptr->next = NULL;
    else
        head = NULL;

    delete tail;
    tail = ptr;
}

Node* List::getAt(int index) {
    Node* ptr = head;
    int n = 0;

    while (n != index) {
        if (ptr == NULL)
            return ptr;
        ptr = ptr->next;
        n++;
    }

    return ptr;
}

Node* List::operator [] (int index) {
    return getAt(index);
}

Node* List::insert(int index, MyData data) {
    Node* right = getAt(index);
    if (right == NULL)
        return push_back(data);

    Node* left = right->prev;
    if (left == NULL)
        return push_front(data);

    Node* ptr = new Node(data);

    ptr->prev = left;
    ptr->next = right;
    left->next = ptr;
    right->prev = ptr;

    return ptr;
}

void List::erase(int index) {
    Node* ptr = getAt(index);
    if (ptr == NULL)
        return;

    if (ptr->prev == NULL) {
        pop_front();
        return;
    }

    if (ptr->next == NULL) {
        pop_back();
        return;
    }

    Node* left = ptr->prev;
    Node* right = ptr->next;
    left->next = right;
    right->prev = left;

    delete ptr;
}

int main()
{
    List lst;
    lst.push_back(1.0);
    lst.push_back(2.0);
    lst.push_back(3.0);
    lst.push_back(4.0);

    for (Node* ptr = lst.head; ptr != NULL; ptr = ptr->next)
        cout << ptr->data << " ";
    cout << endl;

    cout << lst[1]->data << endl;
    lst.insert(2, -5.0);
    return 0;
}
