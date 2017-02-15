
include_directories(
    ${QT_INCLUDES}
)

AddQtExecutable(QtMain QtMain.cpp)
AddQtDependencies(QtMain)

DeployTarget(QtMain)
