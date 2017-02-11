
message("BUILT_DEPLOY ${BUILT_DEPLOY}")
include_directories(
    ${QT_INCLUDE_DIR}
)

set(SOURCES
    main.cpp
)

add_executable(MainTest ${SOURCES})
AddQtDependencies(MainTest)

DeployTarget(MainTest)
