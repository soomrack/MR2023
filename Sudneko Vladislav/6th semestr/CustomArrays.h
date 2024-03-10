#pragma once

#include <iostream>

#ifndef DYNAMIC_ARRAY
	#define DYNAMIC_ARRAY

namespace CustomArrays
{
	template <typename T>
	class DynamicArray
	{
	public:
		DynamicArray();
		DynamicArray(const T[], const size_t);
		DynamicArray(const std::initializer_list<T>&, const size_t);
		DynamicArray(const DynamicArray<T>&);

		~DynamicArray();

		void push_back(T);
		void pop_back();
		void insert(T, size_t);
		void erase();

		T operator[](size_t);

		template<typename U>
		friend std::ostream& operator<<(std::ostream&, DynamicArray<U>&);

	private:
		T*	   _data;
		size_t _size;
		size_t _buffer;

		void resize();
	};

} // namespace CustomArrays

#endif
