#include <ctime>
#include <iostream>
using namespace std;

template<class T>
class List
{
	class Node
	{
	public:
		T data;
		Node* next;

		Node(T t = T(), Node* n = nullptr);
	};
	Node* head;
	int size;

public:
	List();
	~List();
	void pushBack(T value);
	void pushFront(T value);
	int getSize() const;
	T& operator[] (int);
	void popFront();
	void popBack();
	void clear();
	void insert(T value, int index);
	void removeAt(int index);
};

template<class T>
void show(List<T>&);

template <class T>
List<T>::Node::Node(T t, Node* n)
{
	data = t;
	next = n;
}

template<class T>
List<T>::List()
{
	size = 0;
	head = nullptr;
}

template<class T>
List<T>::~List()
{
	clear();
}

template<class T>
void List<T>::pushBack(T value)
{
	if (head == nullptr)
		head = new Node(value);
	else
	{
		for (Node* current = head; ; current = current->next)
			if (current->next == nullptr)
			{
				current->next = new Node(value);
				break;
			}
	}
	size++;
}

template<class T>
void List<T>::pushFront(T value)
{
	head = new Node(value, head);
	size++;
}

template<class T>
int List<T>::getSize() const
{
	return size;
}

template<class T>
T& List<T>::operator[](int index)
{
	if (index > size - 1 || index < 0)
	{
		string message = "Недопустимый индекс ";
		message.append(to_string(index));
		throw out_of_range(message);
	}
	Node* current = head;
	for (int i = 0; i < index; i++)
		current = current->next;
	return current->data;
}

template<class T>
void List<T>::popFront()
{
	if (size <= 0) return;
	Node* temp = head;
	head = head->next;
	delete temp;
	size--;
}

template<class T>
void List<T>::popBack()
{
	removeAt(size - 1);
}

template<class T>
void List<T>::clear()
{
	while (size) popFront();
}

template<class T>
void List<T>::insert(T value, int index)
{
	if (index > size || index < 0)
	{
		string message = "Недопустимый индекс ";
		message.append(to_string(index));
		throw out_of_range(message);
	}
	if (index == 0) pushFront(value);
	else
	{
		Node* previous = head;
		for (int i = 0; i < index - 1; i++)
			previous = previous->next;
		previous->next = new Node(value, previous->next);
		size++;
	}
}

template<class T>
void List<T>::removeAt(int index)
{
	if (index > size - 1 || index < 0)
	{
		string message = "Недопустимый индекс ";
		message.append(to_string(index));
		throw out_of_range(message);
	}
	if (index == 0) popFront();
	else
	{
		Node* previous = head;
		for (int i = 0; i < index - 1; i++)
			previous = previous->next;
		Node* temp = previous->next;
		previous->next = temp->next;
		delete temp;
		size--;
	}
}

template<class T>
void show(List<T>& list)
{
	cout << "size = " << list.getSize() << endl;
	for (int i = 0; i < list.getSize(); i++) cout << list[i] << "  ";
	cout << endl;
}

int main()
{
	setlocale(0, "");
	List<int> list;
	for (int i = 0; i < 5; i++) list.pushBack(i);
	show(list);
	list.popBack();
	list.popFront();
	list[1] = 777;
	show(list);
	system("pause");
}