#include <iostream>
#include <string>

using namespace std;

template<typename T>
class LinkedList
{
public:
	LinkedList();
	~LinkedList();

	void add_head(const T value);
	void add_tail(const T value);
	void delete_head();
	void delete_tail();

	T get_head_data();
	T get_tail_data();

	void pop_front();
	void clear();
	void push_back(T data);
	void push_front(T data);
	void pop_back();
	void insert(T value, int idx);
	void removeAt(const int idx);

	int GetSize() { return Size; };

	T& operator[](const int idx);

private:
	template<typename T>
	class Node
	{
	public:
		Node* pNext;
		Node* pPrev;
		T data;

		Node(T data = T(), Node* pNext = nullptr, Node* pPrev = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
			this->pPrev = pPrev;
		}
	};
	int Size;
	Node<T>* head, * tail;
};

template<typename T>
LinkedList<T>::LinkedList()
{
	Size = 0;
	head = nullptr;
	tail = nullptr;
}

template<typename T>
LinkedList<T>::~LinkedList()
{
	clear();
}

template<typename T>
void LinkedList<T>::add_head(const T value)
{
	if (head == nullptr) {
		head = new Node<T>(value);
		tail = head;
	}
	else {
		head->pPrev = new Node<T>(value, head);
		head = head->pPrev;
	}
	Size++;
}

template<typename T>
void LinkedList<T>::add_tail(const T value)
{
	if (tail == nullptr) {
		tail = new Node<T>(value);
		head = tail;
	}
	else {
		tail->pNext = new Node<T>(value, nullptr, tail);
		tail = tail->pNext;
	}
	Size++;
}

template<typename T>
void LinkedList<T>::delete_head()
{
	if (head == nullptr) {
		return;
	}
	Node<T>* tmp = head;
	head = head->pNext;
	if (head != nullptr) {
		head->pPrev = nullptr;
	}
	else {
		tail = nullptr;
	}
	delete tmp;
	Size--;
}

template<typename T>
void LinkedList<T>::delete_tail()
{
	if (tail == nullptr) {
		return;
	}
	Node<T>* tmp = tail;
	tail = tail->pPrev;
	if (tail != nullptr) {
		tail->pNext = nullptr;
	}
	else {
		head = nullptr;
	}
	delete tmp;
	Size--;
}

template<typename T>
T LinkedList<T>::get_head_data()
{
	if (head == nullptr) {
		throw invalid_argument("List is empty");
	}
	return head->data;
}

template<typename T>
T LinkedList<T>::get_tail_data()
{
	if (tail == nullptr) {
		throw invalid_argument("List is empty");
	}
	return tail->data;
}

template<typename T>
void LinkedList<T>::pop_front()
{
	Node<T>* tmp = head;
	head = head->pNext; if (head != nullptr) {
		head->pPrev = nullptr;
	}
	else {
		tail = nullptr;
	}
	delete tmp;
	Size--;
}

template<typename T>
void LinkedList<T>::clear()
{
	while (Size) {
		pop_front();
	}
}

template<typename T>
void LinkedList<T>::push_back(T data)
{
	if (head == nullptr) {
		head = new Node<T>(data);
		tail = head;
	}
	else
	{
		Node<T>* current = this->head;

		while (current->pNext != nullptr) {
			current = current->pNext;
		}

		current->pNext = new Node<T>(data, nullptr, current);
		tail = current->pNext;
	}
	Size++;
}

template<typename T>
void LinkedList<T>::push_front(T data)
{
	head = new Node<T>(data, head);
	if (head->pNext != nullptr) {
		head->pNext->pPrev = head;
	}
	else {
		tail = head;
	}
	Size++;
}

template<typename T>
void LinkedList<T>::pop_back()
{
	removeAt(Size--);
}

template<typename T>
void LinkedList<T>::insert(T value, int idx)
{
	if (idx == 0) {
		push_front(value);
	}
	else {
		Node<T>* previous = this->head;

		for (int i = 0; i < idx - 1; i++) {
			previous = previous->pNext;
		}

		Node<T>* new_node = new Node<T>(value, previous->pNext, previous);

		if (previous->pNext != nullptr) {
			previous->pNext->pPrev = new_node;
		}

		previous->pNext = new_node;

		Size++;
	}
}

template<typename T>
void LinkedList<T>::removeAt(const int idx)
{
	if (idx == 0) {
		pop_front();
	}
	else {
		Node<T>* previous = this->head;

		for (int i = 0; i < idx - 1; i++) {
			previous = previous->pNext;
		}

		Node<T>* toDelete = previous->pNext;

		if (toDelete->pNext != nullptr) {
			toDelete->pNext->pPrev = previous;
		}

		previous->pNext = toDelete->pNext;

		delete toDelete;

		Size--;
	}
}

template<typename T>
T& LinkedList<T>::operator[](const int idx)
{
	int counter = 0;
	Node<T>* current = this->head;
	while (current != nullptr) {

		if (counter == idx) {
			return current->data;
		}

		current = current->pNext;
		counter++;
	}
}

int main()
{
	LinkedList<int> lst;

	lst.add_head(5);
	lst.add_tail(31);
	lst.add_tail(17);

	cout << "Head data: " << lst.get_head_data() << endl;
	cout << "Tail data: " << lst.get_tail_data() << endl;

	lst.delete_head();
	lst.delete_tail();

	cout << "Head data: " << lst.get_head_data() << endl;
	cout << "Tail data: " << lst.get_tail_data() << endl;

	return 0;
}