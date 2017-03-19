

set(BOOST_LIB_SUFFIX "" CACHE STRING "" FORCE)
if (${PROJ_BUILD_TYPE} STREQUAL "Debug")
    set(BOOST_LIB_SUFFIX "-gd" CACHE STRING "" FORCE)
endif()

macro(BoostLibName NAME LIB)
    set(${NAME} "libboost_${LIB}-vc140-mt${BOOST_LIB_SUFFIX}-1_63.lib")
endmacro()

set(BOOST_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/include" CACHE STRING "" FORCE)

set(BOOST_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib" CACHE STRING "" FORCE)

function(AddBoostLibraries TARGET LIBRARIES)
    foreach(VAR ${LIBRARIES})
        BoostLibName(LIB_NAME ${VAR})
        target_link_libraries(${TARGET}
            "${BOOST_LIB_DIR}/${LIB_NAME}")
    endforeach()
endfunction()
