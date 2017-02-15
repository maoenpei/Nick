#pragma once

#include <map>
#include <string>
#include <vector>

class TagManager
{
public:
    TagManager();
    virtual ~TagManager();

    using KeyType = std::string;
    using TagType = std::string;
    using TagsArray = std::vector<TagType>;

    TagsArray Tags(const KeyType& key);
    void SetTags(const KeyType& key, const TagsArray& arr);
    void ClearTags(const KeyType& key);

    void AddTag(const KeyType& key, const TagType& tag);
    void DelTag(const KeyType& key, const TagType& tag);

private:
    using TagsMap = std::map<KeyType, TagsArray>;
    TagsMap m_TagsInfo; 
};
