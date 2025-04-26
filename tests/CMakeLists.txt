# 测试框架自动引导
include(CTest)
enable_testing()

# Google Test自动集成
if(NOT TARGET GTest::GTest)
    message(STATUS "正在下载并构建Google Test")
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
    )
    FetchContent_MakeAvailable(googletest)
endif()

# 递归发现测试用例
file(GLOB_RECURSE TEST_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
)

# 动态生成测试目标
foreach(test_src IN LISTS TEST_SOURCES)
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name}_test ${test_src})
    target_link_libraries(${test_name}_test
        PRIVATE
        ${PROJECT_NAME}
        GTest::GTest
        GTest::Main
    )
    add_test(NAME ${test_name}_test 
        COMMAND ${test_name}_test
    )
endforeach()

# 覆盖率配置（当启用时）
if(ENABLE_COVERAGE)
    target_compile_options(${PROJECT_NAME} 
        PRIVATE --coverage -fprofile-arcs -ftest-coverage
    )
    target_link_libraries(${PROJECT_NAME} 
        PRIVATE --coverage
    )
endif()