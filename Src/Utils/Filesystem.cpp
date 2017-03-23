
#include "Filesystem.h"

#include <boost/filesystem.hpp>
#include <boost/algorithm/string/replace.hpp>

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

}
