
#include "TagDirViewModel.h"
#include <TagDirManager.h>
//#include <windows.h>
#include <Filesystem.h>

namespace Model{

class TagDirViewItem : public ITagViewItem
{
protected:
    TagDirViewModel* m_model;
    std::string m_name;
    ITagContainer* m_container;

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
    {
        m_container = m_model->m_manager->Container(location() + "/" + m_name);
    }

    virtual std::string Name() const
    {
        return m_name;
    }
    virtual const std::vector<std::string>& Tags() const
    {
        return m_container->Tags();
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
    m_children.clear();
    for (std::string& fName : fileNames) {
        if (fName == ".") {
            m_children.emplace_back(new DirDotViewItem(this));
        } else if (fName == "..") {
            m_children.emplace_back(new DirDotDotViewItem(this));
        } else if (Filesystem::is_directory(path + "/" + fName)) {
            m_children.emplace_back(new DirTagsViewItem(this, fName));
        } else {
            m_children.emplace_back(new TagDirViewItem(this, fName));
        }
    }
    if (Filesystem::is_directory(path + "/..")) {
    //    MessageBoxA(NULL, (path + "/..").c_str(), "fff", 64);
    }
    m_parent.reset(Filesystem::is_directory(path + "/..") ? new DirDotDotViewItem(this) : nullptr);
    m_listeners();
}

TagDirViewModel::TagDirViewModel(const std::string& basePath)
    : m_manager(new TagDirManager())
{
    m_manager->Initialize("SavedTags.txt");
    refresh(basePath);
}

TagDirViewModel::~TagDirViewModel()
{
    m_manager->Finalize();
}

void TagDirViewModel::setPath(const std::string& path)
{
    refresh(Filesystem::validate_path(path));
}

std::vector<ITagViewItem*> TagDirViewModel::Children() const
{
    std::vector<ITagViewItem*> children;
    children.reserve(m_children.size());
    for (auto& item : m_children) {
        children.push_back(item.get());
    }
    return children;
}

ITagViewItem* TagDirViewModel::Parent() const
{
    return m_parent.get();
}

void TagDirViewModel::addListener(std::function<void(void)> listener)
{
    m_listeners.Connect(listener);
}

}
