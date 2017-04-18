
include_directories(
    ${QT_INCLUDES}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${TagManager_INCLUDE}
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

target_link_libraries(QtMain
    ${TagManager_STATIC}
)

DeployTarget(QtMain)
