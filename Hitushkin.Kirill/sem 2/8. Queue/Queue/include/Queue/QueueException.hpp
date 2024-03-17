#ifndef QUEUE_EXCEPTION_HPP
#define QUEUE_EXCEPTION_HPP


#include <stdexcept>
#include <iostream>


namespace queue {

class QueueException: public std::runtime_error
{

public:
    QueueException(const char *file, int line, const std::string &arg) : std::runtime_error(arg)
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