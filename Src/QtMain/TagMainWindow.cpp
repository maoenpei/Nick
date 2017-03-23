

#include "TagMainWindow.h"

#include <ITagViewModel.h>

namespace View {

class EnterWidgetItem : public QListWidgetItem
{
    Model::ITagViewItem* m_item;
public:
    explicit EnterWidgetItem(Model::ITagViewItem* item, QListWidget *view = Q_NULLPTR)
        : QListWidgetItem(QString::fromLocal8Bit(item->Name().c_str()), view)
        , m_item(item)
    {}

    void Enter()
    {
        m_item->Enter();
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
    connect(m_UI->ItemsList, &QListWidget::itemDoubleClicked, this, [](QListWidgetItem *item) {
        EnterWidgetItem* enterItem = static_cast<EnterWidgetItem*>(item);
        enterItem->Enter();
    });
    connect(m_UI->AddressInput, &QLineEdit::textChanged, this, [this](const QString& text) {
        m_spViewModel->setPath(text.toStdString());
    });
    connect(m_UI->upButton, &QPushButton::clicked, this, [this]() {
        auto item = m_spViewModel->Parent();
        if (item) {
            item->Enter();
        }
    });
}

void TagMainWindow::UpdateView()
{
    int cursorPos = m_UI->AddressInput->cursorPosition();
    m_UI->AddressInput->setText(QString::fromLocal8Bit(m_spViewModel->Path().c_str()));
    m_UI->AddressInput->setCursorPosition(cursorPos);

    m_UI->ItemsList->clear();
    for (auto item : m_spViewModel->Children()) {
        m_UI->ItemsList->addItem(new EnterWidgetItem(item, m_UI->ItemsList));
    }
    m_UI->upButton->setEnabled(m_spViewModel->Parent() != nullptr);
}

}
