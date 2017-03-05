#pragma once

#include <ITagViewModel.h>

#include <Connection.h>

#include <string>
#include <vector>

namespace Model{

    class TagDirViewItem;
    class TagDirViewModel : public ITagViewModel
    {
        Control::MultiConnection<void(void)> m_listeners;
        std::string m_path;
        std::vector<std::shared_ptr<TagDirViewItem>> m_items;
        friend class TagDirViewItem;

        void refresh(const std::string& path);

    public:
        TagDirViewModel(const std::string& basePath);

        virtual std::string Path() const override
        {
            return m_path;
        }
        virtual void setPath(const std::string& path) override;
        virtual std::vector<ITagViewItem*> Items() const override;

        virtual void addListener(std::function<void(void)> listener) override;
    };
}