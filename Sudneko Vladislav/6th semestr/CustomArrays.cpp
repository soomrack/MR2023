#include "CustomArrays.h"

namespace CustomArrays {
template <typename T>
DynamicArray<T>::DynamicArray() {
	size = 0;
	free = 5;	// default array size
	buffer = 5; // default buffer
	data = new T[free];
}

template <typename T>
DynamicArray<T>::DynamicArray(const T array[], const size_t size)
	: size(size) {
	buffer = 5; // default buffer
	data = new T[size + buffer];
	free = buffer;
	memcpy(data, array, sizeof(T) * size);
}

template <typename T>
DynamicArray<T>::DynamicArray(const std::initializer_list<T>& array, const size_t size)
	: size(size) {
	buffer = 5; // default buffer
	data = new T[size + buffer];
	std::copy(array.begin(), array.end(), data);
}

template <typename T>
DynamicArray<T>::DynamicArray(const std::initializer_list<T>& array, const size_t size, const size_t buffer)
	: size(size), free(buffer), buffer(buffer) {
	data = new T[size + buffer];
	std::copy(array.begin(), array.end(), data);
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other) {
	size = other.size;
	free = other.free;
	data = new T[size + free];
	memcpy(data, other.data, sizeof(T) * size);
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
	delete[] data;
}

template <typename T>
void DynamicArray<T>::set_buffer(size_t buffer) {
	this->buffer = buffer;
}

template <typename T>
void DynamicArray<T>::resize() {
	T* new_data = new T[size + free + buffer];
	memcpy(new_data, data, sizeof(T) * size);
	delete[] data;
	data = new_data;
	free = free + buffer;
}

template <typename T>
void DynamicArray<T>::push_back(T element) {
	if (free == 0) {
		resize();
	}
	data[size] = element;
	size++;
	free--;
}

template <typename T>
void DynamicArray<T>::pop_back() {
	if (size == 0) {
		throw std::runtime_error("Error: DynamicArray is empty!");
	}
	data[size - 1] = 0;
	size--;
	free++;
}

template <typename T>
void DynamicArray<T>::insert(T element, size_t idx) {
	if (idx < 0 || idx >= size) {
		throw std::out_of_range("Error: Invalid index!");
	}

	if (free == 0) {
		resize();
	}

	memcpy(&data[idx + 1], &data[idx], sizeof(T) * (size - idx));
	data[idx] = element;
	size++;
	free--;
}

template <typename T>
void DynamicArray<T>::erase() {
	memset(data, 0, sizeof(T) * (size));
	free += size;
	size = 0;
}

template <typename T>
T DynamicArray<T>::operator[](size_t idx) {
	return data[idx];
}

template <typename T>
void DynamicArray<T>::print_array() {
	if (size == 0) {
		std::cout << "[]" << std::endl;
		return;
	}

	std::cout << "[";
	for (size_t idx = 0; idx < size; idx++) {
		std::cout << data[idx];
		(idx < size - 1) ? std::cout << ", " : std::cout << "]" << std::endl;
	}
}

template <typename T>
LinkedList<T>::LinkedList() {
	head = nullptr;
	size = 0;
}

template <typename T>
LinkedList<T>::~LinkedList() {
	clear();
}

template <typename T>
void LinkedList<T>::clear() {
	Node<T>* current = head;
	while (current != nullptr) {
		Node<T>* temp = current;
		current = current->next;
		delete temp;
	}
	head = nullptr;
	size = 0;
}

template <typename T>
size_t LinkedList<T>::get_size() {
	return size;
}

template <typename T>
bool LinkedList<T>::is_empty() {
	return size == 0;
}

template <typename T>
void LinkedList<T>::push_front(T value) {
	Node<T>* newNode = new Node<T>(value);
	newNode->next = head;
	head = newNode;
	size++;
}

template <typename T>
void LinkedList<T>::insert(T value, size_t index) {
	if (index < 0 || index > size) {
		throw std::out_of_range("Invalid index!");
	}

	if (index == 0) {
		push_front(value);
	}

	if (index == size) {
		push_back(value);
	}

	Node<T>* newNode = new Node<T>(value);
	Node<T>* current = head;

	for (size_t i = 0; i < index - 1; i++) {
		current = current->next;
	}

	newNode->next = current->next;
	current->next = newNode;
	size++;
}

template <typename T>
void LinkedList<T>::push_back(T value) {
	Node<T>* newNode = new Node<T>(value);

	if (is_empty()) {
		head = newNode;
	} else {
		Node<T>* current = head;
		while (current->next != nullptr) {
			current = current->next;
		}
		current->next = newNode;
	}

	size++;
}

template <typename T>
void LinkedList<T>::print_list() {
	Node<T>* current = head;
	while (current != nullptr) {
		std::cout << current->data << " -> ";
		current = current->next;
	}
	std::cout << "nullptr" << std::endl;
}

template <typename T>
T LinkedList<T>::pop_front() {
	if (is_empty()) {
		throw std::runtime_error("Error: LinkedList is empty!");
	}

	Node<T>* temp = head;
	T		 poppedValue = temp->data;
	head = head->next;
	delete temp;
	size--;

	return poppedValue;
}

template <typename T>
T LinkedList<T>::pop_back() {
	if (is_empty()) {
		throw std::runtime_error("Error: LinkedList is empty!");
	}

	if (size == 1) {
		return pop_front();
	}

	Node<T>* current = head;
	while (current->next->next != nullptr) {
		current = current->next;
	}

	Node<T>* temp = current->next;
	T		 poppedValue = temp->data;
	current->next = nullptr;
	delete temp;
	size--;

	return poppedValue;
}

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList() {
	head = nullptr;
	tail = nullptr;
	size = 0;
}

template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList() {
	clear();
}

template <typename T>
void DoubleLinkedList<T>::clear() {
	Node<T>* current = head;
	while (current != nullptr) {
		Node<T>* temp = current;
		current = current->next;
		delete temp;
	}

	head = nullptr;
	tail = nullptr;
	size = 0;
}

template <typename T>
size_t DoubleLinkedList<T>::get_size() {
	return size;
}

template <typename T>
bool DoubleLinkedList<T>::is_empty() {
	return size == 0;
}

template <typename T>
void DoubleLinkedList<T>::push_front(T value) {
	Node<T>* newNode = new Node<T>(value);

	if (is_empty()) {
		head = newNode;
		tail = newNode;
	} else {
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}

	size++;
}

template <typename T>
void DoubleLinkedList<T>::push_back(T value) {
	Node<T>* newNode = new Node<T>(value);

	if (is_empty()) {
		head = newNode;
		tail = newNode;
	} else {
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}

	size++;
}

template <typename T>
T DoubleLinkedList<T>::pop_front() {
	if (is_empty()) {
		throw std::runtime_error("Error: DoubleLinkedList is empty!");
	}

	Node<T>* temp = head;
	T		 poppedValue = temp->data;

	if (size == 1) {
		head = nullptr;
		tail = nullptr;
	} else {
		head = head->next;
		head->prev = nullptr;
	}

	delete temp;
	size--;

	return poppedValue;
}

template <typename T>
T DoubleLinkedList<T>::pop_back() {
	if (is_empty()) {
		throw std::runtime_error("Error: DoubleLinkedList is empty!");
	}

	Node<T>* temp = tail;
	T		 poppedValue = temp->data;

	if (size == 1) {
		head = nullptr;
		tail = nullptr;
	} else {
		tail = tail->prev;
		tail->next = nullptr;
	}

	delete temp;
	size--;

	return poppedValue;
}

template <typename T>
void DoubleLinkedList<T>::print_list() {
	Node<T>* current = head;
	while (current != nullptr) {
		std::cout << current->data << " -> ";
		current = current->next;
	}
	std::cout << "nullptr" << std::endl;
}

template <typename T>
void DoubleLinkedList<T>::insert(T value, size_t index) {
	if (index < 0 || index > size) {
		throw std::out_of_range("Error: Invalid index!");
	}

	if (index == 0) {
		push_front(value);
		return;
	}

	if (index == size) {
		push_back(value);
		return;
	}

	Node<T>* newNode = new Node<T>(value);
	Node<T>* current = head;

	for (size_t i = 0; i < index - 1; i++) {
		current = current->next;
	}

	newNode->prev = current;
	newNode->next = current->next;
	current->next = newNode;
	newNode->next->prev = newNode;

	size++;
}

template <typename T>
T Stack<T>::pop() {
	if (this->is_empty()) {
		throw std::runtime_error("Error: Stack is empty!");
	}
	return this->pop_front();
}

template <typename T>
void Stack<T>::push(T value) {
	this->push_front(value);
}

template <typename T>
T Stack<T>::top() {
	if (this->is_empty()) {
		throw std::runtime_error("Error: Stack is empty!");
	}
	return this->head->data;
}

template <typename T>
size_t Stack<T>::get_size() {
	return this->get_size();
}

} // namespace CustomArrays

int main() {

	CustomArrays::Stack<int>* stack = new CustomArrays::Stack<int>();

	return 0;
}
