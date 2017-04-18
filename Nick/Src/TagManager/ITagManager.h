#pragma once

#include <map>
#include <string>
#include <vector>

namespace Model {

class ITagContainer
{
public:
    virtual ~ITagContainer() {}

    virtual void AddTag(const std::string& tag) = 0;
    virtual void DelTag(const std::string& tag) = 0;
    virtual bool HasTag(const std::string& tag) = 0;

    virtual const std::vector<std::string>& Tags() const = 0;
};

class ITagManager
{
public:
    virtual ~ITagManager() {};

    virtual ITagContainer* Container(const std::string& key) = 0;
    virtual std::vector<std::string> CommonTags(const std::vector<ITagContainer*>& containers) = 0;
};

}
