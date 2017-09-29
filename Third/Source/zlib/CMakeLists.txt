
set(SOURCES
    zlib/adler32.c
    zlib/crc32.c
    zlib/deflate.c
    zlib/inffast.c
    zlib/inflate.c
    zlib/inftrees.c
    zlib/trees.c
    zlib/zutil.c
)

add_library(Zlib STATIC ${SOURCES})

set(ZLIB_STATIC Zlib CACHE STRING "" FORCE)
set(ZLIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "" FORCE)
