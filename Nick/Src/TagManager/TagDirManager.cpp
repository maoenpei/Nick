
#include "TagDirManager.h"

#include <Filesystem.h>
#include <Stringutil.h>

#include <algorithm>

namespace Model {

class TagContainer : public ITagContainer
{
    std::vector<std::string> m_tags;
public:
    virtual void AddTag(const std::string& tag) override
    {
        auto itr = std::find(m_tags.begin(), m_tags.end(), tag);
        if (itr == m_tags.end()) {
            m_tags.push_back(tag);
        }
    }

    virtual void DelTag(const std::string& tag) override
    {
        auto itr = std::find(m_tags.begin(), m_tags.end(), tag);
        if (itr != m_tags.end()) {
            m_tags.erase(itr);
        }
    }

    virtual bool HasTag(const std::string& tag) override
    {
        auto itr = std::find(m_tags.begin(), m_tags.end(), tag);
        return itr != m_tags.end();
    }

    virtual const std::vector<std::string>& Tags() const override
    {
        return m_tags;
    }
};

TagDirManager::TagDirManager()
{}

void TagDirManager::Initialize(const std::string& path)
{
    m_path = path;
    m_TagsInfo.clear();
    Filesystem::read_file(path, [this](const std::string& line) {
        std::unique_ptr<TagContainer> item(new TagContainer());
        auto results = Stringutil::split(line, "|");
        if (results.size() <= 1) {
            return true;
        }
        for (size_t i = 1; i < results.size(); ++i) {
            item->AddTag(results[i]);
        }
        m_TagsInfo[results[0]] = std::move(item);
        return true;
    });
}

void TagDirManager::Finalize()
{
    auto itr = m_TagsInfo.begin();
    Filesystem::write_file(m_path, [this, &itr](std::string& line) {
        const std::vector<std::string>* pTags = nullptr;
        while (itr != m_TagsInfo.end()) {
            pTags = &itr->second->Tags();
            if (pTags->size() > 0) {
                break;
            }
            itr++;
        }

        if (itr == m_TagsInfo.end()) {
            return false;
        }

        line = itr->first;
        for (const auto& tag : *pTags) {
            line += "|";
            line += tag;
        }
        ++itr;
        return true;
    });
}

ITagContainer* TagDirManager::Container(const std::string& key)
{
    auto itr = m_TagsInfo.find(key);
    if (itr != m_TagsInfo.end()) {
        return itr->second.get();
    }

    std::unique_ptr<TagContainer> item(new TagContainer());
    m_TagsInfo[key] = std::move(item);
    return m_TagsInfo[key].get();
}

std::vector<std::string> TagDirManager::CommonTags(const std::vector<ITagContainer*>& containers)
{
    std::vector<std::string> tags;
    bool isFirst = true;
    for (auto container : containers) {
        const auto& sTags = container->Tags();
        if (!sTags.empty()) {
            if (isFirst) {
                isFirst = false;
                tags = sTags;
            } else {
                auto itr = std::remove_if(tags.begin(), tags.end(), [container](const std::string& tag) {
                    return !container->HasTag(tag);
                });
                tags.erase(itr, tags.end());
            }
        }
    }
    return tags;
}

}
