
if (${CMAKE_VERSION} VERSION_GREATER 3.0)
    # Disable this policy. Ideally LOCATION property can be replaced by either using the
    # target name directly or by the new generator expression. Unfortunately generator
    # expression doesn't support OUTPUT
    cmake_policy(SET CMP0026 OLD)
endif()

# have to define BUILT_DEPLOY BUILD_TARGET
function(DeployTargetToTarget TARGET_NAME OWNER_TARGET)
    get_target_property(TargetPath ${TARGET_NAME} LOCATION)
    get_filename_component(TargetName ${TargetPath} NAME)

    set(DestinationPath ${BUILT_DEPLOY}/${TargetName})
    add_custom_command(
        OUTPUT ${DestinationPath}
        COMMAND ${CMAKE_COMMAND} -E copy ${TargetPath} ${DestinationPath}
        DEPENDS ${TARGET_NAME}
    )

    set(DeployFileTarget "DEPLOY_${TARGET_NAME}")
    add_custom_target(${DeployFileTarget} DEPENDS ${DestinationPath})

    add_dependencies(${OWNER_TARGET} ${DeployFileTarget})
endfunction()

function(DeployTarget TARGET_NAME)
	DeployTargetToTarget(${TARGET_NAME} ${BUILD_TARGET})
endfunction()

function(DeployFileToTarget FILE_PATH OWNER_TARGET)
    get_filename_component(TargetName ${FILE_PATH} NAME)

    set(DestinationPath ${BUILT_DEPLOY}/${TargetName})
    add_custom_command(
        OUTPUT ${DestinationPath}
        COMMAND ${CMAKE_COMMAND} -E copy ${FILE_PATH} ${DestinationPath}
        DEPENDS ${FILE_PATH}
    )

    string(REGEX REPLACE "[/\\: ()]" "_" FileRef ${FILE_PATH})
    set(DeployFileTarget "DEPLOY_${FileRef}")
    add_custom_target(${DeployFileTarget} DEPENDS ${DestinationPath})

    add_dependencies(${OWNER_TARGET} ${DeployFileTarget})
endfunction()

function(DeployFile FILE_PATH)
	DeployFileToTarget(${FILE_PATH} ${BUILD_TARGET})
endfunction()
