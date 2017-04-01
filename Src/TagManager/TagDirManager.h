#pragma once

#include <ITagManager.h>

#include <memory>

namespace Model {

class TagContainer;
class TagDirManager : public ITagManager
{
    std::map<std::string, std::unique_ptr<TagContainer>> m_TagsInfo;
    std::string m_path;
public:
    TagDirManager();

    void Initialize(const std::string& path);
    void Finalize();

    ITagContainer* Container(const std::string& key);
};

}
