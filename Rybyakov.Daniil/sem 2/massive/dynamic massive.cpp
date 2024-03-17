#include <iostream>

class DynamicArray {
private:
	int* data;
	int size;
	int volume;

public:
	DynamicArray();
	DynamicArray(int capacity);
	~DynamicArray();

	int get(int index);
	void set(int index, int value);
	void add(int value);

	void resize(int new_size);
};
