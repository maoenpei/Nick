

#include "TagMainWindow.h"

namespace View {

TagMainWindow::TagMainWindow()
    : m_UI(new Ui::MainWindow())
{
    m_UI->setupUi(this);
    setFixedSize(size());
    setWindowTitle(QString("TagSelector"));
}

void TagMainWindow::Initialize()
{
    
}

}
