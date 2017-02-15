#include <stdio.h>

#include <QApplication>
#include <QDirModel>
#include <QSplitter>
#include <QTreeView>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QSplitter *splitter = new QSplitter;
    QDirModel *model = new QDirModel;

    QTreeView *tree = new QTreeView(splitter);
    tree->setModel(model);
    tree->setRootIndex(model->index("c:\\"));

    QString a("cate");
    splitter->setWindowTitle(a);
    splitter->show();
    return app.exec();
}
