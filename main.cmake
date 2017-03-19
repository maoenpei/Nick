
message("PROJ_DEPLOY:${PROJ_DEPLOY}")
include_directories(
    ${QT_INCLUDES}
)

set(SOURCES
    main.cpp
)

add_executable(MainTest ${SOURCES})
AddQtDependencies(MainTest)

DeployTarget(MainTest)
