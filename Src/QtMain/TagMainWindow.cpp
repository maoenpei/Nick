

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

    Model::ITagViewItem* Item()
    {
        return m_item;
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
    m_spViewModel->addItemListener([this](){
        UpdateView();
    });
    connect(m_UI->ItemsList, &QListWidget::itemDoubleClicked, this, [](QListWidgetItem *widgetItem) {
        EnterWidgetItem* enterItem = static_cast<EnterWidgetItem*>(widgetItem);
        enterItem->Enter();
    });
    connect(m_UI->ItemsList, &QListWidget::itemSelectionChanged, this, [this]() {
        SyncSelection();
    });
    connect(m_UI->AddressInput, &QLineEdit::textChanged, this, [this](const QString& text) {
        m_spViewModel->setPath(text.toLocal8Bit().constData());
    });
    connect(m_UI->upButton, &QPushButton::clicked, this, [this]() {
        auto item = m_spViewModel->Parent();
        if (item) {
            item->Enter();
        }
    });
    connect(m_UI->TagsInput, &QLineEdit::returnPressed, m_UI->addButton, &QPushButton::click);
    connect(m_UI->addButton, &QPushButton::clicked, this, [this]() {
        m_spViewModel->AddTag(m_UI->TagsInput->text().toLocal8Bit().constData());
        UpdateTags();
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

void TagMainWindow::UpdateTags()
{
    std::vector<std::string> tags = m_spViewModel->CommonTags();
    m_UI->CurrentTagsList->clear();
    for (auto& tag : tags) {
        m_UI->CurrentTagsList->addItem(new QListWidgetItem(QString::fromLocal8Bit(tag.c_str())));
    }
}

void TagMainWindow::SyncSelection()
{
    auto widgetItems = m_UI->ItemsList->selectedItems();
    std::vector<Model::ITagViewItem*> items;
    for (auto widgetItem : widgetItems) {
        EnterWidgetItem* enterItem = static_cast<EnterWidgetItem*>(widgetItem);
        items.push_back(enterItem->Item());
    }
    m_spViewModel->Select(items);
    UpdateTags();
}

}
