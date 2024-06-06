#ifndef PARSER_HPP_INCLUDED
#define PARSER_HPP_INCLUDED

#include <string>

#include "description.hpp"

class parser
{
public:
    parser() = delete;
    static std::vector<desc::sptr> parse(const std::string &file);
    static void dump(std::vector<desc::sptr> &flight, const std::string &file);
};

#endif // PARSER_HPP_INCLUDED
