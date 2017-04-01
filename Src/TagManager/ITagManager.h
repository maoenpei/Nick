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

    virtual const std::vector<std::string>& Tags() const = 0;
};

class ITagManager
{
public:
    virtual ~ITagManager() {};

    ITagContainer* Container(const std::string& key);
};

}
