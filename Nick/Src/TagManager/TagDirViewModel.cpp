
#include "TagDirViewModel.h"
#include <TagDirManager.h>
#include <Filesystem.h>

namespace Model{

class TagDirViewItem : public ITagViewItem
{
protected:
    TagDirViewModel* m_model;
    std::string m_name;
    ITagContainer* m_container;
    bool m_selected;

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
        , m_selected(false)
    {
        m_container = m_model->m_manager->Container(location() + "/" + m_name);
    }

    bool isSelected()
    {
        return m_selected;
    }

    void Select(bool isSelected)
    {
        m_selected = isSelected;
    }

    ITagContainer* Container()
    {
        return m_container;
    }

    virtual std::string Name() const override
    {
        return m_name;
    }
    virtual const std::vector<std::string>& Tags() const override
    {
        return m_container->Tags();
    }

    virtual void Enter() override
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
        // boost doesn'r provide '.' / '..' folder
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

void TagDirViewModel::addItemListener(std::function<void(void)> listener)
{
    m_listeners.Connect(listener);
}

std::vector<ITagContainer*> TagDirViewModel::selectedContainers()
{
    std::vector<ITagContainer*> containers;
    for (auto& item : m_children) {
        if (item->isSelected()) {
            containers.push_back(item->Container());
        }
    }
    return containers;
}

void TagDirViewModel::Select(const std::vector<ITagViewItem*>& items)
{
    for (auto& item : m_children) {
        item->Select(false);
    }
    for (auto item : items) {
        static_cast<TagDirViewItem*>(item)->Select(true);
    }
}

std::vector<std::string> TagDirViewModel::CommonTags()
{
    return m_manager->CommonTags(selectedContainers());
}

void TagDirViewModel::AddTag(const std::string& tag)
{
    auto containers = selectedContainers();
    for (auto container : containers) {
        container->AddTag(tag);
    }
}

void TagDirViewModel::DelTag(const std::string& tag)
{
    auto containers = selectedContainers();
    for (auto container : containers) {
        container->DelTag(tag);
    }
}

}
