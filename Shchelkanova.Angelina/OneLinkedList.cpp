#include <iostream>
using namespace std;

typedef int Data;

class Node {
public:
	Data data;
	Node* next;

public:
	Node(Data data) {
		this->data = data;
		this->next = NULL;
	}
};

class OneLinkedList {
public:
	Node* head, * tail;

public:
	OneLinkedList() { // конструктор объекта OneLinkedList
		this->head = this->tail = NULL;
	}

	~OneLinkedList() { // деструкор объекта OneLinkedList
		while (head != NULL) pop_front(); //удаление элементов односвязного списка
	}

	void pop_front(); // удаление первого объекта списка
	void pop_back(); // удаление последнего объекта списка
	void push_back(Data data); // добавление объекта в конец списка
	void push_front(Data data); // добавление объекта в начало списка
	Node* ret(int n); // возвращает указатель на объект списка с указанным индексом n
	void insert(int n, Data data); // вставляет элемент по указанному индексу n
	void erase(int n); // удаляет элемент по указанному индексу n
};

void OneLinkedList::pop_front() {
	if (head == NULL) return;
	if (head == tail) {
		delete tail;
		head = tail = NULL;
		return;
	}

	Node* node = head;
	head = node->next;
	delete node;
};

void OneLinkedList::pop_back() {
	if (tail == NULL) return;
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

void OneLinkedList::push_back(Data data) {
	Node* node = new Node(data);
	if (head == NULL) head = node;
	if (tail != NULL) tail->next = node;
	tail = node;
};

void OneLinkedList::push_front(Data data) {
	Node* node = new Node(data);
	node->next = head;
	head = node;
	if (head == NULL) head = node;
}

Node* OneLinkedList::ret(int n) {
	if (n < 0) return NULL;

	Node* node = head;
	int idx = 0;
	while (node && idx != n && node->next) {
		node = node->next;
		idx++;
	}

	if (idx == n) return node;
	else return NULL;
}

void OneLinkedList::insert(int n, Data data) {
	Node* left = ret(n);
	if (left == NULL) return;

	Node* right = left->next;
	Node* node = new Node(data);

	left->next = node;
	node->next = right;
	if (right == NULL) tail = node;
}

void OneLinkedList::erase(int n) {
	if (n < 0) return;
	if (n == 0) {
		pop_front();
		return;
	}

	Node* left = ret(n - 1);
	Node* node = left->next;
	if (node == NULL) return;
	Node* right = node->next;

	left->next = right;
	if (node == tail) tail = left;
	delete node;
}

int main() {
	OneLinkedList list;
	list.push_front(7);
	list.push_front(3);
	list.push_back(11);

	Node* n = list.ret(0);
	cout << n << endl;

	list.insert(2, 6);
	Node* k = list.ret(3);
	cout << k << endl;

	list.erase(3);
	Node* l = list.ret(3);
	cout << l << endl;

	return 0;
}
