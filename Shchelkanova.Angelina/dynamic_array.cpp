#include <iostream>
using namespace std;

typedef int Data;

class dynamic_array {
private:
	Data* data;
	size_t size;
	size_t capacity;
public:
	dynamic_array();
	dynamic_array(size_t capacity);
	~dynamic_array();

	Data get_element(size_t index);
	void set_element(size_t index, Data value);
	void append(Data value);
	void resize(size_t new_capacity);
	int get_capacity();
	int get_size();

	void print();
};

void dynamic_array::print() {
	for (int i = 0; i <= size; i++)
		cout << data[i] << " ";
}

dynamic_array::dynamic_array() {
	capacity = 8;
	size = 0;
	data = new Data[capacity];
}

dynamic_array::dynamic_array(size_t capacity) {
	size = 0;
	data = new Data[capacity];
}

dynamic_array::~dynamic_array() {
	delete[] data;
}

Data dynamic_array::get_element(size_t index) {
	if (index >= 0 && index <= size)
		return data[index];
	else {
		cout << "Error: Index out of bounds";
		return 0;
	}
}

void dynamic_array::set_element(size_t index, Data value) {
	if (index >= 0 && index <= size)
		data[index] = value;
	else
		cout << "Error: Index out of bounds";
}

void dynamic_array::append(Data value) {
	if (size == capacity) {
		resize(capacity * 2);
	}
	data[size - 1] = value;
}

void dynamic_array::resize(size_t new_capacity) {
	Data* new_data = new Data[new_capacity];
	for (int index = 0; index < size; index++) {
		new_data[index] = data[index];
	}
	delete[] data;
	data = new_data;
	capacity = new_capacity;

}

int dynamic_array::get_size() {
	return size;
}

int dynamic_array::get_capacity() {
	return capacity;
}

int main() {
	dynamic_array arr(5);
	arr.set_element(2, 5);
	cout << arr.get_element(2) << endl;

	arr.append(22);
	arr.append(7);
	arr.append(130);

	arr.resize(8);

	arr.append(44);
	arr.append(24);

	arr.print();

	return 0;
}
