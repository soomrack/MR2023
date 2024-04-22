#include <iostream>
#include <string.h>

using namespace std;

class Dynamic_array {
private:
	int* array_data;
	size_t size;
	size_t buffer;
	size_t size_allocated;

public:
	Dynamic_array();
	Dynamic_array(size_t lenght, size_t buffer_size);
	Dynamic_array(int* data);
	~Dynamic_array();

public:
	int get_element(int idx);
	void set_element(int idx, int element);
	void resize(int new_size);
	void append(int value);
	void print_array();
};


Dynamic_array::Dynamic_array()
{
	size = 0;
	buffer = 10;

	array_data = new int[buffer];
}


Dynamic_array::Dynamic_array(size_t lenght, size_t buffer_size)
{
	size = lenght;
	buffer = buffer_size;
	size_allocated = size + buffer_size;

	array_data = new int[(size_allocated)];
}

Dynamic_array::Dynamic_array(int* data)
{
	size = sizeof(data) / sizeof(int);
	buffer = 5;

	array_data = new int[(size + buffer)];

	memcpy(array_data, data, sizeof(int) * size);
}


Dynamic_array::~Dynamic_array()
{
	delete[] array_data;

	size = 0;
	buffer = 0;
}


int Dynamic_array::get_element(int idx)
{
	if (idx >= 0 && idx < size) {
		return array_data[idx];
	}
	else {
		std::cerr << "Error: Index out of bounds\n";
		return -1;
	}
}


void Dynamic_array::set_element(int idx, int element)
{
	if (idx >= 0 && idx < size) {
		array_data[idx] = element;
	}
	else {
		std::cerr << "Error: Index out of bounds\n";
	}
}


void Dynamic_array::resize(int new_size)
{
	if (new_size > (size_allocated)) {
		size_allocated = new_size + buffer;
		int* new_data = new int[size_allocated];
		memcpy(new_data, array_data, size * sizeof(int));

		size = new_size;

		delete[] array_data;
		array_data = new_data;

		return;
	}
	else
	{
		buffer -= new_size - size;
		size = new_size;
	}
}


void Dynamic_array::append(int value)
{
	resize(size + 1, buffer + 1);

	array_data[size - 1] = value;
}


void Dynamic_array::print_array()
{
	for (int printed_elements = 0; printed_elements < size; ++printed_elements) {
		cout << array_data[printed_elements] << " " << endl;
	}
}


int main()
{
	Dynamic_array array(1, 3);

	array.set_element(0, 13);
	array.print_array();

	//cout << array.get_element(3) << endl;

	//array.resize(2, 3);
	//array.set_element(1, 17);

	//array.append(98);

	array.print_array();

	return 0;
}