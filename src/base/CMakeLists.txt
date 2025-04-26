# src/base/CMakeLists.txt
# 自动配置基础模块
file(GLOB_RECURSE BASE_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
)

file(GLOB_RECURSE BASE_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

add_library(base ${BASE_SOURCES} ${BASE_HEADERS})

target_include_directories(base PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 版本信息
set_target_properties(base PROPERTIES
    VERSION 1.0.0
    SOVERSION 1
)