#pragma once

#include <ITagViewModel.h>

#include <Connection.h>

#include <memory>
#include <string>
#include <vector>

namespace Model{

class TagDirManager;
class TagDirViewItem;
class TagDirViewModel : public ITagViewModel
{
    Control::MultiConnection<void(void)> m_listeners;
    std::string m_path;
    std::vector<std::shared_ptr<TagDirViewItem>> m_children;
    std::shared_ptr<TagDirViewItem> m_parent;
    friend class TagDirViewItem;
    std::unique_ptr<TagDirManager> m_manager;

    void refresh(const std::string& path);

public:
    TagDirViewModel(const std::string& basePath);
    virtual ~TagDirViewModel();

    virtual std::string Path() const override
    {
        return m_path;
    }
    virtual void setPath(const std::string& path) override;
    virtual std::vector<ITagViewItem*> Children() const override;
    virtual ITagViewItem* Parent() const override;

    virtual void addListener(std::function<void(void)> listener) override;
};

}