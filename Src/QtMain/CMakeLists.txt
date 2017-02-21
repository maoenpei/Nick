
include_directories(
    ${QT_INCLUDES}
    ${CMAKE_CURRENT_BINARY_DIR}
)

set(SOURCES
    QtMain.cpp
    TagMainWindow.cpp
)

set(UI_FILES
    MainWindow.ui)

AddQtExecutable(QtMain ${SOURCES})
AddQtDependencies(QtMain)
AddQtUiForTarget(QtMain ${UI_FILES})

DeployTarget(QtMain)
