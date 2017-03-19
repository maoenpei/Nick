
if (${CMAKE_VERSION} VERSION_GREATER 3.0)
    # Disable this policy. Ideally LOCATION property can be replaced by either using the
    # target name directly or by the new generator expression. Unfortunately generator
    # expression doesn't support OUTPUT
    cmake_policy(SET CMP0026 OLD)
endif()

# generate unique name from path
macro(GenerateRef REF_NAME FILE_PATH)
    set(RefList ${REF_NAME_FILE_PATH_LIST})
    if(NOT RefList)
        set(RefList "")
    endif()
    list(LENGTH RefList ListLength)
    math(EXPR LengthSub "${ListLength}-1")
    if (${ListLength} GREATER 0)
        foreach(RefIndex RANGE ${LengthSub})
            list(GET RefList ${RefIndex} RefPath)
            if (${RefPath} EQUAL ${FILE_PATH})
                set(FoundIndex ${RefIndex})
                break()
            endif()
        endforeach()
    endif()
    if (NOT FoundIndex)
        set(FoundIndex ${ListLength})
        list(APPEND RefList ${FILE_PATH})
        set(REF_NAME_FILE_PATH_LIST "${RefList}" CACHE STRING "" FORCE)
    endif()
    set(${REF_NAME} "REF_NAME_${FoundIndex}")
    #string(REGEX REPLACE "[/\\: ()]" "_" ${REF_NAME} ${FILE_PATH})
endmacro()

# have to define PROJ_DEPLOY BUILD_TARGET
function(DeployTargetToTarget TARGET_NAME OWNER_TARGET)
    get_target_property(TargetPath ${TARGET_NAME} LOCATION)
    get_filename_component(TargetName ${TargetPath} NAME)

    set(DestinationPath ${PROJ_DEPLOY}/${TargetName})
    add_custom_command(
        OUTPUT ${DestinationPath}
        COMMAND ${CMAKE_COMMAND} -E copy ${TargetPath} ${DestinationPath}
        DEPENDS ${TARGET_NAME}
    )

    set(DeployFileTarget "DEPLOY_${OWNER_TARGET}_${TARGET_NAME}")
    add_custom_target(${DeployFileTarget} DEPENDS ${DestinationPath})

    add_dependencies(${OWNER_TARGET} ${DeployFileTarget})
endfunction()

function(DeployTarget TARGET_NAME)
	DeployTargetToTarget(${TARGET_NAME} ${BUILD_TARGET})
endfunction()

function(DeployFileToTarget FILE_PATH OWNER_TARGET)
    get_filename_component(TargetName ${FILE_PATH} NAME)

    set(DestinationPath ${PROJ_DEPLOY}/${TargetName})
    add_custom_command(
        OUTPUT ${DestinationPath}
        COMMAND ${CMAKE_COMMAND} -E copy ${FILE_PATH} ${DestinationPath}
        DEPENDS ${FILE_PATH}
    )

    GenerateRef(FileRef ${FILE_PATH})
    set(DeployFileTarget "DEPLOY_${OWNER_TARGET}_${FileRef}")
    add_custom_target(${DeployFileTarget} DEPENDS ${DestinationPath})

    add_dependencies(${OWNER_TARGET} ${DeployFileTarget})
endfunction()

function(DeployFile FILE_PATH)
	DeployFileToTarget(${FILE_PATH} ${BUILD_TARGET})
endfunction()
