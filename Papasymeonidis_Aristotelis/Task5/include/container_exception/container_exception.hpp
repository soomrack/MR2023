#include <string>

class ContainerException : public std::exception
{
private:
    std::string message;

public:
    ContainerException(std::string msg) : message(msg.c_str()) {}
    std::string what() { return message; }
};

extern ContainerException ERRONEOUS_MESSAGE;
extern ContainerException WRONG_CONDITIONS;
extern ContainerException NO_MEMORY_ALLOCATED;
