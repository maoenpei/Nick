
#include <QApplication>

#include <memory>

#include "TagMainWindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    std::shared_ptr<View::TagMainWindow> mainWin = std::make_shared<View::TagMainWindow>();
    mainWin->Initialize();
    mainWin->show();
    return app.exec();
}
