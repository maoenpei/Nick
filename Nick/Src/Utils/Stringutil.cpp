#include "Stringutil.h"

#include <boost/algorithm/string.hpp>

namespace Stringutil {

std::vector<std::string> split(const std::string& str, const std::string& delimitor)
{
    std::vector<std::string> results;
    boost::split(results, str, [&delimitor](const char& ch) {
        return 0 == strncmp(delimitor.c_str(), &ch, delimitor.length());
    });
    return results;
}

}