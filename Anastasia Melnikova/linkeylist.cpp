#include <iostream>
#include <string>
using namespace std;

typedef double MyData;

// Объявление класса Node
class Node {
public:
    MyData data;
    Node* next;
public:
    Node(MyData data) { // конструктор
        this->data = data;
        this->next = NULL;
    }
};

class List {
private:
    Node* head, * tail; // Указатель на первый и последний объект списка
public:
    List() {
        this->head = this->tail = NULL;
    }

    ~List() {
        while (head != NULL) pop_front();
    }

    void pop_front();  // Удаление первого объекта списка
    void push_back(MyData data);  // Добавление объекта в конец списка
    void push_front(MyData data); // Добавление объекта в начало списка
    void pop_back();  // Удаление объекта с конца списка
    Node* getAt(int k);  // Метод возвращает указатель на объект списка с индексом k
    void insert(int k, MyData data);  // Метод вставляет элемент по указанному индексу
    void erase(int k);  // Метод удаляет промежуточный элемент
};

void List::pop_front() { 
    if (head == NULL)
        cout << "Список пустой";
    if (head == tail) {
        delete tail;
        head = tail = NULL;
        return;
    }

    Node* node = head;
    head = node->next;
    delete node;
}

void List::push_back(MyData data) {
    Node* node = new Node(data);
    if (head == NULL) head = node;
    if (tail != NULL) tail->next = node;
    tail = node;
}

void List::push_front(MyData data) {
    Node* node = new Node(data);
    node->next = head;
    head = node;
    if (tail == NULL) tail = node;
}

void List::pop_back() {
    if (tail == NULL)
        cout << "Список пустой";
    if (head == tail) {
        delete tail;
        head = tail = NULL;
        return;
    }

    Node* node = head;
    for (; node->next != tail; node = node->next);
    node->next = NULL;
    delete tail;
    tail = node;
}

Node* List::getAt(int k) {
    if (k < 0) return NULL;

    Node* node = head;
    int n = 0;
    while (node && n != k && node->next) {
        node = node->next;
        n++;
    }
    if (n == k) return node;
    else return NULL;
}

void List::insert(int k, MyData data) {
    Node* left = getAt(k);
    if (left == NULL) return;

    Node* right = left->next;
    Node* node = new Node(data);

    left->next = node;
    node->next = right;
    if (right == NULL) tail = node;
}

void List::erase(int k) {
    if (k < 0) return;
    if (k == 0) {
        pop_front();
        return;
    }

    Node* left = getAt(k - 1);
    Node* node = left->next;
    if (node == NULL) return;
    Node* right = node->next;

    left->next = right;
    if (node == tail) tail = left;
    delete node;
}

int main() {
    List lst;
    lst.push_front(1);
    lst.push_back(3);
    Node* n = lst.getAt(0);
    cout << n << endl;

    lst.insert(1, 5);
    Node* g = lst.getAt(2);
    cout << g << endl;
    return 0;
}