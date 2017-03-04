#pragma once

#include <string>
#include <vector>

namespace Filesystem
{
    bool is_directory(const std::string& path);
    std::vector<std::string> list_directory(const std::string& path);
}
