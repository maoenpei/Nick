#pragma once

#include <functional>
#include <string>
#include <vector>

namespace Filesystem
{
bool is_directory(const std::string& path);
std::vector<std::string> list_directory(const std::string& path);
std::string validate_path(const std::string& path);
bool read_file(const std::string& path, std::function<bool(const std::string& line)> functor);
bool write_file(const std::string& path, std::function<bool(std::string&)> functor);
}
