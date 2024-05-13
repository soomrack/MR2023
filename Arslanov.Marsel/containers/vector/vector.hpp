#pragma once

#include <cstddef>
#include <cstring>
#include <iostream>

// TODO initializer_list
// TODO move (operator=)
template <typename T>
class Vector
{
private:
    size_t sz;
    size_t cap;
    T* arr;

    static constexpr int CAP_OFFSET{5};

public:
    Vector() : sz(0), cap(CAP_OFFSET), arr(new T[cap]) {}

    Vector(size_t size) : sz(size), cap(size + CAP_OFFSET), arr(new T[cap]) {
        memset(arr, 0, sz);
    }

    Vector(size_t size, T value)
        : sz(size), cap(size + CAP_OFFSET), arr(new T[cap]) {
        for (size_t idx = 0; idx < size; ++idx) {
            *(arr + idx) = value;
        }
    }

    ~Vector() { delete[] arr; }

    size_t size() { return sz; }

    size_t capacity() { return cap; }

    void reserve(size_t new_capacity) {
        if (new_capacity < cap) return;
        T* new_arr = reinterpret_cast<T*>(new int8_t[new_capacity * sizeof(T)]);
        // T *new_arr = new T[new_capacity];
        size_t idx = 0;
        // если при копировании объектов произошла ошибка (Конструктор
        // копирования T был не правильно написан), то мы вызываем деструкторы
        // всех объектов, которые скопировали до индекса idx, затем удаляем
        // выделенную память. Также нужно сделать везде, где есть копирование.
        // Также, все это можно сделать с помощью std::uninitialized_copy(arr,
        // arr+sz, new_arr)
        try {
            for (; idx < sz; ++idx) {
                // placement new (явный вызов конструктора по данному адресу).
                // Вызывает конструктор Типа Т по адресу (new_arr+idx) от
                // параметра arr[idx]. При присваивании будет UB, так как во
                // время присваивания удаляется то, что лежало там раньше, а
                // раньше у нас там не было ничего проинициализировано
                new (new_arr + idx) T(arr[idx]);
                // new_arr[idx] = arr[idx];
            }
        } catch (...) {
            for (size_t j = 0; j < idx; ++j) {
                (new_arr + idx)->~T();
            }
            delete[] reinterpret_cast<int8_t*>(new_arr);
            throw;
        }
        // delete вызывает деструкторы по всем адресам объектов, которые там
        // лежат (от 0 до capacity). Но проблема в том, когда sz < cap, то он
        // вызывает деструктор от объектов, которые еще даже не были
        // проинициализированы. Поэтому нужно явно вызвать деструктор для
        // каждого объекта до sz. Деструкторы вызываеются, только если это был
        // массив объектов
        // delete[] arr;
        for (size_t idx = 0; idx < sz; ++idx) {
            (arr + idx)->~T();
        }
        // Для того, чтобы не вызывать деструктор, так как int8_t это просто
        // число
        delete[] reinterpret_cast<int8_t*>(arr);
        arr = new_arr;
        cap = new_capacity;
    }

    void resize(size_t new_size, const T& value = T()) {
        if (new_size > cap) {
            reserve(new_size);
        }

        for (size_t idx = sz; idx < new_size; ++idx) {
            new (arr + idx) T(value);
        }
        if (new_size < sz) {
            sz = new_size;  // ! Bad impl
        }
    }

    void push_back(const T& value) {
        if (sz == cap) {
            reserve(sz * 2);
        }
        new (arr + sz) T(value);
        ++sz;
    }

    void pop_back() {
        --sz;
        (arr + sz)->~T();
    }

    T& at(size_t idx) {
        if (idx > sz) {
            throw std::out_of_range("Out of range");
        }
        return arr[idx];
    }

    T& operator[](size_t idx) { return arr[idx]; }

    //! works only with built-in types
    friend std::ostream& operator<<(std::ostream& os, const Vector<T>& vector) {
        for (size_t idx = 0; idx < vector.sz; ++idx) {
            os << vector.arr[idx] << " ";
        }
        os << std::endl;
        return os;
    }
};
