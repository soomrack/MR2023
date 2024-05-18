#include <iostream>
#include <string>
using namespace std;

typedef int Data;

class Node {
public:
	Data data;
	Node* prev, * next;
public:
	Node(Data data) {
		this->data = data;
		this->prev = this->next = NULL;
	}
};

class DoubleLinkedList {
public:
	Node* head, * tail;

public:
	DoubleLinkedList() {
		head = tail = NULL;
	}

	~DoubleLinkedList() {
		while (head != NULL)
			pop_front();
	}

	Node* push_front(Data data); // добавление объекта в начало списка
	Node* push_back(Data data); // добавление объекта в конец списка
	void pop_front(); // удаление объекта с начала списка
	void pop_back(); // удаление объекта с конца списка
	Node* ret(int n); // возвращает указатель на объект списка с указанным индексом n
	Node* insert(int n, Data data); // вставляет элемент по указанному адресу n
	void erase(int n); // удаление элемента по указанному адресу n
};

Node* DoubleLinkedList::push_front(Data data) {
	Node* node = new Node(data);
	node->next = head;
	if (head != NULL)
		head->prev = node;
	if (tail == NULL)
		tail = node;
	head = node;
	return node;
}

Node* DoubleLinkedList::push_back(Data data) {
	Node* node = new Node(data);
	node->prev = tail;
	if (tail != NULL)
		tail->next = node;
	if (head == NULL)
		head = node;
	tail = node;
	return node;
}

void DoubleLinkedList::pop_front() {
	if (head == NULL) return;

	Node* node = head->next;
	if (node != NULL)
		node->prev = NULL;
	else
		tail = NULL;

	delete head;
	head = node;
}

void DoubleLinkedList::pop_back() {
	if (tail == NULL) return;

	Node* node = tail->prev;
	if (node != NULL)
		node->next = NULL;
	else
		head = NULL;

	delete tail;
	tail = node;
}

Node* DoubleLinkedList::ret(int n) {
	if (n < 0) return NULL;

	Node* node = head;
	int idx = 0;

	while (node && n != idx) {
		node = node->next;
		idx++;
	}
	if (idx == n) return node;
	else return NULL;
}

Node* DoubleLinkedList::insert(int n, Data data) {
	Node* right = ret(n);
	if (right == NULL)
		return push_back(data);

	Node* left = right->prev;
	if (left == NULL) 
		return push_front(data);

	Node* node = new Node(data);

	left->next = node;
	node->prev = left;
	node->next = right;
	right->prev = node;

	return node;
}

void DoubleLinkedList::erase(int n) {
	Node* node = ret(n);
	if (node == NULL)
		return;
	if (node->prev == NULL) {
		pop_front();
		return;
	}

	if (node->next == NULL) {
		pop_back();
		return;
	}

	Node* left = node->prev;
	Node* right = node->next;

	left->next = right;
	right->prev = left;

	delete node;
}

int main() 
{
	DoubleLinkedList list;
	list.push_front(11);
	list.push_front(7);
	list.push_front(1);
	list.push_front(3);

	Node* n = list.ret(0);
	cout << n << endl;

	list.insert(2, 6);
	Node* k = list.ret(2);
	cout << k << endl;

	list.erase(2);
	Node* l = list.ret(2);
	cout << l << endl;

	return 0;
}
