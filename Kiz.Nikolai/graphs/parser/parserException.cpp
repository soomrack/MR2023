#include "exception"
#include "string"


class ParserException : public std::exception {
private:
    std::string exception_msg;
public:
    explicit ParserException(std::string msg) : exception_msg(std::move(msg)) {}

    [[nodiscard]] const char* what() const noexcept override { return exception_msg.c_str(); }
};


