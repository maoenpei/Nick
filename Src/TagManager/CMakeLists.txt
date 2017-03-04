
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Utils_INCLUDE}
)

set(SOURCES
    TagDirViewModel.cpp
)

add_library(TagManager STATIC ${SOURCES})

target_link_libraries(TagManager ${Utils_STATIC})

target_include_directories(TagManager PUBLIC
    ${Utils_INCLUDE}
)

set(TagManager_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}" CACHE STRING "" FORCE)
set(TagManager_STATIC TagManager CACHE STRING "" FORCE)
