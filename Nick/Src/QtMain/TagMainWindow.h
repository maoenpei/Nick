#pragma once

#include <memory>

#include <QMainWindow>
#include <MainWindow.ui.h>

namespace Model {
    class ITagViewModel;
}

namespace View{

class TagMainWindow : public QMainWindow
{
    Ui::MainWindow* m_UI;
    std::unique_ptr<Model::ITagViewModel> m_spViewModel;
public:
    TagMainWindow();

    void Initialize(Model::ITagViewModel* viewModel);

private:
    void UpdateView();
    void UpdateTags();
    void SyncSelection();
};

}
