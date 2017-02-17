
#include <QApplication>
#include <QDirModel>
#include <QSplitter>
#include <QTreeView>
#include <QMainWindow>

#include <MainWindow.ui.h>

#include <memory>

class TagMainWindow : public QMainWindow
{
    Ui::MainWindow* m_UI;
public:
    TagMainWindow()
        : m_UI(new Ui::MainWindow())
    {
        m_UI->setupUi(this);
        setFixedSize(size());
    }
};

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    std::shared_ptr<TagMainWindow> mainWin = std::make_shared<TagMainWindow>();
    mainWin->show();
    return app.exec();
}
