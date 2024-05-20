#include <iostream>
using namespace std;

typedef int Data;

class queue_item {
public:
	int priority;
	queue_item* next;
	Data value;
public:
	queue_item(Data value) {
		this->value = value;
		this->next = NULL;
	}
};

class queue {
private:
	queue_item* head;
	queue_item* tail;
public:
	queue() : head(NULL), tail(NULL) {}
	~queue();

	void push(Data value);
	int pop();
	void print();
	bool empty();
};

class queue_exception : public std::exception {
public:
	queue_exception(const char* const message) : std::exception(message) {}
};

queue_exception empty("Your queue is empty");

bool queue::empty() {
	return head == NULL;
}

queue::~queue() {
	if (head == NULL) return;

	Data trash = 0;

	while (head != NULL)
		trash = pop();
}

void queue::push(Data value) {
	queue_item* node = new queue_item(value);
	if (empty() || value < head->value) {
		node->next = head;
		head = node;
	}
	else {
		queue_item* current = head;
		while (current->next != NULL && value >= current->next->value) {
			current = current->next;
		}
		node->next = current->next;
		current->next = node;
		if (node->next == NULL) {
			tail = node;
		}
	}
}

int queue::pop() {
	if (empty()) throw empty;

	Data pop_data = head->value;

	if (head == tail) {
		head = NULL;
		tail == NULL;
		return pop_data;
	}
	queue_item* node = head;
	pop_data = node->value;
	head = node->next;
	delete node;
	return pop_data;
}

void queue::print() {
	if (empty()) return;
	queue_item* node = head;
	while (node) {
		std::cout << node->value << " ";
		node = node->next;
	}
	std::cout << std::endl;
}

int main() {
	queue A;
	A.push(3);
	A.push(1);
	A.push(5);
	A.push(2);

	A.print();

	while (!A.empty()) {
		std::cout << A.pop() << std::endl;
	}

	return 0;
}
