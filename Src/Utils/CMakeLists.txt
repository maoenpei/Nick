
include_directories(
    ${BOOST_INCLUDES}
)

set(Utils_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}" CACHE STRING "" FORCE)

set(SOURCES
    Filesystem.cpp
)

add_library(Utils STATIC ${SOURCES})

AddBoostLibraries(Utils "filesystem;system")

set(Utils_STATIC Utils CACHE STRING "" FORCE)
