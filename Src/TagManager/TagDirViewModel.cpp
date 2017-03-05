
#include "TagDirViewModel.h"

#include <Filesystem.h>

namespace Model{

class TagDirViewItem : public ITagViewItem
{
protected:
    TagDirViewModel* m_model;
    std::string m_name;

    std::string location()
    {
        return m_model->m_path;
    }
    void enter(const std::string& path)
    {
        m_model->refresh(path);
    }
    void open(const std::string& path)
    {
    }

public:
    TagDirViewItem(TagDirViewModel* model, const std::string& name)
        : m_model(model)
        , m_name(name)
    {}

    virtual std::string Name() const
    {
        return m_name;
    }
    virtual std::vector<std::string> Tags() const
    {
        return std::vector<std::string>();
    }

    virtual void Enter()
    {
        open(location() + "/" + m_name);
    }
};

class DirTagsViewItem : public TagDirViewItem
{
public:
    DirTagsViewItem(TagDirViewModel* model, const std::string& name)
        : TagDirViewItem(model, name)
    {}

    virtual void Enter()
    {
        enter(location() + "/" + m_name);
    }
};

class DirDotViewItem : public TagDirViewItem
{
public:
    DirDotViewItem(TagDirViewModel* model)
        : TagDirViewItem(model, ".")
    {}

    virtual void Enter()
    {
        enter(location());
    }
};

class DirDotDotViewItem : public TagDirViewItem
{
public:
    DirDotDotViewItem(TagDirViewModel* model)
        : TagDirViewItem(model, "..")
    {}

    virtual void Enter()
    {
        std::string path = location();
        size_t pos = path.find_last_of("/");
        enter(path.substr(0, pos));
    }
};

void TagDirViewModel::refresh(const std::string& path)
{
    if (!Filesystem::is_directory(path)) {
        return;
    }

    m_path = path;
    std::vector<std::string> fileNames = Filesystem::list_directory(path);
    m_items.clear();
    for (std::string& fName : fileNames) {
        if (fName == ".") {
            m_items.emplace_back(new DirDotViewItem(this));
        } else if (fName == "..") {
            m_items.emplace_back(new DirDotDotViewItem(this));
        } else if (Filesystem::is_directory(path + "/" + fName)) {
            m_items.emplace_back(new DirTagsViewItem(this, fName));
        } else {
            m_items.emplace_back(new TagDirViewItem(this, fName));
        }
    }
    m_listeners();
}

TagDirViewModel::TagDirViewModel(const std::string& basePath)
{
    refresh(basePath);
}

void TagDirViewModel::setPath(const std::string& path)
{
    refresh(path);
}

std::vector<ITagViewItem*> TagDirViewModel::Items() const
{
    std::vector<ITagViewItem*> items;
    items.reserve(m_items.size());
    for (auto& item : m_items) {
        items.push_back(item.get());
    }
    return items;
}

void TagDirViewModel::addListener(std::function<void(void)> listener)
{
    m_listeners.Connect(listener);
}

}
