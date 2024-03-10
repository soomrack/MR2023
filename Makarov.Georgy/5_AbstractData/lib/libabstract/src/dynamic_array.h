#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <iostream>

class DynamicArrayException : public std::exception {
private:
    std::string exception_msg;
public:
    explicit DynamicArrayException(std::string msg) : exception_msg(std::move(msg)) {}

    const char *what() const noexcept override { return exception_msg.c_str(); }
};


class DynamicArray {
};

#endif //DYNAMIC_ARRAY_HPP
