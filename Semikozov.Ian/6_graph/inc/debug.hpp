#ifndef DEBUG_HPP_INCLUDED
#define DEBUG_HPP_INCLUDED

#include <boost/format.hpp>
#include <map>

namespace debug
{

static boost::format fmt{ "%1% %2%" };
enum status_t
{
    info = 0,
    err,
    warn
};

static std::map<status_t, const char *> sb{ { info, "[info]:" },
                                            { err, "[err]:" },
                                            { warn, "[warn]:" } };
}; // namespace debug

#endif // DEBUG_HPP_INCLUDED
