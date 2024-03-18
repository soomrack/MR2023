#pragma once

#include <iostream>

#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY

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
	template <typename T>
	class Node {
	public:
		T	  data;
		Node* next;

		Node(T value) {
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
	template <typename T>
	class Node {
	public:
		T	  data;
		Node* next;
		Node* prev;

		Node(T value) {
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
class Stack : private LinkedList<T> {
public:
	void   push(T);
	T pop();
	T top();
	size_t get_size();
};


} // namespace CustomArrays

#endif
