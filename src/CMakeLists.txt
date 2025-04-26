# 主程序配置
add_executable(${PROJECT_NAME} main.cc)

# 增强版模块自动发现函数
function(auto_discover_modules)
    file(GLOB children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)
    foreach(child ${children})
        set(full_path ${CMAKE_CURRENT_SOURCE_DIR}/${child})
        if(IS_DIRECTORY ${full_path} AND NOT child STREQUAL "XTool")
            # 递归收集所有源文件
            file(GLOB_RECURSE SRC_FILES 
                "${full_path}/source/*.c"
                "${full_path}/source/*.cpp"
                "${full_path}/*.c"      # 处理直接放在模块根目录的源文件
                "${full_path}/*.cpp"
            )
            
            # 收集所有头文件
            file(GLOB_RECURSE INC_FILES
                "${full_path}/include/*.h"
                "${full_path}/include/*.hpp"
                "${full_path}/*.h"       # 处理直接放在模块根目录的头文件
                "${full_path}/*.hpp"
            )
            
            # 仅当存在源文件或头文件时创建目标
            if(SRC_FILES OR INC_FILES)
                # 创建库类型自动判断
                if(SRC_FILES)
                    add_library(${child} ${SRC_FILES} ${INC_FILES})
                else()
                    # 纯头文件模块创建接口库
                    add_library(${child} INTERFACE)
                    target_sources(${child} INTERFACE ${INC_FILES})
                endif()
                
                # 包含路径设置
                if(INC_FILES)
                    target_include_directories(${child} PUBLIC
                        ${full_path}/include
                        ${full_path}
                    )
                endif()
                
                # 自动链接到主程序
                target_link_libraries(${PROJECT_NAME} PRIVATE ${child})
            else()
                message(STATUS "跳过空目录: ${child}")
            endif()
        endif()
    endforeach()
endfunction()

# 处理XTool特殊目录
if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/XTool)
    add_subdirectory(XTool)
endif()

# 执行模块发现
auto_discover_modules()