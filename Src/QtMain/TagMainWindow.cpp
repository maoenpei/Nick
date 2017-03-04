

#include "TagMainWindow.h"

#include <ITagViewModel.h>

namespace View {

class EnterWidgetItem : public QListWidgetItem
{
    Model::ITagViewItem* m_data;
public:
    explicit EnterWidgetItem(Model::ITagViewItem* data, QListWidget *view = Q_NULLPTR)
        : QListWidgetItem(QString::fromStdString(data->Name()), view)
        , m_data(data)
    {}

    void Enter()
    {
        m_data->Enter();
    }
};

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
    connect(m_UI->ItemsList, &QListWidget::itemDoubleClicked, [](QListWidgetItem *item) {
        EnterWidgetItem* enterItem = static_cast<EnterWidgetItem*>(item);
        enterItem->Enter();
    });
}

void TagMainWindow::UpdateView()
{
    m_UI->AddressInput->setText(QString::fromStdString(m_spViewModel->Path()));
    m_UI->ItemsList->clear();
    for (auto item : m_spViewModel->Items()) {
        m_UI->ItemsList->addItem(new EnterWidgetItem(item, m_UI->ItemsList));
    }
}

}
