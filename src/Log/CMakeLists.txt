file(GLOB_RECURSE LOCAL_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
)

file(GLOB_RECURSE LOCAL_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

add_library(Log ${LOCAL_SOURCES} ${LOCAL_HEADERS})

target_include_directories(Log PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 版本信息
set_target_properties(Log PROPERTIES
    VERSION 1.0.0
    SOVERSION 1
)