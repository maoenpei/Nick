
#include <QApplication>

#include <memory>

#include "TagMainWindow.h"
#include <TagDirViewModel.h>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    std::shared_ptr<View::TagMainWindow> mainWin = std::make_shared<View::TagMainWindow>();
    mainWin->Initialize(new Model::TagDirViewModel("D:/"));
    mainWin->show();
    return app.exec();
}
