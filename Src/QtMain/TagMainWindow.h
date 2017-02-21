#pragma once

#include <QMainWindow>
#include <MainWindow.ui.h>

namespace View{

class TagMainWindow : public QMainWindow
{
    Ui::MainWindow* m_UI;
public:
    TagMainWindow();

    void Initialize();
};

}
