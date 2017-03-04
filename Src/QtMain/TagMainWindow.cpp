

#include "TagMainWindow.h"

#include <ITagViewModel.h>
#include <windows.h>

namespace View {

TagMainWindow::TagMainWindow()
    : m_UI(new Ui::MainWindow())
{
    m_UI->setupUi(this);
    setFixedSize(size());
    setWindowTitle(QString("TagSelector"));
}

void TagMainWindow::Initialize(Model::ITagViewModel* viewModel)
{
    m_spViewModel.reset(viewModel);
    UpdateView();
    m_spViewModel->addListener([this](){
        UpdateView();
    });
}

void TagMainWindow::UpdateView()
{
    m_UI->AddressInput->setText(QString::fromStdString(m_spViewModel->Path()));
    for (auto item : m_spViewModel->Items()) {
        m_UI->ItemsList->addItem(new QListWidgetItem(QString::fromStdString(item->Name()), m_UI->ItemsList));
    }
}

}
