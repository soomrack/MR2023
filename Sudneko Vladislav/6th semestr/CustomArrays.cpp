#include "CustomArrays.h"

namespace CustomArrays
{
	template <typename T>
	DynamicArray<T>::DynamicArray()
	{
		_size = 0;
		_buffer = 50;
		_data = new T[_buffer];
	}

	template <typename T>
	DynamicArray<T>::DynamicArray(const T array[], const size_t size)
		: _size(size), _buffer(size)
	{
		_data = new T[_size * 2];
		memcpy(_data, array, sizeof(T) * _size);
	}

	template <typename T>
	DynamicArray<T>::DynamicArray(const std::initializer_list<T>& array, const size_t size)
		: _size(size), _buffer(size)
	{
		_data = new T[_size * 2];
		std::copy(array.begin(), array.end(), _data);
	}

	template <typename T>
	DynamicArray<T>::DynamicArray(const DynamicArray<T> &other)
	{
		_size = other._size;
		_buffer = other._buffer;
		_data = new T[_size + _buffer];
		memcpy(_data, other._data, sizeof(T) * _size);
	}

	template <typename T>
	DynamicArray<T>::~DynamicArray()
	{
		delete[] _data;
	}

	template <typename T>
	void DynamicArray<T>::resize()
	{
		T* new_data = new T[(_size + _buffer) * 2];
		memcpy(new_data, _data, sizeof(T) * _size);
		delete[] _data;
		_data = new_data;
		_buffer = _size + 2 * _buffer;
	}

	template <typename T>
	void DynamicArray<T>::push_back(T element)
	{
		if (_buffer == 0)
		{
			resize();
		}
		_data[_size] = element;
		_size++;
		_buffer--;
	}

	template <typename T>
	void DynamicArray<T>::pop_back()
	{
		if (_size == 0)
		{
			return;
		}
		_data[_size - 1] = 0;
		_size--;
		_buffer++;
	}

	template <typename T>
	void DynamicArray<T>::insert(T element, size_t idx)
	{
		if (idx < 0 || idx >= _size)
		{
			return;
		}

		if (_buffer == 0)
		{
			resize();
		}

		memcpy(&_data[idx + 1], &_data[idx], sizeof(T) * (_size - idx));
		_data[idx] = element;
		_size++;
		_buffer--;
	}

	template <typename T>
	void DynamicArray<T>::erase()
	{
		memset(_data, 0, sizeof(T) * (_size));
		_buffer += _size;
		_size = 0;
	}

	template <typename T>
	T DynamicArray<T>::operator[](size_t idx)
	{
		return _data[idx];
	}

	template <typename U>
	std::ostream& operator<<(std::ostream& stream, DynamicArray<U>& array)
	{
		if (array._size == 0)
		{
			stream << "[]" << std::endl;
			return stream;
		}

		stream << "[";
		for (size_t idx = 0; idx < array._size; idx++)
		{
			stream << array[idx];
			(idx < array._size - 1) ? stream << ", "
									: stream << "]" << std::endl;
		}

		return stream;
	}

} // namespace CustomArrays

int main()
{

	CustomArrays::DynamicArray<int> array({ 1, 2, 3 }, 3);

	CustomArrays::DynamicArray<int> array2 = array;

	std::cout << array2;

	return 0;
}
