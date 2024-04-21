#include <iostream>
#include <string>

using namespace std;

template<typename T>
class LinkedList
{
public:
	LinkedList();
	~LinkedList();

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
		T data;

		Node(T data = T(), Node* pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}
	};
	int Size;
	Node<T> *head;
};


template<typename T>
LinkedList<T>::LinkedList()
{
	Size = 0;
	head = nullptr;
}


template<typename T>
LinkedList<T>::~LinkedList()
{
	clear();
}


template<typename T>
void LinkedList<T>::pop_front()
{

	Node<T> *tmp = head;

	head = head->pNext;

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
	}
	else
	{
		Node<T>* current = this-> head;

		while(current -> pNext !=nullptr) {
			current = current->pNext;
		}

		current->pNext = new Node<T>(data);
	}

	Size++;
}


template<typename T>
void LinkedList<T>::push_front(T data)
{
	head = new Node<T>(data, head);
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

		Node<T>* new_node = new Node<T>(value, previous->pNext);

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

	lst.push_back(5);
	lst.push_back(31);
	lst.push_back(17);

	for (int i = 0; i < lst.GetSize(); i++) {
		cout << lst[i] << endl;
	}


	return 0;
 }
