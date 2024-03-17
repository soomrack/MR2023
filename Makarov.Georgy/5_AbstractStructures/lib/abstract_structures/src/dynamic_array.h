#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <iostream>

typedef int dtype;

class DynamicArrayException : public std::exception {
private:
    std::string exception_msg;
public:
    explicit DynamicArrayException(std::string msg) : exception_msg(std::move(msg)) {}

    [[nodiscard]] const char *what() const noexcept override { return exception_msg.c_str(); }
};


class DynamicArray {
private:
    size_t size;
    size_t buffer_size;

    dtype *data;

public:
    DynamicArray(size_t size_, size_t buffer_size_);

    DynamicArray(const DynamicArray &array);

    DynamicArray(DynamicArray &&array) noexcept;

    ~DynamicArray();

    dtype get(size_t index);

    void set(size_t index, dtype item);

    [[nodiscard]] size_t get_size() const { return size; };

    [[nodiscard]] size_t get_buffer_size() const { return buffer_size; };

    [[nodiscard]] dtype *get_data() const { return data; };

    void resize(size_t new_size, size_t new_buffer_size);

    void print();
};

#endif //DYNAMIC_ARRAY_H
