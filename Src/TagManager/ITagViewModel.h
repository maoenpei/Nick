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
    virtual std::vector<std::string> Tags() const = 0;

    virtual void Enter() = 0;
};

class ITagViewModel
{
public:
    virtual ~ITagViewModel(){}

    virtual std::string Path() const = 0;
    virtual void setPath(const std::string& path) = 0;

    virtual std::vector<ITagViewItem*> Items() const = 0;

    virtual void addListener(std::function<void(void)> listener) = 0;
};

}
