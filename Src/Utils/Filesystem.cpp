
#include "Filesystem.h"

#include <boost/filesystem.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <fstream>
#include <iostream>

namespace Filesystem{

bool is_directory(const std::string& path)
{
    return boost::filesystem::is_directory(boost::filesystem::path(path));
}

std::vector<std::string> list_directory(const std::string& path)
{
    std::vector<std::string> filenames;

    boost::filesystem::path dir(path + "/");
    boost::filesystem::directory_iterator itr(dir);
    boost::filesystem::directory_iterator itrEnd;
    for (; itr != itrEnd; ++itr) {
        filenames.push_back(itr->path().filename().string());
    }
    return filenames;
}

std::string validate_path(const std::string& path)
{
    std::string ret = path;
    boost::algorithm::replace_all(ret, "\\", "/");
    return ret;
}

bool read_file(const std::string& path, std::function<bool(const std::string& line)> functor)
{
    std::ifstream fs(path.c_str());
    if (!fs) {
        return false;
    }

    std::string line;
    while (std::getline(fs, line)) {
        if (!functor(line)) {
            return true;
        }
    }
    return true;
}

bool write_file(const std::string& path, std::function<bool(std::string&)> functor)
{
    std::ofstream fs(path.c_str());
    if (!fs) {
        return false;
    }

    bool hasNext = false;
    std::string line;
    while (functor(line)) {
        fs << line << "\n";
    }
    return true;
}

}
