#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace Model {

class ITagViewItem
{
public:
    virtual ~ITagViewItem(){}

    virtual std::string Name() const = 0;
    virtual const std::vector<std::string>& Tags() const = 0;

    virtual void Enter() = 0;
};

class ITagViewModel
{
public:
    virtual ~ITagViewModel(){}

    virtual std::string Path() const = 0;
    virtual void setPath(const std::string& path) = 0;

    virtual std::vector<ITagViewItem*> Children() const = 0;
    virtual ITagViewItem* Parent() const = 0;

    virtual void addItemListener(std::function<void(void)> listener) = 0;

    virtual void Select(const std::vector<ITagViewItem*>& items) = 0;
    virtual std::vector<std::string> CommonTags() = 0;
    virtual void AddTag(const std::string& tag) = 0;
    virtual void DelTag(const std::string& tag) = 0;
};

}
