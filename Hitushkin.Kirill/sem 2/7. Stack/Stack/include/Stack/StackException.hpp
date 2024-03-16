#ifndef DYNAMIC_ARRAY_EXCEPTION_HPP
#define DYNAMIC_ARRAY_EXCEPTION_HPP


#include <stdexcept>
#include <iostream>


namespace stack {

class StackException: public std::runtime_error
{

public:
    StackException(const char *file, int line, const std::string &arg) : std::runtime_error(arg)
    {
        msg_ = std::string(file) + ":" + std::to_string(line) + ": " + arg;
    }

    const char *what() const noexcept override 
    {
        return msg_.c_str();
    }

private:

    std::string msg_;

};

}



#endif