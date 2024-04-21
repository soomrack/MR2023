#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY

#include <iostream>

namespace CustomArrays {
template <typename T>
class DynamicArray {
public:
	DynamicArray();
	DynamicArray(const T[], const size_t);
	DynamicArray(const std::initializer_list<T>&, const size_t);
	DynamicArray(const std::initializer_list<T>&, const size_t, const size_t);
	DynamicArray(const DynamicArray<T>&);

	~DynamicArray();

	void push_back(T);
	void pop_back();
	void insert(T, size_t);
	void erase();
	void set_buffer(size_t);
	void print_array();

	T operator[](size_t);

private:
	T*	   data;
	size_t size;
	size_t buffer;
	size_t free;

	void resize();
};

template <typename T>
class LinkedList {
private:
	template <typename U>
	class Node {
	public:
		U	  data;
		Node* next;

		Node(U value) {
			data = value;
			next = nullptr;
		}
	};

	Node<T>* head;
	size_t	 size;

public:
	LinkedList();
	~LinkedList();

	size_t get_size();
	bool   is_empty();
	void   push_front(T);
	void   push_back(T);
	T	   pop_front();
	T	   pop_back();
	void   print_list();
	void   insert(T, size_t);
	void   clear();
};

template <typename T>
class DoubleLinkedList {
private:
	template <typename U>
	class Node {
	public:
		U	  data;
		Node* next;
		Node* prev;

		Node(U value) {
			data = value;
			next = nullptr;
			prev = nullptr;
		}
	};

	Node<T>* head;
	Node<T>* tail;
	size_t	 size;

public:
	DoubleLinkedList();
	~DoubleLinkedList();
	size_t get_size();
	bool   is_empty();
	void   push_front(T);
	void   push_back(T);
	T	   pop_front();
	T	   pop_back();
	void   print_list();
	void   insert(T, size_t);
	void   clear();

};

template <typename T>
class Stack {

	template <typename U>
	class Node {
	public:
		U	  data;
		Node* next;

		Node(U value) : data(value), next(nullptr) {}
	};

	Node<T>* head;
	size_t	 size;

public:
	Stack();
	~Stack();

	void   push(T);
	T pop();
	T top();
	size_t get_size();
	bool   is_empty();
	void   clear();
};


template <typename T>
class Queue {
    template <typename U>
    class Node {
    public:
        U data;
        Node* next;

        Node(U value) : data(value), next(nullptr) {}
    };

    Node<T>* front;
    Node<T>* end;
    size_t size;

public:
    Queue() : front(nullptr), end(nullptr), size(0) {}
    ~Queue() { clear(); }

    void enqueue(T);
    T dequeue();
    T front_element();
    size_t get_size();
    bool is_empty();
    void clear();
};

} // namespace CustomArrays

#endif
