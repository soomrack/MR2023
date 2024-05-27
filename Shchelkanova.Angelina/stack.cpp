#include <iostream>
using namespace std;

typedef int Data;

class stack_item {
public:
	Data data;
	stack_item* next;
};

class stack {
private:
	stack_item* head;
public:
	stack() : head(NULL) {}
	~stack();
	Data peak();
	Data pop();

	bool empty();
	void push(Data value);
	void pop_all();
	void print();
};

class stack_exception : public std::exception {
public:
	stack_exception(const char* const message) : std::exception(message) {}
};

stack_exception empty("Your stack is empty");

bool stack::empty() {
	return head == NULL;
}

stack::~stack() {
	if (head == NULL) return;

	Data trash = 0;

	while (head != NULL) {
		trash = pop();
	}
}

void stack::push(Data value) {
	stack_item* node = new stack_item;
	node->data = value;
	node->next = NULL;

	if (head == NULL) head = node;
	else {
		node->next = head;
		head = node;
	}
}

Data stack::pop() {
	if (empty()) return 0;
	Data pop_data = head->data;

	head = head->next;

	return pop_data;
}

Data stack::peak() 
{
	return head->data;
}

void stack::pop_all() {
	if (empty()) return;

	Data node = 0;

	while (head != NULL) {
		node = pop();
		std::cout << node << " ";
	}

	std::cout << std::endl;
}

void stack::print() {
	if (empty()) {
		std::cout << "stack is empty" << std::endl;
	}
	stack_item* node = head;

	while (node != NULL) {
		std::cout << node->data << " ";
		node = node->next;
	}

	std::cout << std::endl;
}

int main() {
	stack A;
	A.push(3);
	A.push(2);
	A.push(47);
	A.push(4);

	A.print();
	A.pop();
	A.print();
	A.pop();
	A.print();

	return 0;
}
