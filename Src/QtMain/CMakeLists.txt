
include_directories(
    ${QT_INCLUDES}
    ${CMAKE_CURRENT_BINARY_DIR}
)

AddQtUiForTarget(QtMain_UI OUT_FILES MainWindow.ui)

include_directories(
    ${OUT_FILES}
)

AddQtExecutable(QtMain QtMain.cpp)
AddQtDependencies(QtMain)

add_dependencies(QtMain QtMain_UI)

DeployTarget(QtMain)
