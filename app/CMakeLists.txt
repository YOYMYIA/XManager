execute_process(COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/ssl.p12 ${EXECUTABLE_OUTPUT_PATH}/)

aux_source_directory(. TEST_SRC_LIST)
foreach(TEST_SRC ${TEST_SRC_LIST})
    STRING(REGEX REPLACE "^\\./|\\.c[a-zA-Z0-9_]*$" "" TEST_EXE_NAME ${TEST_SRC})
    message(STATUS "添加测试程序:${TEST_EXE_NAME}")
    add_executable(${TEST_EXE_NAME} ${TEST_SRC})

    if(ANDROID OR IOS OR WIN32)
        target_link_libraries(${TEST_EXE_NAME} ${PROJECT_NAME}_static ${LINK_LIB_LIST})
    else()
        target_link_libraries(${TEST_EXE_NAME} ${PROJECT_NAME}_shared ${LINK_LIB_LIST} pthread)
    endif()

endforeach(TEST_SRC ${TEST_SRC_LIST})